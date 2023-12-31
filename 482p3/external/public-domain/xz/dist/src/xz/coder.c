///////////////////////////////////////////////////////////////////////////////
//
/// \file       coder.c
/// \brief      Compresses or uncompresses a file
//
//  Author:     Lasse Collin
//
//  This file has been put into the public domain.
//  You can do whatever you want with this file.
//
///////////////////////////////////////////////////////////////////////////////

#include "private.h"


/// Return value type for coder_init().
enum coder_init_ret {
	CODER_INIT_NORMAL,
	CODER_INIT_PASSTHRU,
	CODER_INIT_ERROR,
};


enum operation_mode opt_mode = MODE_COMPRESS;
enum format_type opt_format = FORMAT_AUTO;
bool opt_auto_adjust = true;


/// Stream used to communicate with liblzma
static lzma_stream strm = LZMA_STREAM_INIT;

/// Filters needed for all encoding all formats, and also decoding in raw data
static lzma_filter filters[LZMA_FILTERS_MAX + 1];

/// Input and output buffers
static io_buf in_buf;
static io_buf out_buf;

/// Number of filters. Zero indicates that we are using a preset.
static size_t filters_count = 0;

/// Number of the preset (0-9)
static size_t preset_number = 6;

/// If a preset is used (no custom filter chain) and preset_extreme is true,
/// a significantly slower compression is used to achieve slightly better
/// compression ratio.
static bool preset_extreme = false;

/// Integrity check type
static lzma_check check;

/// This becomes false if the --check=CHECK option is used.
static bool check_default = true;


extern void
coder_set_check(lzma_check new_check)
{
	check = new_check;
	check_default = false;
	return;
}


extern void
coder_set_preset(size_t new_preset)
{
	preset_number = new_preset;

	// Setting a preset makes us forget a possibly defined custom
	// filter chain.
	while (filters_count > 0) {
		--filters_count;
		free(filters[filters_count].options);
		filters[filters_count].options = NULL;
	}

	return;
}


extern void
coder_set_extreme(void)
{
	preset_extreme = true;
	return;
}


extern void
coder_add_filter(lzma_vli id, void *options)
{
	if (filters_count == LZMA_FILTERS_MAX)
		message_fatal(_("Maximum number of filters is four"));

	filters[filters_count].id = id;
	filters[filters_count].options = options;
	++filters_count;

	return;
}


static void lzma_attribute((noreturn))
memlimit_too_small(uint64_t memory_usage)
{
	message(V_ERROR, _("Memory usage limit is too low for the given "
			"filter setup."));
	message_mem_needed(V_ERROR, memory_usage);
	tuklib_exit(E_ERROR, E_ERROR, false);
}


extern void
coder_set_compression_settings(void)
{
	// Options for LZMA1 or LZMA2 in case we are using a preset.
	static lzma_options_lzma opt_lzma;

	if (filters_count == 0) {
		// We are using a preset. This is not a good idea in raw mode
		// except when playing around with things. Different versions
		// of this software may use different options in presets, and
		// thus make uncompressing the raw data difficult.
		if (opt_format == FORMAT_RAW) {
			// The message is shown only if warnings are allowed
			// but the exit status isn't changed.
			message(V_WARNING, _("Using a preset in raw mode "
					"is discouraged."));
			message(V_WARNING, _("The exact options of the "
					"presets may vary between software "
					"versions."));
		}

		// Get the preset for LZMA1 or LZMA2.
		if (preset_extreme)
			preset_number |= LZMA_PRESET_EXTREME;

		if (lzma_lzma_preset(&opt_lzma, preset_number))
			message_bug();

		// Use LZMA2 except with --format=lzma we use LZMA1.
		filters[0].id = opt_format == FORMAT_LZMA
				? LZMA_FILTER_LZMA1 : LZMA_FILTER_LZMA2;
		filters[0].options = &opt_lzma;
		filters_count = 1;
	}

	// Terminate the filter options array.
	filters[filters_count].id = LZMA_VLI_UNKNOWN;

	// If we are using the .lzma format, allow exactly one filter
	// which has to be LZMA1.
	if (opt_format == FORMAT_LZMA && (filters_count != 1
			|| filters[0].id != LZMA_FILTER_LZMA1))
		message_fatal(_("The .lzma format supports only "
				"the LZMA1 filter"));

	// If we are using the .xz format, make sure that there is no LZMA1
	// filter to prevent LZMA_PROG_ERROR.
	if (opt_format == FORMAT_XZ)
		for (size_t i = 0; i < filters_count; ++i)
			if (filters[i].id == LZMA_FILTER_LZMA1)
				message_fatal(_("LZMA1 cannot be used "
						"with the .xz format"));

	// Print the selected filter chain.
	message_filters_show(V_DEBUG, filters);

	// If using --format=raw, we can be decoding. The memusage function
	// also validates the filter chain and the options used for the
	// filters.
	const uint64_t memory_limit = hardware_memlimit_get(opt_mode);
	uint64_t memory_usage;
	if (opt_mode == MODE_COMPRESS)
		memory_usage = lzma_raw_encoder_memusage(filters);
	else
		memory_usage = lzma_raw_decoder_memusage(filters);

	if (memory_usage == UINT64_MAX)
		message_fatal(_("Unsupported filter chain or filter options"));

	// Print memory usage info before possible dictionary
	// size auto-adjusting.
	message_mem_needed(V_DEBUG, memory_usage);
	if (opt_mode == MODE_COMPRESS) {
		const uint64_t decmem = lzma_raw_decoder_memusage(filters);
		if (decmem != UINT64_MAX)
			message(V_DEBUG, _("Decompression will need "
					"%s MiB of memory."), uint64_to_str(
						round_up_to_mib(decmem), 0));
	}

	if (memory_usage > memory_limit) {
		// If --no-auto-adjust was used or we didn't find LZMA1 or
		// LZMA2 as the last filter, give an error immediately.
		// --format=raw implies --no-auto-adjust.
		if (!opt_auto_adjust || opt_format == FORMAT_RAW)
			memlimit_too_small(memory_usage);

		assert(opt_mode == MODE_COMPRESS);

		// Look for the last filter if it is LZMA2 or LZMA1, so
		// we can make it use less RAM. With other filters we don't
		// know what to do.
		size_t i = 0;
		while (filters[i].id != LZMA_FILTER_LZMA2
				&& filters[i].id != LZMA_FILTER_LZMA1) {
			if (filters[i].id == LZMA_VLI_UNKNOWN)
				memlimit_too_small(memory_usage);

			++i;
		}

		// Decrease the dictionary size until we meet the memory
		// usage limit. First round down to full mebibytes.
		lzma_options_lzma *opt = filters[i].options;
		const uint32_t orig_dict_size = opt->dict_size;
		opt->dict_size &= ~((UINT32_C(1) << 20) - 1);
		while (true) {
			// If it is below 1 MiB, auto-adjusting failed. We
			// could be more sophisticated and scale it down even
			// more, but let's see if many complain about this
			// version.
			//
			// FIXME: Displays the scaled memory usage instead
			// of the original.
			if (opt->dict_size < (UINT32_C(1) << 20))
				memlimit_too_small(memory_usage);

			memory_usage = lzma_raw_encoder_memusage(filters);
			if (memory_usage == UINT64_MAX)
				message_bug();

			// Accept it if it is low enough.
			if (memory_usage <= memory_limit)
				break;

			// Otherwise 1 MiB down and try again. I hope this
			// isn't too slow method for cases where the original
			// dict_size is very big.
			opt->dict_size -= UINT32_C(1) << 20;
		}

		// Tell the user that we decreased the dictionary size.
		message(V_WARNING, _("Adjusted LZMA%c dictionary size "
				"from %s MiB to %s MiB to not exceed "
				"the memory usage limit of %s MiB"),
				filters[i].id == LZMA_FILTER_LZMA2
					? '2' : '1',
				uint64_to_str(orig_dict_size >> 20, 0),
				uint64_to_str(opt->dict_size >> 20, 1),
				uint64_to_str(round_up_to_mib(
					memory_limit), 2));
	}

/*
	// Limit the number of worker threads so that memory usage
	// limit isn't exceeded.
	assert(memory_usage > 0);
	size_t thread_limit = memory_limit / memory_usage;
	if (thread_limit == 0)
		thread_limit = 1;

	if (opt_threads > thread_limit)
		opt_threads = thread_limit;
*/

	if (check_default) {
		// The default check type is CRC64, but fallback to CRC32
		// if CRC64 isn't supported by the copy of liblzma we are
		// using. CRC32 is always supported.
		check = LZMA_CHECK_CRC64;
		if (!lzma_check_is_supported(check))
			check = LZMA_CHECK_CRC32;
	}

	return;
}


/// Return true if the data in in_buf seems to be in the .xz format.
static bool
is_format_xz(void)
{
	return strm.avail_in >= 6 && memcmp(in_buf.u8, "\3757zXZ", 6) == 0;
}


/// Return true if the data in in_buf seems to be in the .lzma format.
static bool
is_format_lzma(void)
{
	// The .lzma header is 13 bytes.
	if (strm.avail_in < 13)
		return false;

	// Decode the LZMA1 properties.
	lzma_filter filter = { .id = LZMA_FILTER_LZMA1 };
	if (lzma_properties_decode(&filter, NULL, in_buf.u8, 5) != LZMA_OK)
		return false;

	// A hack to ditch tons of false positives: We allow only dictionary
	// sizes that are 2^n or 2^n + 2^(n-1) or UINT32_MAX. LZMA_Alone
	// created only files with 2^n, but accepts any dictionary size.
	// If someone complains, this will be reconsidered.
	lzma_options_lzma *opt = filter.options;
	const uint32_t dict_size = opt->dict_size;
	free(opt);

	if (dict_size != UINT32_MAX) {
		uint32_t d = dict_size - 1;
		d |= d >> 2;
		d |= d >> 3;
		d |= d >> 4;
		d |= d >> 8;
		d |= d >> 16;
		++d;
		if (d != dict_size || dict_size == 0)
			return false;
	}

	// Another hack to ditch false positives: Assume that if the
	// uncompressed size is known, it must be less than 256 GiB.
	// Again, if someone complains, this will be reconsidered.
	uint64_t uncompressed_size = 0;
	for (size_t i = 0; i < 8; ++i)
		uncompressed_size |= (uint64_t)(in_buf.u8[5 + i]) << (i * 8);

	if (uncompressed_size != UINT64_MAX
			&& uncompressed_size > (UINT64_C(1) << 38))
		return false;

	return true;
}


/// Detect the input file type (for now, this done only when decompressing),
/// and initialize an appropriate coder. Return value indicates if a normal
/// liblzma-based coder was initialized (CODER_INIT_NORMAL), if passthru
/// mode should be used (CODER_INIT_PASSTHRU), or if an error occurred
/// (CODER_INIT_ERROR).
static enum coder_init_ret
coder_init(file_pair *pair)
{
	lzma_ret ret = LZMA_PROG_ERROR;

	if (opt_mode == MODE_COMPRESS) {
		switch (opt_format) {
		case FORMAT_AUTO:
			// args.c ensures this.
			assert(0);
			break;

		case FORMAT_XZ:
			ret = lzma_stream_encoder(&strm, filters, check);
			break;

		case FORMAT_LZMA:
			ret = lzma_alone_encoder(&strm, filters[0].options);
			break;

		case FORMAT_RAW:
			ret = lzma_raw_encoder(&strm, filters);
			break;
		}
	} else {
		const uint32_t flags = LZMA_TELL_UNSUPPORTED_CHECK
				| LZMA_CONCATENATED;

		// We abuse FORMAT_AUTO to indicate unknown file format,
		// for which we may consider passthru mode.
		enum format_type init_format = FORMAT_AUTO;

		switch (opt_format) {
		case FORMAT_AUTO:
			if (is_format_xz())
				init_format = FORMAT_XZ;
			else if (is_format_lzma())
				init_format = FORMAT_LZMA;
			break;

		case FORMAT_XZ:
			if (is_format_xz())
				init_format = FORMAT_XZ;
			break;

		case FORMAT_LZMA:
			if (is_format_lzma())
				init_format = FORMAT_LZMA;
			break;

		case FORMAT_RAW:
			init_format = FORMAT_RAW;
			break;
		}

		switch (init_format) {
		case FORMAT_AUTO:
			// Uknown file format. If --decompress --stdout
			// --force have been given, then we copy the input
			// as is to stdout. Checking for MODE_DECOMPRESS
			// is needed, because we don't want to do use
			// passthru mode with --test.
			if (opt_mode == MODE_DECOMPRESS
					&& opt_stdout && opt_force)
				return CODER_INIT_PASSTHRU;

			ret = LZMA_FORMAT_ERROR;
			break;

		case FORMAT_XZ:
			ret = lzma_stream_decoder(&strm,
					hardware_memlimit_get(
						MODE_DECOMPRESS), flags);
			break;

		case FORMAT_LZMA:
			ret = lzma_alone_decoder(&strm,
					hardware_memlimit_get(
						MODE_DECOMPRESS));
			break;

		case FORMAT_RAW:
			// Memory usage has already been checked in
			// coder_set_compression_settings().
			ret = lzma_raw_decoder(&strm, filters);
			break;
		}

		// Try to decode the headers. This will catch too low
		// memory usage limit in case it happens in the first
		// Block of the first Stream, which is where it very
		// probably will happen if it is going to happen.
		if (ret == LZMA_OK && init_format != FORMAT_RAW) {
			strm.next_out = NULL;
			strm.avail_out = 0;
			ret = lzma_code(&strm, LZMA_RUN);
		}
	}

	if (ret != LZMA_OK) {
		message_error("%s: %s", pair->src_name, message_strm(ret));
		if (ret == LZMA_MEMLIMIT_ERROR)
			message_mem_needed(V_ERROR, lzma_memusage(&strm));

		return CODER_INIT_ERROR;
	}

	return CODER_INIT_NORMAL;
}


/// Compress or decompress using liblzma.
static bool
coder_normal(file_pair *pair)
{
	// Encoder needs to know when we have given all the input to it.
	// The decoders need to know it too when we are using
	// LZMA_CONCATENATED. We need to check for src_eof here, because
	// the first input chunk has been already read, and that may
	// have been the only chunk we will read.
	lzma_action action = pair->src_eof ? LZMA_FINISH : LZMA_RUN;

	lzma_ret ret;

	// Assume that something goes wrong.
	bool success = false;

	strm.next_out = out_buf.u8;
	strm.avail_out = IO_BUFFER_SIZE;

	while (!user_abort) {
		// Fill the input buffer if it is empty and we haven't reached
		// end of file yet.
		if (strm.avail_in == 0 && !pair->src_eof) {
			strm.next_in = in_buf.u8;
			strm.avail_in = io_read(
					pair, &in_buf, IO_BUFFER_SIZE);

			if (strm.avail_in == SIZE_MAX)
				break;

			if (pair->src_eof)
				action = LZMA_FINISH;
		}

		// Let liblzma do the actual work.
		ret = lzma_code(&strm, action);

		// Write out if the output buffer became full.
		if (strm.avail_out == 0) {
			if (opt_mode != MODE_TEST && io_write(pair, &out_buf,
					IO_BUFFER_SIZE - strm.avail_out))
				break;

			strm.next_out = out_buf.u8;
			strm.avail_out = IO_BUFFER_SIZE;
		}

		if (ret != LZMA_OK) {
			// Determine if the return value indicates that we
			// won't continue coding.
			const bool stop = ret != LZMA_NO_CHECK
					&& ret != LZMA_UNSUPPORTED_CHECK;

			if (stop) {
				// Write the remaining bytes even if something
				// went wrong, because that way the user gets
				// as much data as possible, which can be good
				// when trying to get at least some useful
				// data out of damaged files.
				if (opt_mode != MODE_TEST && io_write(pair,
						&out_buf, IO_BUFFER_SIZE
							- strm.avail_out))
					break;
			}

			if (ret == LZMA_STREAM_END) {
				// Check that there is no trailing garbage.
				// This is needed for LZMA_Alone and raw
				// streams.
				if (strm.avail_in == 0 && !pair->src_eof) {
					// Try reading one more byte.
					// Hopefully we don't get any more
					// input, and thus pair->src_eof
					// becomes true.
					strm.avail_in = io_read(
							pair, &in_buf, 1);
					if (strm.avail_in == SIZE_MAX)
						break;

					assert(strm.avail_in == 0
							|| strm.avail_in == 1);
				}

				if (strm.avail_in == 0) {
					assert(pair->src_eof);
					success = true;
					break;
				}

				// We hadn't reached the end of the file.
				ret = LZMA_DATA_ERROR;
				assert(stop);
			}

			// If we get here and stop is true, something went
			// wrong and we print an error. Otherwise it's just
			// a warning and coding can continue.
			if (stop) {
				message_error("%s: %s", pair->src_name,
						message_strm(ret));
			} else {
				message_warning("%s: %s", pair->src_name,
						message_strm(ret));

				// When compressing, all possible errors set
				// stop to true.
				assert(opt_mode != MODE_COMPRESS);
			}

			if (ret == LZMA_MEMLIMIT_ERROR) {
				// Display how much memory it would have
				// actually needed.
				message_mem_needed(V_ERROR,
						lzma_memusage(&strm));
			}

			if (stop)
				break;
		}

		// Show progress information under certain conditions.
		message_progress_update();
	}

	return success;
}


/// Copy from input file to output file without processing the data in any
/// way. This is used only when trying to decompress unrecognized files
/// with --decompress --stdout --force, so the output is always stdout.
static bool
coder_passthru(file_pair *pair)
{
	while (strm.avail_in != 0) {
		if (user_abort)
			return false;

		if (io_write(pair, &in_buf, strm.avail_in))
			return false;

		strm.total_in += strm.avail_in;
		strm.total_out = strm.total_in;
		message_progress_update();

		strm.avail_in = io_read(pair, &in_buf, IO_BUFFER_SIZE);
		if (strm.avail_in == SIZE_MAX)
			return false;
	}

	return true;
}


extern void
coder_run(const char *filename)
{
	// Set and possibly print the filename for the progress message.
	message_filename(filename);

	// Try to open the input file.
	file_pair *pair = io_open_src(filename);
	if (pair == NULL)
		return;

	// Assume that something goes wrong.
	bool success = false;

	// Read the first chunk of input data. This is needed to detect
	// the input file type (for now, only for decompression).
	strm.next_in = in_buf.u8;
	strm.avail_in = io_read(pair, &in_buf, IO_BUFFER_SIZE);

	if (strm.avail_in != SIZE_MAX) {
		// Initialize the coder. This will detect the file format
		// and, in decompression or testing mode, check the memory
		// usage of the first Block too. This way we don't try to
		// open the destination file if we see that coding wouldn't
		// work at all anyway. This also avoids deleting the old
		// "target" file if --force was used.
		const enum coder_init_ret init_ret = coder_init(pair);

		if (init_ret != CODER_INIT_ERROR && !user_abort) {
			// Don't open the destination file when --test
			// is used.
			if (opt_mode == MODE_TEST || !io_open_dest(pair)) {
				// Initialize the progress indicator.
				const uint64_t in_size
						= pair->src_st.st_size <= 0
						? 0 : pair->src_st.st_size;
				message_progress_start(&strm, in_size);

				// Do the actual coding or passthru.
				if (init_ret == CODER_INIT_NORMAL)
					success = coder_normal(pair);
				else
					success = coder_passthru(pair);

				message_progress_end(success);
			}
		}
	}

	// Close the file pair. It needs to know if coding was successful to
	// know if the source or target file should be unlinked.
	io_close(pair, success);

	return;
}

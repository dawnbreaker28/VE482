# This file is automatically generated.  DO NOT EDIT!
# Generated from: 	NetBSD: mknative-binutils,v 1.8 2011/09/25 04:00:58 christos Exp 
# Generated from: NetBSD: mknative.common,v 1.9 2007/02/05 18:26:01 apb Exp 
#
G_libbfd_la_DEPENDENCIES=elfn32-mips.lo elfxx-mips.lo elf-vxworks.lo elf32.lo elf.lo elflink.lo elf-attrs.lo elf-strtab.lo elf-eh-frame.lo dwarf1.lo ecofflink.lo elf64-mips.lo elf64.lo elf32-mips.lo elf64-gen.lo elf32-gen.lo cpu-mips.lo netbsd-core.lo archive64.lo ofiles
G_libbfd_la_OBJECTS=archive.lo archures.lo bfd.lo bfdio.lo bfdwin.lo  cache.lo coffgen.lo corefile.lo format.lo init.lo libbfd.lo  opncls.lo reloc.lo section.lo syms.lo targets.lo hash.lo  linker.lo srec.lo binary.lo tekhex.lo ihex.lo stabs.lo  stab-syms.lo merge.lo dwarf2.lo simple.lo compress.lo  verilog.lo
G_DEFS=-DHAVE_CONFIG_H
G_INCLUDES=-DNETBSD_CORE   -I. -I${GNUHOSTDIST}/bfd -I${GNUHOSTDIST}/bfd/../include   -DHAVE_bfd_elf32_ntradlittlemips_vec -DHAVE_bfd_elf64_tradbigmips_vec -DHAVE_bfd_elf64_tradlittlemips_vec -DHAVE_bfd_elf32_ntradbigmips_vec -DHAVE_bfd_elf32_tradlittlemips_vec -DHAVE_bfd_elf32_tradbigmips_vec -DHAVE_bfd_elf64_little_generic_vec -DHAVE_bfd_elf64_big_generic_vec -DHAVE_bfd_elf32_little_generic_vec -DHAVE_bfd_elf32_big_generic_vec -I./../intl
G_TDEFAULTS=-DDEFAULT_VECTOR=bfd_elf32_ntradlittlemips_vec -DSELECT_VECS='&bfd_elf32_ntradlittlemips_vec,&bfd_elf64_tradbigmips_vec,&bfd_elf64_tradlittlemips_vec,&bfd_elf32_ntradbigmips_vec,&bfd_elf32_tradlittlemips_vec,&bfd_elf32_tradbigmips_vec,&bfd_elf64_little_generic_vec,&bfd_elf64_big_generic_vec,&bfd_elf32_little_generic_vec,&bfd_elf32_big_generic_vec' -DSELECT_ARCHITECTURES='&bfd_mips_arch'

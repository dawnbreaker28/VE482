# This file is automatically generated.  DO NOT EDIT!
# Generated from: 	NetBSD: mknative-gcc,v 1.67 2012/08/11 16:05:01 skrll Exp 
# Generated from: NetBSD: mknative.common,v 1.9 2007/02/05 18:26:01 apb Exp 
#
G_BUILD_EARLY_SUPPORT=
G_BUILD_ERRORS=build-errors.o
G_BUILD_PRINT=
G_BUILD_RTL=build-rtl.o read-rtl.o build-ggc-none.o vec.o min-insn-modes.o gensupport.o build-print-rtl.o
G_BUILD_SUPPORT=
G_BUILD_VARRAY=
G_ALL_CFLAGS=  -DIN_GCC   -W -Wall -Wwrite-strings -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes -Wmissing-format-attribute -pedantic -Wno-long-long -Wno-variadic-macros -Wno-overlength-strings -Wold-style-definition -Wc++-compat   -DHAVE_CONFIG_H
G_ALL_CPPFLAGS=-I. -I. -I${GNUHOSTDIST}/gcc -I${GNUHOSTDIST}/gcc/. -I${GNUHOSTDIST}/gcc/../include -I./../intl -I${GNUHOSTDIST}/gcc/../libcpp/include     -I${GNUHOSTDIST}/gcc/../libdecnumber -I${GNUHOSTDIST}/gcc/../libdecnumber/dpd -I../libdecnumber   -I/usr/include/libelf 
G_C_AND_OBJC_OBJS=attribs.o c-errors.o c-lex.o c-pragma.o c-decl.o c-typeck.o c-convert.o c-aux-info.o c-common.o c-opts.o c-format.o c-semantics.o c-ppoutput.o c-cppbuiltin.o c-objc-common.o c-dump.o c-pch.o c-parser.o sh-c.o c-gimplify.o tree-mudflap.o c-pretty-print.o c-omp.o
G_C_OBJS=c-lang.o stub-objc.o attribs.o c-errors.o c-lex.o c-pragma.o c-decl.o c-typeck.o c-convert.o c-aux-info.o c-common.o c-opts.o c-format.o c-semantics.o c-ppoutput.o c-cppbuiltin.o c-objc-common.o c-dump.o c-pch.o c-parser.o sh-c.o c-gimplify.o tree-mudflap.o c-pretty-print.o c-omp.o
G_CCCP_OBJS=
G_GCOV_OBJS=gcov.o intl.o version.o errors.o
G_PROTO_OBJS=
G_INCLUDES=-I. -I. -I${GNUHOSTDIST}/gcc -I${GNUHOSTDIST}/gcc/. -I${GNUHOSTDIST}/gcc/../include -I./../intl -I${GNUHOSTDIST}/gcc/../libcpp/include     -I${GNUHOSTDIST}/gcc/../libdecnumber -I${GNUHOSTDIST}/gcc/../libdecnumber/dpd -I../libdecnumber   -I/usr/include/libelf
G_md_file=${GNUHOSTDIST}/gcc/config/sh/sh.md
G_OBJC_OBJS=objc/objc-lang.o objc/objc-act.o
G_OBJS=insn-attrtab.o insn-automata.o insn-emit.o insn-extract.o insn-modes.o insn-opinit.o insn-output.o insn-peep.o insn-preds.o insn-recog.o ggc-page.o alias.o alloc-pool.o auto-inc-dec.o bb-reorder.o bitmap.o bt-load.o builtins.o caller-save.o calls.o cfg.o cfganal.o cfgbuild.o cfgcleanup.o cfgexpand.o cfghooks.o cfglayout.o cfgloop.o cfgloopanal.o cfgloopmanip.o cfgrtl.o combine.o combine-stack-adj.o convert.o coverage.o cse.o cselib.o dbxout.o dbgcnt.o dce.o ddg.o debug.o df-byte-scan.o df-core.o df-problems.o df-scan.o dfp.o diagnostic.o dojump.o dominance.o domwalk.o double-int.o dse.o dwarf2asm.o dwarf2out.o ebitmap.o emit-rtl.o et-forest.o except.o explow.o expmed.o expr.o final.o fixed-value.o fold-const.o function.o fwprop.o gcse.o genrtl.o ggc-common.o gimple.o gimple-iterator.o gimple-low.o gimple-pretty-print.o gimplify.o graph.o graphds.o graphite.o graphite-blocking.o graphite-clast-to-gimple.o graphite-dependences.o graphite-interchange.o graphite-poly.o graphite-ppl.o graphite-scop-detection.o graphite-sese-to-poly.o gtype-desc.o haifa-sched.o hooks.o ifcvt.o init-regs.o integrate.o intl.o ira.o ira-build.o ira-costs.o ira-conflicts.o ira-color.o ira-emit.o ira-lives.o jump.o lambda-code.o lambda-mat.o lambda-trans.o langhooks.o lcm.o lists.o loop-doloop.o loop-init.o loop-invariant.o loop-iv.o loop-unroll.o loop-unswitch.o lower-subreg.o lto-cgraph.o lto-streamer-in.o lto-streamer-out.o lto-section-in.o lto-section-out.o lto-symtab.o lto-opts.o lto-streamer.o lto-wpa-fixup.o lto-compress.o mcf.o mode-switching.o modulo-sched.o omega.o omp-low.o optabs.o options.o opts-common.o opts.o params.o passes.o plugin.o pointer-set.o postreload-gcse.o postreload.o predict.o pretty-print.o print-rtl.o print-tree.o profile.o real.o recog.o reg-stack.o regcprop.o reginfo.o regmove.o regrename.o regstat.o reload.o reload1.o reorg.o resource.o rtl-error.o rtl.o rtlanal.o rtlhooks.o sbitmap.o sched-deps.o sched-ebb.o sched-rgn.o sched-vis.o sdbout.o sel-sched-ir.o sel-sched-dump.o sel-sched.o sese.o simplify-rtx.o sparseset.o sreal.o stack-ptr-mod.o statistics.o stmt.o stor-layout.o store-motion.o stringpool.o targhooks.o timevar.o toplev.o tracer.o tree-affine.o tree-call-cdce.o tree-cfg.o tree-cfgcleanup.o tree-chrec.o tree-complex.o tree-data-ref.o tree-dfa.o tree-dump.o tree-eh.o tree-if-conv.o tree-into-ssa.o tree-iterator.o tree-loop-distribution.o tree-loop-linear.o tree-nested.o tree-nrv.o tree-object-size.o tree-optimize.o tree-outof-ssa.o tree-parloops.o tree-phinodes.o tree-predcom.o tree-pretty-print.o tree-profile.o tree-scalar-evolution.o tree-sra.o tree-switch-conversion.o tree-ssa-address.o tree-ssa-alias.o tree-ssa-ccp.o tree-ssa-coalesce.o tree-ssa-copy.o tree-ssa-copyrename.o tree-ssa-dce.o tree-ssa-dom.o tree-ssa-dse.o tree-ssa-forwprop.o tree-ssa-ifcombine.o tree-ssa-live.o tree-ssa-loop-ch.o tree-ssa-loop-im.o tree-ssa-loop-ivcanon.o tree-ssa-loop-ivopts.o tree-ssa-loop-manip.o tree-ssa-loop-niter.o tree-ssa-loop-prefetch.o tree-ssa-loop-unswitch.o tree-ssa-loop.o tree-ssa-math-opts.o tree-ssa-operands.o tree-ssa-phiopt.o tree-ssa-phiprop.o tree-ssa-pre.o tree-ssa-propagate.o tree-ssa-reassoc.o tree-ssa-sccvn.o tree-ssa-sink.o tree-ssa-structalias.o tree-ssa-ter.o tree-ssa-threadedge.o tree-ssa-threadupdate.o tree-ssa-uncprop.o tree-ssa.o tree-ssanames.o tree-stdarg.o tree-tailcall.o tree-vect-generic.o tree-vect-patterns.o tree-vect-data-refs.o tree-vect-stmts.o tree-vect-loop.o tree-vect-loop-manip.o tree-vect-slp.o tree-vectorizer.o tree-vrp.o tree.o value-prof.o var-tracking.o varasm.o varray.o vec.o version.o vmsdbgout.o web.o xcoffout.o sh.o  host-default.o cgraph.o cgraphbuild.o cgraphunit.o cppdefault.o incpath.o ipa-cp.o ipa-inline.o ipa-prop.o ipa-pure-const.o ipa-reference.o ipa-struct-reorg.o ipa-type-escape.o ipa-utils.o ipa.o matrix-reorg.o prefix.o tree-inline.o tree-nomudflap.o varpool.o
G_out_file=${GNUHOSTDIST}/gcc/config/sh/sh.c
G_version=4.5.4
G_BUILD_PREFIX=
G_RTL_H=rtl.h rtl.def machmode.h mode-classes.def insn-modes.h reg-notes.def insn-notes.def ${GNUHOSTDIST}/gcc/../libcpp/include/line-map.h input.h real.h machmode.h mode-classes.def insn-modes.h statistics.h vec.h fixed-value.h machmode.h mode-classes.def insn-modes.h double-int.h alias.h genrtl.h
G_TREE_H=tree.h all-tree.def tree.def c-common.def ${GNUHOSTDIST}/gcc/cp/cp-tree.def ${GNUHOSTDIST}/gcc/objc/objc-tree.def machmode.h mode-classes.def insn-modes.h tree-check.h builtins.def sync-builtins.def omp-builtins.def ${GNUHOSTDIST}/gcc/../libcpp/include/line-map.h input.h statistics.h vec.h treestruct.def ${GNUHOSTDIST}/gcc/../include/hashtab.h double-int.h alias.h ${GNUHOSTDIST}/gcc/../libcpp/include/symtab.h ${GNUHOSTDIST}/gcc/../include/obstack.h options.h
G_BASIC_BLOCK_H=basic-block.h bitmap.h ${GNUHOSTDIST}/gcc/../include/hashtab.h statistics.h sbitmap.h varray.h ${GNUHOSTDIST}/gcc/../include/partition.h hard-reg-set.h predict.h predict.def vec.h function.h tree.h all-tree.def tree.def c-common.def ${GNUHOSTDIST}/gcc/cp/cp-tree.def ${GNUHOSTDIST}/gcc/objc/objc-tree.def machmode.h mode-classes.def insn-modes.h tree-check.h builtins.def sync-builtins.def omp-builtins.def ${GNUHOSTDIST}/gcc/../libcpp/include/line-map.h input.h statistics.h vec.h treestruct.def ${GNUHOSTDIST}/gcc/../include/hashtab.h double-int.h alias.h ${GNUHOSTDIST}/gcc/../libcpp/include/symtab.h ${GNUHOSTDIST}/gcc/../include/obstack.h options.h ${GNUHOSTDIST}/gcc/../include/hashtab.h vecprim.h cfghooks.h ${GNUHOSTDIST}/gcc/../include/obstack.h
G_GCC_H=gcc.h version.h
G_GTFILES_SRCDIR=
G_GTFILES_FILES_FILES=
G_GTFILES_FILES_LANGS=
G_GTFILES=${GNUHOSTDIST}/gcc/../libcpp/include/line-map.h ${GNUHOSTDIST}/gcc/../libcpp/include/cpplib.h ${GNUHOSTDIST}/gcc/../libcpp/include/cpp-id-data.h ${GNUHOSTDIST}/gcc/input.h ${GNUHOSTDIST}/gcc/coretypes.h auto-host.h ${GNUHOSTDIST}/gcc/../include/ansidecl.h options.h ${GNUHOSTDIST}/gcc/config/sh/sh.h ${GNUHOSTDIST}/gcc/config/dbxelf.h ${GNUHOSTDIST}/gcc/config/elfos.h ${GNUHOSTDIST}/gcc/config/sh/elf.h ${GNUHOSTDIST}/gcc/config/netbsd.h ${GNUHOSTDIST}/gcc/config/netbsd-elf.h ${GNUHOSTDIST}/gcc/config/sh/netbsd-elf.h sysroot-suffix.h ${GNUHOSTDIST}/gcc/defaults.h ${GNUHOSTDIST}/gcc/../include/hashtab.h ${GNUHOSTDIST}/gcc/../include/splay-tree.h ${GNUHOSTDIST}/gcc/bitmap.h ${GNUHOSTDIST}/gcc/alias.h ${GNUHOSTDIST}/gcc/coverage.c ${GNUHOSTDIST}/gcc/rtl.h ${GNUHOSTDIST}/gcc/vecprim.h ${GNUHOSTDIST}/gcc/optabs.h ${GNUHOSTDIST}/gcc/tree.h ${GNUHOSTDIST}/gcc/varray.h ${GNUHOSTDIST}/gcc/libfuncs.h ${GNUHOSTDIST}/gcc/../libcpp/include/symtab.h ${GNUHOSTDIST}/gcc/../include/obstack.h ${GNUHOSTDIST}/gcc/real.h ${GNUHOSTDIST}/gcc/function.h ${GNUHOSTDIST}/gcc/insn-addr.h ${GNUHOSTDIST}/gcc/hwint.h ${GNUHOSTDIST}/gcc/fixed-value.h ${GNUHOSTDIST}/gcc/ipa-reference.h ${GNUHOSTDIST}/gcc/output.h ${GNUHOSTDIST}/gcc/cfgloop.h ${GNUHOSTDIST}/gcc/cselib.h ${GNUHOSTDIST}/gcc/basic-block.h  ${GNUHOSTDIST}/gcc/cgraph.h ${GNUHOSTDIST}/gcc/reload.h ${GNUHOSTDIST}/gcc/caller-save.c ${GNUHOSTDIST}/gcc/alias.c ${GNUHOSTDIST}/gcc/bitmap.c ${GNUHOSTDIST}/gcc/cselib.c ${GNUHOSTDIST}/gcc/cgraph.c ${GNUHOSTDIST}/gcc/ipa-prop.c ${GNUHOSTDIST}/gcc/ipa-cp.c ${GNUHOSTDIST}/gcc/ipa-inline.c ${GNUHOSTDIST}/gcc/matrix-reorg.c ${GNUHOSTDIST}/gcc/dbxout.c ${GNUHOSTDIST}/gcc/ipa-struct-reorg.c ${GNUHOSTDIST}/gcc/dwarf2out.c ${GNUHOSTDIST}/gcc/dwarf2asm.c ${GNUHOSTDIST}/gcc/tree-vect-generic.c ${GNUHOSTDIST}/gcc/dojump.c ${GNUHOSTDIST}/gcc/emit-rtl.c ${GNUHOSTDIST}/gcc/except.h ${GNUHOSTDIST}/gcc/explow.c ${GNUHOSTDIST}/gcc/expr.c ${GNUHOSTDIST}/gcc/expr.h ${GNUHOSTDIST}/gcc/function.c ${GNUHOSTDIST}/gcc/except.c ${GNUHOSTDIST}/gcc/gcse.c ${GNUHOSTDIST}/gcc/integrate.c ${GNUHOSTDIST}/gcc/lists.c ${GNUHOSTDIST}/gcc/optabs.c ${GNUHOSTDIST}/gcc/profile.c ${GNUHOSTDIST}/gcc/reginfo.c ${GNUHOSTDIST}/gcc/mcf.c ${GNUHOSTDIST}/gcc/reg-stack.c ${GNUHOSTDIST}/gcc/cfglayout.c ${GNUHOSTDIST}/gcc/cfglayout.h ${GNUHOSTDIST}/gcc/sdbout.c ${GNUHOSTDIST}/gcc/stor-layout.c ${GNUHOSTDIST}/gcc/stringpool.c ${GNUHOSTDIST}/gcc/tree.c ${GNUHOSTDIST}/gcc/varasm.c ${GNUHOSTDIST}/gcc/gimple.h ${GNUHOSTDIST}/gcc/gimple.c ${GNUHOSTDIST}/gcc/tree-mudflap.c ${GNUHOSTDIST}/gcc/tree-flow.h ${GNUHOSTDIST}/gcc/tree-ssanames.c ${GNUHOSTDIST}/gcc/tree-eh.c ${GNUHOSTDIST}/gcc/tree-ssa-address.c ${GNUHOSTDIST}/gcc/tree-cfg.c ${GNUHOSTDIST}/gcc/tree-dfa.c ${GNUHOSTDIST}/gcc/tree-iterator.c ${GNUHOSTDIST}/gcc/gimplify.c ${GNUHOSTDIST}/gcc/tree-chrec.h ${GNUHOSTDIST}/gcc/tree-scalar-evolution.c ${GNUHOSTDIST}/gcc/tree-ssa-operands.h ${GNUHOSTDIST}/gcc/tree-profile.c ${GNUHOSTDIST}/gcc/tree-nested.c ${GNUHOSTDIST}/gcc/varpool.c ${GNUHOSTDIST}/gcc/tree-parloops.c ${GNUHOSTDIST}/gcc/omp-low.c ${GNUHOSTDIST}/gcc/targhooks.c ${GNUHOSTDIST}/gcc/config/sh/sh.c ${GNUHOSTDIST}/gcc/passes.c ${GNUHOSTDIST}/gcc/cgraphunit.c ${GNUHOSTDIST}/gcc/tree-ssa-propagate.c ${GNUHOSTDIST}/gcc/tree-phinodes.c ${GNUHOSTDIST}/gcc/ipa-reference.c ${GNUHOSTDIST}/gcc/tree-ssa-structalias.c ${GNUHOSTDIST}/gcc/lto-symtab.c ${GNUHOSTDIST}/gcc/tree-ssa-alias.h ${GNUHOSTDIST}/gcc/ipa-prop.h [cp] ${GNUHOSTDIST}/gcc/cp/rtti.c ${GNUHOSTDIST}/gcc/cp/mangle.c ${GNUHOSTDIST}/gcc/cp/name-lookup.h ${GNUHOSTDIST}/gcc/cp/name-lookup.c ${GNUHOSTDIST}/gcc/cp/cp-tree.h ${GNUHOSTDIST}/gcc/cp/decl.h ${GNUHOSTDIST}/gcc/cp/call.c ${GNUHOSTDIST}/gcc/cp/decl.c ${GNUHOSTDIST}/gcc/cp/decl2.c ${GNUHOSTDIST}/gcc/cp/pt.c ${GNUHOSTDIST}/gcc/cp/repo.c ${GNUHOSTDIST}/gcc/cp/semantics.c ${GNUHOSTDIST}/gcc/cp/tree.c ${GNUHOSTDIST}/gcc/cp/parser.c ${GNUHOSTDIST}/gcc/cp/method.c ${GNUHOSTDIST}/gcc/cp/typeck2.c ${GNUHOSTDIST}/gcc/c-common.c ${GNUHOSTDIST}/gcc/c-common.h ${GNUHOSTDIST}/gcc/c-lex.c ${GNUHOSTDIST}/gcc/c-pragma.h ${GNUHOSTDIST}/gcc/c-pragma.c ${GNUHOSTDIST}/gcc/cp/class.c ${GNUHOSTDIST}/gcc/cp/cp-objcp-common.c ${GNUHOSTDIST}/gcc/cp/cp-lang.c [lto] ${GNUHOSTDIST}/gcc/lto/lto-tree.h ${GNUHOSTDIST}/gcc/lto/lto-lang.c ${GNUHOSTDIST}/gcc/lto/lto.c [objc] ${GNUHOSTDIST}/gcc/objc/objc-act.h ${GNUHOSTDIST}/gcc/c-parser.c ${GNUHOSTDIST}/gcc/c-tree.h ${GNUHOSTDIST}/gcc/c-decl.c ${GNUHOSTDIST}/gcc/c-objc-common.c ${GNUHOSTDIST}/gcc/c-common.c ${GNUHOSTDIST}/gcc/c-common.h ${GNUHOSTDIST}/gcc/c-pragma.h ${GNUHOSTDIST}/gcc/c-pragma.c ${GNUHOSTDIST}/gcc/objc/objc-act.c [objcp] ${GNUHOSTDIST}/gcc/objcp/objcp-decl.c ${GNUHOSTDIST}/gcc/objc/objc-act.c ${GNUHOSTDIST}/gcc/objc/objc-act.h ${GNUHOSTDIST}/gcc/cp/rtti.c ${GNUHOSTDIST}/gcc/cp/mangle.c ${GNUHOSTDIST}/gcc/cp/name-lookup.h ${GNUHOSTDIST}/gcc/cp/name-lookup.c ${GNUHOSTDIST}/gcc/cp/cp-tree.h ${GNUHOSTDIST}/gcc/cp/decl.h ${GNUHOSTDIST}/gcc/cp/call.c ${GNUHOSTDIST}/gcc/cp/decl.c ${GNUHOSTDIST}/gcc/cp/decl2.c ${GNUHOSTDIST}/gcc/cp/pt.c ${GNUHOSTDIST}/gcc/cp/repo.c ${GNUHOSTDIST}/gcc/cp/semantics.c ${GNUHOSTDIST}/gcc/cp/tree.c ${GNUHOSTDIST}/gcc/cp/parser.c ${GNUHOSTDIST}/gcc/cp/method.c ${GNUHOSTDIST}/gcc/cp/typeck2.c ${GNUHOSTDIST}/gcc/c-common.c ${GNUHOSTDIST}/gcc/c-common.h ${GNUHOSTDIST}/gcc/c-lex.c ${GNUHOSTDIST}/gcc/c-pragma.h ${GNUHOSTDIST}/gcc/c-pragma.c ${GNUHOSTDIST}/gcc/cp/cp-objcp-common.c [c] ${GNUHOSTDIST}/gcc/c-lang.c ${GNUHOSTDIST}/gcc/c-tree.h ${GNUHOSTDIST}/gcc/c-decl.c ${GNUHOSTDIST}/gcc/c-common.c ${GNUHOSTDIST}/gcc/c-common.h ${GNUHOSTDIST}/gcc/c-pragma.h ${GNUHOSTDIST}/gcc/c-pragma.c ${GNUHOSTDIST}/gcc/c-objc-common.c ${GNUHOSTDIST}/gcc/c-parser.c ${GNUHOSTDIST}/gcc/c-lang.h
G_GTFILES_LANG_DIR_NAMES=
G_tm_defines=NETBSD_ENABLE_PTHREADS SH_MULTILIB_CPU_DEFAULT="m3" SUPPORT_SH3=1 SUPPORT_SH3=1 SUPPORT_SH3E=1 SUPPORT_SH4=1
G_host_xm_file=
G_host_xm_defines=
G_tm_p_file=
G_target_cpu_default=SELECT_SH3
G_TM_H=tm.h      options.h ${GNUHOSTDIST}/gcc/config/sh/sh.h ${GNUHOSTDIST}/gcc/config/dbxelf.h ${GNUHOSTDIST}/gcc/config/elfos.h ${GNUHOSTDIST}/gcc/config/sh/elf.h ${GNUHOSTDIST}/gcc/config/netbsd.h ${GNUHOSTDIST}/gcc/config/netbsd-elf.h ${GNUHOSTDIST}/gcc/config/sh/netbsd-elf.h sysroot-suffix.h ${GNUHOSTDIST}/gcc/defaults.h insn-constants.h insn-flags.h options.h
G_ALL_OPT_FILES=${GNUHOSTDIST}/gcc/lto/lang.opt ${GNUHOSTDIST}/gcc/c.opt ${GNUHOSTDIST}/gcc/common.opt ${GNUHOSTDIST}/gcc/config/sh/sh.opt
G_tm_file_list=options.h ${GNUHOSTDIST}/gcc/config/sh/sh.h ${GNUHOSTDIST}/gcc/config/dbxelf.h ${GNUHOSTDIST}/gcc/config/elfos.h ${GNUHOSTDIST}/gcc/config/sh/elf.h ${GNUHOSTDIST}/gcc/config/netbsd.h ${GNUHOSTDIST}/gcc/config/netbsd-elf.h ${GNUHOSTDIST}/gcc/config/sh/netbsd-elf.h sysroot-suffix.h ${GNUHOSTDIST}/gcc/defaults.h
G_build_xm_include_list=auto-build.h ansidecl.h
G_lang_specs_files=${GNUHOSTDIST}/gcc/cp/lang-specs.h ${GNUHOSTDIST}/gcc/lto/lang-specs.h ${GNUHOSTDIST}/gcc/objc/lang-specs.h
G_tm_p_include_list=config/sh/sh-protos.h tm-preds.h
G_LIB2ADDEHDEP= unwind-dw2-fde.h unwind-dw2-fde.c
G_CXX_OBJS=cp-lang.o stub-objc.o call.o decl.o expr.o pt.o typeck2.o class.o decl2.o error.o lex.o parser.o ptree.o rtti.o typeck.o cvt.o except.o friend.o init.o method.o search.o semantics.o tree.o repo.o dump.o optimize.o mangle.o cp-objcp-common.o name-lookup.o cxx-pretty-print.o cp-gimplify.o tree-mudflap.o attribs.o c-common.o c-format.o c-pragma.o c-semantics.o c-lex.o c-dump.o sh-c.o c-pretty-print.o c-opts.o c-pch.o incpath.o c-ppoutput.o c-cppbuiltin.o prefix.o c-gimplify.o c-omp.o
G_CXX_C_OBJS=attribs.o c-common.o c-format.o c-pragma.o c-semantics.o c-lex.o c-dump.o sh-c.o c-pretty-print.o c-opts.o c-pch.o incpath.o c-ppoutput.o c-cppbuiltin.o prefix.o c-gimplify.o c-omp.o
G_F77_OBJS=
G_libcpp_a_OBJS=charset.o directives.o directives-only.o errors.o expr.o files.o identifiers.o init.o lex.o line-map.o macro.o mkdeps.o pch.o symtab.o traditional.o
G_ENABLE_SHARED=
G_SHLIB_LINK= -shared
G_SHLIB_MULTILIB=.

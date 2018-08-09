	.file	"main.c"
# GNU C89 (Ubuntu 5.4.0-6ubuntu1~16.04.4) version 5.4.0 20160609 (i686-linux-gnu)
#	compiled by GNU C version 5.4.0 20160609, GMP version 6.1.0, MPFR version 3.1.4, MPC version 1.0.3
# GGC heuristics: --param ggc-min-expand=98 --param ggc-min-heapsize=127997
# options passed:  -nostdinc -I ./arch/x86/include
# -I arch/x86/include/generated/uapi -I arch/x86/include/generated
# -I include -I ./arch/x86/include/uapi -I arch/x86/include/generated/uapi
# -I ./include/uapi -I include/generated/uapi -I ubuntu/include
# -imultiarch i386-linux-gnu -D __KERNEL__ -D CONFIG_AS_CFI=1
# -D CONFIG_AS_CFI_SIGNAL_FRAME=1 -D CONFIG_AS_CFI_SECTIONS=1
# -D CONFIG_AS_SSSE3=1 -D CONFIG_AS_CRC32=1 -D CONFIG_AS_AVX=1
# -D CONFIG_AS_AVX2=1 -D CONFIG_AS_SHA1_NI=1 -D CONFIG_AS_SHA256_NI=1
# -D CC_HAVE_ASM_GOTO -D MODULE -D KBUILD_STR(s)=#s
# -D KBUILD_BASENAME=KBUILD_STR(main)
# -isystem /usr/lib/gcc/i686-linux-gnu/5/include
# -include ./include/linux/kconfig.h
# -MD /home/william/Linux_Device_Driver/10/read_modify_write/kernel/.main.s.d
# /home/william/Linux_Device_Driver/10/read_modify_write/kernel/main.c
# -mno-sse -mno-mmx -mno-sse2 -mno-3dnow -mno-avx -m32 -msoft-float
# -mregparm=3 -mpreferred-stack-boundary=2 -march=i686 -mtune=generic
# -maccumulate-outgoing-args
# -auxbase-strip /home/william/Linux_Device_Driver/10/read_modify_write/kernel/main.s
# -O2 -Wundef -Wstrict-prototypes -Wno-trigraphs
# -Werror=implicit-function-declaration -Wno-format-security
# -Wno-sign-compare -Wno-maybe-uninitialized -Wframe-larger-than=1024
# -Wno-unused-but-set-variable -Wdeclaration-after-statement
# -Wno-pointer-sign -Werror=implicit-int -Werror=strict-prototypes
# -Werror=date-time -Wall -std=gnu90 -p -fno-strict-aliasing -fno-common
# -freg-struct-return -fno-pic -ffreestanding
# -fno-asynchronous-unwind-tables -fno-delete-null-pointer-checks
# -fstack-protector-strong -fno-omit-frame-pointer
# -fno-optimize-sibling-calls -fno-var-tracking-assignments
# -fno-strict-overflow -fconserve-stack -fverbose-asm
# --param allow-store-data-races=0
# options enabled:  -faggressive-loop-optimizations -falign-labels
# -fauto-inc-dec -fbranch-count-reg -fcaller-saves
# -fchkp-check-incomplete-type -fchkp-check-read -fchkp-check-write
# -fchkp-instrument-calls -fchkp-narrow-bounds -fchkp-optimize
# -fchkp-store-bounds -fchkp-use-static-bounds
# -fchkp-use-static-const-bounds -fchkp-use-wrappers
# -fcombine-stack-adjustments -fcompare-elim -fcprop-registers
# -fcrossjumping -fcse-follow-jumps -fdefer-pop -fdevirtualize
# -fdevirtualize-speculatively -fdwarf2-cfi-asm -fearly-inlining
# -feliminate-unused-debug-types -fexpensive-optimizations
# -fforward-propagate -ffunction-cse -fgcse -fgcse-lm -fgnu-runtime
# -fgnu-unique -fguess-branch-probability -fhoist-adjacent-loads -fident
# -fif-conversion -fif-conversion2 -findirect-inlining -finline
# -finline-atomics -finline-functions-called-once -finline-small-functions
# -fipa-cp -fipa-cp-alignment -fipa-icf -fipa-icf-functions
# -fipa-icf-variables -fipa-profile -fipa-pure-const -fipa-reference
# -fipa-sra -fira-hoist-pressure -fira-share-save-slots
# -fira-share-spill-slots -fisolate-erroneous-paths-dereference -fivopts
# -fkeep-static-consts -fleading-underscore -flifetime-dse -flra-remat
# -flto-odr-type-merging -fmath-errno -fmerge-constants
# -fmerge-debug-strings -fmove-loop-invariants -foptimize-strlen
# -fpartial-inlining -fpeephole -fpeephole2 -fprefetch-loop-arrays
# -fprofile -free -freg-struct-return -freorder-blocks
# -freorder-blocks-and-partition -freorder-functions -frerun-cse-after-loop
# -fsched-critical-path-heuristic -fsched-dep-count-heuristic
# -fsched-group-heuristic -fsched-interblock -fsched-last-insn-heuristic
# -fsched-rank-heuristic -fsched-spec -fsched-spec-insn-heuristic
# -fsched-stalled-insns-dep -fschedule-fusion -fschedule-insns2
# -fsemantic-interposition -fshow-column -fshrink-wrap -fsigned-zeros
# -fsplit-ivs-in-unroller -fsplit-wide-types -fssa-phiopt
# -fstack-protector-strong -fstdarg-opt -fstrict-volatile-bitfields
# -fsync-libcalls -fthread-jumps -ftoplevel-reorder -ftrapping-math
# -ftree-bit-ccp -ftree-builtin-call-dce -ftree-ccp -ftree-ch
# -ftree-coalesce-vars -ftree-copy-prop -ftree-copyrename -ftree-cselim
# -ftree-dce -ftree-dominator-opts -ftree-dse -ftree-forwprop -ftree-fre
# -ftree-loop-if-convert -ftree-loop-im -ftree-loop-ivcanon
# -ftree-loop-optimize -ftree-parallelize-loops= -ftree-phiprop -ftree-pre
# -ftree-pta -ftree-reassoc -ftree-scev-cprop -ftree-sink -ftree-slsr
# -ftree-sra -ftree-switch-conversion -ftree-tail-merge -ftree-ter
# -ftree-vrp -funit-at-a-time -fverbose-asm -fzero-initialized-in-bss -m32
# -m96bit-long-double -maccumulate-outgoing-args -malign-stringops
# -mavx256-split-unaligned-load -mavx256-split-unaligned-store -mglibc
# -mieee-fp -mlong-double-80 -mno-fancy-math-387 -mno-red-zone -mno-sse4
# -mpush-args -msahf -mtls-direct-seg-refs -mvzeroupper

	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"sample driver installed.\n"
.LC1:
	.string	"n %d\n"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB2:
	.text
.LHOTB2:
	.p2align 4,,15
	.type	sample_init, @function
sample_init:
	pushl	%ebp	#
	movl	%esp, %ebp	#,
	subl	$12, %esp	#,
1:	call	mcount
	movl	$.LC0, (%esp)	#,
	movl	$0, -4(%ebp)	#, n
	call	printk	#
	movl	-4(%ebp), %eax	# n, D.16011
	movl	$.LC1, (%esp)	#,
	addl	$1, %eax	#, D.16011
	movl	%eax, -4(%ebp)	# D.16011, n
	movl	-4(%ebp), %eax	# n, D.16011
	movl	%eax, 4(%esp)	# D.16011,
	call	printk	#
	xorl	%eax, %eax	#
	leave
	ret
	.size	sample_init, .-sample_init
	.section	.text.unlikely
.LCOLDE2:
	.text
.LHOTE2:
	.globl	init_module
	.set	init_module,sample_init
	.section	.rodata.str1.1
.LC3:
	.string	"sample driver removed.\n"
	.section	.text.unlikely
.LCOLDB4:
	.text
.LHOTB4:
	.p2align 4,,15
	.type	sample_exit, @function
sample_exit:
	pushl	%ebp	#
	movl	%esp, %ebp	#,
	subl	$4, %esp	#,
1:	call	mcount
	movl	$.LC3, (%esp)	#,
	call	printk	#
	leave
	ret
	.size	sample_exit, .-sample_exit
	.section	.text.unlikely
.LCOLDE4:
	.text
.LHOTE4:
	.globl	cleanup_module
	.set	cleanup_module,sample_exit
	.section	.modinfo,"a",@progbits
	.type	__UNIQUE_ID_license0, @object
	.size	__UNIQUE_ID_license0, 21
__UNIQUE_ID_license0:
	.string	"license=Dual BSD/GPL"
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits

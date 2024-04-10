savedcmd_/root/modules/pollselect_scullpipe/scullpipe.mod.o := gcc -Wp,-MMD,/root/modules/pollselect_scullpipe/.scullpipe.mod.o.d -nostdinc -I/root/kernel-ark-os-build/arch/x86/include -I./arch/x86/include/generated -I/root/kernel-ark-os-build/include -I./include -I/root/kernel-ark-os-build/arch/x86/include/uapi -I./arch/x86/include/generated/uapi -I/root/kernel-ark-os-build/include/uapi -I./include/generated/uapi -include /root/kernel-ark-os-build/include/linux/compiler-version.h -include /root/kernel-ark-os-build/include/linux/kconfig.h -include /root/kernel-ark-os-build/include/linux/compiler_types.h -D__KERNEL__ -fmacro-prefix-map=/root/kernel-ark-os-build/= -std=gnu11 -fshort-wchar -funsigned-char -fno-common -fno-PIE -fno-strict-aliasing -mno-sse -mno-mmx -mno-sse2 -mno-3dnow -mno-avx -fcf-protection=branch -fno-jump-tables -m64 -falign-jumps=1 -falign-loops=1 -mno-80387 -mno-fp-ret-in-387 -mpreferred-stack-boundary=3 -mskip-rax-setup -mtune=generic -mno-red-zone -mcmodel=kernel -Wno-sign-compare -fno-asynchronous-unwind-tables -mindirect-branch=thunk-extern -mindirect-branch-register -mindirect-branch-cs-prefix -mfunction-return=thunk-extern -fno-jump-tables -mharden-sls=all -fpatchable-function-entry=16,16 -fno-delete-null-pointer-checks -O2 -fno-allow-store-data-races -fstack-protector-strong -ftrivial-auto-var-init=zero -fno-stack-clash-protection -pg -mrecord-mcount -mfentry -DCC_USING_FENTRY -falign-functions=16 -fstrict-flex-arrays=3 -fno-strict-overflow -fno-stack-check -fconserve-stack -Wall -Wundef -Werror=implicit-function-declaration -Werror=implicit-int -Werror=return-type -Werror=strict-prototypes -Wno-format-security -Wno-trigraphs -Wno-frame-address -Wno-address-of-packed-member -Wframe-larger-than=2048 -Wno-main -Wno-unused-but-set-variable -Wno-unused-const-variable -Wno-dangling-pointer -Wvla -Wno-pointer-sign -Wcast-function-type -Wno-array-bounds -Wno-alloc-size-larger-than -Wimplicit-fallthrough=5 -Werror=date-time -Werror=incompatible-pointer-types -Werror=designated-init -Wenum-conversion -Wno-unused-but-set-variable -Wno-unused-const-variable -Wno-restrict -Wno-packed-not-aligned -Wno-format-overflow -Wno-format-truncation -Wno-stringop-overflow -Wno-stringop-truncation -Wno-missing-field-initializers -Wno-type-limits -Wno-shift-negative-value -Wno-maybe-uninitialized -Wno-sign-compare -g -DMODULE -DKBUILD_BASENAME='"scullpipe.mod"' -DKBUILD_MODNAME='"scullpipe"' -D__KBUILD_MODNAME=kmod_scullpipe -c -o /root/modules/pollselect_scullpipe/scullpipe.mod.o /root/modules/pollselect_scullpipe/scullpipe.mod.c

source_/root/modules/pollselect_scullpipe/scullpipe.mod.o := /root/modules/pollselect_scullpipe/scullpipe.mod.c

deps_/root/modules/pollselect_scullpipe/scullpipe.mod.o := \
    $(wildcard include/config/UNWINDER_ORC) \
    $(wildcard include/config/MODULE_UNLOAD) \
    $(wildcard include/config/RETPOLINE) \
  /root/kernel-ark-os-build/include/linux/compiler-version.h \
    $(wildcard include/config/CC_VERSION_TEXT) \
  /root/kernel-ark-os-build/include/linux/kconfig.h \
    $(wildcard include/config/CPU_BIG_ENDIAN) \
    $(wildcard include/config/BOOGER) \
    $(wildcard include/config/FOO) \
  /root/kernel-ark-os-build/include/linux/compiler_types.h \
    $(wildcard include/config/DEBUG_INFO_BTF) \
    $(wildcard include/config/PAHOLE_HAS_BTF_TAG) \
    $(wildcard include/config/FUNCTION_ALIGNMENT) \
    $(wildcard include/config/CC_IS_GCC) \
    $(wildcard include/config/X86_64) \
    $(wildcard include/config/ARM64) \
    $(wildcard include/config/HAVE_ARCH_COMPILER_H) \
    $(wildcard include/config/CC_HAS_ASM_INLINE) \
  /root/kernel-ark-os-build/include/linux/compiler_attributes.h \
  /root/kernel-ark-os-build/include/linux/compiler-gcc.h \
    $(wildcard include/config/ARCH_USE_BUILTIN_BSWAP) \
    $(wildcard include/config/SHADOW_CALL_STACK) \
    $(wildcard include/config/KCOV) \
  /root/kernel-ark-os-build/include/linux/module.h \
    $(wildcard include/config/MODULES) \
    $(wildcard include/config/SYSFS) \
    $(wildcard include/config/MODULES_TREE_LOOKUP) \
    $(wildcard include/config/LIVEPATCH) \
    $(wildcard include/config/STACKTRACE_BUILD_ID) \
    $(wildcard include/config/ARCH_USES_CFI_TRAPS) \
    $(wildcard include/config/MODULE_SIG) \
    $(wildcard include/config/GENERIC_BUG) \
    $(wildcard include/config/KALLSYMS) \
    $(wildcard include/config/SMP) \
    $(wildcard include/config/TRACEPOINTS) \
    $(wildcard include/config/TREE_SRCU) \
    $(wildcard include/config/BPF_EVENTS) \
    $(wildcard include/config/DEBUG_INFO_BTF_MODULES) \
    $(wildcard include/config/JUMP_LABEL) \
    $(wildcard include/config/TRACING) \
    $(wildcard include/config/EVENT_TRACING) \
    $(wildcard include/config/FTRACE_MCOUNT_RECORD) \
    $(wildcard include/config/KPROBES) \
    $(wildcard include/config/HAVE_STATIC_CALL_INLINE) \
    $(wildcard include/config/KUNIT) \
    $(wildcard include/config/PRINTK_INDEX) \
    $(wildcard include/config/CONSTRUCTORS) \
    $(wildcard include/config/FUNCTION_ERROR_INJECTION) \
    $(wildcard include/config/DYNAMIC_DEBUG_CORE) \
    $(wildcard include/config/RHEL_DIFFERENCES) \
  /root/kernel-ark-os-build/include/linux/list.h \
    $(wildcard include/config/LIST_HARDENED) \
    $(wildcard include/config/DEBUG_LIST) \
  /root/kernel-ark-os-build/include/linux/container_of.h \
  /root/kernel-ark-os-build/include/linux/build_bug.h \
  /root/kernel-ark-os-build/include/linux/compiler.h \
    $(wildcard include/config/TRACE_BRANCH_PROFILING) \
    $(wildcard include/config/PROFILE_ALL_BRANCHES) \
    $(wildcard include/config/OBJTOOL) \
  arch/x86/include/generated/asm/rwonce.h \
  /root/kernel-ark-os-build/include/asm-generic/rwonce.h \
  /root/kernel-ark-os-build/include/linux/kasan-checks.h \
    $(wildcard include/config/KASAN_GENERIC) \
    $(wildcard include/config/KASAN_SW_TAGS) \
  /root/kernel-ark-os-build/include/linux/types.h \
    $(wildcard include/config/HAVE_UID16) \
    $(wildcard include/config/UID16) \
    $(wildcard include/config/ARCH_DMA_ADDR_T_64BIT) \
    $(wildcard include/config/PHYS_ADDR_T_64BIT) \
    $(wildcard include/config/64BIT) \
    $(wildcard include/config/ARCH_32BIT_USTAT_F_TINODE) \
  /root/kernel-ark-os-build/include/uapi/linux/types.h \
  arch/x86/include/generated/uapi/asm/types.h \
  /root/kernel-ark-os-build/include/uapi/asm-generic/types.h \
  /root/kernel-ark-os-build/include/asm-generic/int-ll64.h \
  /root/kernel-ark-os-build/include/uapi/asm-generic/int-ll64.h \
  /root/kernel-ark-os-build/arch/x86/include/uapi/asm/bitsperlong.h \
  /root/kernel-ark-os-build/include/asm-generic/bitsperlong.h \
  /root/kernel-ark-os-build/include/uapi/asm-generic/bitsperlong.h \
  /root/kernel-ark-os-build/include/uapi/linux/posix_types.h \
  /root/kernel-ark-os-build/include/linux/stddef.h \
  /root/kernel-ark-os-build/include/uapi/linux/stddef.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/posix_types.h \
    $(wildcard include/config/X86_32) \
  /root/kernel-ark-os-build/arch/x86/include/uapi/asm/posix_types_64.h \
  /root/kernel-ark-os-build/include/uapi/asm-generic/posix_types.h \
  /root/kernel-ark-os-build/include/linux/kcsan-checks.h \
    $(wildcard include/config/KCSAN) \
    $(wildcard include/config/KCSAN_WEAK_MEMORY) \
    $(wildcard include/config/KCSAN_IGNORE_ATOMICS) \
  /root/kernel-ark-os-build/include/linux/poison.h \
    $(wildcard include/config/ILLEGAL_POINTER_VALUE) \
  /root/kernel-ark-os-build/include/linux/const.h \
  /root/kernel-ark-os-build/include/vdso/const.h \
  /root/kernel-ark-os-build/include/uapi/linux/const.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/barrier.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/alternative.h \
    $(wildcard include/config/CALL_THUNKS) \
  /root/kernel-ark-os-build/include/linux/stringify.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/asm.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/extable_fixup_types.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/nops.h \
  /root/kernel-ark-os-build/include/asm-generic/barrier.h \
  /root/kernel-ark-os-build/include/linux/stat.h \
  /root/kernel-ark-os-build/arch/x86/include/uapi/asm/stat.h \
  /root/kernel-ark-os-build/include/uapi/linux/stat.h \
  /root/kernel-ark-os-build/include/linux/time.h \
    $(wildcard include/config/POSIX_TIMERS) \
  /root/kernel-ark-os-build/include/linux/cache.h \
    $(wildcard include/config/ARCH_HAS_CACHE_LINE_SIZE) \
  /root/kernel-ark-os-build/include/uapi/linux/kernel.h \
  /root/kernel-ark-os-build/include/uapi/linux/sysinfo.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/cache.h \
    $(wildcard include/config/X86_L1_CACHE_SHIFT) \
    $(wildcard include/config/X86_INTERNODE_CACHE_SHIFT) \
    $(wildcard include/config/X86_VSMP) \
  /root/kernel-ark-os-build/include/linux/linkage.h \
    $(wildcard include/config/ARCH_USE_SYM_ANNOTATIONS) \
  /root/kernel-ark-os-build/include/linux/export.h \
    $(wildcard include/config/MODVERSIONS) \
  /root/kernel-ark-os-build/arch/x86/include/asm/linkage.h \
    $(wildcard include/config/CALL_PADDING) \
    $(wildcard include/config/RETHUNK) \
    $(wildcard include/config/SLS) \
    $(wildcard include/config/FUNCTION_PADDING_BYTES) \
    $(wildcard include/config/UML) \
  /root/kernel-ark-os-build/arch/x86/include/asm/ibt.h \
    $(wildcard include/config/X86_KERNEL_IBT) \
  /root/kernel-ark-os-build/include/linux/math64.h \
    $(wildcard include/config/ARCH_SUPPORTS_INT128) \
  /root/kernel-ark-os-build/include/linux/math.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/div64.h \
  /root/kernel-ark-os-build/include/asm-generic/div64.h \
  /root/kernel-ark-os-build/include/vdso/math64.h \
  /root/kernel-ark-os-build/include/linux/time64.h \
  /root/kernel-ark-os-build/include/vdso/time64.h \
  /root/kernel-ark-os-build/include/uapi/linux/time.h \
  /root/kernel-ark-os-build/include/uapi/linux/time_types.h \
  /root/kernel-ark-os-build/include/linux/time32.h \
  /root/kernel-ark-os-build/include/linux/timex.h \
  /root/kernel-ark-os-build/include/uapi/linux/timex.h \
  /root/kernel-ark-os-build/include/uapi/linux/param.h \
  arch/x86/include/generated/uapi/asm/param.h \
  /root/kernel-ark-os-build/include/asm-generic/param.h \
    $(wildcard include/config/HZ) \
  /root/kernel-ark-os-build/include/uapi/asm-generic/param.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/timex.h \
    $(wildcard include/config/X86_TSC) \
  /root/kernel-ark-os-build/arch/x86/include/asm/processor.h \
    $(wildcard include/config/X86_VMX_FEATURE_NAMES) \
    $(wildcard include/config/X86_IOPL_IOPERM) \
    $(wildcard include/config/STACKPROTECTOR) \
    $(wildcard include/config/VM86) \
    $(wildcard include/config/X86_USER_SHADOW_STACK) \
    $(wildcard include/config/PARAVIRT_XXL) \
    $(wildcard include/config/X86_DEBUGCTLMSR) \
    $(wildcard include/config/CPU_SUP_AMD) \
    $(wildcard include/config/XEN) \
  /root/kernel-ark-os-build/arch/x86/include/asm/processor-flags.h \
    $(wildcard include/config/PAGE_TABLE_ISOLATION) \
  /root/kernel-ark-os-build/arch/x86/include/uapi/asm/processor-flags.h \
  /root/kernel-ark-os-build/include/linux/mem_encrypt.h \
    $(wildcard include/config/ARCH_HAS_MEM_ENCRYPT) \
    $(wildcard include/config/AMD_MEM_ENCRYPT) \
  /root/kernel-ark-os-build/arch/x86/include/asm/mem_encrypt.h \
    $(wildcard include/config/X86_MEM_ENCRYPT) \
  /root/kernel-ark-os-build/include/linux/init.h \
    $(wildcard include/config/HAVE_ARCH_PREL32_RELOCATIONS) \
    $(wildcard include/config/STRICT_KERNEL_RWX) \
    $(wildcard include/config/STRICT_MODULE_RWX) \
    $(wildcard include/config/LTO_CLANG) \
  /root/kernel-ark-os-build/include/linux/cc_platform.h \
    $(wildcard include/config/ARCH_HAS_CC_PLATFORM) \
  /root/kernel-ark-os-build/arch/x86/include/uapi/asm/bootparam.h \
  /root/kernel-ark-os-build/include/linux/screen_info.h \
  /root/kernel-ark-os-build/include/uapi/linux/screen_info.h \
  /root/kernel-ark-os-build/include/linux/apm_bios.h \
  /root/kernel-ark-os-build/include/uapi/linux/apm_bios.h \
  /root/kernel-ark-os-build/include/uapi/linux/ioctl.h \
  arch/x86/include/generated/uapi/asm/ioctl.h \
  /root/kernel-ark-os-build/include/asm-generic/ioctl.h \
  /root/kernel-ark-os-build/include/uapi/asm-generic/ioctl.h \
  /root/kernel-ark-os-build/include/linux/edd.h \
  /root/kernel-ark-os-build/include/uapi/linux/edd.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/ist.h \
  /root/kernel-ark-os-build/arch/x86/include/uapi/asm/ist.h \
  /root/kernel-ark-os-build/include/video/edid.h \
    $(wildcard include/config/X86) \
  /root/kernel-ark-os-build/include/uapi/video/edid.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/math_emu.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/ptrace.h \
    $(wildcard include/config/PARAVIRT) \
    $(wildcard include/config/IA32_EMULATION) \
  /root/kernel-ark-os-build/arch/x86/include/asm/segment.h \
    $(wildcard include/config/XEN_PV) \
  /root/kernel-ark-os-build/arch/x86/include/asm/page_types.h \
    $(wildcard include/config/PHYSICAL_START) \
    $(wildcard include/config/PHYSICAL_ALIGN) \
    $(wildcard include/config/DYNAMIC_PHYSICAL_MASK) \
  /root/kernel-ark-os-build/arch/x86/include/asm/page_64_types.h \
    $(wildcard include/config/KASAN) \
    $(wildcard include/config/DYNAMIC_MEMORY_LAYOUT) \
    $(wildcard include/config/X86_5LEVEL) \
    $(wildcard include/config/RANDOMIZE_BASE) \
  /root/kernel-ark-os-build/arch/x86/include/asm/kaslr.h \
    $(wildcard include/config/RANDOMIZE_MEMORY) \
  /root/kernel-ark-os-build/arch/x86/include/uapi/asm/ptrace.h \
  /root/kernel-ark-os-build/arch/x86/include/uapi/asm/ptrace-abi.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/paravirt_types.h \
    $(wildcard include/config/PGTABLE_LEVELS) \
    $(wildcard include/config/ZERO_CALL_USED_REGS) \
    $(wildcard include/config/PARAVIRT_DEBUG) \
  /root/kernel-ark-os-build/arch/x86/include/asm/desc_defs.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/pgtable_types.h \
    $(wildcard include/config/X86_INTEL_MEMORY_PROTECTION_KEYS) \
    $(wildcard include/config/X86_PAE) \
    $(wildcard include/config/MEM_SOFT_DIRTY) \
    $(wildcard include/config/HAVE_ARCH_USERFAULTFD_WP) \
    $(wildcard include/config/PROC_FS) \
  /root/kernel-ark-os-build/arch/x86/include/asm/pgtable_64_types.h \
    $(wildcard include/config/KMSAN) \
    $(wildcard include/config/DEBUG_KMAP_LOCAL_FORCE_MAP) \
  /root/kernel-ark-os-build/arch/x86/include/asm/sparsemem.h \
    $(wildcard include/config/SPARSEMEM) \
    $(wildcard include/config/NUMA_KEEP_MEMINFO) \
  /root/kernel-ark-os-build/arch/x86/include/asm/nospec-branch.h \
    $(wildcard include/config/CALL_THUNKS_DEBUG) \
    $(wildcard include/config/CALL_DEPTH_TRACKING) \
    $(wildcard include/config/NOINSTR_VALIDATION) \
    $(wildcard include/config/CPU_UNRET_ENTRY) \
    $(wildcard include/config/CPU_SRSO) \
    $(wildcard include/config/CPU_IBPB_ENTRY) \
  /root/kernel-ark-os-build/include/linux/static_key.h \
  /root/kernel-ark-os-build/include/linux/jump_label.h \
    $(wildcard include/config/HAVE_ARCH_JUMP_LABEL_RELATIVE) \
  /root/kernel-ark-os-build/arch/x86/include/asm/jump_label.h \
    $(wildcard include/config/HAVE_JUMP_LABEL_HACK) \
  /root/kernel-ark-os-build/include/linux/objtool.h \
    $(wildcard include/config/FRAME_POINTER) \
  /root/kernel-ark-os-build/include/linux/objtool_types.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/cpufeatures.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/required-features.h \
    $(wildcard include/config/X86_MINIMUM_CPU_FAMILY) \
    $(wildcard include/config/MATH_EMULATION) \
    $(wildcard include/config/X86_CMPXCHG64) \
    $(wildcard include/config/X86_CMOV) \
    $(wildcard include/config/X86_P6_NOP) \
    $(wildcard include/config/MATOM) \
  /root/kernel-ark-os-build/arch/x86/include/asm/disabled-features.h \
    $(wildcard include/config/X86_UMIP) \
    $(wildcard include/config/ADDRESS_MASKING) \
    $(wildcard include/config/INTEL_IOMMU_SVM) \
    $(wildcard include/config/X86_SGX) \
    $(wildcard include/config/INTEL_TDX_GUEST) \
  /root/kernel-ark-os-build/arch/x86/include/asm/msr-index.h \
  /root/kernel-ark-os-build/include/linux/bits.h \
  /root/kernel-ark-os-build/include/vdso/bits.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/unwind_hints.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/orc_types.h \
  /root/kernel-ark-os-build/arch/x86/include/uapi/asm/byteorder.h \
  /root/kernel-ark-os-build/include/linux/byteorder/little_endian.h \
  /root/kernel-ark-os-build/include/uapi/linux/byteorder/little_endian.h \
  /root/kernel-ark-os-build/include/linux/swab.h \
  /root/kernel-ark-os-build/include/uapi/linux/swab.h \
  /root/kernel-ark-os-build/arch/x86/include/uapi/asm/swab.h \
  /root/kernel-ark-os-build/include/linux/byteorder/generic.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/percpu.h \
    $(wildcard include/config/X86_64_SMP) \
  /root/kernel-ark-os-build/include/linux/kernel.h \
    $(wildcard include/config/PREEMPT_VOLUNTARY_BUILD) \
    $(wildcard include/config/PREEMPT_DYNAMIC) \
    $(wildcard include/config/HAVE_PREEMPT_DYNAMIC_CALL) \
    $(wildcard include/config/HAVE_PREEMPT_DYNAMIC_KEY) \
    $(wildcard include/config/PREEMPT_) \
    $(wildcard include/config/DEBUG_ATOMIC_SLEEP) \
    $(wildcard include/config/MMU) \
    $(wildcard include/config/PROVE_LOCKING) \
  /root/kernel-ark-os-build/include/linux/stdarg.h \
  /root/kernel-ark-os-build/include/linux/align.h \
  /root/kernel-ark-os-build/include/linux/array_size.h \
  /root/kernel-ark-os-build/include/linux/limits.h \
  /root/kernel-ark-os-build/include/uapi/linux/limits.h \
  /root/kernel-ark-os-build/include/vdso/limits.h \
  /root/kernel-ark-os-build/include/linux/bitops.h \
  /root/kernel-ark-os-build/include/linux/typecheck.h \
  /root/kernel-ark-os-build/include/asm-generic/bitops/generic-non-atomic.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/bitops.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/rmwcc.h \
  /root/kernel-ark-os-build/include/linux/args.h \
  /root/kernel-ark-os-build/include/asm-generic/bitops/sched.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/arch_hweight.h \
  /root/kernel-ark-os-build/include/asm-generic/bitops/const_hweight.h \
  /root/kernel-ark-os-build/include/asm-generic/bitops/instrumented-atomic.h \
  /root/kernel-ark-os-build/include/linux/instrumented.h \
  /root/kernel-ark-os-build/include/linux/kmsan-checks.h \
  /root/kernel-ark-os-build/include/asm-generic/bitops/instrumented-non-atomic.h \
    $(wildcard include/config/KCSAN_ASSUME_PLAIN_WRITES_ATOMIC) \
  /root/kernel-ark-os-build/include/asm-generic/bitops/instrumented-lock.h \
  /root/kernel-ark-os-build/include/asm-generic/bitops/le.h \
  /root/kernel-ark-os-build/include/asm-generic/bitops/ext2-atomic-setbit.h \
  /root/kernel-ark-os-build/include/linux/hex.h \
  /root/kernel-ark-os-build/include/linux/kstrtox.h \
  /root/kernel-ark-os-build/include/linux/log2.h \
    $(wildcard include/config/ARCH_HAS_ILOG2_U32) \
    $(wildcard include/config/ARCH_HAS_ILOG2_U64) \
  /root/kernel-ark-os-build/include/linux/minmax.h \
  /root/kernel-ark-os-build/include/linux/panic.h \
    $(wildcard include/config/PANIC_TIMEOUT) \
  /root/kernel-ark-os-build/include/linux/printk.h \
    $(wildcard include/config/MESSAGE_LOGLEVEL_DEFAULT) \
    $(wildcard include/config/CONSOLE_LOGLEVEL_DEFAULT) \
    $(wildcard include/config/CONSOLE_LOGLEVEL_QUIET) \
    $(wildcard include/config/EARLY_PRINTK) \
    $(wildcard include/config/PRINTK) \
    $(wildcard include/config/DYNAMIC_DEBUG) \
  /root/kernel-ark-os-build/include/linux/kern_levels.h \
  /root/kernel-ark-os-build/include/linux/ratelimit_types.h \
  /root/kernel-ark-os-build/include/linux/spinlock_types_raw.h \
    $(wildcard include/config/DEBUG_SPINLOCK) \
    $(wildcard include/config/DEBUG_LOCK_ALLOC) \
  /root/kernel-ark-os-build/arch/x86/include/asm/spinlock_types.h \
  /root/kernel-ark-os-build/include/asm-generic/qspinlock_types.h \
    $(wildcard include/config/NR_CPUS) \
  /root/kernel-ark-os-build/include/asm-generic/qrwlock_types.h \
  /root/kernel-ark-os-build/include/linux/lockdep_types.h \
    $(wildcard include/config/PROVE_RAW_LOCK_NESTING) \
    $(wildcard include/config/LOCKDEP) \
    $(wildcard include/config/LOCK_STAT) \
  /root/kernel-ark-os-build/include/linux/once_lite.h \
  /root/kernel-ark-os-build/include/linux/dynamic_debug.h \
  /root/kernel-ark-os-build/include/linux/sprintf.h \
  /root/kernel-ark-os-build/include/linux/static_call_types.h \
    $(wildcard include/config/HAVE_STATIC_CALL) \
  /root/kernel-ark-os-build/include/linux/instruction_pointer.h \
  /root/kernel-ark-os-build/include/asm-generic/percpu.h \
    $(wildcard include/config/DEBUG_PREEMPT) \
    $(wildcard include/config/HAVE_SETUP_PER_CPU_AREA) \
  /root/kernel-ark-os-build/include/linux/threads.h \
    $(wildcard include/config/BASE_SMALL) \
  /root/kernel-ark-os-build/include/linux/percpu-defs.h \
    $(wildcard include/config/DEBUG_FORCE_WEAK_PER_CPU) \
  /root/kernel-ark-os-build/arch/x86/include/asm/current.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/asm-offsets.h \
  include/generated/asm-offsets.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/GEN-for-each-reg.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/proto.h \
  /root/kernel-ark-os-build/arch/x86/include/uapi/asm/ldt.h \
  /root/kernel-ark-os-build/arch/x86/include/uapi/asm/sigcontext.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/cpuid.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/string.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/string_64.h \
    $(wildcard include/config/ARCH_HAS_UACCESS_FLUSHCACHE) \
  /root/kernel-ark-os-build/arch/x86/include/asm/paravirt.h \
    $(wildcard include/config/PARAVIRT_SPINLOCKS) \
    $(wildcard include/config/DEBUG_ENTRY) \
  /root/kernel-ark-os-build/include/linux/bug.h \
    $(wildcard include/config/BUG_ON_DATA_CORRUPTION) \
  /root/kernel-ark-os-build/arch/x86/include/asm/bug.h \
    $(wildcard include/config/DEBUG_BUGVERBOSE) \
  /root/kernel-ark-os-build/include/linux/instrumentation.h \
  /root/kernel-ark-os-build/include/asm-generic/bug.h \
    $(wildcard include/config/BUG) \
    $(wildcard include/config/GENERIC_BUG_RELATIVE_POINTERS) \
  /root/kernel-ark-os-build/include/linux/cpumask.h \
    $(wildcard include/config/FORCE_NR_CPUS) \
    $(wildcard include/config/HOTPLUG_CPU) \
    $(wildcard include/config/DEBUG_PER_CPU_MAPS) \
    $(wildcard include/config/CPUMASK_OFFSTACK) \
  /root/kernel-ark-os-build/include/linux/bitmap.h \
  /root/kernel-ark-os-build/include/linux/errno.h \
  /root/kernel-ark-os-build/include/uapi/linux/errno.h \
  arch/x86/include/generated/uapi/asm/errno.h \
  /root/kernel-ark-os-build/include/uapi/asm-generic/errno.h \
  /root/kernel-ark-os-build/include/uapi/asm-generic/errno-base.h \
  /root/kernel-ark-os-build/include/linux/find.h \
  /root/kernel-ark-os-build/include/linux/string.h \
    $(wildcard include/config/BINARY_PRINTF) \
    $(wildcard include/config/FORTIFY_SOURCE) \
  /root/kernel-ark-os-build/include/linux/err.h \
  /root/kernel-ark-os-build/include/linux/overflow.h \
  /root/kernel-ark-os-build/include/uapi/linux/string.h \
  /root/kernel-ark-os-build/include/linux/fortify-string.h \
  /root/kernel-ark-os-build/include/linux/bitmap-str.h \
  /root/kernel-ark-os-build/include/linux/atomic.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/atomic.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/cmpxchg.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/cmpxchg_64.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/atomic64_64.h \
  /root/kernel-ark-os-build/include/linux/atomic/atomic-arch-fallback.h \
    $(wildcard include/config/GENERIC_ATOMIC64) \
  /root/kernel-ark-os-build/include/linux/atomic/atomic-long.h \
  /root/kernel-ark-os-build/include/linux/atomic/atomic-instrumented.h \
  /root/kernel-ark-os-build/include/linux/gfp_types.h \
    $(wildcard include/config/KASAN_HW_TAGS) \
  /root/kernel-ark-os-build/include/linux/numa.h \
    $(wildcard include/config/NODES_SHIFT) \
    $(wildcard include/config/NUMA) \
    $(wildcard include/config/HAVE_ARCH_NODE_DEV_GROUP) \
  /root/kernel-ark-os-build/arch/x86/include/asm/frame.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/page.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/page_64.h \
    $(wildcard include/config/DEBUG_VIRTUAL) \
    $(wildcard include/config/X86_VSYSCALL_EMULATION) \
  /root/kernel-ark-os-build/include/linux/range.h \
  /root/kernel-ark-os-build/include/asm-generic/memory_model.h \
    $(wildcard include/config/FLATMEM) \
    $(wildcard include/config/SPARSEMEM_VMEMMAP) \
  /root/kernel-ark-os-build/include/linux/pfn.h \
  /root/kernel-ark-os-build/include/asm-generic/getorder.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/msr.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/cpumask.h \
  /root/kernel-ark-os-build/arch/x86/include/uapi/asm/msr.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/shared/msr.h \
  /root/kernel-ark-os-build/include/linux/tracepoint-defs.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/special_insns.h \
  /root/kernel-ark-os-build/include/linux/irqflags.h \
    $(wildcard include/config/TRACE_IRQFLAGS) \
    $(wildcard include/config/PREEMPT_RT) \
    $(wildcard include/config/IRQSOFF_TRACER) \
    $(wildcard include/config/PREEMPT_TRACER) \
    $(wildcard include/config/DEBUG_IRQFLAGS) \
    $(wildcard include/config/TRACE_IRQFLAGS_SUPPORT) \
  /root/kernel-ark-os-build/include/linux/cleanup.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/irqflags.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/fpu/types.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/vmxfeatures.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/vdso/processor.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/shstk.h \
  /root/kernel-ark-os-build/include/linux/personality.h \
  /root/kernel-ark-os-build/include/uapi/linux/personality.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/tsc.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/cpufeature.h \
  /root/kernel-ark-os-build/include/vdso/time32.h \
  /root/kernel-ark-os-build/include/vdso/time.h \
  /root/kernel-ark-os-build/include/linux/uidgid.h \
    $(wildcard include/config/MULTIUSER) \
    $(wildcard include/config/USER_NS) \
  /root/kernel-ark-os-build/include/linux/highuid.h \
  /root/kernel-ark-os-build/include/linux/buildid.h \
    $(wildcard include/config/CRASH_CORE) \
  /root/kernel-ark-os-build/include/linux/kmod.h \
  /root/kernel-ark-os-build/include/linux/umh.h \
  /root/kernel-ark-os-build/include/linux/gfp.h \
    $(wildcard include/config/HIGHMEM) \
    $(wildcard include/config/ZONE_DMA) \
    $(wildcard include/config/ZONE_DMA32) \
    $(wildcard include/config/ZONE_DEVICE) \
    $(wildcard include/config/CONTIG_ALLOC) \
  /root/kernel-ark-os-build/include/linux/mmzone.h \
    $(wildcard include/config/ARCH_FORCE_MAX_ORDER) \
    $(wildcard include/config/CMA) \
    $(wildcard include/config/MEMORY_ISOLATION) \
    $(wildcard include/config/ZSMALLOC) \
    $(wildcard include/config/UNACCEPTED_MEMORY) \
    $(wildcard include/config/SWAP) \
    $(wildcard include/config/NUMA_BALANCING) \
    $(wildcard include/config/TRANSPARENT_HUGEPAGE) \
    $(wildcard include/config/LRU_GEN) \
    $(wildcard include/config/LRU_GEN_STATS) \
    $(wildcard include/config/MEMCG) \
    $(wildcard include/config/MEMORY_HOTPLUG) \
    $(wildcard include/config/COMPACTION) \
    $(wildcard include/config/MEMORY_FAILURE) \
    $(wildcard include/config/PAGE_EXTENSION) \
    $(wildcard include/config/DEFERRED_STRUCT_PAGE_INIT) \
    $(wildcard include/config/HAVE_MEMORYLESS_NODES) \
    $(wildcard include/config/SPARSEMEM_EXTREME) \
    $(wildcard include/config/HAVE_ARCH_PFN_VALID) \
  /root/kernel-ark-os-build/include/linux/spinlock.h \
    $(wildcard include/config/PREEMPTION) \
  /root/kernel-ark-os-build/include/linux/preempt.h \
    $(wildcard include/config/PREEMPT_COUNT) \
    $(wildcard include/config/TRACE_PREEMPT_TOGGLE) \
    $(wildcard include/config/PREEMPT_NOTIFIERS) \
  /root/kernel-ark-os-build/arch/x86/include/asm/preempt.h \
  /root/kernel-ark-os-build/include/linux/thread_info.h \
    $(wildcard include/config/THREAD_INFO_IN_TASK) \
    $(wildcard include/config/GENERIC_ENTRY) \
    $(wildcard include/config/HAVE_ARCH_WITHIN_STACK_FRAMES) \
    $(wildcard include/config/HARDENED_USERCOPY) \
    $(wildcard include/config/SH) \
  /root/kernel-ark-os-build/include/linux/restart_block.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/thread_info.h \
    $(wildcard include/config/COMPAT) \
  /root/kernel-ark-os-build/include/linux/bottom_half.h \
  /root/kernel-ark-os-build/include/linux/lockdep.h \
    $(wildcard include/config/DEBUG_LOCKING_API_SELFTESTS) \
  /root/kernel-ark-os-build/include/linux/smp.h \
    $(wildcard include/config/UP_LATE_INIT) \
  /root/kernel-ark-os-build/include/linux/smp_types.h \
  /root/kernel-ark-os-build/include/linux/llist.h \
    $(wildcard include/config/ARCH_HAVE_NMI_SAFE_CMPXCHG) \
  /root/kernel-ark-os-build/arch/x86/include/asm/smp.h \
    $(wildcard include/config/DEBUG_NMI_SELFTEST) \
  /root/kernel-ark-os-build/include/linux/debug_locks.h \
  /root/kernel-ark-os-build/include/linux/stacktrace.h \
    $(wildcard include/config/ARCH_STACKWALK) \
    $(wildcard include/config/STACKTRACE) \
    $(wildcard include/config/HAVE_RELIABLE_STACKTRACE) \
  arch/x86/include/generated/asm/mmiowb.h \
  /root/kernel-ark-os-build/include/asm-generic/mmiowb.h \
    $(wildcard include/config/MMIOWB) \
  /root/kernel-ark-os-build/include/linux/spinlock_types.h \
  /root/kernel-ark-os-build/include/linux/rwlock_types.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/spinlock.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/qspinlock.h \
  /root/kernel-ark-os-build/include/asm-generic/qspinlock.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/qrwlock.h \
  /root/kernel-ark-os-build/include/asm-generic/qrwlock.h \
  /root/kernel-ark-os-build/include/linux/rwlock.h \
    $(wildcard include/config/PREEMPT) \
  /root/kernel-ark-os-build/include/linux/spinlock_api_smp.h \
    $(wildcard include/config/INLINE_SPIN_LOCK) \
    $(wildcard include/config/INLINE_SPIN_LOCK_BH) \
    $(wildcard include/config/INLINE_SPIN_LOCK_IRQ) \
    $(wildcard include/config/INLINE_SPIN_LOCK_IRQSAVE) \
    $(wildcard include/config/INLINE_SPIN_TRYLOCK) \
    $(wildcard include/config/INLINE_SPIN_TRYLOCK_BH) \
    $(wildcard include/config/UNINLINE_SPIN_UNLOCK) \
    $(wildcard include/config/INLINE_SPIN_UNLOCK_BH) \
    $(wildcard include/config/INLINE_SPIN_UNLOCK_IRQ) \
    $(wildcard include/config/INLINE_SPIN_UNLOCK_IRQRESTORE) \
    $(wildcard include/config/GENERIC_LOCKBREAK) \
  /root/kernel-ark-os-build/include/linux/rwlock_api_smp.h \
    $(wildcard include/config/INLINE_READ_LOCK) \
    $(wildcard include/config/INLINE_WRITE_LOCK) \
    $(wildcard include/config/INLINE_READ_LOCK_BH) \
    $(wildcard include/config/INLINE_WRITE_LOCK_BH) \
    $(wildcard include/config/INLINE_READ_LOCK_IRQ) \
    $(wildcard include/config/INLINE_WRITE_LOCK_IRQ) \
    $(wildcard include/config/INLINE_READ_LOCK_IRQSAVE) \
    $(wildcard include/config/INLINE_WRITE_LOCK_IRQSAVE) \
    $(wildcard include/config/INLINE_READ_TRYLOCK) \
    $(wildcard include/config/INLINE_WRITE_TRYLOCK) \
    $(wildcard include/config/INLINE_READ_UNLOCK) \
    $(wildcard include/config/INLINE_WRITE_UNLOCK) \
    $(wildcard include/config/INLINE_READ_UNLOCK_BH) \
    $(wildcard include/config/INLINE_WRITE_UNLOCK_BH) \
    $(wildcard include/config/INLINE_READ_UNLOCK_IRQ) \
    $(wildcard include/config/INLINE_WRITE_UNLOCK_IRQ) \
    $(wildcard include/config/INLINE_READ_UNLOCK_IRQRESTORE) \
    $(wildcard include/config/INLINE_WRITE_UNLOCK_IRQRESTORE) \
  /root/kernel-ark-os-build/include/linux/list_nulls.h \
  /root/kernel-ark-os-build/include/linux/wait.h \
  /root/kernel-ark-os-build/include/uapi/linux/wait.h \
  /root/kernel-ark-os-build/include/linux/seqlock.h \
  /root/kernel-ark-os-build/include/linux/mutex.h \
    $(wildcard include/config/MUTEX_SPIN_ON_OWNER) \
    $(wildcard include/config/DEBUG_MUTEXES) \
  /root/kernel-ark-os-build/include/linux/osq_lock.h \
  /root/kernel-ark-os-build/include/linux/nodemask.h \
  /root/kernel-ark-os-build/include/linux/random.h \
    $(wildcard include/config/VMGENID) \
  /root/kernel-ark-os-build/include/uapi/linux/random.h \
  /root/kernel-ark-os-build/include/linux/irqnr.h \
  /root/kernel-ark-os-build/include/uapi/linux/irqnr.h \
  /root/kernel-ark-os-build/include/linux/prandom.h \
  /root/kernel-ark-os-build/include/linux/once.h \
  /root/kernel-ark-os-build/include/linux/percpu.h \
    $(wildcard include/config/RANDOM_KMALLOC_CACHES) \
    $(wildcard include/config/NEED_PER_CPU_PAGE_FIRST_CHUNK) \
  /root/kernel-ark-os-build/include/linux/mmdebug.h \
    $(wildcard include/config/DEBUG_VM) \
    $(wildcard include/config/DEBUG_VM_IRQSOFF) \
    $(wildcard include/config/DEBUG_VM_PGFLAGS) \
  /root/kernel-ark-os-build/include/linux/pageblock-flags.h \
    $(wildcard include/config/HUGETLB_PAGE) \
    $(wildcard include/config/HUGETLB_PAGE_SIZE_VARIABLE) \
  /root/kernel-ark-os-build/include/linux/page-flags-layout.h \
  include/generated/bounds.h \
  /root/kernel-ark-os-build/include/linux/mm_types.h \
    $(wildcard include/config/HAVE_ALIGNED_STRUCT_PAGE) \
    $(wildcard include/config/USERFAULTFD) \
    $(wildcard include/config/ANON_VMA_NAME) \
    $(wildcard include/config/PER_VMA_LOCK) \
    $(wildcard include/config/SCHED_MM_CID) \
    $(wildcard include/config/HAVE_ARCH_COMPAT_MMAP_BASES) \
    $(wildcard include/config/MEMBARRIER) \
    $(wildcard include/config/AIO) \
    $(wildcard include/config/MMU_NOTIFIER) \
    $(wildcard include/config/ARCH_WANT_BATCHED_UNMAP_TLB_FLUSH) \
    $(wildcard include/config/IOMMU_SVA) \
    $(wildcard include/config/KSM) \
  /root/kernel-ark-os-build/include/linux/mm_types_task.h \
    $(wildcard include/config/SPLIT_PTLOCK_CPUS) \
    $(wildcard include/config/ARCH_ENABLE_SPLIT_PMD_PTLOCK) \
  /root/kernel-ark-os-build/arch/x86/include/asm/tlbbatch.h \
  /root/kernel-ark-os-build/include/linux/auxvec.h \
  /root/kernel-ark-os-build/include/uapi/linux/auxvec.h \
  /root/kernel-ark-os-build/arch/x86/include/uapi/asm/auxvec.h \
  /root/kernel-ark-os-build/include/linux/kref.h \
  /root/kernel-ark-os-build/include/linux/refcount.h \
  /root/kernel-ark-os-build/include/linux/rbtree.h \
  /root/kernel-ark-os-build/include/linux/rbtree_types.h \
  /root/kernel-ark-os-build/include/linux/rcupdate.h \
    $(wildcard include/config/PREEMPT_RCU) \
    $(wildcard include/config/TINY_RCU) \
    $(wildcard include/config/RCU_STRICT_GRACE_PERIOD) \
    $(wildcard include/config/RCU_LAZY) \
    $(wildcard include/config/TASKS_RCU_GENERIC) \
    $(wildcard include/config/RCU_STALL_COMMON) \
    $(wildcard include/config/NO_HZ_FULL) \
    $(wildcard include/config/KVM_XFER_TO_GUEST_WORK) \
    $(wildcard include/config/RCU_NOCB_CPU) \
    $(wildcard include/config/TASKS_RCU) \
    $(wildcard include/config/TASKS_TRACE_RCU) \
    $(wildcard include/config/TASKS_RUDE_RCU) \
    $(wildcard include/config/TREE_RCU) \
    $(wildcard include/config/DEBUG_OBJECTS_RCU_HEAD) \
    $(wildcard include/config/PROVE_RCU) \
    $(wildcard include/config/ARCH_WEAK_RELEASE_ACQUIRE) \
  /root/kernel-ark-os-build/include/linux/context_tracking_irq.h \
    $(wildcard include/config/CONTEXT_TRACKING_IDLE) \
  /root/kernel-ark-os-build/include/linux/rcutree.h \
  /root/kernel-ark-os-build/include/linux/maple_tree.h \
    $(wildcard include/config/MAPLE_RCU_DISABLED) \
    $(wildcard include/config/DEBUG_MAPLE_TREE) \
  /root/kernel-ark-os-build/include/linux/rwsem.h \
    $(wildcard include/config/RWSEM_SPIN_ON_OWNER) \
    $(wildcard include/config/DEBUG_RWSEMS) \
  /root/kernel-ark-os-build/include/linux/completion.h \
  /root/kernel-ark-os-build/include/linux/swait.h \
  /root/kernel-ark-os-build/include/linux/uprobes.h \
    $(wildcard include/config/UPROBES) \
  /root/kernel-ark-os-build/arch/x86/include/asm/uprobes.h \
  /root/kernel-ark-os-build/include/linux/notifier.h \
  /root/kernel-ark-os-build/include/linux/srcu.h \
    $(wildcard include/config/TINY_SRCU) \
    $(wildcard include/config/NEED_SRCU_NMI_SAFE) \
  /root/kernel-ark-os-build/include/linux/workqueue.h \
    $(wildcard include/config/DEBUG_OBJECTS_WORK) \
    $(wildcard include/config/FREEZER) \
    $(wildcard include/config/WQ_WATCHDOG) \
  /root/kernel-ark-os-build/include/linux/timer.h \
    $(wildcard include/config/DEBUG_OBJECTS_TIMERS) \
  /root/kernel-ark-os-build/include/linux/ktime.h \
  /root/kernel-ark-os-build/include/linux/jiffies.h \
  /root/kernel-ark-os-build/include/vdso/jiffies.h \
  include/generated/timeconst.h \
  /root/kernel-ark-os-build/include/vdso/ktime.h \
  /root/kernel-ark-os-build/include/linux/timekeeping.h \
    $(wildcard include/config/GENERIC_CMOS_UPDATE) \
  /root/kernel-ark-os-build/include/linux/clocksource_ids.h \
  /root/kernel-ark-os-build/include/linux/debugobjects.h \
    $(wildcard include/config/DEBUG_OBJECTS) \
    $(wildcard include/config/DEBUG_OBJECTS_FREE) \
  /root/kernel-ark-os-build/include/linux/rcu_segcblist.h \
  /root/kernel-ark-os-build/include/linux/srcutree.h \
  /root/kernel-ark-os-build/include/linux/rcu_node_tree.h \
    $(wildcard include/config/RCU_FANOUT) \
    $(wildcard include/config/RCU_FANOUT_LEAF) \
  /root/kernel-ark-os-build/include/linux/percpu_counter.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/mmu.h \
    $(wildcard include/config/MODIFY_LDT_SYSCALL) \
  /root/kernel-ark-os-build/include/linux/page-flags.h \
    $(wildcard include/config/ARCH_USES_PG_UNCACHED) \
    $(wildcard include/config/PAGE_IDLE_FLAG) \
    $(wildcard include/config/ARCH_USES_PG_ARCH_X) \
    $(wildcard include/config/HUGETLB_PAGE_OPTIMIZE_VMEMMAP) \
  /root/kernel-ark-os-build/include/linux/local_lock.h \
  /root/kernel-ark-os-build/include/linux/local_lock_internal.h \
  /root/kernel-ark-os-build/include/linux/memory_hotplug.h \
    $(wildcard include/config/HAVE_ARCH_NODEDATA_EXTENSION) \
    $(wildcard include/config/ARCH_HAS_ADD_PAGES) \
    $(wildcard include/config/MEMORY_HOTREMOVE) \
  /root/kernel-ark-os-build/arch/x86/include/asm/mmzone.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/mmzone_64.h \
  /root/kernel-ark-os-build/include/linux/topology.h \
    $(wildcard include/config/USE_PERCPU_NUMA_NODE_ID) \
    $(wildcard include/config/SCHED_SMT) \
  /root/kernel-ark-os-build/include/linux/arch_topology.h \
    $(wildcard include/config/ACPI_CPPC_LIB) \
    $(wildcard include/config/GENERIC_ARCH_TOPOLOGY) \
  /root/kernel-ark-os-build/arch/x86/include/asm/topology.h \
    $(wildcard include/config/SCHED_MC_PRIO) \
  /root/kernel-ark-os-build/arch/x86/include/asm/mpspec.h \
    $(wildcard include/config/EISA) \
    $(wildcard include/config/X86_LOCAL_APIC) \
    $(wildcard include/config/X86_MPPARSE) \
  /root/kernel-ark-os-build/arch/x86/include/asm/mpspec_def.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/x86_init.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/apicdef.h \
  /root/kernel-ark-os-build/include/asm-generic/topology.h \
  /root/kernel-ark-os-build/include/linux/cpu_smt.h \
    $(wildcard include/config/HOTPLUG_SMT) \
  /root/kernel-ark-os-build/include/linux/sysctl.h \
    $(wildcard include/config/SYSCTL) \
  /root/kernel-ark-os-build/include/uapi/linux/sysctl.h \
  /root/kernel-ark-os-build/include/linux/elf.h \
    $(wildcard include/config/ARCH_USE_GNU_PROPERTY) \
    $(wildcard include/config/ARCH_HAVE_ELF_PROT) \
  /root/kernel-ark-os-build/arch/x86/include/asm/elf.h \
    $(wildcard include/config/X86_X32_ABI) \
  /root/kernel-ark-os-build/arch/x86/include/asm/ia32.h \
  /root/kernel-ark-os-build/include/linux/compat.h \
    $(wildcard include/config/ARCH_HAS_SYSCALL_WRAPPER) \
    $(wildcard include/config/COMPAT_OLD_SIGACTION) \
    $(wildcard include/config/ODD_RT_SIGACTION) \
  /root/kernel-ark-os-build/include/linux/sem.h \
    $(wildcard include/config/SYSVIPC) \
  /root/kernel-ark-os-build/include/uapi/linux/sem.h \
  /root/kernel-ark-os-build/include/linux/ipc.h \
  /root/kernel-ark-os-build/include/linux/rhashtable-types.h \
  /root/kernel-ark-os-build/include/uapi/linux/ipc.h \
  arch/x86/include/generated/uapi/asm/ipcbuf.h \
  /root/kernel-ark-os-build/include/uapi/asm-generic/ipcbuf.h \
  /root/kernel-ark-os-build/arch/x86/include/uapi/asm/sembuf.h \
  /root/kernel-ark-os-build/include/linux/socket.h \
  arch/x86/include/generated/uapi/asm/socket.h \
  /root/kernel-ark-os-build/include/uapi/asm-generic/socket.h \
  arch/x86/include/generated/uapi/asm/sockios.h \
  /root/kernel-ark-os-build/include/uapi/asm-generic/sockios.h \
  /root/kernel-ark-os-build/include/uapi/linux/sockios.h \
  /root/kernel-ark-os-build/include/linux/uio.h \
    $(wildcard include/config/ARCH_HAS_COPY_MC) \
  /root/kernel-ark-os-build/include/uapi/linux/uio.h \
  /root/kernel-ark-os-build/include/uapi/linux/socket.h \
  /root/kernel-ark-os-build/include/uapi/linux/if.h \
  /root/kernel-ark-os-build/include/uapi/linux/libc-compat.h \
  /root/kernel-ark-os-build/include/uapi/linux/hdlc/ioctl.h \
  /root/kernel-ark-os-build/include/linux/fs.h \
    $(wildcard include/config/READ_ONLY_THP_FOR_FS) \
    $(wildcard include/config/FS_POSIX_ACL) \
    $(wildcard include/config/SECURITY) \
    $(wildcard include/config/CGROUP_WRITEBACK) \
    $(wildcard include/config/IMA) \
    $(wildcard include/config/FILE_LOCKING) \
    $(wildcard include/config/FSNOTIFY) \
    $(wildcard include/config/FS_ENCRYPTION) \
    $(wildcard include/config/FS_VERITY) \
    $(wildcard include/config/EPOLL) \
    $(wildcard include/config/UNICODE) \
    $(wildcard include/config/QUOTA) \
    $(wildcard include/config/FS_DAX) \
    $(wildcard include/config/BLOCK) \
  /root/kernel-ark-os-build/include/linux/wait_bit.h \
  /root/kernel-ark-os-build/include/linux/kdev_t.h \
  /root/kernel-ark-os-build/include/uapi/linux/kdev_t.h \
  /root/kernel-ark-os-build/include/linux/dcache.h \
  /root/kernel-ark-os-build/include/linux/rculist.h \
    $(wildcard include/config/PROVE_RCU_LIST) \
  /root/kernel-ark-os-build/include/linux/rculist_bl.h \
  /root/kernel-ark-os-build/include/linux/list_bl.h \
  /root/kernel-ark-os-build/include/linux/bit_spinlock.h \
  /root/kernel-ark-os-build/include/linux/lockref.h \
    $(wildcard include/config/ARCH_USE_CMPXCHG_LOCKREF) \
  /root/kernel-ark-os-build/include/linux/stringhash.h \
    $(wildcard include/config/DCACHE_WORD_ACCESS) \
  /root/kernel-ark-os-build/include/linux/hash.h \
    $(wildcard include/config/HAVE_ARCH_HASH) \
  /root/kernel-ark-os-build/include/linux/path.h \
  /root/kernel-ark-os-build/include/linux/list_lru.h \
    $(wildcard include/config/MEMCG_KMEM) \
  /root/kernel-ark-os-build/include/linux/shrinker.h \
    $(wildcard include/config/SHRINKER_DEBUG) \
  /root/kernel-ark-os-build/include/linux/xarray.h \
    $(wildcard include/config/XARRAY_MULTI) \
  /root/kernel-ark-os-build/include/linux/sched/mm.h \
    $(wildcard include/config/MMU_LAZY_TLB_REFCOUNT) \
    $(wildcard include/config/ARCH_HAS_MEMBARRIER_CALLBACKS) \
  /root/kernel-ark-os-build/include/linux/sched.h \
    $(wildcard include/config/VIRT_CPU_ACCOUNTING_NATIVE) \
    $(wildcard include/config/SCHED_INFO) \
    $(wildcard include/config/SCHEDSTATS) \
    $(wildcard include/config/SCHED_CORE) \
    $(wildcard include/config/FAIR_GROUP_SCHED) \
    $(wildcard include/config/RT_GROUP_SCHED) \
    $(wildcard include/config/RT_MUTEXES) \
    $(wildcard include/config/UCLAMP_TASK) \
    $(wildcard include/config/UCLAMP_BUCKETS_COUNT) \
    $(wildcard include/config/KMAP_LOCAL) \
    $(wildcard include/config/CGROUP_SCHED) \
    $(wildcard include/config/BLK_DEV_IO_TRACE) \
    $(wildcard include/config/COMPAT_BRK) \
    $(wildcard include/config/CGROUPS) \
    $(wildcard include/config/BLK_CGROUP) \
    $(wildcard include/config/PSI) \
    $(wildcard include/config/PAGE_OWNER) \
    $(wildcard include/config/EVENTFD) \
    $(wildcard include/config/CPU_SUP_INTEL) \
    $(wildcard include/config/TASK_DELAY_ACCT) \
    $(wildcard include/config/ARCH_HAS_SCALED_CPUTIME) \
    $(wildcard include/config/VIRT_CPU_ACCOUNTING_GEN) \
    $(wildcard include/config/POSIX_CPUTIMERS) \
    $(wildcard include/config/POSIX_CPU_TIMERS_TASK_WORK) \
    $(wildcard include/config/KEYS) \
    $(wildcard include/config/DETECT_HUNG_TASK) \
    $(wildcard include/config/IO_URING) \
    $(wildcard include/config/AUDIT) \
    $(wildcard include/config/AUDITSYSCALL) \
    $(wildcard include/config/UBSAN) \
    $(wildcard include/config/UBSAN_TRAP) \
    $(wildcard include/config/TASK_XACCT) \
    $(wildcard include/config/CPUSETS) \
    $(wildcard include/config/X86_CPU_RESCTRL) \
    $(wildcard include/config/FUTEX) \
    $(wildcard include/config/PERF_EVENTS) \
    $(wildcard include/config/RSEQ) \
    $(wildcard include/config/FAULT_INJECTION) \
    $(wildcard include/config/LATENCYTOP) \
    $(wildcard include/config/FUNCTION_GRAPH_TRACER) \
    $(wildcard include/config/BCACHE) \
    $(wildcard include/config/VMAP_STACK) \
    $(wildcard include/config/BPF_SYSCALL) \
    $(wildcard include/config/GCC_PLUGIN_STACKLEAK) \
    $(wildcard include/config/X86_MCE) \
    $(wildcard include/config/KRETPROBES) \
    $(wildcard include/config/RETHOOK) \
    $(wildcard include/config/ARCH_HAS_PARANOID_L1D_FLUSH) \
    $(wildcard include/config/RV) \
    $(wildcard include/config/USER_EVENTS) \
    $(wildcard include/config/ARCH_TASK_STRUCT_ON_STACK) \
    $(wildcard include/config/PREEMPT_NONE) \
    $(wildcard include/config/PREEMPT_VOLUNTARY) \
    $(wildcard include/config/DEBUG_RSEQ) \
  /root/kernel-ark-os-build/include/uapi/linux/sched.h \
  /root/kernel-ark-os-build/include/linux/pid.h \
  /root/kernel-ark-os-build/include/linux/shm.h \
  /root/kernel-ark-os-build/include/uapi/linux/shm.h \
  /root/kernel-ark-os-build/include/uapi/asm-generic/hugetlb_encode.h \
  /root/kernel-ark-os-build/arch/x86/include/uapi/asm/shmbuf.h \
  /root/kernel-ark-os-build/include/uapi/asm-generic/shmbuf.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/shmparam.h \
  /root/kernel-ark-os-build/include/linux/kmsan_types.h \
  /root/kernel-ark-os-build/include/linux/plist.h \
    $(wildcard include/config/DEBUG_PLIST) \
  /root/kernel-ark-os-build/include/linux/hrtimer.h \
    $(wildcard include/config/HIGH_RES_TIMERS) \
    $(wildcard include/config/TIME_LOW_RES) \
    $(wildcard include/config/TIMERFD) \
  /root/kernel-ark-os-build/include/linux/hrtimer_defs.h \
  /root/kernel-ark-os-build/include/linux/timerqueue.h \
  /root/kernel-ark-os-build/include/linux/seccomp.h \
    $(wildcard include/config/SECCOMP) \
    $(wildcard include/config/HAVE_ARCH_SECCOMP_FILTER) \
    $(wildcard include/config/SECCOMP_FILTER) \
    $(wildcard include/config/CHECKPOINT_RESTORE) \
    $(wildcard include/config/SECCOMP_CACHE_DEBUG) \
  /root/kernel-ark-os-build/include/uapi/linux/seccomp.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/seccomp.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/unistd.h \
  /root/kernel-ark-os-build/arch/x86/include/uapi/asm/unistd.h \
  arch/x86/include/generated/uapi/asm/unistd_64.h \
  arch/x86/include/generated/asm/unistd_64_x32.h \
  arch/x86/include/generated/asm/unistd_32_ia32.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/ia32_unistd.h \
  /root/kernel-ark-os-build/include/asm-generic/seccomp.h \
  /root/kernel-ark-os-build/include/uapi/linux/unistd.h \
  /root/kernel-ark-os-build/include/linux/resource.h \
  /root/kernel-ark-os-build/include/uapi/linux/resource.h \
  arch/x86/include/generated/uapi/asm/resource.h \
  /root/kernel-ark-os-build/include/asm-generic/resource.h \
  /root/kernel-ark-os-build/include/uapi/asm-generic/resource.h \
  /root/kernel-ark-os-build/include/linux/latencytop.h \
  /root/kernel-ark-os-build/include/linux/sched/prio.h \
  /root/kernel-ark-os-build/include/linux/sched/types.h \
  /root/kernel-ark-os-build/include/linux/signal_types.h \
    $(wildcard include/config/OLD_SIGACTION) \
  /root/kernel-ark-os-build/include/uapi/linux/signal.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/signal.h \
  /root/kernel-ark-os-build/arch/x86/include/uapi/asm/signal.h \
  /root/kernel-ark-os-build/include/uapi/asm-generic/signal-defs.h \
  /root/kernel-ark-os-build/arch/x86/include/uapi/asm/siginfo.h \
  /root/kernel-ark-os-build/include/uapi/asm-generic/siginfo.h \
  /root/kernel-ark-os-build/include/linux/syscall_user_dispatch.h \
  /root/kernel-ark-os-build/include/linux/task_io_accounting.h \
    $(wildcard include/config/TASK_IO_ACCOUNTING) \
  /root/kernel-ark-os-build/include/linux/posix-timers.h \
  /root/kernel-ark-os-build/include/linux/alarmtimer.h \
    $(wildcard include/config/RTC_CLASS) \
  /root/kernel-ark-os-build/include/uapi/linux/rseq.h \
  /root/kernel-ark-os-build/include/linux/kcsan.h \
  /root/kernel-ark-os-build/include/linux/rv.h \
    $(wildcard include/config/RV_REACTORS) \
  /root/kernel-ark-os-build/include/linux/livepatch_sched.h \
  arch/x86/include/generated/asm/kmap_size.h \
  /root/kernel-ark-os-build/include/asm-generic/kmap_size.h \
    $(wildcard include/config/DEBUG_KMAP_LOCAL) \
  /root/kernel-ark-os-build/include/linux/sync_core.h \
    $(wildcard include/config/ARCH_HAS_SYNC_CORE_BEFORE_USERMODE) \
  /root/kernel-ark-os-build/arch/x86/include/asm/sync_core.h \
  /root/kernel-ark-os-build/include/linux/radix-tree.h \
  /root/kernel-ark-os-build/include/linux/capability.h \
  /root/kernel-ark-os-build/include/uapi/linux/capability.h \
  /root/kernel-ark-os-build/include/linux/semaphore.h \
  /root/kernel-ark-os-build/include/linux/fcntl.h \
    $(wildcard include/config/ARCH_32BIT_OFF_T) \
  /root/kernel-ark-os-build/include/uapi/linux/fcntl.h \
  arch/x86/include/generated/uapi/asm/fcntl.h \
  /root/kernel-ark-os-build/include/uapi/asm-generic/fcntl.h \
  /root/kernel-ark-os-build/include/uapi/linux/openat2.h \
  /root/kernel-ark-os-build/include/linux/migrate_mode.h \
  /root/kernel-ark-os-build/include/linux/percpu-rwsem.h \
  /root/kernel-ark-os-build/include/linux/rcuwait.h \
  /root/kernel-ark-os-build/include/linux/sched/signal.h \
    $(wildcard include/config/SCHED_AUTOGROUP) \
    $(wildcard include/config/BSD_PROCESS_ACCT) \
    $(wildcard include/config/TASKSTATS) \
    $(wildcard include/config/STACK_GROWSUP) \
  /root/kernel-ark-os-build/include/linux/signal.h \
    $(wildcard include/config/DYNAMIC_SIGFRAME) \
  /root/kernel-ark-os-build/include/linux/sched/jobctl.h \
  /root/kernel-ark-os-build/include/linux/sched/task.h \
    $(wildcard include/config/HAVE_EXIT_THREAD) \
    $(wildcard include/config/ARCH_WANTS_DYNAMIC_TASK_STRUCT) \
    $(wildcard include/config/HAVE_ARCH_THREAD_STRUCT_WHITELIST) \
  /root/kernel-ark-os-build/include/linux/uaccess.h \
    $(wildcard include/config/ARCH_HAS_SUBPAGE_FAULTS) \
  /root/kernel-ark-os-build/include/linux/fault-inject-usercopy.h \
    $(wildcard include/config/FAULT_INJECTION_USERCOPY) \
  /root/kernel-ark-os-build/arch/x86/include/asm/uaccess.h \
    $(wildcard include/config/CC_HAS_ASM_GOTO_OUTPUT) \
    $(wildcard include/config/CC_HAS_ASM_GOTO_TIED_OUTPUT) \
    $(wildcard include/config/X86_INTEL_USERCOPY) \
  /root/kernel-ark-os-build/include/linux/mmap_lock.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/smap.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/extable.h \
    $(wildcard include/config/BPF_JIT) \
  /root/kernel-ark-os-build/arch/x86/include/asm/tlbflush.h \
  /root/kernel-ark-os-build/include/linux/mmu_notifier.h \
  /root/kernel-ark-os-build/include/linux/interval_tree.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/invpcid.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/pti.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/pgtable.h \
    $(wildcard include/config/DEBUG_WX) \
    $(wildcard include/config/HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD) \
    $(wildcard include/config/ARCH_HAS_PTE_DEVMAP) \
    $(wildcard include/config/HAVE_ARCH_SOFT_DIRTY) \
    $(wildcard include/config/ARCH_ENABLE_THP_MIGRATION) \
    $(wildcard include/config/PAGE_TABLE_CHECK) \
  /root/kernel-ark-os-build/arch/x86/include/asm/pkru.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/fpu/api.h \
    $(wildcard include/config/X86_DEBUG_FPU) \
  /root/kernel-ark-os-build/arch/x86/include/asm/coco.h \
  /root/kernel-ark-os-build/include/asm-generic/pgtable_uffd.h \
  /root/kernel-ark-os-build/include/linux/page_table_check.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/pgtable_64.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/fixmap.h \
    $(wildcard include/config/PROVIDE_OHCI1394_DMA_INIT) \
    $(wildcard include/config/X86_IO_APIC) \
    $(wildcard include/config/PCI_MMCONFIG) \
    $(wildcard include/config/ACPI_APEI_GHES) \
    $(wildcard include/config/INTEL_TXT) \
  /root/kernel-ark-os-build/arch/x86/include/uapi/asm/vsyscall.h \
  /root/kernel-ark-os-build/include/asm-generic/fixmap.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/pgtable-invert.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/uaccess_64.h \
  /root/kernel-ark-os-build/include/asm-generic/access_ok.h \
    $(wildcard include/config/ALTERNATE_USER_ADDRESS_SPACE) \
  /root/kernel-ark-os-build/include/linux/cred.h \
  /root/kernel-ark-os-build/include/linux/key.h \
    $(wildcard include/config/KEY_NOTIFICATIONS) \
    $(wildcard include/config/NET) \
  /root/kernel-ark-os-build/include/linux/assoc_array.h \
    $(wildcard include/config/ASSOCIATIVE_ARRAY) \
  /root/kernel-ark-os-build/include/linux/sched/user.h \
    $(wildcard include/config/VFIO_PCI_ZDEV_KVM) \
    $(wildcard include/config/IOMMUFD) \
    $(wildcard include/config/WATCH_QUEUE) \
  /root/kernel-ark-os-build/include/linux/ratelimit.h \
  /root/kernel-ark-os-build/include/linux/rcu_sync.h \
  /root/kernel-ark-os-build/include/linux/delayed_call.h \
  /root/kernel-ark-os-build/include/linux/uuid.h \
  /root/kernel-ark-os-build/include/linux/errseq.h \
  /root/kernel-ark-os-build/include/linux/ioprio.h \
  /root/kernel-ark-os-build/include/linux/sched/rt.h \
  /root/kernel-ark-os-build/include/linux/iocontext.h \
    $(wildcard include/config/BLK_ICQ) \
  /root/kernel-ark-os-build/include/uapi/linux/ioprio.h \
  /root/kernel-ark-os-build/include/linux/fs_types.h \
  /root/kernel-ark-os-build/include/linux/mount.h \
  /root/kernel-ark-os-build/include/linux/mnt_idmapping.h \
  /root/kernel-ark-os-build/include/linux/slab.h \
    $(wildcard include/config/DEBUG_SLAB) \
    $(wildcard include/config/SLUB_TINY) \
    $(wildcard include/config/FAILSLAB) \
    $(wildcard include/config/KFENCE) \
    $(wildcard include/config/SLAB) \
    $(wildcard include/config/SLUB) \
  /root/kernel-ark-os-build/include/linux/percpu-refcount.h \
  /root/kernel-ark-os-build/include/linux/kasan.h \
    $(wildcard include/config/KASAN_STACK) \
    $(wildcard include/config/KASAN_VMALLOC) \
  /root/kernel-ark-os-build/include/linux/kasan-enabled.h \
  /root/kernel-ark-os-build/include/uapi/linux/fs.h \
  /root/kernel-ark-os-build/include/linux/quota.h \
    $(wildcard include/config/QUOTA_NETLINK_INTERFACE) \
  /root/kernel-ark-os-build/include/uapi/linux/dqblk_xfs.h \
  /root/kernel-ark-os-build/include/linux/dqblk_v1.h \
  /root/kernel-ark-os-build/include/linux/dqblk_v2.h \
  /root/kernel-ark-os-build/include/linux/dqblk_qtree.h \
  /root/kernel-ark-os-build/include/linux/projid.h \
  /root/kernel-ark-os-build/include/uapi/linux/quota.h \
  /root/kernel-ark-os-build/include/uapi/linux/aio_abi.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/compat.h \
  /root/kernel-ark-os-build/include/linux/sched/task_stack.h \
    $(wildcard include/config/DEBUG_STACK_USAGE) \
  /root/kernel-ark-os-build/include/uapi/linux/magic.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/user32.h \
  /root/kernel-ark-os-build/include/asm-generic/compat.h \
    $(wildcard include/config/COMPAT_FOR_U64_ALIGNMENT) \
  /root/kernel-ark-os-build/arch/x86/include/asm/syscall_wrapper.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/user.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/user_64.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/fsgsbase.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/vdso.h \
  /root/kernel-ark-os-build/include/uapi/linux/elf.h \
  /root/kernel-ark-os-build/include/uapi/linux/elf-em.h \
  /root/kernel-ark-os-build/include/linux/kobject.h \
    $(wildcard include/config/UEVENT_HELPER) \
    $(wildcard include/config/DEBUG_KOBJECT_RELEASE) \
  /root/kernel-ark-os-build/include/linux/sysfs.h \
  /root/kernel-ark-os-build/include/linux/kernfs.h \
    $(wildcard include/config/KERNFS) \
  /root/kernel-ark-os-build/include/linux/idr.h \
  /root/kernel-ark-os-build/include/linux/kobject_ns.h \
  /root/kernel-ark-os-build/include/linux/moduleparam.h \
    $(wildcard include/config/ALPHA) \
    $(wildcard include/config/PPC64) \
  /root/kernel-ark-os-build/include/linux/rbtree_latch.h \
  /root/kernel-ark-os-build/include/linux/error-injection.h \
  /root/kernel-ark-os-build/include/asm-generic/error-injection.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/module.h \
  /root/kernel-ark-os-build/include/asm-generic/module.h \
    $(wildcard include/config/HAVE_MOD_ARCH_SPECIFIC) \
    $(wildcard include/config/MODULES_USE_ELF_REL) \
    $(wildcard include/config/MODULES_USE_ELF_RELA) \
  /root/kernel-ark-os-build/include/linux/build-salt.h \
    $(wildcard include/config/BUILD_SALT) \
  /root/kernel-ark-os-build/include/linux/elfnote.h \
  /root/kernel-ark-os-build/include/linux/elfnote-lto.h \
    $(wildcard include/config/LTO) \
  /root/kernel-ark-os-build/include/linux/export-internal.h \
    $(wildcard include/config/PARISC) \
  /root/kernel-ark-os-build/include/linux/vermagic.h \
    $(wildcard include/config/PREEMPT_BUILD) \
  include/generated/utsrelease.h \
  /root/kernel-ark-os-build/arch/x86/include/asm/vermagic.h \
    $(wildcard include/config/M486SX) \
    $(wildcard include/config/M486) \
    $(wildcard include/config/M586) \
    $(wildcard include/config/M586TSC) \
    $(wildcard include/config/M586MMX) \
    $(wildcard include/config/MCORE2) \
    $(wildcard include/config/M686) \
    $(wildcard include/config/MPENTIUMII) \
    $(wildcard include/config/MPENTIUMIII) \
    $(wildcard include/config/MPENTIUMM) \
    $(wildcard include/config/MPENTIUM4) \
    $(wildcard include/config/MK6) \
    $(wildcard include/config/MK7) \
    $(wildcard include/config/MK8) \
    $(wildcard include/config/MELAN) \
    $(wildcard include/config/MCRUSOE) \
    $(wildcard include/config/MEFFICEON) \
    $(wildcard include/config/MWINCHIPC6) \
    $(wildcard include/config/MWINCHIP3D) \
    $(wildcard include/config/MCYRIXIII) \
    $(wildcard include/config/MVIAC3_2) \
    $(wildcard include/config/MVIAC7) \
    $(wildcard include/config/MGEODEGX1) \
    $(wildcard include/config/MGEODE_LX) \
  /root/kernel-ark-os-build/arch/x86/include/asm/orc_header.h \
  arch/x86/include/generated/asm/orc_hash.h \

/root/modules/pollselect_scullpipe/scullpipe.mod.o: $(deps_/root/modules/pollselect_scullpipe/scullpipe.mod.o)

$(deps_/root/modules/pollselect_scullpipe/scullpipe.mod.o):

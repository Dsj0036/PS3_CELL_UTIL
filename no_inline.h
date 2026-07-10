#if defined(_MSC_VER)
#define _SYS_NOINLINE __declspec(noinline)
#elif defined(__GNUC__) || defined(__clang__)
#define _SYS_NOINLINE __attribute__((noinline))
#else
#define _SYS_NOINLINE
#endif

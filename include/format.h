#include "_ns.h"
#include "array.h"
#include "lwstring.h"
_SYS_NS
// 6/26/26 - Added

int32_t format_string(sys::lwstring* output, const char* format, va_list);

lwstring sformat(int32_t*, const char*,...);

lwstring sformat(const char* fmt, ...);
_SYS_ENS

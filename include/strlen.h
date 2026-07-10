#pragma once
#include "_ns.h"
#include <sys\types.h>
_SYS_NS
/* Return the length of the null-terminated string STR.  Scan for
   the null terminator quickly by testing four bytes at a time.  */
size_t strlen(const char* str);
_SYS_ENS
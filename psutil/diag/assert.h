#pragma once
#include <psutil\ns.h>
#include <psutil\diag\abort.h>
_SYS_NS
#define _sys_assertd(condition, description) sys::_assert(condition, #condition, description, __LINE__, __FUNCTION__)
#define _sys_assert(condition) _sys_assertd(condition, "");

void _assert(bool c, const char* cStr, const char* descript, int line, const char* func) {
	if (!(c))
		abort_expresivef(-1, "%s\n%s\nline: %i - %s", cStr, descript, line, func);
}

_SYS_ENS
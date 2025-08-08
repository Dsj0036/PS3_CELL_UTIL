#pragma once

#include <psutil\ns.h>
#include <psutil\xtypes.h>

_SYS_NS
void abort(unsigned long long );
void abort_expresive(uint32_t, const char*);
void abort_expresivef(uint32_t code, const char*, ...);
_SYS_ENS
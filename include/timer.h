#pragma once
#include "_ns.h"
#include "_pragma_static_getter.h"

_SYS_NS
_SYS_DEFINE_STATIC_GETTER(timebase, unsigned long long);
_SYS_DEFINE_STATIC_GETTER(timebase_freq, unsigned long long);
unsigned long long _read_timebase();
unsigned long long _read_timebase_frequency();
unsigned long long timeu();
unsigned long long timems();
_SYS_ENS

#pragma once
#include "strlen.h"
#include "_ns.h"
extern "C" unsigned int murmurhash3_32(const char* key, int len, unsigned int seed = 42);

_SYS_NS

/// Convenience inline shortcut.
inline uint32_t murmurhash32(const char* const& lwstr) {
    size_t R = sys::strlen(lwstr);
    return murmurhash3_32(lwstr, static_cast<int>(R), 0xdead);
}
_SYS_ENS

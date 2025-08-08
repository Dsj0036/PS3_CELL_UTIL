#pragma once
#include <psutil\ns.h>



_SYS_NS

template<typename T>
static inline bool tryset(T*& nullable, const T& val) {
	if (nullable)
		*nullable = val;
	return nullable != nullptr;
}
template<typename T>
static inline bool tryset(T** nullable, T* val) {
	if (nullable) {
		if (!*nullable) {
			*nullable = val;
		}
	}
	return nullable != nullptr;
}

_SYS_ENS
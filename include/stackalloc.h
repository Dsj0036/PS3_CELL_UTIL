#pragma once
#include <alloca.h>
#include "traits.h"
#ifndef __SYSTEM_STACK_ALLOC__
#define __SYSTEM_STACK_ALLOC__
#define stackalloc(size) \
	static_assert((size) != 0, "stackalloc: invalid size"); \
	alloca(size)

// Freed along the stack, the type must be destroyed manually.
#define stackalloct(T) ((T*)alloca(sizeof(T))) 


#endif 
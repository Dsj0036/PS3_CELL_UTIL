#pragma once

#ifndef __SYS_DEFAULT_ALLOCATOR__
#define __SYS_DEFAULT_ALLOCATOR__
#include "_ns.h"
#include "allocator.h"
_SYS_NS

// Default PlayStation 3 Allocator is a CRT dunkenware STD wrap.

using default_allocator_t = crt_alloc;
_SYS_DEFINE_STATIC_GETTER_INLINE(default_allocator, default_allocator_t*,
	crt_alloc::instance().__validate();
//return &crt_allocator;}
return &sys::crt_alloc::instance();
);

_SYS_ENS
#endif
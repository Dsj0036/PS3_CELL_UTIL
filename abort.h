#pragma once
#include <pch.h>
#include <sys\types.h>
#include "no_inline.h"
#include "lwstring.h"
namespace sys {
	// Prints the caller trace after and fail exit.
	int stack_trace();

	_SYS_NOINLINE void abort(unsigned long long code) __attribute__((noreturn));
	sys::lwstring stack_trace_str(int skip);
}
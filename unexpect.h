#pragma once
#include "throw.h"
#include <exception>
#include "ctx.h"
namespace sys {
	void __unexpect(const char* conditionString, __static_stack_info inl);
}

#define unexpect(condition) do { if ((condition)) { sys_ctx sys::__unexpect(#condition, ctx); }} while(0);
#define __expect(condition)unexpect(!(condition))

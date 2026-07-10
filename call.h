#pragma once
#include <sys\types.h>
#include "no_inline.h"
namespace sys {

	
	template<class R, typename ...Args>
	_SYS_NOINLINE R function_call(uint32_t opdToc, uint32_t opdAddr, const Args&...param) {

		volatile unsigned int toc_t[2] = { opdAddr,  opdToc };

		//using FUNCTION = R(*)(Args...);

		R(*temp)(Args...) = (R(*)(Args...)) & toc_t;

		return temp(param...);
		//return ((FUNCTION)&toc_t)(param...);
	}
}
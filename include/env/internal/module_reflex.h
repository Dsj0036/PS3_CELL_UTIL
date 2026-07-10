#pragma once
#include "..\..\_pragma_section_reflex.h"
#include <sys/moduleexport.h>
#include <sys/prx.h>
namespace sys {
	namespace detail {
		struct module final {
			int hdl;
			module* deps;
			const char* name;
			int(*load)();
			int(*exit)();

			constexpr module(int hdl, module* deps, const char* name, int(*load)(), int(*exit)())
				: hdl(hdl), deps(deps), name(name), load(load), exit(exit)
			{

			}
		};
	}
}
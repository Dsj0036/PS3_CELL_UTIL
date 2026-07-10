#pragma once
namespace sys {

	namespace env {
		extern const char* const version_string;
		extern const int version_major;
		extern const int version_minor;
		extern const int version_patch;

		struct module_def
		{
			const char* name;
			const module_def* const* dependencies;
			unsigned int dependency_count;
			void (*initializer)();
			void (*finalizer)();
			bool initialized{false};

			inline constexpr module_def(const char* name, module_def* const *dependencies, unsigned int depcount, void(*init)(), void(*finish)()) 
				: name(name),dependencies(dependencies), dependency_count(depcount), initializer(init), finalizer(finish)
			{
			}
		};


		inline constexpr module_def create_module(const char* name, void(*initializer)()) {
			return  module_def(name, 0, 0, initializer, 0);
		}

	}
}

#define __XSYSTEM_CORE_DEFINE_SUBMODULE(Name, NameIdStr, InitializerFunction) namespace sys { namespace env { namespace modules {\
const module_def Name = sys::env::create_module(NameIdStr, InitializerFunction);}}} \
 const sys::env::module_def* __module_##Name __attribute__((aligned(4), section(".rodata.progmoddef", "a"), used, unused)) = &sys::env::modules::Name;


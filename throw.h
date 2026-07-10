#pragma once
#include "no_inline.h"
#include "exception.h" // instead of stdexcept
#include "threading.h"
#include "traits.h"
#include "ctx.h"
// #include <stdexcept> std::exception is unsupported.
namespace sys {
	// std::exception is unsupported.
	//void _raiseUnhandledFatal(const std::exception&, int, const char*, const char*);
	void _raiseUnhandledFatal(const sys::exception&, int, const char*, const char*);


	// syntax convenience wrapper for the FAIL macro
	class j_raises_fatal_wrapper {
		bool traps;
		int line();
		const char* function();
		const char* filename();
	public:

		template<typename Exception>
		inline void operator<<(const Exception& err) {
			if (!sys::is_exception<Exception>()) {
				__builtin_trap();
			}
			_raiseUnhandledFatal(err, line(), function(), filename());
		}
		inline void operator<<(const char* s) {
			sys::runtime_error R{ s };
			_raiseUnhandledFatal(R, line(), function(), filename());
		}

		void __spbf() {
			traps = true;
		}
		inline bool must_trap() const{
			return traps;
		}

		_SYS_NOINLINE void _static_prethrow(int line, const char* func, const char* file);
	};


	extern j_raises_fatal_wrapper fatal;

	inline void set_program_breaks_on_fatal() {
		fatal.__spbf();

	}
	inline bool breaks_on_fatal() {
		return fatal.must_trap();
	}
}


#define THROW(exception_type) auto v = new exception_type;\
sys_ctx;\
sys::throw_thread_exception(v, sys::typenameOf<sys::remove_pointer<decltype(v)>::type>(), ctx);


#define FAIL sys::fatal._static_prethrow(__LINE__, __func__, __FILE__); sys::fatal << 

namespace sys {

	// Since SNC does not support pure virtual declarations, this is an approach.
	inline void throw_pure_virtual_usage() {
		THROW(sys::pure_virtual_error());

	}
}

#define TRY \
    { \
        sys::faultable_scope ___scope; \
        sys::_push_faultable_scope(&___scope);




#define CATCH(e, fallback) if (___scope.exception != NULL)  {sys::thread_context* __ctx = sys::get_thread_ctx(); if (__ctx->fault_scope->tname == sys::typenameOf<sys::remove_pointer<e>::type>()){fallback; }}} 


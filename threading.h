#pragma once
#include "_ns.h"

#include <sys/ppu_thread.h>

#include <ppu_asm_intrinsics.h>

#include <ppu_intrinsics.h>

#include "thread.h"

#include "ctx.h"



namespace sys {
	static constexpr int32_t MAX_PROGRAM_THREADS = 32;
	class exception;

	namespace detail {

		struct faultable_scope;
		struct thread_context;

		thread_context* get_thread_ctx();
		thread_context* get_thread_ctx(sys::ppu_thread*);
		struct faultable_scope;
		
		uint32_t get_thread_hash(sys_ppu_thread_t id, size_t stack);
		void init_threading();
		void push_faultable_scope(faultable_scope*);

		inline uint32_t get_hash(thread_context& in) {
			///return _get_thread_hash(in.id, in.st.pst_size);
			return 0;
		}

		inline uint32_t get_hash(sys::ppu_thread* in) {
			//return _get_thread_hash(in->handle(), in->stackSize());
			return 0;
		}
		inline bool is_main_thread(thread_context& ctx) {

			//return ((uint32_t)ctx.kt) == 0xdead;
			return 0;
		}

	}
	void throw_thread_exception(sys::exception* err, const char* typename_, sys::__static_stack_info);


}

#pragma once
namespace sys {

	struct __static_stack_info {
		const char* signature;
		const char* filename;
		const char* exceptionType;
		int line{0};

		__static_stack_info(const char* sig, const char* file, const char* exception, int ln)
			: signature(sig), filename(file), exceptionType(exception), line(ln) {}
	};
}
#define sys_ctx sys::__static_stack_info ctx{__PRETTY_FUNCTION__, __FILE__, (const char*)0, __LINE__};

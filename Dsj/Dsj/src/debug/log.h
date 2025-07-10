#pragma once
#include "..\system\core.h"
#include "..\system\all_intrinsics_builtin.h"
#include <sys\console.h>
namespace pllx{
	class Logger {
		char __cache[512];
	private:
		Logger() {}
		Logger(const Logger&) = delete;
	public:

		void writeLine(const char* msg);
		void _msg_append(const char* msg, size_t msglen = 0, const char* pth = nullptr);
		void warn(const char* msg, ...);
		void info(const char* msg, ...);
		void error(const char* msg, ...);


		static Logger& getLogger();
	};
}
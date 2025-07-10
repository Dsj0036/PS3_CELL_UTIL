#pragma once
#include "log.h"
namespace pllx {
	void Logger::writeLine(const char* msg) {
		console_line(msg);
	}
	void Logger::_msg_append(const char* msg, size_t msglen, const char* pth) {
		if (!msg)
			return;
		console_write("[pllx] ", 7);
		if (pth) {
			console_putc('(');
			console_write(pth, sys::strlen(pth));
			console_putc(')');
			console_putc(' ');
		}
		if (!*msg)
			return;
		size_t len = 0;
		if (msglen == 0)
			len = sys::strlen(msg);
		else
			len = msglen;
		console_write(msg, len);
		console_putc('\n');
	}
	void Logger::warn(const char* msg, ...) {

		va_list list;
		va_start(list, msg);
		*__cache = '\0';
		int32_t r = _sys_vsnprintf(__cache, 512, msg, list);
		_msg_append(__cache, r, "Warning");
		va_end(list);
	}
	void Logger::info(const char* msg, ...) {

		va_list list;
		va_start(list, msg);
		*__cache = '\0';
		int32_t r = _sys_vsnprintf(__cache, 512, msg, list);
		_msg_append(__cache, r, "Info");
		va_end(list);
	}
	void Logger::error(const char* msg, ...) {

		va_list list;
		va_start(list, msg);
		*__cache = '\0';
		int32_t r = _sys_vsnprintf(__cache, 512, msg, list);
		_msg_append(__cache, r, "Error");
		va_end(list);
	}
	Logger& Logger::getLogger() {
		static Logger logger;
		return logger;
	}
}


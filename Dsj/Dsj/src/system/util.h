#pragma once
#include "types.h"
namespace sys {
	namespace util {

		template <typename x>	x abs(x a);

		template <typename x>	x min(x a, x b);

		template <typename x>	x max(x a, x b);

		inline bool isalpha(int ch) {
			return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
		}
		inline bool isnum(int ch) {
			return (ch >= '0' && ch <= '9');
		}
		inline bool isalnum(int ch) {
			return isalpha(ch) || isnum(ch);
		}

		template<typename T> static inline bool tryset(T*& nullable, const T& val);

		template<typename T> static inline bool tryset(T** nullable, T* val);

		template<typename T> static inline void safedelete(T** nullable);

		template <typename... Arguments> size_t strnprintfcat(char* buffer, const char* format, size_t len, Arguments... s);

		template <typename T> T&& move(T& arg);


		double stod(const char* str);

		const char* strstr_array(const char* const strings[], const char* target, int count, bool matchCase);

		float stof(const char* str);

		uintptr_t funcopdoff(uint32_t classed_ptr, uint32_t offset);
	}

}
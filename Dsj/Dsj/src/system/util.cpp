#include "util.h"
#include "defs.h"
#include "all_intrinsics_builtin.h"
namespace sys {
	namespace util {
		
		template<typename T>
		static inline bool tryset(T*& nullable, const T& val) {
			if (nullable)
				*nullable = val;
			return nullable != nullptr;
		}
		template<typename T>
		static inline bool tryset(T** nullable, T* val) {
			if (nullable) {
				if (!*nullable) {
					*nullable = val;
				}
			}
			return nullable != nullptr;
		}

		template<typename T>
		static inline void safedelete(T** nullable) {
			if (nullable) {
				if (!*nullable) {
					delete* nullable;
					*nullable = nullptr;
				}
			}
		}

		template <typename x>	x abs(x a) { return ABS(a); }
		template <typename x>	x min(x a, x b) { return (MIN(a, b) };
		template <typename x>	x max(x a, x b) { return (MAX(a, b) };


		double util::stod(const char* str) {
			double result = 0.0f;
			// double factor = 1.0f;
			bool negative = false;
			bool decimalPointEncountered = false;
			float decimalFactor = 0.1f;

			// !! Ensure skipping leading spaces otherwises it will always return 0.0
			while (*str == ' ') {
				str++;
			}
			if (*str == '-') {
				negative = true;
				str++;
			}
			while (*str != '\0') {
				if (*str == '.') {
					decimalPointEncountered = true;
				}
				else if (*str >= '0' && *str <= '9') {
					if (decimalPointEncountered) {
						result += (*str - '0') * decimalFactor;
						decimalFactor *= 0.1f;
					}
					else {
						result = result * 10.0f + (*str - '0');
					}
				}
				else {
					break;
				}
				str++;
			}
			if (negative) {
				result = -result;
			}

			return result;
		}
		/// <summary>
		/// Parse Dot Floating Value String
		/// </summary>
		/// <param name="str"></param>
		/// <returns></returns>
		float util::stof(const char* str) {
			float result = 0.0f;
			//float factor = 1.0f;
			bool negative = false;
			bool decimalPointEncountered = false;
			float decimalFactor = 0.1f;
			// !! Ensure skipping leading spaces otherwises it will always return 0.0
			while (*str == ' ') {
				str++;
			}
			if (*str == '-') {
				negative = true;
				str++;
			}
			while (*str != '\0') {
				if (*str == '.') {
					decimalPointEncountered = true;
				}
				else if (*str >= '0' && *str <= '9') {
					if (decimalPointEncountered) {
						result += (*str - '0') * decimalFactor;
						decimalFactor *= 0.1f;
					}
					else {
						result = result * 10.0f + (*str - '0');
					}
				}
				else {
					break;
				}
				str++;
			}
			if (negative) {
				result = -result;
			}

			return result;
		}

		template <typename... Arguments>
		size_t strnprintfcat(char* buffer, const char* format, size_t len, Arguments... s) {
			char temp[0x256]{ 0 };

			sys::snprintf(temp, sizeof(temp) - 1, format, s...);

			size_t currentLen = sys::strlen(buffer);
			sys::_sys_strncat(buffer, temp, len - currentLen - 1);

			return sys::strlen(buffer);
		}
		template <typename T>
		T&& move(T& arg) {
			return static_cast<T&&>(arg);
		}
		uintptr_t util::funcopdoff(uint32_t classed_ptr, uint32_t offset) {
			uint32_t table_value = *(uint32_t*)(classed_ptr);
			return *(uint32_t*)(table_value + offset);
		}
	}
	
}
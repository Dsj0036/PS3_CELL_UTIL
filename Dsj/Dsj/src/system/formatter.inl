#pragma once
#include "..\incl\TCSB.h"
#include "util.h"
#include "all_intrinsics_builtin.h"
#include <wchar.h>
namespace sys {
	namespace formatter {

		char* _gdecstr(double val, int decimals) {
			char* r = new char[40] {0};

			auto bs = CStringBuilder(r, 40);
			bs.addf(val);
			if (decimals > 0) { // assume 0 indicates ignoring.
				char* dot_pos = _sys_strchr(r, '.');
				if (dot_pos) {
					int max_len = dot_pos - r + decimals + 1;
					if (max_len < _sys_strlen(r)) {
						r[max_len] = '\0';
					}
				}
			}


			return r;
		}
		char* _ghexstr(uint64_t anyh, bool uppercase, bool i64) {
			char* r = new char[32] {0};
			const char* format = i64 ? (uppercase ? "%llX" : "%llx") : (uppercase ? "%lX" : "%lx");
			_sys_snprintf(r, 32, format, anyh);
			return r;
		}


		void _itow(int value, wchar_t* out, int max_len) {
			int i = max_len - 2;
			bool isNegative = value < 0;
			if (isNegative) value = -value;

			out[i + 1] = L'\0';

			do {
				out[i--] = (wchar_t)(L'0' + (value % 10));
				value /= 10;
			} while (value && i >= 0);

			if (isNegative && i >= 0) {
				out[i--] = L'-';
			}

			for (int j = i + 1, k = 0; out[j]; ++j, ++k)
				out[k] = out[j];

			out[max_len - 1] = L'\0';
		}

		inline bool _is_it(const wchar* data, const wchar* comparing) {
			return std::wcsncmp(comparing, data, std::wcslen(comparing)) == 0;
		}

		inline bool _is_it(const char* data, const char* comparing) {
			return _sys_strcmp(data, comparing) == 0;
		}
		inline bool is_alnum(int c) {
			return sys::util::isnum(c) || sys::util::isalpha(c);
		}

	}
}
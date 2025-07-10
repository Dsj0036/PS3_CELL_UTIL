
#include "all_intrinsics_builtin.h"
#include "core.h"
#include <sys\timer.h>
namespace sys {
	void* memalign(size_t boundary, size_t size) {
		return _sys_memalign(boundary, size);
	}
	void* memmove(void* dest, const void* src, size_t n) {
		unsigned char* d = static_cast<unsigned char*>(dest);
		const unsigned char* s = static_cast<const unsigned char*>(src);

		if (d == s || n == 0) {
			return dest;
		}

		if (d < s || d >= s + n) {
			while (n--) {
				*d++ = *s++;
			}
		}
		else {
			d += n;
			s += n;
			while (n--) {
				*(--d) = *(--s);
			}
		}

		return dest;
	}

	unsigned int strlen(const char* x) { return _sys_strlen(x); };
	unsigned int strlen(void* x) {return _sys_strlen((char*)x);};

	int memcmp(const void* a, const void* b, size_t num) { return _sys_memcmp(a, b, num); };
	void* memcpy(const void* srcDest, const void* srcSrc, size_t num) { return _sys_memcpy((void*)srcDest, (void*)srcSrc, num); };
	void* memset(void* srcDest, int value, size_t len) { return _sys_memset(srcDest, value, len); };
	char* strncpy(char* srcDest, const char* srcSrc, size_t srcSize) { return _sys_strncpy(srcDest, srcSrc, srcSize); };
	char* strcpy(char* srcDest, const char* srcSrc) {
		return _sys_strcpy(srcDest, srcSrc);
	};


	int strncmp(const char* srcDest, const char* srcSrc, size_t srcSize) {
		return _sys_strncmp(srcDest, srcSrc, srcSize);
	};

	int _strcmp(const char* s1, const char* s2) {
		while (*s1 && (*s1 == *s2)) {
			++s1;
			++s2;
		}
		return *(unsigned char*)s1 - *(unsigned char*)s2;
	}

	int wcsncmp(const wchar_t* a, const wchar_t* b, size_t size) {
		if (size <= 0) {
			return -1;
		}
		size_t iter = 0;
		while (iter < size) {
			if (_sys_memcmp(a, b, 2) != 0) {
				return false;
			}
			iter++;
		}
		return iter == size;
	}
	size_t wcslen(const wchar_t* widestring) {
		if (!widestring) {
			return 0;
		}
		size_t x = 0;
		while (widestring[x] != L'\0') {
			x++;
		}
		return x;
	}

	void* malloc(size_t size) { return _sys_malloc(size); };
	void free(void* alloc) {
		_sys_free(alloc);
	}


	template <typename ...args> int printf(const char* format, args...x) {
		_sys_printf(format, x...);
	}

	template <typename ...args> int snprintf(char* buff, size_t num, const char* frm, args...x)
	{
		return _sys_snprintf(buff, num, frm, x...)
	};
	void strncat(char* dest, char* src, size_t num) {
		_sys_strncat(dest, src, num);
	}
	void* strchr(char* src, int ch) { return _sys_strrchr(src, ch); };
	int tolower(int c) { return _sys_tolower(c); };
	int toupper(int c) { return _sys_toupper(c); };
	template <typename ...args> int sprintf(char* buf, char* format, args...x) {
		_sys_sprintf(buf, format, x...);
	}

	static inline int usleep(usecond_t us) {
		return sys_timer_usleep(us);
	}

	static inline int sleep(unsigned int seconds) {
		return sys_timer_usleep(seconds * 1000000ULL);
	}

	static inline int sleepMs(uint64_t milliseconds) {
		return sys_timer_usleep(milliseconds * 1000ULL);
	}


}

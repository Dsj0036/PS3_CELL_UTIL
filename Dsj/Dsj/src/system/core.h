#pragma once
#include "types.h"

namespace sys {
	void* memalign(size_t boundary, size_t size);

	void* memmove(void* dest, const void* src, size_t n);

	unsigned int strlen(const char* x);

	unsigned int strlen(const void* unsafew);

	int memcmp(const void* a, const void* b, size_t num);

	void* memcpy(const void* srcDest, const void* srcSrc, size_t num);

	void* memset(void* srcDest, int value, size_t len);

	char* strncpy(char* srcDest, const char* srcSrc, size_t srcSize);

	char* strcpy(char* srcDest, const char* srcSrc);

	int strncmp(const char* srcDest, const char* srcSrc, size_t srcSize);

	int _strcmp(const char* s1, const char* s2);


	int wcsncmp(const wchar_t* a, const wchar_t* b, size_t size);

	size_t wcslen(const wchar_t* widestring);

	void* malloc(size_t size);

	void free(void* alloc);;

	template <typename ...args> int printf(const char* format, args...x);

	template <typename ...args> int snprintf(char* buff, size_t num, const char* frm, args...x);

	void strncat(char* dest, char* src, size_t num);

	void* strchr(char* src, int ch);

	int tolower(int c);

	int toupper(int c);

	template <typename ...args> int sprintf(char* buf, char* format, args...x);

	static inline int usleep(usecond_t us);

	static inline int sleep(unsigned int seconds);

	static inline int sleepMs(uint64_t milliseconds);




}

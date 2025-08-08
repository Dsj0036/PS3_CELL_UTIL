#ifndef _C_MEMORY_H
#define _C_MEMORY_H
#include <yvals.h>

extern "C"
{
	int				_sys_printf(const char* format, ...);
	int				_sys_sprintf(char* s, const char* format, ...);
	int				_sys_snprintf(char* s, size_t n, const char* format, ...);
	void* _sys_memalign(size_t boundary, size_t size);
	void* _sys_malloc(size_t n);
	void			_sys_free(void* ptr);
	void* _sys_memchr(void* ptr, int value, size_t num);
	void* _sys_memcpy(void* destination, const void* source, size_t num);
	int				_sys_memcmp(const void* ptr1, const void* ptr2, size_t num);
	void* _sys_memset(void* ptr, int value, size_t num);
	void* _sys_memmove(void* destination, const void* source, size_t num);
	char* _sys_strcat(char* destination, const char* source);
	char* _sys_strchr(char* str, int character);
	int				_sys_strcmp(const char* str1, const char* str2);
	char* _sys_strcpy(char* destination, const char* source);
	size_t			_sys_strlen(const char* str);
	char* _sys_strncat(char* destination, const char* source, size_t num);
	int				_sys_strncmp(const char* str1, const char* str2, size_t num);
	char* _sys_strncpy(char* destination, const char* source, size_t num);
	char* _sys_strrchr(char* str, int character);
	int				_sys_tolower(int c);
	int				_sys_toupper(int c);
	int				_sys_vprintf(const char* format, va_list arg);
	int				_sys_vsnprintf(char* buffer, size_t buf_size, const char* format, va_list arg);

}

#endif

#pragma once
/// Do not include this header at the global context.
/// Usage only for builtin system intrinsics.
/// 
extern "C" {

	int            _sys_printf(const char* format, ...);
	int            _sys_sprintf(char* s, const char* format, ...);
	int            _sys_snprintf(char* s, unsigned int n, const char* format, ...);
	void* _sys_memalign(unsigned int boundary, unsigned int size);
	void* _sys_malloc(unsigned int n);
	void        _sys_free(void* ptr);
	void* _sys_memchr(void* ptr, int value, unsigned int num);
	void* _sys_wmemchr(wchar_t* ptr, wchar_t value, unsigned int num);
	void* _sys_memcpy(void* destination, const void* source, unsigned int num);
	int   _sys_memcmp(const void* ptr1, const void* ptr2, unsigned int num);
	void* _sys_memset(void* ptr, int value, unsigned int num);
	void* _sys_memmove(void* destination, const void* source, unsigned int num);

	char* _sys_strcat(char* destination, const char* source);
	char* _sys_strchr(char* str, int character);
	int   _sys_strcmp(const char* str1, const char* str2);
	int   _sys_strcasecmp(const char* str1, const char* str2);
	int   _sys_strncasecmp(const char* str1, const char* str2, unsigned int num);
	int   _sys_wcscasecmp(const wchar_t* str1, const wchar_t* str2);
	int   _sys_wcsncasecmp(const wchar_t* str1, const wchar_t* str2, unsigned int num);
	int   _sys_wcsncmp(const wchar_t* str1, const wchar_t* str2, unsigned int num);
	char* _sys_strcpy(char* destination, const char* source);
	unsigned int _sys_strlen(const char* str);
	char* _sys_strncat(char* destination, const char* source, unsigned int num);
	int   _sys_strncmp(const char* str1, const char* str2, unsigned int num);
	char* _sys_strncpy(char* destination, const char* source, unsigned int num);
	char* _sys_strrchr(char* str, int character);
	int		_sys_tolower(int c);
	int		_sys_toupper(int c);
	int _sys_vprintf(const char* format, char* arg);
	int _sys_vsnprintf(char* buffer, unsigned int buf_size, const char* format, char* arg);
}

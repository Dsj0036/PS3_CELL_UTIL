#pragma once

extern "C"
{
	int            _sys_printf(const char* format, ...);
	int            _sys_sprintf(char* s, const char* format, ...);
	int            _sys_snprintf(char* s, size_t n, const char* format, ...);
	void* _sys_memalign(size_t boundary, size_t size);
	void* _sys_malloc(size_t n);
	void        _sys_free(void* ptr);
	void* _sys_memchr(void* ptr, int value, size_t num);
	// Performs a memory copy to destination from source with specified number of bytes
	void* _sys_memcpy(void* destination, const void* source, size_t num);
	int   _sys_memcmp(const void* ptr1, const void* ptr2, size_t num);
	void* _sys_memset(void* ptr, int value, size_t num);
	void* _sys_memmove(void* destination, const void* source, size_t num);

	char* _sys_strcat(char* destination, const char* source);
	char* _sys_strchr(char* str, int character);
	int   _sys_strcmp(const char* str1, const char* str2);
	char* _sys_strcpy(char* destination, const char* source);
	size_t _sys_strlen(const char* str);
	char* _sys_strncat(char* destination, const char* source, size_t num);
	int   _sys_strncmp(const char* str1, const char* str2, size_t num);
	char* _sys_strncpy(char* destination, const char* source, size_t num);
	char* _sys_strrchr(char* str, int character);
	int		_sys_tolower(int c);
	int		_sys_toupper(int c);

}
namespace sys {
	static inline bool isalpha(int ch) {
		return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
	}
	static inline bool isnum(int ch) {
		return (ch >= '0' && ch <= '9');
	}
	static inline bool isalnum(int ch) {
		return isalpha(ch) || isnum(ch);
	}
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
}


//#define malloc _sys_malloc
#define s_printf _sys_printf
#define s_snprintf _sys_snprintf
//#define strncat _sys_strncat
//#define strrchr _sys_strrchr
//#define tolower _sys_tolower
//#define toupper _sys_toupper
//#define strncmp _sys_strncmp
//#define sprintf _sys_sprintf
//#define free _sys_free
#define strleng _sys_strlen
//#define strcpy _sys_strcpy

#pragma once
#include <wchar.h>   // funciones estándar wide-char C
#include <cwchar>    // funciones estándar wide-char C++
#include <xstring>
#include <string.h>
// Asegura visibilidad C si se usa desde C++
#ifdef __cplusplus
extern "C" {
#endif
    static inline char* strchr_builtin(char* _Str, int _Ch)
    {
        return ::strchr(_Str, _Ch);
    }
    // Funciones wide-char estilo stdlib C (C11 / C++ compliant)
    static inline size_t wcslen_builtin(const wchar_t* s) {
        return ::wcslen(s);
    }

    static inline int wcsncmp_builtin(const wchar_t* s1, const wchar_t* s2, size_t n) {
        return ::wcsncmp(s1, s2, n);
    }

    static inline int wcscmp_builtin(const wchar_t* s1, const wchar_t* s2) {
        return ::wcscmp(s1, s2);
    }

    static inline wchar_t* wcscpy_builtin(wchar_t* dest, const wchar_t* src) {
        return ::wcscpy(dest, src);
    }

    static inline wchar_t* wcsncpy_builtin(wchar_t* dest, const wchar_t* src, size_t n) {
        return ::wcsncpy(dest, src, n);
    }

    static inline wchar_t* wcschr_builtin(const wchar_t* str, wchar_t ch) {
        return ::wcschr(const_cast<wchar_t*>(str), ch);
    }

#ifdef __cplusplus
}
#endif

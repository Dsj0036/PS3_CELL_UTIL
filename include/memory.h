#pragma once
#include <sys\types.h>
#include <stddef.h>
#include "_sys_mem.h"
#include "traits.h"

namespace sys {


	class __wrapped_forward_operator {
		__wrapped_forward_operator() = default;
	public:


		template<typename T>
		inline constexpr T&& operator<<(T&& t) noexcept
		{
			return static_cast<sys::remove_reference_t<T>&&>(t);
		}
		//template<typename T>
		//inline T&& operator<<(T any) {
			//return static_cast<T&&>(any);
		//}
		inline static __wrapped_forward_operator& op() {
			static __wrapped_forward_operator _{};
			return _;
		}
	};
	static __wrapped_forward_operator& _fw{ sys::__wrapped_forward_operator::op() };
	/*Instanced at sys_mem.cpp*/

	/// Empty String Constant.
	extern const char* EMPTY_STRING;

	/// Empty Wstring Constant.
	extern const wchar_t* EMPTY_WSTRING;


	// Convenience alias to an numeric static_cast.
	// This does absolutely nothing on assembly more than a integer move.
	template<typename T>
	inline uint64_t u64_from_ptr(T* ptr) {
		return static_cast<uint64_t>(
			(uintptr_t)(ptr)
			);
	}

	template <typename ...ANY> inline int				printf(const char* format, const ANY&...param) {
		{
			return _sys_printf(format, param...);
		}
	}
	template <typename ...ANY> inline int				sprintf(char* s, const char* format, const ANY&...param) {
		{
			return _sys_sprintf(s, format, param...);
		}
	}
	template <typename ...ANY> inline int				snprintf(char* s, unsigned int n, const char* format, const ANY&...param) {
		{
			return _sys_snprintf(s, n, format, param...);
		}
	}

	inline void trap() {
		__builtin_trap();
	}

	inline void* memalign(unsigned int boundary, unsigned int size) {
		return _sys_memalign(boundary, size);
	}
	inline void* malloc(unsigned int n) {
		return _sys_malloc(n);
	}
	inline void			free(void* ptr) {
		return _sys_free(ptr);
	}
	inline void* memchr(void* ptr, int value, unsigned int num) {
		return _sys_memchr(ptr, value, num);
	}
	inline void* wmemchr(wchar_t* ptr, wchar_t value, unsigned int num) {
		return _sys_memchr(ptr, value, num);
	}
	inline void* memcpy(void* destination, const void* source, unsigned int num) {
		return _sys_memcpy(destination, source, num);
	}
	inline int				memcmp(const void* ptr1, const void* ptr2, unsigned int num) {
		return _sys_memcmp(ptr1, ptr2, num);
	}
	inline void* memset(void* ptr, int value, unsigned int num) {
		return _sys_memset(ptr, value, num);
	}
	inline void* memmove(void* destination, const void* source, unsigned int num) {
		return _sys_memmove(destination, source, num);
	}
	inline char* strcat(char* destination, const char* source) {
		return _sys_strcat(destination, source);
	}
	inline char* strchr(char* str, int character) {
		return _sys_strchr(str, character);
	}
	inline int				strcmp(const char* str1, const char* str2) {
		return _sys_strcmp(str1, str2);
	}
	inline char* strcpy(char* destination, const char* source) {
		return _sys_strcpy(destination, source);
	}
	inline unsigned int	sys_strlen(const char* str) {
		return sys_strlen(str);

	}
	inline char* strncat(char* destination, const char* source, unsigned int num) {
		return _sys_strncat(destination, source, num);
	}
	inline int				strncmp(const char* str1, const char* str2, unsigned int num) {
		return _sys_strncmp(str1, str2, num);
	}
	inline char* strncpy(char* destination, const char* source, unsigned int num) {
		return _sys_strncpy(destination, source, num);
	}
	inline char* strrchr(const char* str, int character) {
		return _sys_strrchr(const_cast<char*>(str), character);
	}
	inline int				tolower(int c) {
		return _sys_tolower(c);
	}
	inline int				toupper(int c) {
		return _sys_toupper(c);
	}
	inline int			vprintf(const char* format, va_list arg) {
		return _sys_vprintf(format, arg);
	}
	// Includes null terminator.
	inline int			vsnprintf(char* buffer, unsigned int buf_size, const char* format, va_list arg) {
		return _sys_vsnprintf(buffer, buf_size, format, arg);
	}

	inline void* memclr(unsigned int ptr, int count) {
		return _sys_memset(reinterpret_cast<void*>(ptr), 0, count);
	}

	inline void* memclr(void* x, int bytes_count) {
		if (!x) {
			return nullptr;
		}
		return _sys_memset(x, 0, bytes_count);
	}

	/**
	 * @brief Performs a non-trivial copy of `count` elements from `origin` to `destination`.
	 *
	 * This function constructs new objects in-place using the copy constructor of T.
	 * It assumes `destination` points to uninitialized memory.
	 *
	 * @tparam T Type of the elements to copy.
	 * @param origin Pointer to the source array.
	 * @param destination Pointer to the destination array.
	 * @param count Number of elements to copy.
	 */
	template<typename T>
	void copy_objects_non_trivial(T* origin, T* destination, int count) {
		for (int i = 0; i < count; i++)
			new (&destination[i]) T(origin[i]);
	}

	/**
	 * @brief Performs a non-trivial partial copy from `origin` to `dest` with custom indices.
	 *
	 * This function constructs new objects in-place in `dest` using the copy constructor of T.
	 * It assumes the memory at destination is uninitialized.
	 *
	 * @tparam T Type of the elements to copy.
	 * @param origin Pointer to the source array.
	 * @param originIndex Starting index in the source array.
	 * @param dest Pointer to the destination array.
	 * @param destIndex Starting index in the destination array.
	 * @param count Number of elements to copy.
	 */
	template<typename T>
	void copy_objects_non_trivial(T* origin, int originIndex, T* dest, int destIndex, int count) {
		for (int i = 0; i < count; i++)
			new (&dest[destIndex + i]) T(origin[originIndex + i]);
	}
	/**
	 * @brief Copies an array of elements from `origin` to `dst`, with optional destruction.
	 *
	 * This function iterates over `origin` and copies each element into `dst`.
	 * If `pre_destroy_dst` is true, it destroys each destination element before copying.
	 * If `post_destroy_origin` is true, it destroys each source element after copying.
	 *
	 * @tparam T Type of the elements.
	 * @param origin Pointer to the source array.
	 * @param dst Pointer to the destination array.
	 * @param count Number of elements to copy.
	 * @param pre_destroy_dst Whether to destroy existing objects at destination before copying.
	 * @param post_destroy_origin Whether to destroy source objects after copying.
	 */
	template<typename T>
	void _copy_array(T* origin, T* dst, size_t count, bool pre_destroy_dst, bool post_destroy_origin) {
		sys::iter<T> niceIterator = sys::iter<T>(origin, count);
		T* dstOff = dst;

		for (T& srcDataElement : niceIterator) {
			_copy(dstOff++, &srcDataElement, pre_destroy_dst);
			if (post_destroy_origin)
				srcDataElement.~T();
		}
	}



	template<typename C, size_t s>
	void* clear(C(&x)[s]) {
		return _sys_memset(x, 0, sizeof(C) * s);  // Use sizeof to get the total size
	}
	template<class T>
	void memclr(T* t) {
		_sys_memset(t, 0, sizeof(T));  // Use sizeof to get the total size

	}
	void* memclr(unsigned int ptr, int count);
	void* memclr(void* x, int bytes_count);

	void* copy(void* srcSrc, void* srcDest, unsigned int size);

	template <typename C>
	void* copy(const C* srcSrc, C* srcDest) {
		return _sys_memcpy(srcDest, srcSrc, sizeof(C));
	}

	/// <summary>
	/// Performs a memory comparison, between two ranges.
	/// </summary>
	bool mcompare(const void* a, const void* b, unsigned int size);

	/// <summary>
	/// Performs an shallow memory comparison, between two instances.
	/// </summary>
	template <typename C>
	bool compare(const C* a, const C* b) {
		return _sys_memcmp(a, b, sizeof(C)) == 0;
	}

	template <typename T>
	inline T&& move(T& arg) {
		return static_cast<T&&>(arg);
	}
	void* move(void* srcSrc, void* srcDest, unsigned int size);

	template <typename C>
	void* move(C* srcSrc, C* srcDest) {
		return _sys_memmove(srcSrc, srcDest, sizeof(C));
	}


	unsigned long long  packTuple(int a, int b, int c);

	void unpackTuple(unsigned long long tuple, int& a, int& b, int& c);

	template<class T>
	const T* pointer_cast(const T* const ptr) {
		return const_cast<T*>(ptr);
	}

	template<class T>
	T* unsafe_pointer_cast(void* any) {
		return reinterpret_cast<T*>(any);
	}


	inline uintptr_t funcopdoff(uint32_t classed_ptr, uint32_t offset) {
		uint32_t table_value = *(uint32_t*)(classed_ptr);
		return *(uint32_t*)(table_value + offset);
	}
	uintptr_t make_uintptr(const void* any, ptrdiff_t diff) noexcept;
	uintptr_t make_uintptr(const volatile void* any, ptrdiff_t diff) noexcept;
	uintptr_t make_uintptr(const uintptr_t any, ptrdiff_t diff) noexcept;
}
inline void* operator new(size_t, void* px){
	return px;
}
#define _sfw sys::_fw << 


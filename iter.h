#pragma once
#include "pch.h"
#include "heap.h"
#include "unexpect.h"
#include "default_allocator.h"
#include "new"
namespace sys {
	template<typename T>
	struct iter {
		T* _ptr;
		size_t _size = 0;


		template<size_t N>
		iter(T(&array)[N]) : _ptr(array), _size(N) {}

		iter(T* ptr, size_t num) : _ptr(ptr), _size(num) {}

		iter(std::nullptr_t) : _ptr(nullptr), _size(0) {}

		T* begin() { return _ptr; }
		const T* begin() const { return _ptr; }
		T* end() { return _ptr + _size; }
		const T* end() const { return _ptr + _size; }

		size_t size() const { return _size; }
		T& operator[](size_t i) { return _ptr[i]; }
		const T& operator[](size_t i) const { return _ptr[i]; }

		bool not_null() const { return _ptr != nullptr; }

		static const iter<T> null_iter;
	};

	template<typename T, typename Allocator>
	class heap_iter_base {
		handle _ptr;

	public:
		/// <summary>
		/// Initializes an iterator with undefined content.
		/// </summary>
		/// <param name=""></param>
		heap_iter_base() : _ptr() {

		}

		heap_iter_base(const heap_iter_base&) = delete;

		heap_iter_base(heap_iter_base&& r) {
			steal(sys::move(r));
		}

		inline void steal(heap_iter_base&& other) {

			_ptr.steal(sys::move(other._ptr));
		}

		/// <summary>
		/// Initializes the inner elements array handle with the specified count. 
		/// </summary>
		/// <param name="dataCount"></param>
		void assign_new_crt(size_t dataCount) {
			if (dataCount == 0) {
				return;
			}
			auto& alloca = Allocator::instance();

			auto hdl = sys::newx::factory_explicit_allocate_type_array<T>(&alloca, dataCount);
			this->_ptr.reset();

			this->_ptr._unsafe_assign(hdl);
			hdl._unsafe_pop();// update remove hdl value since moved, this flags it correctly.
		}

		void assign(std::nullptr_t) {
			this->_ptr.reset();
		}

		/// <summary>
		/// Pops the handle used by this instance, and invalidates ownership for this scope. 
		/// </summary>
		/// <returns>An typed pointer for the heap objects array field, not being managed anymore by this iterator.</returns>

//T* pop() {
//	return (T*)_ptr.pop();
//}

		handle& hdl() { return this->_ptr; }
		const handle& hdl() const { return this->_ptr; }

		const T* ptr() const { return (T*)_ptr.ptr(); }
		T* ptr() { return (T*)_ptr.ptr(); }

		bool is_empty() const { return size() == 0 || this->hdl().ptr() == NULL; }

		T* begin() { return ((T*)_ptr.ptr()); }
		const T* begin() const { return ((T*)_ptr.ptr()); }
		T* end() { return((T*)_ptr.ptr()) + size(); }
		const T* end() const { return ((T*)_ptr.ptr()) + size(); }

		T& at(size_t i) { return ((T*)_ptr.ptr())[i]; }
		const T& at(size_t i) const { return ((T*)_ptr.ptr())[i]; }

		size_t size() const {
			return
				this->_ptr.size() / sizeof(T);
		}

		T& operator[](size_t i) {
			return ((T*)_ptr.ptr())[i];
		}
		const T& operator[](size_t i) const {
			const sys::handle& hdl = _ptr;
			__expect(hdl.ptr() != NULL);

			return ((T*)_ptr.ptr())[i];
		}

		heap_iter_base& operator =(std::nullptr_t) {
			assign(nullptr);
			return *this;
		}

		heap_iter_base& operator =(heap_iter_base&& other) {
			steal(sys::move(other));
			return *this;
		}

		heap_iter_base& operator=(sys::iter<T> other_content) {
			if (other_content._size == 0)
			{
				assign(nullptr);
			}
			else {
				assign_new_crt(other_content._size);
				int i = 0;
				for (T& val : other_content) {
					this->at(i) = val;
					++i;
				}
			}
			return *this;
		}
		bool not_null() const { return ((T*)_ptr.ptr()) != nullptr; }
	};

	template<typename T>
	using heap_iter = heap_iter_base<T, default_allocator_t>;
}
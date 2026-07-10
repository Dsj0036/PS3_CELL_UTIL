#pragma once
#include <typeinfo>
#include "..\no_inline.h"
#include "default_delete.h"

namespace sys {
	template<typename T, class deleter = sys::default_delete<T>>
	class unique_ptr {
		T* _px;
	public:
		unique_ptr(T* dynamic) : _px(dynamic) {}
		template<typename T2>
		unique_ptr(T2* dynamic) : _px(static_cast<T*>(dynamic)) {}

		unique_ptr() : unique_ptr(new T()) {}
		unique_ptr(std::nullptr_t) noexcept : _px(nullptr) {}
		unique_ptr(const unique_ptr&) = delete;
		unique_ptr(unique_ptr&& other) noexcept : _px(other._px) { other._px = nullptr; }

		inline T* get() { return _px; }
		inline const T* get() const { return _px; }

		const uintptr_t address() const {
			return reinterpret_cast<uintptr_t>(_px);
		}
		bool is_null() const {
			return _px == nullptr;
		}
		T* release() noexcept {
			T* p = _px;
			_px = nullptr;
			return p;
		}
		void dispose() noexcept {
			if (this->_px)
			{
				this->_px->~T();
				deleter()(this->_px);
				this->_px = nullptr;
			}

		}
		T* reset() {
			if (this->_px) {
				this->_px->~T();
				deleter()(this->_px);
			}

			T* p = _px;
			_px = nullptr;
			return p;
		}
		void reset(T* new_ptr) {
			reset();
			this->_px = new_ptr;
		}
		unique_ptr& operator= (T* x) noexcept {
			reset(x);
			return *this;
		}
		unique_ptr& operator= (unique_ptr&& x) noexcept {
			reset();
			this->_px = x._px;
			x._px = nullptr;
			return *this;
		}
		unique_ptr& operator= (std::nullptr_t) noexcept {
			reset();
			return *this;
		}
		template <class U, class E>  unique_ptr& operator= (unique_ptr<U, E>&& x) noexcept;
		unique_ptr& operator= (const unique_ptr&) = delete;

		inline T* operator ->() { return _px; }
		inline T* operator ->() const { return _px; }

		inline T& operator *() { return *_px; }
		inline const T& operator*()const { return *_px; }

		operator bool() const { return _px != nullptr; }
		operator const T* () const { return _px; }
		operator T* () { return _px; }

		~unique_ptr() {
			reset();
		}

	};



	template<typename T>
	inline sys::unique_ptr<T> make_unique(T* const& ptr) {
		return { ptr };
	}
}
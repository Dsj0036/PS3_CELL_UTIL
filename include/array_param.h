#pragma once
namespace sys {

	// Not recommended for no fundamental types.
	// Wraps an array iterator that can be constructed by casting explicit arrays with known sizes.
	template<typename T>
	struct array_param {

		array_param() = delete;

		template<size_t SIZE>
		array_param(T(&vals)[SIZE]) {
			//_vals = const_cast<T*>((const T*)vals);
			_vals = vals;
			_length = SIZE;
		}
		array_param(T& single_val) {
			_vals = &single_val;
			_length = 1;
		}

		size_t length() const {
			return _length;
		}
		const  T* data() const {
			return _vals;
		}

		T* data() {
			return _vals;
		}
	private:
		T* _vals{ nullptr };
		size_t _length{ 0 };
	};

}
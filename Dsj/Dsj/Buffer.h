#pragma once
#include "System.h"
#include "BinaryReader.h"
#include "include\collections\array.h"
#define assert(condition) __assert__(condition, __LINE__, __FILE__, #condition)

// include "additions\BinaryWriter.h"
class BinaryWriter;

/*
*	@brief Provides a span for managing a block of memory.
*/
typedef class Buffer {
	size_t size;
	byte* data;
public:
	/**
  * @brief Constructs a Buffer from a pointer to any data and its length.
  * @param any_ Pointer to the data.
  * @param length Length of the data.
  */
	Buffer(const void* any_, size_t length) : size(length), data((byte*)_sys_memalign(16, size)) {
		assert(data != nullptr);
		sys::memcpy(data, any_, size);
	}

	/**
  * @brief Constructs a Buffer from a vector of bytes.
  * @param vec Vector of bytes.
  */
	Buffer(const vector<byte>& vec) : size(vec.size()), data((byte*)_sys_memalign(16, size)) {
		assert(data != nullptr);
		sys::memcpy(data, vec.data(), size);
	}

	/**
  * @brief Constructs a Buffer from a System::Array of bytes.
  * @param arr System::Array of bytes.
  */
	Buffer(const System::Array<byte>& arr) : size(arr.Count()), data((byte*)_sys_memalign(16, size)) {
		assert(data != nullptr);
		sys::memcpy(data, arr.Raw(), size);
	}

	/**
  * @brief Constructs a Buffer with a specified length.
  * @param length Length of the buffer.
  */
	Buffer(size_t length) : size(length), data((byte*)_sys_memalign(16, length)) {
		assert(data != nullptr);
	}

	/**
  * @brief Copy constructor for Buffer.
  * @param buff Buffer to copy from.
  */
	Buffer(const Buffer& buff) {
		*this = buff;
	}

	Buffer() = delete;

	/**
  * @brief Gets the size of the buffer.
  * @return Size of the buffer.
  */
	size_t getSize() const {
		return size;
	}

	/**
  * @brief Gets a constant pointer to the data.
  * @return Constant pointer to the data.
  */
	const byte* getData() const {
		return data;
	}

	/**
  * @brief Gets a pointer to the data.
  * @return Pointer to the data.
  */
	byte* const getData() {
		return data;
	}

	/**
  * @brief Creates a BinaryReader for the buffer.
  * @return BinaryReader for the buffer.
  */
	BinaryReader read() const {
		return { data, size };
	}

	/**
  * @brief Creates a BinaryWriter for the buffer.
  * @return BinaryWriter for the buffer.
  */
	BinaryWriter write();

	/**
  * @brief Sets all bytes in the buffer to zero.
  */
	inline void zero() {
		sys::memset(data, 0, size);
	}

	/**
  * @brief Copies the buffer to another buffer.
  * @param dst Destination buffer.
  */
	inline void copyTo(Buffer& dst) const {
		assert(dst.size >= size);
		sys::memcpy(dst.data, data, size);
	}

	/**
  * @brief Copies data from another buffer to this buffer.
  * @param src Source buffer.
  */
	inline void impregnate(const Buffer& src) {
		impregnate(src.data, src.size);
	}

	/**
  * @brief Copies data from a vector of bytes to this buffer.
  * @param vec Vector of bytes.
  */
	inline void impregnate(const vector<byte>& vec) {
		impregnate(vec.data(), vec.size());
	}

	/**
  * @brief Copies data from a byte array to this buffer.
  * @param src Source byte array.
  */
	template<size_t implicit>
	inline void impregnate(const byte* src) {
		impregnate(src, implicit);
	}

	/**
  * @brief Copies data from a byte array to this buffer.
  * @param src Source byte array.
  * @param length Length of the source byte array.
  */
	inline void impregnate(const byte* src, size_t length) {
		assert(length >= size);
		sys::memcpy(data, src, MIN(length, size));
	}

	/**
  * @brief Clones the buffer.
  * @return Cloned buffer.
  */
	inline Buffer clone() const {
		return *this;
	}

	/**
  * @brief Converts the buffer to a System::Array of bytes.
  * @return System::Array of bytes.
  */
	System::Array<byte> toArray() const {
		System::Array<byte> arr;
		arr.AddRange(data, size);
		return arr;
	}

	/**
  * @brief Converts the buffer to a vector of bytes.
  * @return Vector of bytes.
  */
	vector<byte> toVector() const {
		vector<byte> vec;
		vec.f_inject_at(0, data, size);
		return vec;
	}

	/**
  * @brief Resizes the buffer.
  * @param newSize New size of the buffer.
  */
	void resize(size_t newSize) {
		byte* newData = (byte*)_sys_memalign(16, newSize);
		sys::memcpy(newData, data, MIN(size, newSize));
		_sys_free(data);
		data = newData;
		size = newSize;
	}

	/**
  * @brief Assignment operator for Buffer.
  * @param src Source buffer.
  * @return Reference to this buffer.
  */
	const Buffer& operator=(const Buffer& src) {
		if (data) {
			_sys_free(data);
		}
		size = src.size;
		data = (byte*)_sys_memalign(16, size);
		sys::memcpy(data, src.data, size);
		return *this;
	}

	/**
  * @brief Indexing operator for Buffer.
  * @param r Index.
  * @return Reference to the byte at the specified index.
  */
	byte& operator[](size_t r) {
		assert(r < size && data != nullptr);
		return data[r];
	}

	/**
  * @brief Constant indexing operator for Buffer.
  * @param r Index.
  * @return Constant reference to the byte at the specified index.
  */
	const byte& operator[](size_t r) const {
		assert(r < size && data != nullptr);
		return data[r];
	}

	/**
  * @brief Dereference operator for Buffer.
  * @return Reference to the first byte in the buffer.
  */
	byte& operator*() {
		return *data;
	}

	/**
  * @brief Pointer arithmetic operator for Buffer.
  * @param r Offset.
  * @return Pointer to the byte at the specified offset.
  */
	byte* const operator+(size_t r) {
		return data + r;
	}

	/**
  * @brief Constant pointer arithmetic operator for Buffer.
  * @param r Offset.
  * @return Constant pointer to the byte at the specified offset.
  */
	const byte* const operator+(size_t r) const {
		return data + r;
	}

	/**
  * @brief Conversion operator to void pointer.
  * @return Void pointer to the data.
  */
	operator void* () {
		return data;
	}

	/**
  * @brief Constant conversion operator to void pointer.
  * @return Constant void pointer to the data.
  */
	operator const void* () const {
		return data;
	}

	/**
  * @brief Conversion operator to uintptr_t.
  * @return uintptr_t representation of the data pointer.
  */
	operator const uintptr_t() const {
		return (uintptr_t)data;
	}

	/**
  * @brief Destructor for Buffer.
  */
	~Buffer() {
		if (data) {
			_sys_free(data);
		}
	}
} Span;
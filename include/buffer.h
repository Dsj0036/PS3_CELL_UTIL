#pragma once
/// @file buffer.h
/// @brief Lightweight buffer management template class for efficient memory operations.
/// @details This header provides a generic buffer template class with support for
///          custom allocators, move semantics, and various memory operations.

#pragma once
#include "_ns.h"
#include <sys\integertypes.h>
#include "unexpect.h"
#include <alloca.h>
#include <xmemory>
#include "traits.h"
#include "forward.h"
#include <xmemory>
_SYS_NS

/// @struct __empty_buffer_tag
/// @brief Tag type used to initialize empty buffers.
/// @details Used as a marker type for creating uninitialized or empty buffer instances.
struct __empty_buffer_tag final {};

/// @brief Global empty buffer tag instance.
static const __empty_buffer_tag empty_buffer{};

/// @template lightweight_buffer
/// @brief A lightweight, templated buffer class for efficient memory management.
/// @tparam _Ty The element type stored in the buffer.
/// @tparam size_type The type used for size calculations (typically size_t).
/// @tparam Allocator The allocator used for memory allocation/deallocation (default: std::allocator<_Ty>).
/// @details Provides efficient memory management with support for move semantics,
///          cloning, merging, and various utility functions for buffer manipulation.
template<class _Ty, class size_type, class Allocator = std::allocator<_Ty>>
class lightweight_buffer {
	size_type mSize{ 0 };           ///< Number of elements currently stored in the buffer.
	_Ty* mBuff{ nullptr };          ///< Pointer to the allocated buffer memory.
private:
	bool mOwnsMemory{ true };
public:
	/// @brief Constructs an empty buffer using the empty_buffer tag.
	/// @param Tag The empty_buffer_tag indicating initialization as empty.
	lightweight_buffer(const __empty_buffer_tag&)
		: mSize(0), mBuff(nullptr) {
	}

	/// @brief Constructs an empty buffer.
	lightweight_buffer()
		: mSize(0), mBuff(nullptr) {
	}
	lightweight_buffer(lightweight_buffer& other) {
		steal(other);
	}

	lightweight_buffer& operator =(lightweight_buffer& other) {
		steal(other);
		return *this;
	}
	
	/// @brief Move constructor.
	/// @param other The buffer to move from (will be left empty).
	/// @details Transfers ownership of the buffer memory from the source object.
	
	lightweight_buffer(lightweight_buffer&& other) {
		steal(other);
	}
	lightweight_buffer(const lightweight_buffer& other) = delete;

	void steal(lightweight_buffer& other) {
		this->mSize = other.mSize;
		this->mBuff = other.mBuff;
		this->mOwnsMemory = other.mOwnsMemory;
		other.mSize = 0;
		other.mBuff = nullptr;
		other.mOwnsMemory = false;
	}

	/// @brief Clone function. 
	/// Creates a deep copy of the source buffer's data.
	/// @param other The buffer to copy from.
	void clone_from(const lightweight_buffer& other) {
		this->dispose();
		this->mSize = other.mSize;
		_construct();
		_sys_memcpy(mBuff, other.mBuff, sizeof(_Ty) * other.mSize);
	}

	/// @brief Constructs a buffer with a specified number of uninitialized elements.
	/// @param size The number of elements to allocate.
	lightweight_buffer(size_t size)
		: mBuff(), mSize(size)
	{
		_construct();
	}

	/// @brief Constructs a buffer filled with a repeated value.
	/// @param all The value to fill the buffer with.
	/// @param count The number of elements to allocate and fill.
	lightweight_buffer(_Ty all, size_t count)
		: mBuff(), mSize(count)
	{
		_construct();
		sys::memset(mBuff, static_cast<int>(all), sizeof(_Ty) * mSize);
	}

	/// @brief Constructs a buffer from an initializer list.
	/// @param list The initializer list containing initial values.
	//lightweight_buffer(const std::initializer_list<_Ty>& list) {
	//	this->mSize = list.size();
	//	_construct();
	//	sys::memcpy(this->mBuff, list.begin(), sizeof(_Ty) * mSize);
	//}

private:
	/// @brief Internal helper function to allocate buffer memory.
	/// @throws Assertion failure if memory allocation fails.
	inline void _construct() {
		this->mBuff = allocator().allocate(mSize);
		if (!mBuff) {
			FAIL sys::out_of_memory_error{};
		}
	}

public:
	/// @brief Returns an rvalue reference to this buffer (for explicit move semantics).
	/// @return An rvalue reference to this buffer object.
	lightweight_buffer&& move() {
		return sys::move(*this);
	}

	/// @brief Returns a const pointer to the buffer data.
	/// @return Const pointer to the first element.
	const _Ty* c_ptr() const { return mBuff; }

	/// @brief Returns a mutable pointer to the buffer data.
	/// @return Pointer to the first element.
	_Ty* c_ptr() { return mBuff; }

	/// @brief Returns a const pointer to the buffer data.
	/// @return Const pointer to the first element.
	const _Ty* data() const { return mBuff; }

	/// @brief Returns a mutable pointer to the buffer data.
	/// @return Pointer to the first element.
	_Ty* data() { return mBuff; }


	void set_ref_data(_Ty* data, size_t size) {
		this->dispose();
		this->mBuff = data;
		this->mSize = size;
		this->mOwnsMemory = false;
	}

	/// @brief Conversion operator to mutable byte pointer.
	/// @return Pointer to buffer data cast to byte*.
	operator unsigned char* () { return this->data(); }

	/// @brief Conversion operator to const byte pointer.
	/// @return Const pointer to buffer data cast to const byte*.
	operator const unsigned char* () const { return this->data(); }

	/// @brief Returns an iterator to the beginning of the buffer.
	/// @return Pointer to the first element.
	_Ty* begin() { return mBuff; }

	/// @brief Returns an iterator to the end of the buffer (one past the last element).
	/// @return Pointer one past the last element.
	_Ty* end() { return mBuff + mSize; }

	/// @brief Returns a const iterator to the beginning of the buffer.
	/// @return Const pointer to the first element.
	const _Ty* begin() const { return mBuff; }

	/// @brief Returns a const iterator to the end of the buffer.
	/// @return Const pointer one past the last element.
	const _Ty* end() const { return mBuff + mSize; }

	/// @brief Assignment operator for empty_buffer_tag (empties the buffer).
	/// @param Tag The empty_buffer_tag marker.
	/// @return Reference to this buffer after disposal.
	/// @details Clears and deallocates the buffer contents.
	lightweight_buffer& operator =(sys::__empty_buffer_tag) {
		this->dispose();
		return *this;
	}

	/// @brief Fills the buffer with zeros.
	/// @warning This function bypasses type safety and treats data as raw bytes.
	/// @details Sets all bytes in the buffer to zero using memset.
	void set_zero() {
		_sys_memset(mBuff, 0, sizeof(_Ty) * mSize);
	}

	/// @brief Compares this buffer with another buffer.
	/// @param other The buffer to compare with.
	/// @return 0 if equal, 1 if other is larger, -1 if other is smaller.
	/// @details Comparison is based on size first, then on memory contents.
	int compare(const lightweight_buffer& other) const {
		if (other.size() > this->size()) return 1;
		if (other.size() < this->size()) return -1;
		return _sys_memcmp(this->mBuff, other.mBuff, this->size());
	}

	/// @brief Copies a portion of this buffer to an external location.
	/// @param out Destination pointer where data will be copied.
	/// @param src_offset Offset in this buffer from which to start copying.
	/// @param src_size Source size parameter (currently unused).
	/// @param dst_size Destination size specifying the copy range.
	/// @return Number of elements copied.
	/// @details Copies data from src_offset to dst_size into the external buffer.
	size_t copy(const _Ty* out, size_t src_offset, size_t src_size, size_t dst_size) const {
		sys::memcpy(out, c_ptr() + src_offset,
			(dst_size - src_offset) * type_size());
		return (dst_size - src_offset);
	}

	/// @brief Creates a deep copy of this buffer.
	/// @return A new buffer containing a copy of this buffer's data.
	/// @details Uses move semantics to return the cloned buffer efficiently.
	lightweight_buffer clone() const {
		lightweight_buffer result = sys::empty_buffer;
		result.assign(this->mBuff, this->mSize);
		return result.move();
	}

	/// @brief Returns the capacity of the buffer (number of elements).
	/// @return Const reference to the number of elements allocated.
	const size_t& capacity() const {
		return mSize;
	}

	/// @brief Returns the size of the buffer in bytes.
	/// @return Total size in bytes (element count × element size).
	size_t size() const {
		return sizeof(_Ty) * mSize;
	}

	/// @brief Checks if the buffer contains allocated data.
	/// @return true if the buffer is allocated and non-empty, false otherwise.
	bool occupied() const {
		return this->mBuff != nullptr && this->mSize != 0;
	}

	/// @brief Resizes the buffer to a new size.
	/// @param count The new number of elements.
	/// @details Reallocates memory, preserves existing data up to the smaller size,
	///          and zero-initializes new elements if the buffer is enlarged.
	void set_size(size_t count) {
		_Ty* new_buffer = allocator().allocate(sizeof(_Ty) * count);


		size_t common = sys::min(mSize, count);
		if (mBuff)
			sys::memcpy(new_buffer, mBuff, common * sizeof(_Ty));

		if (count > mSize)
			sys::memset(new_buffer + common, 0, (count - common) * sizeof(_Ty));

		dispose();

		mBuff = new_buffer;
		mSize = count;
	}

	/// @brief Resets the buffer to an empty state.
	/// @details Deallocates all memory and clears internal pointers.
	void reset() {
		this->dispose();
		this->mOwnsMemory = true;
	}

	/// @brief Resets the buffer and assigns it to external memory.
	/// @param other Pointer to external memory to manage.
	/// @param size Number of elements in the external memory.
	/// @warning This function is unsafe as it assumes ownership of unmanaged memory.
	/// @details The buffer will attempt to deallocate this memory on disposal.
	void reset(_Ty* other, size_t size) {
		reset();
		this->mBuff = other;
		this->mSize = size;
		this->mOwnsMemory = false;
	}

	/// @brief Resets the buffer and assigns it to external memory.
	/// @param other Pointer to external memory to manage.
	/// @param size Number of elements in the external memory.
	/// @warning This function is unsafe as it assumes ownership of unmanaged memory.
	/// @details The buffer will attempt to deallocate this memory on disposal.
	void reset_heap(_Ty* other, size_t size) {
		reset();
		this->mBuff = other;
		this->mSize = size;
		this->mOwnsMemory = true;
	}
	/// @brief Allocates a new buffer of the specified size.
	/// @param count Number of elements to allocate.
	/// @details Disposes any existing buffer before allocation.
	void assign(size_t count) {
		dispose();
		mBuff = allocator().allocate(count);
		__expect(mBuff != NULL);
		mSize = count;
	}

	/// @brief Allocates a buffer and copies data from an external source.
	/// @param other Pointer to the source data.
	/// @param count Number of elements to copy.
	/// @details Disposes any existing buffer before allocation and copying.
	void assign(const _Ty* other, size_t count) {
		dispose();
		mBuff = allocator().allocate(count);
		__expect(mBuff != NULL);
		mSize = count;

		sys::memcpy(this->mBuff, other, sizeof(_Ty) * count);
	}

	/// @brief Returns the allocator instance for this buffer.
	/// @return An instance of the Allocator type.
	static Allocator allocator() {
		return {};
	}

	/// @brief Returns the size of a single element type.
	/// @return Size in bytes of type _Ty.
	/// @details Compile-time constant expression.
	static size_t constexpr type_size() {
		return sizeof(_Ty);
	}

	/// @brief Deallocates the buffer memory and resets internal state.
	/// @details Safe to call multiple times; checks for nullptr before deallocation.
	void dispose() {
		if (mBuff && mOwnsMemory) {
			allocator().deallocate(mBuff, mSize);
			mBuff = nullptr;
		}
		mSize = 0;
		mOwnsMemory = true;
	}
	lightweight_buffer& operator =(const lightweight_buffer& other) {
		this->assign(other.data(), other.mSize);
		return *this;
	}


	/// @brief Checks if the buffer has been disposed.
	/// @return true if both pointer and size are zero, false otherwise.
	bool disposed() const {
		return this->mBuff == nullptr && this->mSize == 0;
	}

	/// @brief Merges two buffers into a new buffer.
	/// @param left The first buffer to merge.
	/// @param right The second buffer to merge.
	/// @return A new buffer containing the concatenated data from both buffers.
	/// @details Creates a new buffer with the combined size and copies data in order.
	static lightweight_buffer merge(const lightweight_buffer& left, const lightweight_buffer& right)
	{
		size_t resulting_size = left.mSize + right.mSize;
		lightweight_buffer content = empty_buffer;
		_Ty* buffer = allocator().allocate(resulting_size);
		_sys_memcpy(buffer, left.data(), left.size());
		_sys_memcpy(buffer + left.size(), right.data(), right.size());
		content.reset(buffer, resulting_size);
		return content;
	}
	size_t append(const lightweight_buffer& other) {
		if (!other.occupied()) return this->mSize;

		lightweight_buffer result(this->mSize + other.mSize);
		if (this->occupied())
			sys::memcpy(result.data(), this->data(), this->mSize * sizeof(_Ty));

		sys::memcpy(result.data() + this->mSize, other.data(), other.mSize * sizeof(_Ty));

		this->dispose();
		this->mBuff = result.mBuff;
		this->mSize = result.mSize;
		this->mOwnsMemory = true;

		result.mBuff = nullptr;
		result.mSize = 0;
		return this->mSize;
	}
	size_t append(const _Ty* buff, size_t count) {
		lightweight_buffer result = lightweight_buffer(0, this->mSize + (count * sizeof(_Ty)));
		_sys_memcpy(result.mBuff + this->mSize, buff, count * sizeof(_Ty));

		this->mBuff = result.mBuff;
		this->mSize = result.mSize;
		result.mBuff = nullptr;
		result.mSize = 0;
		return this->mSize;
	}

	

	/// @brief Destructor.
	/// @details Automatically calls dispose() to clean up allocated resources.
	~lightweight_buffer()
	{
		dispose();
	}

};

/// @typedef buffer
/// @brief Convenience typedef for a byte buffer (unsigned char elements).
using buffer = lightweight_buffer<unsigned char, size_t>;

/// @typedef const_buffer
/// @brief Convenience typedef for a const byte buffer.
using const_buffer = const lightweight_buffer<unsigned char, size_t>;

/// @typedef char_buffer
/// @brief Convenience typedef for a character buffer.
using char_buffer = lightweight_buffer<char, size_t>;

_SYS_ENS


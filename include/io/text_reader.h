#pragma once
#include "binary_reader.h"
#include "..\collection.h"
_SYS_NS

/**
 * @file text_reader.h
 * @brief Text-based stream reader utilities.
 */

 /**
  * @class text_reader
  * @brief Provides sequential reading and searching operations over a text buffer.
  *
  * The text_reader class wraps an internal binary reader and exposes higher-level
  * text operations such as character reading, string extraction, comparisons,
  * seeking and pattern searching.
  *
  * The reader does not own the underlying stream data unless explicitly managed
  * by the associated stream/allocator implementation.
  *
  * Supports:
  * - Single byte character streams
  * - Wide character streams (16-bit alignment required)
  * - Sequential and random seeking
  * - Case-sensitive and case-insensitive comparisons
 */
	class text_reader
{
	binary_reader reader;

public:


	text_reader(sys::stream* stream) : reader(stream) {}


	void _unsafe_assign(binary_reader& other) {
		reader._unsafe_assign(&other);
	}

	/**
	 * @brief Checks whether the reader reached the end of the stream.
	 *
	 * @return true if no more readable data is available, otherwise false.
	 */
	bool is_eof() const;


	/**
	 * @brief Gets a pointer to the current read position.
	 *
	 * @return Pointer to the current byte position.
	 */
	const char* cur() const;


	/**
	 * @brief Gets a writable pointer to the current read position.
	 *
	 * @return Pointer to the current byte position.
	 */
	char* cur();


	/**
	 * @brief Gets the current wide-character position.
	 *
	 * The current stream position must be aligned to a 16-bit boundary.
	 *
	 * @throws invalid_operation_error If the current position is not aligned.
	 *
	 * @return Pointer to the current wide-character position.
	 */
	const wchar_t* curw() const;


	/**
	 * @brief Gets the writable wide-character position.
	 *
	 * @throws invalid_operation_error If the current position is not aligned.
	 *
	 * @return Pointer to the current wide-character position.
	 */
	wchar_t* curw();


	/**
	 * @brief Gets the current stream offset.
	 *
	 * @return Current byte offset from the beginning of the stream.
	 */
	size_t offset() const;


	/**
	 * @brief Gets the total readable length.
	 *
	 * @return Total size of the underlying data.
	 */
	uint64_t length() const;


	/**
	 * @brief Reads a fixed amount of bytes as a string.
	 *
	 * @param c Number of bytes to read.
	 *
	 * @throws invalid_argument_error If size is zero.
	 * @throws out_of_memory_error If requested data exceeds remaining data.
	 *
	 * @return Newly created string containing the requested data.
	 */
	sys::lwstring read(int32_t c);


	/**
	 * @brief Reads a fixed amount of wide characters.
	 *
	 * The stream position must be aligned to a 16-bit boundary.
	 *
	 * @param c Number of wide characters to read.
	 *
	 * @throws invalid_operation_error If the stream is not aligned.
	 *
	 * @return Wide string containing the requested data.
	 */
	sys::lwwstring readw(int32_t c);


	/**
	 * @brief Reads until the specified character is found.
	 *
	 * The delimiter is not consumed.
	 *
	 * @param c Delimiter character.
	 * @param out Optional output string.
	 *
	 * @return Number of characters read.
	 */
	int read_to(char c, sys::lwstring* out);


	int read_line(sys::lwstring* out);

	/**
	 * @brief Reads wide characters until the specified delimiter is found.
	 *
	 * @param c Wide delimiter character.
	 * @param out Optional output string.
	 *
	 * @return Number of characters read.
	 */
	int readw_to(wchar_t c, sys::lwwstring* out);


	/**
	 * @brief Reads all remaining data.
	 *
	 * @return Remaining stream contents.
	 */
	sys::lwstring read_to_end();


	/**
	 * @brief Reads all remaining wide-character data.
	 *
	 * @return Remaining wide string contents.
	 */
	sys::lwwstring readw_to_end();


	/**
	 * @brief Reads a single byte character.
	 *
	 * @return Character value.
	 */
	char read_char();


	/**
	 * @brief Reads a single wide character.
	 *
	 * @return Wide character value.
	 */
	wchar_t read_wchar();


	/**
	 * @brief Peeks the next byte character without advancing.
	 *
	 * @return Next character.
	 */
	char peek_char();


	/**
	 * @brief Peeks the next wide character without advancing.
	 *
	 * @return Next wide character.
	 */
	wchar_t peek_wchar();


	/**
	 * @brief Compares data at the current position.
	 *
	 * @param expected Expected string.
	 * @param offset Relative offset.
	 * @param count Number of characters to compare.
	 *
	 * @return Comparison result.
	 */
	int compare(
		const sys::lwstring& expected,
		int32_t offset,
		int32_t count
	) const;


	/**
	 * @brief Performs an exact comparison.
	 *
	 * @return Comparison result.
	 */
	int compare_exact(
		const sys::lwstring& expected,
		int32_t offset,
		int32_t count
	) const;


	/**
	 * @brief Checks whether the next characters match a string.
	 *
	 * @param expected Expected value.
	 * @param comparison Comparison mode.
	 *
	 * @return true when the expected value matches.
	 */
	bool expect(
		const sys::lwstring& expected,
		int comparison
	) const;


	/**
	 * @brief Checks for a string and optionally advances the stream.
	 *
	 * @param expected Expected value.
	 * @param comparison Comparison mode.
	 * @param then_skip Advance when matched.
	 *
	 * @return true if matched.
	 */
	bool expect(
		const sys::lwstring& expected,
		int comparison,
		bool then_skip
	);


	bool expect_cstr(const char* str, int comparison, bool then_skip);


	/**
	 * @brief Advances the reader position.
	 *
	 * @param count Number of bytes to skip.
	 *
	 * @return New position.
	 */
	int skip(size_t count);


	/**
	 * @brief Skips one character if it matches.
	 *
	 * @param ch Character to test.
	 *
	 * @return Number of skipped bytes.
	 */
int skip_char(char ch);


/**
 * @brief Moves the reader position.
 *
 * @param offset Offset amount.
 * @param origin Seek origin.
 *
 * @return New absolute position.
 */
uint64_t seek(
	int64_t offset,
	int origin
);


/**
 * @brief Finds the next occurrence of a string.
 *
 * @param str String to search.
 * @param comparison Comparison mode.
 *
 * @return Relative index or -1 if not found.
 */
int32_t next_index_of(
	const sys::lwstring& str,
	int comparison
);


/**
 * @brief Finds the next byte character.
 *
 * @return Relative index or -1 if not found.
 */
int32_t next_index_of(char ch);


/**
 * @brief Finds the next wide character.
 *
 * @return Relative index or -1 if not found.
 */
int32_t next_index_of(wchar_t ch);


/**
 * @brief Finds an absolute byte position.
 *
 * @return Absolute index or -1 if not found.
 */
int32_t find_abs_index_of(char ch);


/**
 * @brief Finds an absolute wide character position.
 *
 * @return Absolute index or -1 if not found.
 */
int32_t find_abs_index_of(wchar_t ch);


/**
 * @brief Moves the reader to the next occurrence of a character.
 *
 * @param ch Character to find.
 * @param out_advanced_offset Optional amount advanced.
 *
 * @return true if found.
 */
bool seek_to_next_char(
	char ch,
	int* out_advanced_offset = nullptr
);


/**
 * @brief Moves the reader to the next occurrence of a wide character.
 *
 * @return true if found.
 */
bool seek_to_next_char(
	wchar_t ch,
	int* out_advanced_offset = nullptr
);
};


class memory_stream;
/**
 * @class scoped_text_reader
 * @brief RAII wrapper providing text reading over a managed memory stream.
 *
 * The scoped_text_reader class creates an internal memory_stream from an
 * external text buffer and exposes text_reader functionality while maintaining
 * ownership of the underlying stream lifetime.
 *
 * The internal stream is allocated through the provided allocator and is
 * automatically disposed when the scoped_text_reader instance is destroyed.
 *
 * Lifetime relationship:
 *
 * @code
 * scoped_text_reader
 *      |
 *      +-- typed_handle<memory_stream>
 *              |
 *              +-- memory_stream
 *                      |
 *                      +-- text_reader
 * @endcode
 *
 * The source buffer is not copied. The created memory stream references the
 * provided memory region.
 */
class scoped_text_reader
{
protected:

	/**
	 * @brief Internal text reader instance.
	 *
	 * This object provides the actual text parsing operations.
	 */
	text_reader reader;


	/**
	 * @brief Owned memory stream handle.
	 *
	 * Maintains the lifetime of the memory stream used by the reader.
	 */
	sys::typed_handle<memory_stream> source;


	/**
	 * @brief Constructs a scoped reader over an existing text buffer.
	 *
	 * Creates a memory_stream using the specified allocator and initializes
	 * the internal reader to operate over that stream.
	 *
	 * The buffer is not copied and must remain valid while the reader is used.
	 *
	 * @param buffer Pointer to the source text buffer.
	 * @param length Size of the buffer in bytes.
	 * @param allocator Allocator used for the internal stream allocation.
	 */
	scoped_text_reader(
		const char* buffer,
		size_t length,
		sys::alloc* allocator
	);


public:	
	/**
	 * @brief Gets access to the managed memory stream handle.
	 *
	 * @return Mutable reference to the internal stream handle.
	 */
	inline sys::typed_handle<memory_stream>& stream()
	{
		return source;
	}


	/**
	 * @brief Gets constant access to the managed memory stream handle.
	 *
	 * @return Constant reference to the internal stream handle.
	 */
	inline const sys::typed_handle<memory_stream>& stream() const
	{
		return source;
	}


	/**
	 * @brief Provides pointer-like access to the text reader.
	 *
	 * Allows usage equivalent to accessing a text_reader instance directly.
	 *
	 * Example:
	 *
	 * @code
	 * scoped_text_reader reader(data, size, allocator);
	 *
	 * reader->read_to_end();
	 * @endcode
	 *
	 * @return Pointer to the internal text reader.
	 */
	inline text_reader* operator->()
	{
		return &reader;
	}


	/**
	 * @brief Provides constant pointer-like access to the text reader.
	 *
	 * @return Constant pointer to the internal text reader.
	 */
	inline const text_reader* operator->() const
	{
		return &reader;
	}


	/**
	 * @brief Destroys the scoped reader.
	 *
	 * Releases the owned memory stream resource.
	 */
	~scoped_text_reader() noexcept;



	class detail final{
		detail() = delete;
	public:
		static scoped_text_reader from_string_view(sys::string_view view, sys::alloc* alloc);
		static scoped_text_reader from_string(const sys::lwstring& str, sys::alloc* alloc, size_t length = 0);
	};
};


inline scoped_text_reader read_string_view_scoped(const string_view& view) {
	return scoped_text_reader::detail::from_string_view(view, sys::default_allocator);
}

inline scoped_text_reader read_string_scoped(const sys::lwstring& string) {
	return scoped_text_reader::detail::from_string(string, sys::default_allocator, 0);
}

inline scoped_text_reader read_string_scoped(const sys::lwstring& string, size_t length) {
	return scoped_text_reader::detail::from_string(string, sys::default_allocator, length);
}




inline scoped_text_reader read_string_view_scoped(const string_view& view, sys::alloc* allocator) {
	return scoped_text_reader::detail::from_string_view(view, allocator);
}

inline scoped_text_reader read_string_scoped(const sys::lwstring& string, sys::alloc* allocator) {
	return scoped_text_reader::detail::from_string(string, allocator, 0);
}

inline scoped_text_reader read_string_scoped(const sys::lwstring& string, size_t length, sys::alloc* allocator) {
	return scoped_text_reader::detail::from_string(string, allocator, length);
}

_SYS_ENS
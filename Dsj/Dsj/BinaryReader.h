#pragma once
#include "System.h"
#include "include\io.h"
#include "include\io\FileStream.hpp"	
#include "include\io\MemoryStream.hpp"	
#include "string_stream.h"


/**
 * @class BinaryReader
 * @brief A class to read primitive data types as binary values in a specific encoding.
 */
class BinaryReader {
	byte* origin;   ///< Pointer to the origin of the data.
	byte* position; ///< Pointer to the current position in the data.
	size_t length;  ///< Length of the data.

public:
	/**
  * @brief Constructs a BinaryReader with the specified data and length.
  * @param origin Pointer to the data.
  * @param length Length of the data.
  */
	BinaryReader(const void* origin, size_t length) {
		this->origin = (byte*)origin;
		this->position = this->origin;
		this->length = length;
	}

	int32_t offset() const {
		return (int32_t)(position - origin);
	}

	/**
  * @brief Copies a specified number of bytes from the current position to the buffer.
  * @param buffer Pointer to the buffer where data will be copied.
  * @param count Number of bytes to copy.
  */
	void copy(void* buffer, size_t count) {
		assert(position != nullptr && position < origin + length);
		assert(position + count < origin + length);
		sys::memcpy(buffer, position, count);
	}

	/**
  * @brief Copies a specified number of bytes from a specified offset to the buffer.
  * @param buffer Pointer to the buffer where data will be copied.
  * @param srcOff Offset from the current position.
  * @param dstLen Number of bytes to copy.
  */
	void copy(void* buffer, size_t srcOff, size_t dstLen) {
		assert(position != nullptr && position < origin + length);
		assert(position + srcOff < origin + length);
		sys::memcpy(buffer, position + srcOff, dstLen);
	}
	std::string SubstrsrchAny(char first, ...) {
		vector<char> delimiters;

		// Captura los delimitadores
		va_list args;
		va_start(args, first);
		delimiters.push_back(first);

		while (true) {
			char next = va_arg(args, int); // 'char' se promueve a 'int' en va_arg
			if (next == '\0') break;
			delimiters.push_back(next);
		}
		va_end(args);

		// Comienza la lectura
		vector<char> str;
		while (!isEOF()) {
			char ch = Peek();
			if (std::find(delimiters.begin(), delimiters.end(), ch) != delimiters.end()) {
				break;
			}
			str.push_back(ReadInt8());
		}

		return std::string(str.data(), str.size());
	}



	/**
  * @brief Peeks at the next byte without advancing the position.
  * @return Reference to the next byte.
  */
	byte& Peek() {
		assert(position != nullptr && position < origin + length);
		return *position;
	}
	/*
	*	@brief Peeks at the byte at the specified offset without advancing the position.
	*	@return Reference to the byte at the specified offset.
	*/
	byte& Peek(size_t off) const {
		assert(position != nullptr && position + off < origin + length);
		return *(position + off);
	}

	/**
  * @brief Reads a 32-bit integer from the current position.
  * @return The 32-bit integer read.
  */
	int32_t ReadInt32() {
		assert(position != nullptr && position < origin + length);
		int32_t value = *(int32_t*)position;
		position += sizeof(int32_t);
		return value;
	}

	/**
  * @brief Reads a 32-bit unsigned integer from the current position.
  * @return The 32-bit unsigned integer read.
  */
	uint32_t ReadUInt32() {
		assert(position != nullptr && position < origin + length);
		uint32_t value = *(uint32_t*)position;
		position += sizeof(uint32_t);
		return value;
	}

	/**
  * @brief Reads a 16-bit integer from the current position.
  * @return The 16-bit integer read.
  */
	int16_t ReadInt16() {
		assert(position != nullptr && position < origin + length);
		int16_t value = *(int16_t*)position;
		position += sizeof(int16_t);
		return value;
	}

	/**
  * @brief Reads a 16-bit unsigned integer from the current position.
  * @return The 16-bit unsigned integer read.
  */
	uint16_t ReadUInt16() {
		assert(position != nullptr && position < origin + length);
		uint16_t value = *(uint16_t*)position;
		position += sizeof(uint16_t);
		return value;
	}

	/**
  * @brief Reads an 8-bit integer from the current position.
  * @return The 8-bit integer read.
  */
	int8_t ReadInt8() {
		assert(position != nullptr && position < origin + length);
		int8_t value = *(int8_t*)position;
		position += sizeof(int8_t);
		return value;
	}

	/**
  * @brief Reads an 8-bit unsigned integer from the current position.
  * @return The 8-bit unsigned integer read.
  */
	uint8_t ReadUInt8() {
		assert(position != nullptr && position < origin + length);
		uint8_t value = *(uint8_t*)position;
		position += sizeof(uint8_t);
		return value;
	}

	/**
  * @brief Reads a single-precision floating-point number from the current position.
  * @return The single-precision floating-point number read.
  */
	float ReadSingle() {
		assert(position != nullptr && position < origin + length);
		float value = *(float*)position;
		position += sizeof(float);
		return value;
	}

	/**
  * @brief Reads a double-precision floating-point number from the current position.
  * @return The double-precision floating-point number read.
  */
	double ReadDouble() {
		assert(position != nullptr && position < origin + length);
		double value = *(double*)position;
		position += sizeof(double);
		return value;
	}

	/**
  * @brief Reads a specified number of bytes from the current position into the buffer.
  * @param buffer Pointer to the buffer where data will be copied.
  * @param count Number of bytes to read.
  */
	void ReadBytes(byte* buffer, size_t count) {
		assert(position != nullptr && position < origin + length);
		assert(position + count < origin + length);
		sys::memcpy(buffer, position, count);
		position += count;
	}

	/**
  * @brief Closes the BinaryReader and releases any resources associated with it.
  */
	void Close() {
		position = nullptr;
		origin = nullptr;
		length = 0;
	}

	/**
  * @brief Sets the position within the current stream.
  * @param offset The point relative to the origin to begin seeking from.
  */
	void Seek(size_t offset) {
		assert(position != nullptr && position < origin + length);
		position = origin + offset;
	}
	bool isEOF() const {
		return position >= origin + length;
	}

	/**
  * @brief Sets the position within the current stream.
  * @param offset The point relative to the origin to begin seeking from.
  * @param origin Specifies the beginning, the end, or the current position as a reference point for offset.
  */
	void Seek(size_t offset, System::IO::SeekOrigin origin) {
		switch (origin) {
		case System::IO::SeekOrigin::Begin:
			position = this->origin + offset;
			break;
		case System::IO::SeekOrigin::Current:
			position += offset;
			break;
		case System::IO::SeekOrigin::End:
			position = this->origin + length - offset;
			break;
		}
	}
	/**
	 * @brief Reads a string from the current position.
	 * @return The string read.
	*/
	std::string ReadString() {
		string_stream ss;
		while (position < origin + length) {
			byte c = *position;
			if (c == 0) {
				position++;
				break;
			}
			ss.push_back(c);
			position++;
		}
		return ss.tostring();
	}

	/**
	 * @brief Peeks at the next 32-bit integer without advancing the position.
	 * @return The 32-bit integer peeked.
	 */
	int32_t PeekInt32() const {
		assert(position != nullptr && position < origin + length);
		return *(int32_t*)position;
	}

	/**
	 * @brief Peeks at the next 32-bit unsigned integer without advancing the position.
	 * @return The 32-bit unsigned integer peeked.
	 */
	uint32_t PeekUInt32() const {
		assert(position != nullptr && position < origin + length);
		return *(uint32_t*)position;
	}

	/**
	 * @brief Peeks at the next 16-bit integer without advancing the position.
	 * @return The 16-bit integer peeked.
	 */
	int16_t PeekInt16() const {
		assert(position != nullptr && position < origin + length);
		return *(int16_t*)position;
	}

	/**
	 * @brief Peeks at the next 16-bit unsigned integer without advancing the position.
	 * @return The 16-bit unsigned integer peeked.
	 */
	uint16_t PeekUInt16() const {
		assert(position != nullptr && position < origin + length);
		return *(uint16_t*)position;
	}

	/**
	 * @brief Peeks at the next 8-bit integer without advancing the position.
	 * @return The 8-bit integer peeked.
	 */
	int8_t PeekInt8() const {
		assert(position != nullptr && position < origin + length);
		return *(int8_t*)position;
	}

	/**
	 * @brief Peeks at the next 8-bit unsigned integer without advancing the position.
	 * @return The 8-bit unsigned integer peeked.
	 */
	uint8_t PeekUInt8() const {
		assert(position != nullptr && position < origin + length);
		return *(uint8_t*)position;
	}

	/**
	 * @brief Peeks at the next single-precision floating-point number without advancing the position.
	 * @return The single-precision floating-point number peeked.
	 */
	float PeekSingle() const {
		assert(position != nullptr && position < origin + length);
		return *(float*)position;
	}

	/**
	 * @brief Peeks at the next double-precision floating-point number without advancing the position.
	 * @return The double-precision floating-point number peeked.
	 */
	double PeekDouble() const {
		assert(position != nullptr && position < origin + length);
		return *(double*)position;
	}
	/*
	* @brief Peeks at the next string without advancing the position.
	* @return The string peeked.
	*/
	std::string PeekString() {
		string_stream ss;
		do {
			ss.push_back(*position);
		} while ((position++) < origin + length && *position != 0);
		return ss.tostring();
	}

	inline void cpy(const void* output, size_t startOffset, size_t count)const {
		sys::memcpy(output, origin + startOffset, count);
	}


	/*
	* @brief Finds the specified query in the data assuming the current position.
	* @param query The query to find.
	* @param offset The offset to start searching from.
	* @return The position of the query in the data.
	*/
	size_t Find(const std::string& query, size_t offset = 0)const {
		BinaryReader reader(position + offset, length - offset);
		size_t off = 0;
		do {
			if (sys::memcmp((char*)query.c_str(), reader.position + offset + off, query.length()) == 0) {
				return off;
			}

		} while ((!reader.isEOF()) && reader.Peek(off) != 0);
		return -1ull;
	}
	/*
		@brief Translates the current position to the specified query.
		@param query The query to translate to.
		@param length The length of the query.
		@return True if the query was found, false otherwise.
	*/
	bool TranslateTo(const byte* query, size_t length) {
		while (!this->isEOF()) {
			if (sys::memcmp(query, position, length) == 0) {
				return true;
			}
			++position;
		}
		return false;
	}
	/*
		@brief Begins another reading instance from the current position.
		@return A new BinaryReader instance.
	*/
	BinaryReader Descendant() {
		return { position, length - (position - origin) };
	}
};
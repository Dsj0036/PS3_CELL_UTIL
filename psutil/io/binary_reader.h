#pragma once

#include <psutil\ns.h>
#include <psutil\xtypes.h>
#include <psutil\diag\assert.h>
#include <string>
_SYS_NS
	/**
	 * @class binary_reader
	 * @brief A class to read primitive data types as binary values in a specific encoding.
	 */
	class binary_reader {
	byte* origin;   ///< Pointear to the origin of the data.
	byte* position; ///< Pointer to the current position in the data.
	size_t length;  ///< Length of the data.
	public:
		binary_reader(const binary_reader& other);
		/**
	  * @brief Constructs a BinaryReader with the specified data and length.
	  * @param origin Pointer to the data.
	  * @param length Length of the data.
	  */
		binary_reader(const void* origin, size_t length);

		uintptr_t get_end()const;
		byte previous() const;
		/**
		* @brief Returns the length of the data in this reader.
		*/
		size_t size() const;
		int32_t offset() const;

		/**
	  * @brief Copies a specified number of bytes from the current position to the buffer.
	  * @param buffer Pointer to the buffer where data will be copied.
	  * @param count Number of bytes to copy.
	  */
		void copy(void* buffer, size_t count);

		/**
	  * @brief Copies a specified number of bytes from a specified offset to the buffer.
	  * @param buffer Pointer to the buffer where data will be copied.
	  * @param srcOff Offset from the current position.
	  * @param dstLen Number of bytes to copy.
	  */
		void copy(void* buffer, size_t srcOff, size_t dstLen);

		/**
	  * @brief Peeks at the next byte without advancing the position.
	  * @return Reference to the next byte.
	  */
		byte& Peek();
		/*
		*	@brief Peeks at the byte at the specified offset without advancing the position.
		*	@return Reference to the byte at the specified offset.
		*/
		byte& Peek(size_t off) const;

		/**
	  * @brief Reads a 32-bit integer from the current position.
	  * @return The 32-bit integer read.
	  */
		int32_t ReadInt32();

		/**
	  * @brief Reads a 32-bit unsigned integer from the current position.
	  * @return The 32-bit unsigned integer read.
	  */
		uint32_t ReadUInt32();

		/**
	  * @brief Reads a 16-bit integer from the current position.
	  * @return The 16-bit integer read.
	  */
		int16_t ReadInt16();

		/**
	  * @brief Reads a 16-bit unsigned integer from the current position.
	  * @return The 16-bit unsigned integer read.
	  */
		uint16_t ReadUInt16();

		/**
	  * @brief Reads an 8-bit integer from the current position.
	  * @return The 8-bit integer read.
	  */
		int8_t ReadInt8();

		/**
	  * @brief Reads an 8-bit unsigned integer from the current position.
	  * @return The 8-bit unsigned integer read.
	  */
		uint8_t ReadUInt8();

		/**
	  * @brief Reads a single-precision floating-point2i number from the current position.
	  * @return The single-precision floating-point2i number read.
	  */
		float ReadSingle();

		/**
	  * @brief Reads a double-precision floating-point2i number from the current position.
	  * @return The double-precision floating-point2i number read.
	  */
		double ReadDouble();

		/**
	  * @brief Reads a specified number of bytes from the current position into the buffer.
	  * @param buffer Pointer to the buffer where data will be copied.
	  * @param count Number of bytes to read.
	  */
		void ReadBytes(byte* buffer, size_t count);
		/**
		* @brief Reads a specified number of bytes from the current position into the buffer.
		* @param buffer Pointer to the buffer where data will be copied.
		* @param count Number of bytes to read.
		*/
		void ReadChars(char* buffer, size_t count);

		/**
	  * @brief Closes the BinaryReader and releases any resources associated with it.
	  */
		void Close();
		void Open(const void* origin, size_t length);
		void Open(const std::string& text);

		/**
	  * @brief Sets the position within the current stream.
	  * @param offset The point2i relative to the origin to begin seeking from.
	  */
		void Seek(size_t offset);
		bool isEOF() const;

		/**
	  * @brief Sets the position within the current stream.
	  * @param offset The point relative to the origin to begin seeking from.
	  * @param origin Specifies the beginning, the end, or the current position as a reference point2i for offset.
	  */
		void Seek(size_t offset, int origin);
		/**
		 * @brief Reads a string from the current position.
		 * @return The string read.
		*/
		std::string ReadString();


		/**
		 * @brief Peeks at the next 32-bit integer without advancing the position.
		 * @return The 32-bit integer peeked.
		 */
		int32_t PeekInt32() const;
		/**
		 * @brief Peeks at the next 32-bit unsigned integer without advancing the position.
		 * @return The 32-bit unsigned integer peeked.
		 */
		uint32_t PeekUInt32() const;

		/**
		 * @brief Peeks at the next 16-bit integer without advancing the position.
		 * @return The 16-bit integer peeked.
		 */
		int16_t PeekInt16() const;

		/**
		 * @brief Peeks at the next 16-bit unsigned integer without advancing the position.
		 * @return The 16-bit unsigned integer peeked.
		 */
		uint16_t PeekUInt16() const;

		/**
		 * @brief Peeks at the next 8-bit integer without advancing the position.
		 * @return The 8-bit integer peeked.
		 */
		int8_t PeekInt8() const;

		/**
		 * @brief Peeks at the next 8-bit unsigned integer without advancing the position.
		 * @return The 8-bit unsigned integer peeked.
		 */
		uint8_t PeekUInt8() const;

		/**
		 * @brief Peeks at the next single-precision floating-point2i number without advancing the position.
		 * @return The single-precision floating-point2i number peeked.
		 */
		float PeekSingle() const;

		/**
		 * @brief Peeks at the next double-precision floating-point2i number without advancing the position.
		 * @return The double-precision floating-point2i number peeked.
		 */
		double PeekDouble() const;
		/*
		* @brief Peeks at the next string without advancing the position.
		* @return The string peeked.
		*/
		std::string PeekString();
		/*
		* @brief Finds the specified query in the data.
		* @param query The query to find.
		* @param offset The offset to start searching from.
		* @return The position of the query in the data.
		*/
		size_t Find(const std::string& query, size_t offset = 0)const;
		/*
			@brief Translates the current position to the specified query.
			@param query The query to translate to.
			@param length The length of the query.
			@return True if the query was found, false otherwise.
		*/
		bool TranslateTo(const byte* query, size_t length);
		/*
			@brief Previews the next data at the current stream position.
			@return Location to the rest of the data.
		*/
		const byte* current() const;
		/*
			@brief Previews the next data at the current stream position.
			@return Location to the rest of the data.
		*/
		byte* current();
		/*
			@brief Gets the count of the rest of the elements. Zero if EOF.
			@return Count
		*/
		int32_t restLength()const;
		int Skip(signed long count = 1);

		/*
			@brief Begins another reading instance from the current position.
			@return A new BinaryReader instance.
		*/
		binary_reader Descendant()const;
		binary_reader clone() const;
		binary_reader& resetOrigin();

};

_SYS_ENS

#include <psutil\io\binary_reader.h>
#include <psutil\vector.h>
#include <psutil\text\string_comparison.h>
_SYS_NS
class binary_reader;
/**
 * @class TextReader
 * @brief A class for reading text data from a binary stream with utility methods for manipulating the text data.
 *
 * This class wraps a `BinaryReader` and provides methods to read characters, compare data, skip content,
 * and perform other operations useful for text processing, such as searching for delimiters and reading
 * specific sections of a text stream.
 */
class text_reader {

	binary_reader _reader; ///< The internal BinaryReader used for reading data.

public:
	/**
	 * @brief Constructs a TextReader with a text string.
	 *
	 * Initializes the internal BinaryReader with the provided text string.
	 *
	 * @param text The text to initialize the reader with.
	 */
	text_reader(const std::string& text);

	/**
	 * @brief Constructs a TextReader from an existing BinaryReader stream.
	 *
	 * Initializes the TextReader using the provided BinaryReader.
	 *
	 * @param stream The BinaryReader instance to use for reading.
	 */
	text_reader(const binary_reader& stream);

	/**
	 * @brief Opens a new text stream from a string.
	 *
	 * @param text The string to read from.
	 */
	inline void open(const std::string& text);

	/**
	 * @brief Opens a new text stream from a buffer.
	 *
	 * @param buffer The buffer to read from.
	 * @param count The number of bytes to read from the buffer.
	 */
	inline void open(const char* buffer, size_t count);

	/**
	 * @brief Closes the current text stream.
	 */
	inline void close();

	/**
	 * @brief Checks if the reader is currently opened and valid.
	 *
	 * @return `true` if the reader is open and valid, `false` otherwise.
	 */
	inline bool opened() const;

	/**
	 * @brief Returns a descendant TextReader that shares the same BinaryReader.
	 *
	 * @return A new TextReader instance representing a descendant of the current reader.
	 */
	inline text_reader descendant() const;

	/**
	 * @brief Checks if the end of the file (EOF) has been reached.
	 *
	 * @return `true` if the end of the file is reached, `false` otherwise.
	 */
	inline bool isEOF() const;

	/**
	 * @brief Reads a single character from the stream.
	 *
	 * @return The character read from the stream, or `\0` if EOF is reached.
	 */
	inline char readChar();

	/**
	 * @brief Peeks at the next character in the stream without consuming it.
	 *
	 * @return The next character in the stream, or `\0` if the stream is not open.
	 */
	inline char peekChar();
	/**
	 * @brief Peeks at the next character in the stream without consuming it.
	 *
	 * @return The next character in the stream, or `\0` if the stream is not open.
	 */
	inline char peekChar2();

	/**
	 * @brief Compares the current data with the expected string based on the provided rules.
	 *
	 * @param expect The expected string.
	 * @param expectOffset The offset to start comparing in the expected string.
	 * @param srcOffset The offset to start comparing in the current data.
	 * @param count The number of characters to compare.
	 * @param comparison The comparison method to use.
	 *
	 * @return `1` for an exact match, `0` for an ordinal comparison result, or `-1` if the reader is not opened.
	 */
	int compareCurrent(const std::string& expect, int expectOffset, int srcOffset, int count, e_string_comparison comparison) const;

	/**
	 * @brief Compares the current data with the expected string for an exact match.
	 *
	 * @param expect The expected string.
	 * @param srcOffset The offset to start comparing in the current data.
	 * @param expectOffset The offset to start comparing in the expected string.
	 *
	 * @return `true` if the data matches the expected string exactly, `false` otherwise.
	 */
	bool compareCurrentExact(const std::string& expect, int srcOffset = 0, int expectOffset = 0) const;

	/**
	 * @brief Compares the current data with the expected string and optionally skips the characters if they match.
	 *
	 * @param expectAtPos The expected string at the current position.
	 * @param thenSkip If `true`, skips the matched characters.
	 *
	 * @return `true` if the data matches the expected string, `false` otherwise.
	 */
	bool expectWord(const std::string& expectAtPos, bool thenSkip = false);

	/**
	 * @brief Compares the current data with the expected string using the specified comparison method and optionally skips the characters if they match.
	 *
	 * @param expectAtPos The expected string at the current position.
	 * @param method The comparison method to use.
	 * @param thenSkip If `true`, skips the matched characters.
	 *
	 * @return `true` if the data matches the expected string, `false` otherwise.
	 */
	bool expectWord(const std::string& expectAtPos, e_string_comparison comparison_method, bool thenSkip = false);

	/**
	 * @brief Skips a specific number of characters in the text stream.
	 *
	 * @param count The number of characters to skip.
	 *
	 * @return The number of characters skipped.
	 */
	int skip(size_t count = 1);

	int skipChar(char ch);

	/**
	 * @brief Seeks to a specific position in the text stream.
	 *
	 * @param ea The position to seek to.
	 * @param origin The origin from which to seek.
	 */
	void seek(int ea, int origin);

	/**
	 * @brief Scans for matching patterns in the text stream.
	 *
	 * This method is used for advanced pattern matching.
	 */
	void matchesScan(const std::string& format);

	/**
	 * @brief Searches for the first occurrence of any of the specified characters in the stream.
	 *
	 * @param outFoundIndex The index of the found character.
	 * @param outDeltaOffset The offset where the character was found.
	 * @param skipThen If `true`, skips to the found character.
	 * @param delimiters The list of characters to search for.
	 *
	 * @return `true` if a matching character is found, `false` otherwise.
	 */
	bool _until_ex(int srcOffset, int* outFoundIndex, int* outDeltaOffset, bool skipThen, const vector<char>& delimiters);

	/**
	 * @brief Searches for the first occurrence of any of the specified characters in the stream using a variable argument list.
	 *
	 * @param outFoundIndex The index of the found character.
	 * @param outDeltaOffset The offset where the character was found.
	 * @param skipThen If `true`, skips to the found character.
	 * @param delimiterChars The variable list of characters to search for (terminated by `0`).
	 *
	 * @return `true` if a matching character is found, `false` otherwise.
	 */
	bool _vuntil_ex(int srcOffset, int* outFoundIndex, int* outDeltaOffset, bool skipThen, char delimiterChars...);

	/**
	 * @brief Finds the next occurrence of a specific character in the text stream.
	 *
	 * @param ch The character to search for.
	 *
	 * @return The index of the next occurrence of the character, or `-1` if not found.
	 */
	signed int findNextIndexOf(char ch);
	/**
	 * @brief Finds the next index of an unescaped character in the text.
	 *
	 * This function searches for the next occurrence of a specified character
	 * in the text, ensuring that it is not preceded by an escape character ('\\').
	 * The search is performed by scanning through the text starting from the
	 * current position and continuing until the end of the text or the character is found.
	 *
	 * @param ch The character to search for in the text.
	 *
	 * @return The index (relative to the current position) of the next occurrence
	 *         of the unescaped character, or -1 if the character is not found.
	 *
	 * @note The function performs a peeking operation and checks if the character
	 *       is preceded by an escape character. If the character is escaped, it
	 *       continues searching further.
	 */
	signed int findNextIndexOfUnescaped(char ch);
	/**
	 * @brief Finds the occurrence of a specific character in the entire text stream.
	 *
	 * @param ch The character to search for.
	 *
	 * @return The index of the next occurrence of the character, or `-1` if not found.
	 */
	signed int findIndexOfAbs(char ch);
	signed int findIndexOfAbs(int srcOffset, char ch);

	/**
	* @brief Searches for any of the given query strings in a TextReader, with optional behavior when a single match is found.
	*
	* This function scans the provided TextReader to find any occurrence of the given query strings,
	* using the specified string comparison method. It optionally allows skipping characters in the
	* main reader if a single query is found and `skipThenIfSingle` is set to true.
	*
	* @param reader               Reference to the TextReader to search through.
	* @param queries              Vector of query strings to search for. At least one must be provided.
	* @param outAbsFoundIndex     Optional pointer to an integer that will receive the absolute offset
	*                             (including any skipped characters) where a match was found. If no match
	*                             is found, it will be set to -1.
	* @param outRelativeFoundIndex Optional pointer to an integer that will receive the relative number of characters
	*                             skipped before finding a match. If no match is found, it will be set to -1.
	* @param skipThenIfSingle     If true and only a single query is provided, the main reader will skip forward
	*                             by the number of characters that were examined to reach the match.
	* @param comparisonMethod     Defines the method used for comparing strings (e.g., case-sensitive, case-insensitive).
	*
	* @return true if any of the query strings were found; false otherwise.
	*
	* @note
	* - If `queries` contains only one element and `skipThenIfSingle` is true, `reader` will be advanced
	*   by the number of characters skipped before the match was found.
	* - If both `outAbsFoundIndex` and/or `outRelativeFoundIndex` are provided, they will be set accordingly
	*   even if no match is found.
	* - The search is performed character-by-character from the reader's current position to the end.
	*/
	static bool _textReaderAdvancedFind(
		text_reader& reader,
		const vector<std::string>& queries,
		int* outAbsFoundIndex,
		int* outRelativeFoundIndex,
		bool skipThenIfSingle,
		e_string_comparison comparisonMethod);

	/**
	 * @brief Jumps to the next occurrence of a specific character in the stream.
	 *
	 * @param ch The character to jump to.
	 *
	 * @return `true` if the jump is successful, `false` otherwise.
	 */
	bool jumpToNextChar(char ch);

	/**
	* @brief Advances the TextReader position to the next occurrence of a given string.
	*
	* This function searches for the next occurrence of the specified text within the reader,
	* using the given string comparison method. If the text is found, the reader advances
	* to the position right before the match. Otherwise, the reader remains unchanged.
	*
	* @param text                The string to search for within the reader.
	* @param comparisonMethod    The method used for comparing strings (default is exact match).
	*                             Possible values include case-sensitive and case-insensitive comparisons.
	*
	* @return true if the specified string was found and the reader was moved; false if not found.
	*
	* @note
	* - Internally, this function uses `_textReaderAdvancedFind()` with `skipThenIfSingle` set to true.
	* - This function does not return the result of the search explicitly; it assumes movement happens automatically.
	* - If you need to know whether the jump was successful, consider adapting the function to return the search result.
	*/
	bool jumpToNextString(const std::string& text, e_string_comparison comparisonMethod);

	bool skipFollowing(const std::string& text);

	signed int findNextIndexOf(const std::string& word, e_string_comparison comparisonMethod);
	/**
	* @brief Finds all positions where any of the specified words occur in the TextReader.
	*
	* This function performs a full scan of the underlying text and collects all positions
	* where any of the given words match the content, according to the specified string comparison method.
	*
	* @param words               A vector of strings to search for in the reader.
	* @param comparisonMethod    The method used to compare strings (default is exact match).
	*                             Can be set for case-sensitive or case-insensitive matching.
	*
	* @return A vector of integers representing the relative offsets where matches were found.
	*         Each offset corresponds to the number of characters skipped from the origin.
	*         If no matches are found, an empty vector is returned.
	*
	* @note
	* - The search is **absolute** from the beginning of the underlying reader data (`resetOrigin()` is called).
	* - Matches are detected character-by-character across the entire reader content.
	* - The returned positions are relative to the starting point (origin) of the reader's data.
	*/
	vector<int> indexOfAny(const vector<std::string>& word, e_string_comparison comparisonMethod);
	/**
	 * @brief Reads a specific number of characters from the stream.
	 *
	 * @param count The number of characters to read.
	 *
	 * @return A string containing the read characters.
	 */
	std::string read(int count);

	/**
	 * @brief Reads characters from the stream until a delimiter is encountered.
	 *
	 * @param delimiters A list of characters that act as delimiters.
	 *
	 * @return A string containing the characters read until a delimiter is found.
	 */
	std::string readTo(const vector<char>& delimiters);
	/**
	 * @brief Reads all remaining characters in the stream.
		 /**
	 * @brief Reads all remaining characters in the stream.
	 *
	 * @return A string containing all characters from the current position to the end of the stream.
	 */
	std::string readToEnd();

	/**
	 * @brief Reads characters from the stream until the specified character is encountered.
	 *
	 * @param c The character to stop at.
	 *
	 * @return A string containing the characters read until the specified character is found.
	 */
	std::string readTo(char c);

	/**
	 * @brief Reads a substring from the stream with a specified offset and length, starting from a given seek position.
	 *
	 * @param srcOffset The offset from the current position to start reading from.
	 * @param count The number of characters to read.
	 * @param seekOrigin The position to seek from (`Begin`, `Current`, or `End`).
	 *
	 * @return A string containing the substring read.
	 */
	std::string readSubstr(int srcOffset, int count, int seekOrigin);


	vector<int> findAll(char ch);




	/**
	 * @brief Gets the internal BinaryReader used by this TextReader.
	 *
	 * @return A reference to the internal BinaryReader instance.
	 */
	binary_reader& getReader();

	/**
	 * @brief Gets the internal BinaryReader used by this TextReader (const version).
	 *
	 * @return A const reference to the internal BinaryReader instance.
	 */
	const binary_reader& getReader() const;

	size_t offset() const;
	const char* point() const;
};
_SYS_ENS
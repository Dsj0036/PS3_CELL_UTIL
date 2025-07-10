#include "print.h"
#include "include\odps3lib.h"
#include "BinaryReader.h"
#include "GC.h"
namespace strutil
{
	const char* scan_error = nullptr;

	class scanned_type {
	private:
		union {
			char v_char;			// single character. %s
			char* v_str;			// string. %s
			double v_dbl;			// signed decimal %lf
			int v_int;	// integer, %i
			unsigned int v_uint;	// unsigned int, %x, %u, %o
			float v_flt;			// floating point. %f 
			void* v_ptr;			// ptr %p
		} _object;

	public:
		enum type {
			undefined,
			character,
			string,
			decimal,
			integer,
			unsigned_integer,
			floating_point,
			pointer,
		};
	private:
		type typeofthis;
	public:
		scanned_type() {
			typeofthis = undefined;
		}


		inline float	as_float()const { return _object.v_flt; }
		inline int32_t	as_int()const { return _object.v_int; }
		inline double	as_double()const { return _object.v_dbl; }
		inline char* as_cstr()const { return _object.v_str; }
		inline void* as_ptr()const { return _object.v_ptr; }

		inline type get_type() const {
			return typeofthis;
		}

		inline void set(float v) {
			_object.v_flt = v;
			typeofthis = floating_point;
		}
		inline void set(double v) {
			_object.v_dbl = v;
			typeofthis = decimal;
		}
		inline void set(int v) {
			_object.v_int = v;
			typeofthis = integer;
		}
		inline void set(unsigned int v) {
			_object.v_uint = v;
			typeofthis = unsigned_integer;
		}
		inline void set(char* v) {
			_object.v_str = v;
			typeofthis = string;
		}
		inline void set(const char* v) {
			_object.v_str = const_cast<char*>(v);
			typeofthis = string;
		}
		inline void set(char v) {
			_object.v_char = v;
			typeofthis = character;
		}
		inline void set(void* v) {
			_object.v_ptr = v;
			typeofthis = pointer;
		}
		inline void set_undefined() {
			_object.v_uint = 0;
			typeofthis = undefined;
		}


	};


	// Checks if an text pointer is correct for reading.
	static inline bool pointsctrly(const char* txtSpssd) {
		if (!txtSpssd)
			return false;
		return sys::strlen(txtSpssd) > 0;
	}

	bool streq(const char* ptr, const char* comp) {
		return !_sys_strncmp(comp, ptr, _sys_strlen(comp));
	}

	// moves to the next appearisson of the expected character on a string.
	int movenext(const char*& ptr, char expect) {
		if (!ptr)
			return false;

		const char* r = ptr;
		int r_ = 0;

		while (r != nullptr && *r && *r != expect) {
			r++;
			r_++;
		}
		ptr = r;
		return *r == expect;
	}
	// moves to the next appearisson of the expected string on an string.
	int movenext(const char*& ptr, const std::string& query) {
		if (!ptr)
			return false;
		if (!query.length())
			return;
		const char* r = ptr;
		int r_ = 0;
		while (r != nullptr && *r && !streq(ptr, query.c_str())) {
			r++;
			r_++;
		}
		ptr = r;
		return r_;
	}

	// extracts part of an string.
	std::string substr(const char* data, size_t offset, size_t count) {
		return std::string(data).substr(offset, count);
	}
	// Skips possible spaces at the start of the pointed data.
	int skipsp(const char*& ptr) {
		if (!ptr)
			return false;
		if (sys::strlen(ptr) == 0)
			return false;
		const char* r = ptr;
		int r_ = 0;
		while (r != nullptr && *r && isspace_ascii(*r)) {
			r++;
			r_++;
		}
		ptr = r;
		return r_;
	}
	// returns the trailed character and moves to a different character.
	const char* untrail(char*& ptr) {
		if (!pointsctrly(ptr))
			return 0;

		const char* R = ptr;
		if (sys::is_alnum(*R)) {
			return 0;
		}
		while (*ptr == *R) {
			++ptr;
		}
		return R;
	}
	// untrails texts by removing consecutive symbols.
	static int untrailText(char* buffer, size_t buffersize) {

		if (!buffer)
			return false;
		if (sys::strlen(buffer) == 0)
			return false;
		const char* origin = buffer;
		int counted = 0;
		string_stream ss;
		do {
			const char* ch = untrail(buffer);
			if (ch)
				ss << *ch;
			else { ++buffer; counted++; }

		} while (pointsctrly(buffer) && buffer < (origin + buffersize));
		ss.terminate();
		if (counted) {
			sys::memset(buffer, 0, buffersize);
			sys::memcpy(buffer, ss.c_str(), MIN(ss.length(), buffersize));
		}
		return counted;
	}
	static std::string padLeft(const std::string& text, int ch, int maxLength) {
		string_stream ss;

		int cnt = maxLength - text.length();
		while (cnt) {
			ss << (char)ch;
			cnt--;
		}
		ss.append(text.c_str(), text.length());
		ss.terminate();
	}
	static std::string padRight(const std::string& text, int ch, int maxLength) {
		string_stream ss;

		int cnt = maxLength - text.length();
		ss.append(text.c_str(), text.length());
		while (cnt) {
			ss << (char)ch;
			cnt--;
		}
		ss.terminate();
	}

	// Determines if the char is allowed for a format specifier.
	static bool is_valid_specifier_char(char val) {
		return val == '_' || sys::is_alnum(val);
	}
	// Determines if an format specifier is correct.
	static bool is_valid_specifier(const char* format) {
		if (!format) {
			return false;
		}
		if (!sys::strlen(format))
			return false;

		if (*format == '%')
			format++;

		int length = 0;
		const char* frm = format;
		while (*frm) {
			if (!is_valid_specifier_char(*frm))
				return false;
			++frm;
		}
		return true;

	}
	static int scan_float(scanned_type& output, const char* text, int padLeftMax = 0, int maxDecimals = 0) {
		if (!System::Text::couldBeFloatValueRepresentation(text, '.', false)) {
			scan_error = "Input is not a valid float candidate.";
			return 0;
		}

		const char* iter = text;
		bool found_dot = false;
		int int_len = 0, dec_len = 0;

		if (*iter == '-' && sys::isnum(*(iter + 1))) iter++;  // soporte negativo

		while (*iter && (sys::isnum(*iter) || *iter == '.')) {
			if (*iter == '.') {
				if (int_len == 0 || (padLeftMax > 0 && int_len > padLeftMax)) {
					scan_error = "Invalid integer part before dot.";
					return 0;
				}
				found_dot = true;
				iter++;
				break;
			}
			int_len++;
			iter++;
		}

		if (found_dot) {
			while (sys::isnum(*iter)) {
				dec_len++;
				if (maxDecimals > 0 && dec_len > maxDecimals) {
					scan_error = "Too many decimal digits.";
					return 0;
				}
				iter++;
			}
		}
		else if (maxDecimals > 0) {
			// optionally allow integers if maxDecimals > 0
			// or treat this as error, depending on spec
		}

		output.set(System::Float::Parse(text));
		scan_error = nullptr;
		return int(iter - text);  // cantidad de caracteres consumidos
	}
	struct expressive_result {
		bool valid;
		vector<std::string> extracted;
	};

	static bool validate_token(const char* text, char specifier, int& out_len) {
		int len = 0;
		const char* it = text;

		switch (specifier) {
		case 'i':
			while (sys::isnum(*it)) { len++; it++; }
			break;
		case 'f':
			while (sys::isnum(*it) || *it == '.') { len++; it++; }
			break;
		case 'x':
			while (System::Text::IsHexadecimalCharacter(*it)) { len++; it++; }
			break;
		case 's':
			while (*it && *it != ' ') { len++; it++; }
			break;
		case 'd':
			while (sys::isnum(*it) || *it == '.') { len++; it++; }
			break;
		case '*':
			len = sys::strlen(text);
			break;
		default:
			return false;
		}

		if (len == 0)
			return false;

		string_stream ss;
		for (int i = 0; i < len; i++) ss << text[i];
		ss.terminate();

		switch (specifier) {
		case 'f':
			if (!System::Text::couldBeFloatValueRepresentation(ss.c_str(), '.', false))
				return false;
			break;
		case 'd':
		case 'i':
			if (!System::Text::couldBeIntegerRepresentation(ss.c_str()))
				return false;
			break;
		case 'x':
			if (!System::Text::couldBeHexadecimalRepresentation(ss.c_str()))
				return false;
			break;
		}

		out_len = len;
		return true;
	}

	static std::string extract_token(const char* text, int len) {
		std::string token;
		for (int i = 0; i < len; ++i)
			token += text[i];
		return token;
	}
	static expressive_result iterate_expressive(const char* text, const char* format) {
		expressive_result result;
		result.valid = false;

		if (!pointsctrly(text) || !pointsctrly(format))
			return result;

		const char* formatIt = format;
		const char* textIt = text;

		while (*formatIt && *textIt) {
			if (*formatIt != '%') {
				if (*formatIt != *textIt)
					return result;
				formatIt++;
				textIt++;
				continue;
			}

			char specifier = *(formatIt + 1);
			int len = 0;

			if (!validate_token(textIt, specifier, len)) {
				return result;
			}

			std::string token = extract_token(textIt, len);
			result.extracted.push_back(token);

			textIt += len;
			formatIt += 2;
		}

		result.valid = true;
		return result;
	}


	static bool matches_expressive(const char* text, const char* format) {
		if (!pointsctrly(text))
			return false;
		if (!pointsctrly(format))
			return true;
		const char* formatIt = format;
		const char* textIt = text;
		int maxLength = sys::strlen(textIt);

		while (*formatIt && *textIt) {
			while (*formatIt != '%') {
				formatIt++;
				textIt++;
			}
			if (*formatIt == '%') {
				const char* specifiers = formatIt + 1;


				switch (*(formatIt + 1)) {
				case 's': {
					string_stream ss;
					BinaryReader reader(textIt, maxLength);
					const char* rest_of_text = formatIt;
					while (*rest_of_text && is_valid_specifier_char(*rest_of_text)) {
						rest_of_text++;
					}
					while (*textIt && !streq(textIt, rest_of_text)) {
						ss << *textIt;
						textIt++;
					}
					formatIt++;
					formatIt++;
					break;
				}
				case 'i': {
					string_stream ss;
					const char* maxIter = "2147483647";
					while (sys::isnum(*textIt) && *textIt) {
						if (ss.length() > sys::strlen(maxIter))
							return false;
						ss << *textIt;
						textIt++;
					}
					formatIt++;
					formatIt++;
					break;
				}
				case 'f': {
					string_stream ss;

					while (*textIt && (sys::isnum(*textIt) || *textIt == '.')) {
						ss << *textIt;
						textIt++;
					}
					ss.terminate();
					if (!System::Text::couldBeFloatValueRepresentation(ss.c_str(), '.', false)) {
						return false;
					}
					break;
				}
				case 'd': {


					const char* rest_of_text = formatIt;
					while (*rest_of_text && is_valid_specifier_char(*rest_of_text)) {
						rest_of_text++;
					}

					string_stream ss;
					int cnt = 0;
					while (*textIt) {
						if ((sys::isnum(*textIt) || *textIt == '.') && !streq(textIt, rest_of_text)) {
							ss << *textIt;
						}
						textIt++;
					}
					ss.terminate();
					if (!System::Text::couldBeIntegerRepresentation(ss.c_str())) {
						return false;
					}
					formatIt++;
					formatIt++;
					break;
				}
				case 'x': {

					const char* rest_of_text = formatIt;
					while (*rest_of_text && is_valid_specifier_char(*rest_of_text)) {
						rest_of_text++;
					}

					string_stream ss;
					int cnt = 0;
					while (*textIt) {
						if ((System::Text::IsHexadecimalCharacter(*textIt)) && !streq(textIt, rest_of_text)) {
							ss << *textIt;
						}
						if (!(System::Text::IsHexadecimalCharacter(*textIt))) {
							return false;
						}
						textIt++;
					}
					ss.terminate();
					if (!System::Text::couldBeIntegerRepresentation(ss.c_str())) {
						return false;
					}
					formatIt++;
					formatIt++;
				}
				case '*':
				default:
				{
					formatIt++;
					formatIt++;
					break;
				}

				}

			}
		}
		return true;
	}
}
namespace scripting
{


	struct object {
		const char* opt_name = nullptr;
		int id;
		explicit object(int i) : id(i) {}
	};

	struct list_descendant {
		object* data;
		list_descendant* next;

		list_descendant(object* obj) : data(obj), next(nullptr) {}
	};

	class root_list {
		list_descendant* head;
		list_descendant* back;

		root_list() : head(nullptr), back(nullptr) {}

		void add(object* obj) {
			list_descendant* node = new list_descendant(obj);

			if (!head) {
				head = back = node;
			}
			else {
				back->next = node;
				back = node;
			}
		}
		~root_list() {
			list_descendant* current = head;
			while (current) {
				list_descendant* next = current->next;
				delete current->data;
				delete current;
				current = next;
			}
		}
	};
	class callstack {

	};
	class data_object {
		int value_aux = 0; // auxiliar value if ptr contents lengths smaller than 5
		const char* opt_name;
		const void* value; // pointer to a bunch of data or the auxiliar value bytes.
	};

	class function {
	public:
		std::string name;
		vector<object> arguments;
		vector<object> data;
		callstack behave;
		void invoke() {

		}

	};

	class script {
	public:
		vector<function> functions;

	};
}
static void skip_whitespace(const char*& ptr) {
	while (ptr) {
		if ((*ptr == ' ' ||
			*ptr == '\t' ||
			*ptr == '\r' ||
			*ptr == '\v' ||
			*ptr == '\n'))
			ptr++;
		else
			break;
	}
}

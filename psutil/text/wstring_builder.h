

class wstring_stream {
	vector<wchar> _data;
public:
	wstring_stream() : _data() {}
	using r = wstring_stream&;

	inline int length()const { return _data.size(); }
	inline int capacity() const { return _data.capacity(); }
	inline wstring_stream& pad(byte count) {
		byte c = 0;
		while (c < count) {
			this->_data.push_back(L' ');
			++c;
		}
		return *this;
	}
	inline r push_back(char c) {
		this->_data.push_back(static_cast<wchar_t>(c));
		return *this;
	}
	inline r pop_back() {
		this->_data.pop_back();
		return *this;
	}
	inline r push_back(wchar c) { this->_data.push_back(c); return *this; }
	inline r append(const char* cstr) {
		int count = sys::strlen(cstr);
		forIndexIn(count) { push_back(cstr[i]); }
		return *this;
	}
	inline r append(const wchar* wstr) {
		int count = std::wcslen(wstr);
		forIndexIn(count) { push_back(wstr[i]); }
		return *this;
	}

	inline r push_back(const std::wstring& r) {
		this->append(r.c_str());
		return *this;
	}

	inline r append(const wchar* wstr, int srcOff, int count = 0) {
		if (!wstr || srcOff < 0) return *this;
		int len = std::wcslen(wstr);
		if (count == 0) {
			count = len;
		}
		if (srcOff >= len) return *this;
		int maxCount = (srcOff + count > len) ? len - srcOff : count;
		for (int i = 0; i < maxCount; ++i) {
			_data.push_back(wstr[srcOff + i]);
		}
		return *this;
	}
	inline const wchar_t* begin() const {
		return this->_data.data();
	}
	inline const wchar_t* end() const {
		return this->_data.data() + this->_data.size();
	}
	inline wchar_t* begin() {
		return this->_data.begin();
	}
	inline wchar_t* end() {
		return this->_data.begin() + this->_data.size();
	}
	template<typename ...va>
	inline r format(const wchar* f, va...args) {
		wchar buffer[512]{ 0 };
		swprintf(buffer, 512, f, args...);
		append(buffer);
		sys::memset(buffer, 0, sizeof(buffer));
		return *this;
	}
	inline const wchar_t* c_str()const {
		return this->_data.data();
	}
	inline std::wstring str() const {
		return std::wstring(this->_data.data(), this->length());
	}
	inline void terminate() {
		this->_data.push_back(L'\0');
		return;
	}
	inline r append(const std::string& str) {
		forIndexIn(str.length()) { this->_data.push_back(str[i]); }
		return *this;
	}
	inline r reserve(size_t count) {
		this->_data.reserve(count);
		return *this;
	}
	inline r removeAt(size_t index) {
		this->_data.remove_at(index);
		return *this;
	}
	inline r insertAt(size_t index, wchar_t c) {
		this->_data.insert(index, c);
		return *this;
	}
	inline r clear() {
		this->_data.clear();
		return *this;
	}
	inline wchar_t last() const {
		return this->_data[this->_data.size() - 1];
	}
	inline wchar_t first() const {
		return this->_data.operator[](0);
	}
	wchar_t elementAt(size_t index) const {
		if (index >= this->length()) {
			return 0;
		}
		return this->_data[index];
	}
	inline size_t copyTo(wstring_stream& const dst, uint srcOffset = 0, uint count = 0) const {
		if (count == 0) {
			count = this->length();
		}
		uint i{};
		for (i = srcOffset; i < srcOffset + count; i++) {
			if (this->elementAt(i) == 0)
				break;
			dst.push_back(this->elementAt(i));
		}
		return i;
	}


	wstring_stream substream(size_t srcOffset = 0, size_t count = 0) const {
		wstring_stream _string_stream;
		this->copyTo(_string_stream, srcOffset, count);
		return _string_stream;
	}
	inline std::wstring substr(size_t srcOff = 0, size_t count = 0) const {
		if (count == 0 || count > this->length()) {
			count = this->length();
		}
		if (srcOff >= this->length()) {
			srcOff = 0;
		}


		std::wstring result;
		for (size_t i = srcOff; i < srcOff + (count); i++) {
			result.push_back(this->elementAt(i));
		}
		return result;
	}
	inline string_stream to_utf8() const {
		size_t size_buf = this->_data.size() * 4 + 1;

		char* buffer = new char[size_buf];
		_sws2utf8s(this->_data.data(), buffer, size_buf);

		string_stream result(buffer, sys::strlen(buffer));

		delete[] buffer;
		return result;
	}


	wstring_stream clone()const {
		return substream();
	}
	size_t _indexOf(wchar_t c)const {
		size_t off = 0;
		do {
			if (this->elementAt(off) == c)
				return off;
			++off;
		} while (off < this->length());
		return -1ull;
	}
	size_t _indexOf(const wchar* str) const {
		int qlen = std::wcslen(str);
		size_t idx = 0;
		while (idx < this->length()) {
			if (sys::wcsncmp(this->c_str(), str, qlen) == 0) {
				return idx;
			}
			++idx;
		}
		return -1ull;
	}
	inline size_t indexOf(const std::wstring& str) const { return _indexOf(str.c_str()); }
	inline r operator<<(wchar_t c) {
		this->_data.push_back(c);
		return *this;
	}
	inline r operator<<(const wchar_t* str) {
		return this->append(str);
	}

	inline r operator<<(const std::wstring& str) {
		return this->append(str.c_str());
	}
	inline r operator<<(int32_t r) {
		this->_num(r);
		return *this;
	}
	inline r operator<<(double r) {
		this->_num(r);
		return *this;
	}
	inline r operator<<(bool r) {
		operator<<(r ? L"true" : L"false");
		return *this;
	}
	template<typename NUM>
	inline r _num(NUM num_) {
		char printbuff[48]{ 0 };
		tcsb::CStringBuilder sb(printbuff, 48);
		sb.addf(num_);
		append(printbuff);
		sys::memset(printbuff, 0, 48);
		return *this;
	}

};
std::string url_encode(const std::string& src) {
	static const char* hex = "0123456789ABCDEF";
	string_stream encoded;

	for (unsigned char c : src) {
		if ((c >= 'a' && c <= 'z') ||
			(c >= 'A' && c <= 'Z') ||
			(c >= '0' && c <= '9') ||
			c == '-' || c == '_' || c == '.' || c == '~') {
			encoded << c;
		}
		else if (c == ' ') {
			encoded << '+';
		}
		else if (c == '\n') {
			encoded << "%0A";
		}
		else if (c == '\r') {
			encoded << "%0D";
		}
		else if (c == '\t') {
			encoded << "%09";
		}
		else if (c == '/') {
			encoded << '%';
			encoded << '2';
			encoded << 'F';
		}
		else if (c == ':') {
			encoded << '%';
			encoded << '3';
			encoded << 'A';
		}
		else {
			encoded << '%' << hex[c >> 4] << hex[c & 0x0F];
		}
	}
	encoded.terminate();
	return encoded.c_str();
}
std::string url_decode(const std::string& src) {
	string_stream decoded;

	for (size_t i = 0; i < src.length(); ++i) {
		char c = src[i];

		if (c == '+') {
			decoded << ' ';
		}
		else if (c == '%' && i + 2 < src.length()) {
			char h1 = src[i + 1];
			char h2 = src[i + 2];

			auto hexToChar = [](char ch) -> int {
				if (ch >= '0' && ch <= '9') return ch - '0';
				if (ch >= 'A' && ch <= 'F') return ch - 'A' + 10;
				if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;
				return -1;
				};

			int high = hexToChar(h1);
			int low = hexToChar(h2);

			if (high != -1 && low != -1) {
				decoded << static_cast<char>((high << 4) | low);
				i += 2; // Skip the next two characters
			}
			else {
				decoded << c; // Keep '%' if the hex is invalid
			}
		}
		else {
			decoded << c;
		}
	}

	decoded.terminate();
	return decoded.c_str();
}
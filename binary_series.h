#pragma once
#include "_ns.h"
#include "lwstring.h"
#include "enumdef.h"
#include "algorithm.h"
#include "list.h"
#include "bswap.h"
#include "buffer.h"
#include "format.h"
#include "hash_code.h"
_SYS_NS

SMART_ENUM(binary_entry_type,
	T_NONE,
	T_BOOL,
	T_CHAR,
	T_SHORT,
	T_INTEGER,
	T_FLOAT,
	T_DOUBLE,
	);
class binary_series {

	sys::lwstring _patternExp;
	size_t _length{ 0 }; // length in bytes of all entries values.
	public:
	class _entry {
	public:
		union {
			bool boolean;
			char charc;
			short shortv;
			int intv;
			float floatv;
			double doublev;
		} value;
		_entry() : ty(binary_entry_type::T_NONE){

		}
		binary_entry_type ty;

		void set_bool(bool x) {
			value.boolean = x;
			ty = binary_entry_type::T_BOOL;
		}

		void set_char(char x) {
			value.charc = x;
			ty = binary_entry_type::T_CHAR;
		}

		void set_short(short x) {
			value.shortv = x;
			ty = binary_entry_type::T_SHORT;
		}

		void set_int(int x) {
			value.intv = x;
			ty = binary_entry_type::T_INTEGER;
		}

		void set_float(float x) {
			value.floatv = x;
			ty = binary_entry_type::T_FLOAT;
		}

		void set_double(double x) {
			value.doublev = x;
			ty = binary_entry_type::T_DOUBLE;
		}
		bool operator ==(_entry& other) const {
			return ty == other.ty && sys::memcmp(&other.value, &this->value, sizeof(value)) == 0;
		}
		sys::lwstring to_string()const {
			const char* _tys= nullptr;
			switch (ty) {
			case binary_entry_type::T_BOOL:   	_tys = "BOOL"; break;
			case binary_entry_type::T_CHAR:   	_tys = "CHAR"; break;
			case binary_entry_type::T_SHORT:  	_tys = "SHORT"; break;
			case binary_entry_type::T_INTEGER:	_tys = "INTEGER"; break;
			case binary_entry_type::T_FLOAT:  	_tys = "FLOAT"; break;
			case binary_entry_type::T_DOUBLE:   _tys = "DOUBLE"; break;
			case binary_entry_type::T_NONE:   _tys = "NONE"; break;

			}
			uint64_t d; 
			sys::memcpy(&d, this->get_ptr(), size_of(char_for(ty)));
			return sys::sformat("(%s)%X ", _tys, d);

		}
		/**
		 * @brief Returns a pointer to the active value based on current type.
		 * @return void* pointer to internal union field, or nullptr if invalid type.
		 */
		void* get_ptr() {
			switch (ty)
			{
			case binary_entry_type::T_BOOL:    return &value.boolean;
			case binary_entry_type::T_CHAR:    return &value.charc;
			case binary_entry_type::T_SHORT:    return &value.shortv;
			case binary_entry_type::T_INTEGER:  return &value.intv;
			case binary_entry_type::T_FLOAT:    return &value.floatv;
			case binary_entry_type::T_DOUBLE:   return &value.doublev;
			default: return nullptr;
			}
		}

		/**
		 * @brief Const version of get_ptr().
		 */
		const void* get_ptr() const {
			switch (ty)
			{
			case binary_entry_type::T_BOOL:    return &value.boolean;
			case binary_entry_type::T_CHAR:    return &value.charc;
			case binary_entry_type::T_SHORT:    return &value.shortv;
			case binary_entry_type::T_INTEGER:  return &value.intv;
			case binary_entry_type::T_FLOAT:    return &value.floatv;
			case binary_entry_type::T_DOUBLE:   return &value.doublev;
			default: return nullptr;
			}
		}
	};
private:
	list<_entry> _entries;


	void invalidate_pattern_string() {
		if (!this->_patternExp.empty())
			this->_patternExp.clear();
	}
	void update_pattern_string() {
		if (this->_entries.size() == 0) return;

		char* ez = new char[this->_entries.size()];
		char* px = ez;
		for (_entry& e : _entries) {
			*px = char_for(e.ty);
			px++;
		}
		this->_patternExp.assign(ez);
		delete[] ez;
	}
public:
	binary_series() : _entries(8) {
		_length = 0;
	}
	binary_series(binary_series&& other) : _length(other._length), _entries(nullptr) {
		_entries.steal(other._entries);
		other._length = 0;
	}
	binary_series(const binary_series& other) = delete;

	sys::buffer convert_to_buffer() {
		sys::buffer buffer(_length);
		for (_entry& e : this->_entries)
			buffer.append((unsigned char*)e.get_ptr(), size_of(char_for(e.ty)));
		return buffer;
	}
	const _entry* begin() const {return this->_entries.begin();}
	const _entry* end() const {return this->_entries.end();}
	void clear() {
		invalidate_pattern_string();
		_entries.clear();
		_length = 0;
	}
	void add_bool(bool b) {
		_entry ent;
		ent.value.boolean = b;
		ent.ty = binary_entry_type::T_BOOL;
		_length += size_of(char_for(ent.ty));
		_entries.add(ent);
		invalidate_pattern_string();
	}
	void add_char(char b) {
		_entry ent;
		ent.value.charc = b;
		ent.ty = binary_entry_type::T_CHAR;
		_length += size_of(char_for(ent.ty));
		_entries.add(ent);
		invalidate_pattern_string();
	}
	void add_short(short b) {
		_entry ent;
		ent.value.shortv = b;
		ent.ty = binary_entry_type::T_SHORT;
		_length += size_of(char_for(ent.ty));
		_entries.add(ent);
		invalidate_pattern_string();
	}
	void add_int(int b) {
		_entry ent;
		ent.value.intv = b;
		ent.ty = binary_entry_type::T_INTEGER;
		_length += size_of(char_for(ent.ty));
		_entries.add(ent);
		invalidate_pattern_string();
	}

	void add_float(float b) {
		_entry ent;
		ent.value.floatv = b;
		ent.ty = binary_entry_type::T_FLOAT;
		_length += size_of(char_for(ent.ty));
		_entries.add(ent);
		invalidate_pattern_string();
	}
	void add_double(double b) {
		_entry ent;
		ent.value.doublev = b;
		ent.ty = binary_entry_type::T_DOUBLE;
		_length += size_of(char_for(ent.ty));
		_entries.add(ent);
		invalidate_pattern_string();
	}
	size_t size() const {
		return this->_entries.size();
	}
	size_t sizeb() const {
		return this->_length;
	}
	sys::lwstring get_pattern_string() {
		if (this->_patternExp.empty()) update_pattern_string();
		return this->_patternExp;
	}

	static binary_entry_type type_of(char id) {

		switch (id)
		{
		case 'b': return	binary_entry_type::T_BOOL;
		case 'c': return	binary_entry_type::T_CHAR;
		case 's': return	binary_entry_type::T_SHORT;
		case 'i': return	binary_entry_type::T_INTEGER;
		case 'f':return		binary_entry_type::T_FLOAT;
		case 'd': return	binary_entry_type::T_DOUBLE;
		default:return		binary_entry_type::T_NONE;
		}

	}
	static char char_for(binary_entry_type e) {
		switch (e) {
		case binary_entry_type::T_BOOL:return 'b';
		case binary_entry_type::T_CHAR:return 'c';
		case binary_entry_type::T_SHORT:return 's';
		case binary_entry_type::T_INTEGER:return 'i';
		case binary_entry_type::T_FLOAT:return 'f';
		case binary_entry_type::T_DOUBLE: return 'd';
		default: return 0;
		}
	}
	static size_t size_of(char id) {

		switch (id)
		{
		case 'b': return sizeof(bool);
		case 'c': return sizeof(char); ;
		case 's': return sizeof(short); ;
		case 'i': return sizeof(int32_t); ;
		case 'f':return sizeof(float);
		case 'd': return (sizeof(double));
		default:return 0;
		}

	}
	static bool try_parse(void* data, sys::lwstring str, binary_series* out, bool swapEndian)
	{
		sys::string_view strv = str.view();

		size_t ptsz = 0;
		int num = 0;
		const char* p = strv.c_str();

		auto add_count = [&](size_t x) {
			ptsz += x;
			num++;
			};

		constexpr int MAX_ENTRIES = 128;
		_entry* dta = new _entry[MAX_ENTRIES];
		while (*p)
		{
			size_t tsz = size_of(*p);
			if (tsz == 0) {
				delete[] dta;
				return false;
			}

			_entry& x = dta[num];
			x.ty = type_of(*p);

			byte* offset = ((byte*)data + ptsz);

			switch (x.ty)
			{
			case binary_entry_type::T_BOOL:
				x.set_bool(*(byte*)offset);
				break;

			case binary_entry_type::T_CHAR:
				x.set_char(*(char*)offset);
				break;

			case binary_entry_type::T_SHORT:
			{
				short v = *(short*)offset;
				sys::memcpy(&v, offset, sizeof(short));
				if (swapEndian) v = bswap16(v);
				x.set_short(v);
				break;
			}

			case binary_entry_type::T_INTEGER:
			{
				int v;;
				sys::memcpy(&v, offset, sizeof(int));
				if (swapEndian) v = bswap32(v);
				x.set_int(v);
				break;
			}

			case binary_entry_type::T_FLOAT:
			{
				float v;
				sys::memcpy(&v, offset, sizeof(float));
				if (swapEndian) v = bswapf(v);
				x.set_float(v);
				break;
			}

			case binary_entry_type::T_DOUBLE:
			{
				double v;
				sys::memcpy(&v, offset, sizeof(double));
				if (swapEndian) v = bswapd(v);
				x.set_double(v);
				break;
			}
			}

			add_count(tsz);
			++p;
		}

		dta = sys::fundamental_trim_excess(dta, MAX_ENTRIES, num);

		out->clear();
		out->_length = ptsz;
		out->_entries.set_specific(dta, num);

		return true;
	}

};

_SYS_ENS
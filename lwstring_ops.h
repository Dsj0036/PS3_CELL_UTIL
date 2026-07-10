#pragma once
#include "lwstring.h"
#include "_ns.h"
#include "algorithm.h"
_SYS_NS

template<class Char>
class lwstring_ops {
	using lwstring_type = sys::basic_lightweight_string<Char>;
	lwstring_type* _owner = NULL;
	size_t _length = 0;
	

	inline lwstring_ops(lwstring_type& in) : _owner(&in), _length(in.length()){

	}

public:

	lwstring_type substring(int32_t off, int32_t count) const {
		if (count == 0) return {};
		if (count == -1 || count > _length) count = _length;
		
		size_t rlen = sys::min(count, _length - off);
		const Char* str = (_pBegin + pos);
		return lwstring_type(str, rlen);
	}
	lwstring_type substring(int32_t off) const {
		return substring(off, -1);
	}
	
	
	int32_t index_of(Char c) const;
	int32_t index_of(const lwstring_type& str) const;

	int32_t last_index_of(Char c) const;
	int32_t last_index_of(const lwstring_type& str) const;

	lwstring_type trim_start(Char c) const;
	lwstring_type trim_end(Char c) const;

	lwstring_type pad_left(Char c) const;
	lwstring_type pad_right(Char c) const;

	lwstring_type insert(Char c, int32_t index, int32_t count); 
	lwstring_type insert(const lwstring_type& str, int32_t index); 

	lwstring_type replace(const lwstring_type& str) const;
	lwstring_type remove(const lwstring_type& str) const;

	bool contains(const lwstring_type& str) const;

	inline int32_t length() const { return _length; }
};
_SYS_ENS
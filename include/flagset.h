#include "types.h"
#include <sys/types.h>

template<class _size = uint32_t>
struct t_flagset {
	_size value{ 0 };

	template<typename E>
	inline void add(E val) {
		if (value & (_size)val)return;
		value |= (_size)val;
	}

	template<typename E>
	inline void remove(E val) {
		if ((value & (_size)val) == 0)return;
		value &= ~((_size)val);
	}

	template<typename E>
	inline bool has(E val) const {
		return (value & (_size)val) != 0;
	}

	template<typename E>
	inline void set(E val, bool b) {
		if (b) add(val);
		else remove(val);
	}

	inline void clear() { value = 0; }

	inline bool empty() const { return value == 0; }

	inline operator _size() const { return value; }

	inline t_flagset& operator&=(_size num) {
		value &= num;
		return *this;
	}
}; 
using flagset32 = t_flagset<uint32_t>;
using flagset16 = t_flagset<uint16_t>;
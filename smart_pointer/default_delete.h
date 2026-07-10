#pragma once
#include "..\_ns.h"

namespace sys {

	template<typename T>
	class default_delete {
	public:
		void operator ()(T* o) {
			delete o;
		}
	};

	template<typename T>
	class default_delete<T[]> {
	public:
		void operator ()(T* o) {
			delete[] o;
		}
	};

}

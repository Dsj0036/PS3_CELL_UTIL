#pragma once
#include <sys\types.h>
#include <stddef.h>
namespace sys{

	template<typename _SENDER_TYPE, typename ...Args>
	class callback {
	public:
		using signature = void(*)(_SENDER_TYPE, Args...);

		callback() : _value(nullptr) {}

		callback& operator +=(signature function) {
			_value = function;
			return *this;
		}
		callback& operator =(signature function) {
			return operator+=(function);
		}
		void invoke(_SENDER_TYPE sender, const Args&...va) {
			if (_value != NULL)
				_value(sender, va...);
		}
	private:
		signature _value;
	};
}
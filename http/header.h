#pragma once
#include "..\lwstring.h"
#include "..\_ns.h"
_SYS_NS
namespace http {

	class header {
	public:
		header() {}
		header(const sys::lwstring& key, const sys::lwstring& value) : mKey(key), mValue(value) {

		}
		inline const sys::lwstring& key() const { return mKey; }
		inline sys::lwstring& key() { return mKey; }


		inline const sys::lwstring& value() const { return mValue; }
		inline sys::lwstring& value() { return mValue; }

	private:
		sys::lwstring mKey{ EMPTY_STRING };
		sys::lwstring mValue{ EMPTY_STRING };
	};
}
_SYS_ENS
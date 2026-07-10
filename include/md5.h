#pragma once
#include "array.h"
#include "string_view.h"
#include "lwstring.h"
namespace sys {
	class md5 final {
	public:
		static md5 compute(const void* in, size_t length);
		static md5 compute(const string_view& in);
		bool operator ==(const md5& other)const;
		bool operator !=(const md5& other)const;
		md5& operator =(const md5& other);
		static md5 fromString(const char* str);
		sys::lwstring toString() const;
	private:
		uint64_t left{0};
		uint64_t right{0};
	};
	

}
#pragma once
#include "..\_ns.h"
#include "header.h"
#include "..\list.h"
#include "..\io\binary_reader.h"
#include "..\io\memory_stream.h"
#include "..\io\text_reader.h"
#include "..\lexical_cast.h"
#include "..\smart_pointer\shared_ptr.h"

_SYS_NS
namespace http {

	class response {
	public:

		enum class ParseError :int {
			NONE,
			INVALID_FORMAT,
			NO_HTTP_VERSION_SPECIFIED,
			INVALID_HTTP_VERSION,
			INVALID_RESPONSE_CODE,
			INVALID_RESPONSE_CODE_MESSAGE,

		};

		response(const sys::lwstring& string);
		response();

		static sys::shared_ptr<response> parse(sys::stream* stream, response::ParseError& error);

		/// ITERATORS

		sys::iter<const header> headers() const {
			return sys::iter<const header>(mHeaders.data(), mHeaders.size());
		}
		sys::iter<header> headers() {
			return sys::iter<header>(mHeaders.data(), mHeaders.size());
		}

		/// GETTERS

		inline int code() const { return mResponseCode; }

		inline sys::lwstring& responseStr() { return mResponseStr; }
		inline const sys::lwstring& responseStr() const { return mResponseStr; }

		inline sys::lwstring& body() { return mBody; }
		inline const sys::lwstring& body() const { return mBody; }

		inline sys::lwstring& str() { return mSrcContent; }
		inline const sys::lwstring& str() const { return mSrcContent; }

		inline int headerCount() const { return mHeaders.size(); }

		header* getHeader(const char* name);

	private:
		// do not expose vector, just wrap it :p
		sys::list<header> mHeaders;
		int mResponseCode{ 0 };
		sys::lwstring mResponseStr{ EMPTY_STRING };
		sys::lwstring mBody{ EMPTY_STRING };
		sys::lwstring mSrcContent{ EMPTY_STRING };
	};

}
_SYS_ENS
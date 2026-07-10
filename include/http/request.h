#pragma once
#include "..\_ns.h"

#include "netex\net.h"
#include "cell\http\client.h"
#include "cell\http\util.h"
#include "cell\http\error.h"

#include "..\smart_pointer\shared_ptr.h"
#include "..\list.h"
#include "..\string_builder.h"
#include "..\format.h"

#include "uri.h"
#include "header.h"

_SYS_NS
struct uri;
namespace http {
	class request {
	public:
		enum class Method : unsigned char {
			GET,
			POST,
			PUT,
			PATCH,
			DELETE,
			HEAD,
			OPTIONS,
		};


		static const char* methodStr(Method method) {
			switch (method) {
			case Method::GET: return "GET";
			case Method::POST:	   return "POST";
			case Method::PUT:	   return "PUT";
			case Method::PATCH:	   return "PATCH";
			case Method::DELETE:   return "DELETE";
			case Method::HEAD: 	   return "HEAD";
			case Method::OPTIONS: return "OPTIONS";
			default: return "UNKNOWN";
			}
		}

		const sys::list<header>& headers() const { return mHeaders; }
		void setMethod(Method method) { mMethod = method; }
		const Method& method() const { return mMethod; }

		void setHostName(const sys::lwstring& host) { mHostName = host; }
		const sys::lwstring& hostName() const { return mHostName; }

		void setPath(const sys::lwstring& path) { mPath = path; }
		const sys::lwstring& path() const { return mPath; }

		void setBody(const sys::lwstring& body) { mBody = body; }
		const sys::lwstring& body() const { return mBody; }

		void setContentLength(uint64_t len) { mContentLength = len; }
		uint64_t contentLength() const { return mContentLength; }

		void setNoContentLength() { mContentLength = 0; }
		void setNoBody() { mBody.clear(); }

		void addHeader(const sys::lwstring& key, const sys::lwstring& value) {
			mHeaders.add({ key, value });
		}

		void setHeader(const sys::lwstring& key, const sys::lwstring& value) {
			removeHeader(key);
			addHeader(key, value);
		}

		bool hasHeader(const sys::lwstring& key) const {

			for (auto& header : mHeaders)
				if (header.key() == key)
					return true;

			return false;
		}

		void removeHeader(const sys::lwstring& key) {
			int m = 0;
			for (auto& header : mHeaders) {
				if (header.key() == key) {
					mHeaders.remove_at(m);
					break;
				}
				m++;
			}
		}

		inline sys::list<header>& headers() { return mHeaders; }


		void setUri(const sys::shared_ptr<uri>& val) {
			if (val.is_null())
				return;

			setHostName(val->hostname);
			setPath(sys::lwstring::nw(val->path.empty() ? "/" : val->path.c_str()));

			if (val->port != 0) {
				if ((val->scheme == "http" && val->port != 80) ||
					(val->scheme == "https" && val->port != 443)) {
					sys::lwstring hostWithPort = sys::sformat("%s:%u",
						val->hostname.c_str(), val->port);
					setHostName(hostWithPort);
				}
			}

			if (!val->username.empty()) {
				sys::lwstring auth = val->username;
				
				if (!val->password.empty())
					auth = sys::sformat("%s:%s", val->username.c_str(), val->password.c_str());


				// update: avoid computing authlength two times, just save it instead.
				size_t authLength = auth.length();

				size_t bSize = CELL_HTTP_UTIL_BASE64_ENC_BUF_SIZE(authLength);

				char* bAuth = new char[bSize];
				
				sys::memset(bAuth, 0, bSize);

				cellHttpUtilBase64Encoder(bAuth, auth.c_str(), authLength);

				auth._unsafe_assign_crt(bAuth);

				addHeader(sys::lwstring::nw("Authorization"),
					sys::sformat("Basic %s", auth.c_str()));
			}
		}

		sys::lwstring build() const {
			sys::string_builder ss;

			ss.appendf("%s %s HTTP/%s\r\n", methodStr(this->mMethod), mPath.c_str(), VERSION);

			ss.appendf("Host: %s\r\n", mHostName.c_str());

			ss.appendf("User-Agent: %s\r\n", AGENT);

			for (auto& h : mHeaders) {
				ss.appendf("%s: %s\r\n", h.key().c_str(), h.value().c_str());
			}

			if (mContentLength > 0)
				ss.appendf("Content-Length: %llu\r\n", mContentLength);

			ss.append("\r\n");

			if (!mBody.empty()) {
				ss.append(mBody.c_str());
			}
			ss.terminate();

			return ss.to_string();
		}
	private:

		sys::lwstring mHostName{ sys::EMPTY_STRING };
		sys::lwstring mPath{ sys::EMPTY_STRING };
		Method mMethod{ Method::GET };


		sys::lwstring mBody{ sys::EMPTY_STRING };

		// u64 is maybe too big for cell sockets.
		uint64_t mContentLength{ 0 };

		// consider converting this to an unordered_map.
		sys::list<header> mHeaders;
	};
}
using http_request_method = http::request::Method;
static constexpr const char* (*http_request_method_to_string)(http_request_method) = http::request::methodStr;
_SYS_ENS

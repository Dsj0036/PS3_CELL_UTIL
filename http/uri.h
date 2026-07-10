#pragma once
#include "..\lwstring.h"

namespace sys {
	struct uri {
		sys::lwstring scheme;   /* http or https                  */
		sys::lwstring hostname; /* www.foo.com; 192.168.0.1       */
		sys::lwstring username;
		sys::lwstring password;
		sys::lwstring path;     /* /; /bar.html; /mydir/some.txt  */
		uint32_t port;        /* port number in host byte order */
	};


	/*
	* WARNING:
	* Changing the HTTP version string to anything other than "1.0" (e.g. "1.1")
	* may cause protocol-level inconsistencies when handling the response.
	*
	* In particular, when the remote server uses persistent connections or
	* chunked transfer encoding (typical of HTTP/1.1), the receiver may not
	* properly detect the end of the message body. As a result, the internal
	* socket `recv()` call can block indefinitely waiting for additional data
	* that never arrives — effectively causing the kernel to enter an
	* infinite wait loop on the connection.
	*
	* Always keep this set to "1.0" unless proper Content-Length handling,
	* connection closing, and chunk decoding have been fully implemented.
	*/
	static constexpr const char* VERSION = "1.0";
	static constexpr const char* AGENT = "Mozilla/5.0 (PLAYSTATION 3; 4.91)";


}

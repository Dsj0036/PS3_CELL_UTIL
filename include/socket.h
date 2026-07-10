#pragma once
#include <netinet\in.h>
#include <arpa\inet.h>
#include "socket_enum.h"
#include "memory.h"
#include "_ns.h"
#include "optional.h"
#include "error_code.h"
#include <netex\errno.h>
#include "resulting.h"
#include "throw.h"
extern "C"
{
#include <netex\net.h>
#include <netex\sockinfo.h>
}

_SYS_NS
struct socket_addr {
	unsigned char size{ 0 };
	sa_family_t family{ 0 };
	in_port_t port{ 0 };
	struct in_addr address;

	void clear() {
		size = 0;
		family = 0;
		port = 0;
		address .s_addr= 0;
	}
	static socket_addr create_inet(const char* ip_address, int port) {
		socket_addr address;
		sys::memset(&address.address, 0, sizeof(address.address));
		address.port = port;
		address.address.s_addr = inet_addr(ip_address);
		address.family = eIpAddressFamily::ADF_INET;
		return address;
	}
	static socket_addr create_inet(const char* ip_address, int port, ip_address_family fam) {
		socket_addr address;
		sys::memset(&address.address, 0, sizeof(address.address));
		address.port = port;
		address.address.s_addr = inet_addr(ip_address);
		address.family = fam;
		return address;
	}
	void copy_from(const socket_addr& r) {
		this->size = r.size;
		this->family= r.family;
		this->port = r.port;
		this->address.s_addr= r.address.s_addr;
	}

private:
	char sin_zero[8]{ 0 };
};

class socket {
public:
	class eSocketState final {
	public:
		enum Enum : unsigned char {
			Default = 0,
			Opened = 1,
			Connected = 1 << 2,
			Bound = 1 << 3,
		};
	};
	using socket_state = eSocketState::Enum;
	static constexpr int MIN_TIMEOUT_MILLISECONDS = 1;
	static constexpr int MAX_POSSIBLE_SOCKET_ID = 1023;

private:



	socket_addr _connectedEndpoint{};
	// Bound address to local
	socket_addr _boundEndpoint;

	int _descriptor{ -1 };
	unsigned char _state{ socket_state::Default };

public:
	socket();

	inline socket(sys::uninitialized_opt_t) {
		_boundEndpoint.address.s_addr = -1u;
		_connectedEndpoint.address.s_addr = -1u;
	}
	socket(socket&);
	explicit inline socket(const socket& r) {

		_boundEndpoint.copy_from(r._boundEndpoint);
		_connectedEndpoint.copy_from(r._connectedEndpoint);
		_state = r._state;
		_descriptor = r._descriptor;
	}


	static constexpr inline bool isValidHandle(int s) {
		return s >= 0 && s <= MAX_POSSIBLE_SOCKET_ID;
	}

	
	void steal(socket& other);
	int handle() const;
	

	socket& open(ip_address_family family, socket_type type, socket_option opt = socket_option::SOPT_NULL);
	ip_address_family address_family()const;
	bool opened() const;
	int bind(socket_addr addr);
	int connect(socket_addr addr);
	int disconnect();
	int close();
	int accept_client(sys::socket*);
	int abort_socket(int s);
	sys::result<sys_net_sockinfo_t> getInfo(int hdl);
	int send(const void* in, size_t len, socket_flag flag);
	ssize_t receive(void* output, size_t len, socket_flag flag);
	inline bool is_connected() const {
		return this->_state & socket_state::Connected;
	}
	inline bool is_bound() const {
		return this->_state & socket_state::Bound;
	}
	/// <summary>
	/// Movement.
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	socket& operator = (socket& other) {
		this->steal(other);
		return *this;
	}
	static sys::result<socket> create(ip_address_family family, socket_type type, socket_option opt = socket_option::SOPT_NULL);
	~socket();
};

//__DEF_SYSTEM_EXCEPTION_TYPE_2__(socket_exception, "Internal system failure",
// Initialize with an specified cause.
	//socket_exception(void* func, int system_error);
//);


_SYS_ENS

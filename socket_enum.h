#pragma once
namespace sys {
	class eSocketType {
	public:
		enum Enum {
			TYPE_SOCK_STREAM = 1,
			TYPE_SOCK_DGRAM = 2,
			TYPE_SOCK_RAW = 3,
			TYPE_SOCK_DGRAM_P2P = 6,
			TYPE_SOCK_STREAM_P2P = 10,
		};
	};
	class eSocketOpt {
	public:
		enum Enum {
			SOPT_NULL,
			SOPT_REUSEADDR = (2 << 1),
			SOPT_KEEPALIVE = (2 << 2),
			SOPT_BROADCAST = (2 << 4),
			SOPT_LINGER = (2 << 6),
			SOPT_OOBINLINE = (2 << 6),
			SOPT_REUSEPORT = (2 << 8),
			SOPT_ONESBCAST = 0x0800,
			SOPT_USECRYPTO = 0x1000,
			SOPT_USESIGNATURE = 0x2000,

		};
	};
	class eIpAddressFamily {
	public:
		enum Enum {

			ADF_UNSPEC = 0,
			ADF_LOCAL = 1,
			ADF_UNIX = ADF_LOCAL,
			ADF_INET = 2,
			ADF_IMPLINK = 3,
			ADF_PUP = 4,
			ADF_CHAOS = 5,
			ADF_NS = 6,
			ADF_ISO = 7,
			ADF_OSI = ADF_ISO,
			ADF_ECMA = 8,
			ADF_DATAKIT = 9,
			ADF_CCITT = 10,
			ADF_SNA = 11,
			ADF_DECnet = 12,
			ADF_DLI = 13,
			ADF_LAT = 14,
			ADF_HYLINK = 15,
			ADF_APPLETALK = 16,
			ADF_ROUTE = 17,
			ADF_LINK = 18,
		};

	};
	class eSocketShutdown {
	public:
		enum Enum : unsigned char{
			Read = 0,
			Write = 1,
			Both = 2,
		};
	};
	class eSocketFlag {
	public:
		enum Enum : int {
			/*
#define	MSG_OOB		0x1
#define	MSG_PEEK	0x2
#define MSG_DONTROUTE	0x4
#define MSG_EOR		0x8
#define MSG_TRUNC	0x10
#define MSG_CTRUNC	0x20
#define	MSG_WAITALL	0x40
#define	MSG_DONTWAIT	0x80
#define MSG_BCAST	0x100
#define MSG_MCAST	0x200
#define MSG_USECRYPTO	0x400
#define MSG_USESIGNATURE	0x800
			*/
			NONE,
			OOB			= 0x1,
			PEEK = 0x2,
			DONT_ROUTE = 0x4,
			EOR = 0x8,
			TRUNC = 0x10,
			CTRUNC = 0x20,
			WAIT_ALL = 0x40,
			DONT_WAIT = 0x80,
			BCAST = 0x100,
			MCAST = 0x200,
			USE_CRYPTO = 0x400,
			USE_SIGNATURE = 0x800,
		};
	};
	using socket_type = eSocketType::Enum;
	using socket_option = eSocketOpt::Enum;
	using ip_address_family = eIpAddressFamily::Enum;
	using socket_shutdown = eSocketShutdown::Enum;
	using socket_flag = eSocketFlag::Enum;


}
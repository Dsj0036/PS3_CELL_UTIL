
#ifndef SYSTEM_H
#include "System.h"
#endif


namespace Debug {
	// mallocated
	const char* sprx_path = "/dev_hdd0/tmp/dclient/session.txt";
	bool disable = false;
	int debugger_socket = -1;
	bool debugger_is_attached = false;


	char* last = "";
	void cout(char c, bool endl = false)
	{
		if (disable) { return; }
		char cs[2] = { c, endl ? '\n' : ' ' };
		last = cs;
		FS_APPEND_STRING((char*)(sprx_path), cs, 0);
	}
	void cout(char* text)
	{
		if (disable) { return; }
		FS_APPEND_STRING((char*)(sprx_path), text, 0);
		last = text;
	}
	void coutl(char* text)
	{
		if (disable) { return; }

		FS_APPEND_STRING((char*)(sprx_path), text, 0);
		FS_APPEND_STRING((char*)(sprx_path), "\n", 0);
		last = text;
	}
	void coutf(char* format, int value) {
		if (disable) { return; }
		char loc[0x300];
		_sys_memset(loc, 0, 0x300);
		_sys_snprintf(loc, 0x300, format, value);
		FS_APPEND_STRING((char*)sprx_path, loc, 0);
		last = loc;
	}

	void coutf(char* format, int value, int v2) {
		if (disable) { return; }
		char loc[0x300];
		_sys_memset(loc, 0, 0x300);
		_sys_snprintf(loc, 0x300, format, value, v2);
		FS_APPEND_STRING((char*)sprx_path, loc, 0);
		last = loc;
	}
	void coutf(char* format, int value, int v2, int v3) {
		if (disable) { return; }
		char loc[0x300];
		_sys_memset(loc, 0, 0x300);
		_sys_snprintf(loc, 0x300, format, value, v2, v3);
		FS_APPEND_STRING((char*)sprx_path, loc, 0);
	}

	void coutf(char* format, int value, int v2, int v3, int v4) {
		if (disable) { return; }
		char loc[0x300];
		_sys_memset(loc, 0, 0x300);
		_sys_snprintf(loc, 0x300, format, value, v2, v3, v4);
		FS_APPEND_STRING((char*)sprx_path, loc, 0);
	}

	void coutf(char* format, int value, int v2, int v3, int v4, float v5) {
		if (disable) { return; }
		char loc[0x300];
		_sys_memset(loc, 0, 0x300);
		_sys_snprintf(loc, 0x300, format, value, v2, v3, v4, v5);
		FS_APPEND_STRING((char*)sprx_path, loc, 0);
	}

	void coutf(char* format, char* value) {
		if (disable) { return; }
		char loc[0x300];
		_sys_memset(loc, 0, 0x300);
		_sys_snprintf(loc, 0x300, format, value);
		FS_APPEND_STRING((char*)sprx_path, loc, 0);
		last = loc;
	}

	void coutf(char* format, char* value, char* v2) {
		if (disable) { return; }
		char loc[0x300];
		_sys_memset(loc, 0, 0x300);
		_sys_snprintf(loc, 0x300, format, value, v2);
		FS_APPEND_STRING((char*)sprx_path, loc, 0);
		last = loc;
	}
	void coutf(char* format, char* value, char* v2, char* v3) {
		if (disable) { return; }
		char loc[0x300];
		_sys_memset(loc, 0, 0x300);
		_sys_snprintf(loc, 0x300, format, value, v2, v3);
		FS_APPEND_STRING((char*)sprx_path, loc, 0);
		last = loc;
	}
	void coutf(char* format, char* value, char* v2, char* v3, char* v4) {
		if (disable) { return; }
		char loc[0x300];
		_sys_memset(loc, 0, 0x300);
		_sys_snprintf(loc, 0x300, format, value, v2, v3, v4);
		FS_APPEND_STRING((char*)sprx_path, loc, 0);
		last = loc;
	}
	template <typename ...Arguments>
	void coutf(char* format, Arguments ...args) {
		if (disable) { return; }
		char loc[0x300];
		_sys_memset(loc, 0, 0x300);
		_sys_snprintf(loc, 0x300, format, args...);
		FS_APPEND_STRING((char*)sprx_path, loc, 0);

	}
	void coutif(bool check, char* txt) {
		if (check)
		{
			if (disable) { return; }
			cout(txt);
		}
	}
	void coutfail(char* name, int operResult) {
		if (disable) { return; }
		if (operResult < 0) {
			char loc[0x300];
			_sys_memset(loc, 0, 0x300);
			_sys_snprintf(loc, 0x300, "%s: (%x)\n", name, operResult);
			FS_APPEND_STRING((char*)sprx_path, loc, 0);
			last = loc;
		}
	}
	void coutm(void(*streaming)(int fd)) {
		if (disable) { return; }
		FS_APPEND_STRING((char*)(sprx_path), "", streaming);
	}
	void debugger_socket_init_extern() {
		debugger_socket = socket(2, 1, 0);
		if (debugger_socket < 0) {
			Debug::coutl("Debug initialization: Error creating socket. Local tracing only.");
		}

		sockaddr_in addr;
		_sys_memset(&addr, 0, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_port = 80;
		const char* my_address = "192.168.0.1";
		addr.sin_addr.s_addr = inet_addr(my_address);
		int ret = connect(debugger_socket, (const sockaddr*)&addr, sizeof(addr));
		if (ret < 0) {

			addr.sin_addr.s_addr = inet_addr("192.168.0.1");
			ret = connect(debugger_socket, (const sockaddr*)&addr, sizeof(addr));
		}
		Debug::coutf("Socket connection results: %x\n", ret);
		debugger_is_attached = ret == 0;

	}

	void write_object_address(const char* name, void* o) {
		char buffer[50];
		snprintf(buffer, 50, "🔰 %s is stored at %x\n", name, fn(o));
		coutl(buffer);
	}
	void Initialize() {
		FS_PURGE(sprx_path);
		FS_CREATE((char*)sprx_path);
		// AF INET | SOCK STREAM.
		threaded(debugger_socket_init_extern, "init_debugger_socket");

	}

	void ensureDebugger() {
		if (!debugger_is_attached) {
			threaded(debugger_socket_init_extern, "init_debugger_socket");
		}
	}

}
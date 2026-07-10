#pragma once
#include <sys\event.h>
#include "array.h"
#include "smart_pointer/unique_ptr.h"
#include "resulting.h"
_SYS_NS
class event_queue;
class event_port {
	sys_event_port_t mHandle{ SYS_EVENT_PORT_ID_INVALID };
	uint64_t mUid;
public:
	event_port(uint64_t uid);
	event_port(const event_port& other);
	const sys_event_port_t& handle() const;


	const uint64_t& uid()const;
	int initialize();
	int connectToQueueLocal(event_queue& queue);

	int disconnectFromQueue();

	void dispose();

	~event_port();

};
class event_queue_attribute {
	sys_event_queue_attr mAttr;
public:
	event_queue_attribute(sys_protocol_t protocol, int type, uint64_t name);
	int type() const;
	uint64_t name() const;
	sys_protocol_t protocol() const;

	sys_event_queue_attr& attrib();
};
class event_queue {
	friend event_port;

	event_port mPort;
	sys_event_queue_t mHandle{ SYS_EVENT_QUEUE_ID_INVALID };
	event_queue_attribute mAttrib;
	uint8_t mCapacity = 0;
public:
	event_queue(event_port& port, sys_protocol_t protocol, int type, uint64_t name, uint8_t capacity);


	const uint8_t& capacity() const;

	uint64_t uid()const;
	const sys_event_queue_t& handle() const;
	const event_port& port() const;

	bool initialized() const;

	int initialize();

	int  receive(sys::unique_ptr<sys_event >& out, usecond_t timeout);
	int tryReceive(int size, sys::array<sys_event>& out, usecond_t timeout);

	void dispose();

	~event_queue();

};



_SYS_ENS

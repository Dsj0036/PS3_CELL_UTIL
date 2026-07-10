#pragma once
#include "_ns.h"
#include "memory.h"
#include "throw.h"
#include "_pragma_static_getter.h"
#include "type_info.h"
_SYS_NS
class crt_alloc;

class handle;
class alloc {
	friend handle;
protected:
	alloc() {};
public:

	// HANDLE AND DATA ALLOCATOR
	virtual inline void* unsafe_malloc(size_t n, size_t align) {
		FAIL(sys::pure_virtual_error("Invalid function usage is NOT allowed."));
		return NULL;
	}

	// HANDLE AND DATA DEALLOCATOR
	virtual inline void unsafe_free(void* px) {
		sys::printf("Invalid function usage is NOT allowed.");
		FAIL(sys::pure_virtual_error("Invalid function usage is NOT allowed."));
	}
	// HELPER.
	template<typename T>
	inline T* malloc() {
		return static_cast<T*>(unsafe_malloc(sizeof(T), alignof(T)));
	}

	// HANDLE CONSTRUCTION BEHAVIOUR
	//virtual sys::handle malloc(size_t x, size_t align) {
	//	FAIL(sys::pure_virtual_error("Invalid function usage is NOT allowed."));
	//}
	//// HANDLE DESTRUCTION BEHAVIOUR
	//virtual bool free(sys::handle v) {
	//	FAIL(sys::pure_virtual_error("Invalid function usage is NOT allowed."));
	//}
	virtual ~alloc() = default;
};
class crt_alloc : public alloc{
	int hdl;
	crt_alloc() : alloc() {
		hdl = 0xBEEF;
	}

public:

	// HANDLE AND DATA ALLOCATOR
	void* unsafe_malloc(size_t n, size_t align) override {
		return sys::memalign(align, n);
	}
	// HANDLE AND DATA DEALLOCATOR
	void unsafe_free(void* px) override{
		sys::free(px);
	}
	virtual ~crt_alloc() = default;

	static crt_alloc& instance() {
		static crt_alloc alloc{};
		return alloc;
	}
	void __validate() {
		__expect(hdl == 0xbeef);
	}
};




_SYS_ENS

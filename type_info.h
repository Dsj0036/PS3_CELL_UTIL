#pragma once
#include <stdint.h>
#include "_ns.h"
#include "lwstring.h"
#include "constexpr_fnv1a.h"
#include "_pragma_section_reflex.h"
_SYS_NS

template<typename T>
constexpr bool has_reflection() {
	return false;
}

#define UTIL_KEY_ID(TYPE, VALUE) template<>\
	constexpr uint32_t builtin_key_id<TYPE>(){return VALUE;}

#define SYS_TYPE_REGISTRY_FLAGS_NESTED		(1 << 1)
#define SYS_TYPE_REGISTRY_FLAGS_PRIVATE		(1 << 2)
#define SYS_TYPE_REGISTRY_FLAGS_PROTECTED	(1 << 3)
#define SYS_TYPE_REGISTRY_FLAGS_STATIC		(1 << 4)
#define SYS_TYPE_REGISTRY_FLAGS_FINAL		(1 << 5)
#define SYS_TYPE_REGISTRY_FLAGS_CHILD		(1 << 6)
#define SYS_TYPE_REGISTRY_FLAGS_CLASS		(1 << 7)
#define SYS_TYPE_REGISTRY_FLAGS_STRUCT		(1 << 8)

namespace reflex {
	struct member {
		const char* name;
		uint16_t offset;
		uint32_t type_id;
		uint8_t flags;

		constexpr member(const char* nm, uint16_t offset, uint32_t type_id, uint8_t flags)
			: name(nm), offset(offset), type_id(type_id), flags(flags) {

		}
	};


	struct registry {
		const char* name;
		uint16_t size;
		uint16_t alignment;
		uint32_t id;
		const member* members;
		uint8_t member_count;
		uint16_t flags;

		constexpr registry(const char* name, uint16_t size, uint16_t alignment, uint16_t id, const member* members, uint8_t member_count, uint16_t flags)
			: name(name), size(size), id(id), alignment(alignment), members(members), member_count{ member_count }, flags(flags) {

		}


	};

	template<typename T>
	static constexpr const char* builtin_key() {
		return __FUNCTION__;
	}
	template<typename T>
	static constexpr uint32_t builtin_key_id() {
		return 0;
	}

	UTIL_KEY_ID(bool, 0);
	UTIL_KEY_ID(unsigned char, 1);
	UTIL_KEY_ID(unsigned short, 2);
	UTIL_KEY_ID(unsigned int, 3);
	UTIL_KEY_ID(unsigned long, 4);
	UTIL_KEY_ID(unsigned long long, 5);
	UTIL_KEY_ID(char, 7);
	UTIL_KEY_ID(short, 8);
	UTIL_KEY_ID(int, 9);
	UTIL_KEY_ID(float, 10);
	UTIL_KEY_ID(double, 11);
	UTIL_KEY_ID(long, 12);
	UTIL_KEY_ID(long long, 13);
	UTIL_KEY_ID(long double, 14);

	struct reflex_member_access;
	class myObject {
		friend reflex_member_access;
		int v;

	private:

	};


	// This show be used at the global scope.
#define SYS_TYPE_BEGIN(CODENAME, FULL_NAME) namespace reflected_meta_##CODENAME { using type = FULL_NAME;

	// This show be used at the global scope.
#define SYS_TYPE_DECLARE_MEMBER_ARRAY static constexpr _SYS_PRAGMA_SECTION_REFLEX_ sys::reflex::member members[]{

#define SYS_TYPE_DECLARE_MEMBER_ARRAY_2 static constexpr _SYS_PRAGMA_SECTION_REFLEX_ sys::reflex::member members[]

	// This show be used at the global scope.
#define SYS_TYPE_DECLARE_MEMBER(TY, NAME) sys::reflex::member{#NAME, offsetof(type, NAME), sys::reflex::builtin_key_id<TY>(), 0} 


#define SYS_TYPE_END_MEMBER_ARRAY_2 ; 

	// This show be used at the global scope.
#define SYS_TYPE_INFO(FULL_NAME, TYPE_FLAGS) static constexpr _SYS_PRAGMA_SECTION_REFLEX_ const sys::reflex::registry info{\
	#FULL_NAME,\
		sizeof(FULL_NAME),\
		alignof(FULL_NAME), \
		sys::reflex::builtin_key_id<FULL_NAME>(), \
		members, \
		sys::extent<decltype(members)>::value,\
		TYPE_FLAGS\
	};



#define SYS_TYPE_END(CODENAME) } template<> inline const sys::reflex::registry* sys::type_info<reflected_meta_##CODENAME::type>(){ return &reflected_meta_##CODENAME::info; } 

#define SYS_TYPE_DECLARE(CODENAME, TYPE_FULL_NAME, MEMBERS, TYPE_FLAGS ) SYS_TYPE_BEGIN(CODENAME, TYPE_FULL_NAME) \
SYS_TYPE_DECLARE_MEMBER_ARRAY_2 MEMBERS SYS_TYPE_END_MEMBER_ARRAY_2 \
SYS_TYPE_INFO(TYPE_FULL_NAME, TYPE_FLAGS)




	}; // namespace reflex

	template<typename T>
	inline const reflex::registry* type_info() {
		return NULL;
	}




	_SYS_ENS // namespace sys
#undef UTIL_KEY_ID

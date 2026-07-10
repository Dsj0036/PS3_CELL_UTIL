#pragma once
namespace sys {


	void _assert(bool condition, const char* conditionStr, 
		const char* functionName, const char* fileName, int line);

	
}
#ifdef _DEBUG
#define sys_assert(condition) sys::_assert(condition, #condition, __FUNCTION__, __FILE__, __LINE__);
#else 
#define _sys_assert(condition) (void)0
#endif
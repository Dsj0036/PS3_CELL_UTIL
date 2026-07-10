#pragma once
#include <stdint.h>
struct nothrow_t
{	// placement new tag type to suppress exceptions
};

/**
 * @file malloc.h
 * @brief Custom memory allocation operators for Onyx System
 * 
 * @details
 * This header provides custom implementations of the global `operator new` and 
 * `operator delete` functions. These overrides are necessary to redirect memory 
 * allocation and deallocation calls from the standard C++ library functions to 
 * system-provided intrinsics.
 * 
 * @rationale
 * The default standard library memory allocation functions are not suitable for 
 * kernel-level code execution. When strict manual linkage is enabled, the linker 
 * would resolve memory operations to standard library implementations, which can:
 * - Access invalid memory regions in kernel context
 * - Bypass required privilege levels
 * - Cause kernel panics and subsequent hard-resets
 * 
 * By overriding these operators, we ensure all dynamic memory operations utilize
 * system-provided allocator intrinsics that are properly integrated with the 
 * Onyx kernel's memory management infrastructure.
 * 
 * @warning
 * These functions MUST be linked against external kernel allocator intrinsics.
 * Failure to provide proper implementations will result in kernel crashes.
 */

// Single object allocation operators
/**
 * @brief Allocate memory for a single object
 * @param size Number of bytes to allocate
 * @return Pointer to allocated memory, or nullptr on failure
 */
void* operator new(size_t size);

/**
 * @brief Allocate memory with no-throw guarantee
 * @param size Number of bytes to allocate
 * @return Pointer to allocated memory, or nullptr on failure (no exception)
 */
void* operator new(size_t size, const nothrow_t&);

/**
 * @brief Allocate aligned memory for a single object
 * @param size Number of bytes to allocate
 * @param align Required alignment in bytes
 * @return Pointer to allocated aligned memory
 */
void* operator new(size_t size, size_t align);

/**
 * @brief Allocate aligned memory with no-throw guarantee
 * @param size Number of bytes to allocate
 * @param align Required alignment in bytes
 * @return Pointer to allocated aligned memory, or nullptr on failure
 */
void* operator new(size_t size, size_t align, const nothrow_t&);

// Array allocation operators
/**
 * @brief Allocate memory for an array of objects
 * @param size Total number of bytes to allocate
 * @return Pointer to allocated memory
 */
void* operator new[](size_t size);

/**
 * @brief Allocate array memory with no-throw guarantee
 * @param size Total number of bytes to allocate
 * @return Pointer to allocated memory, or nullptr on failure
 */
void* operator new[](size_t size, const nothrow_t&);

/**
 * @brief Allocate aligned array memory
 * @param size Total number of bytes to allocate
 * @param align Required alignment in bytes
 * @return Pointer to allocated aligned memory
 */
void* operator new[](size_t size, size_t align);

/**
 * @brief Allocate aligned array memory with no-throw guarantee
 * @param size Total number of bytes to allocate
 * @param align Required alignment in bytes
 * @return Pointer to allocated aligned memory, or nullptr on failure
 */
void* operator new[](size_t size, size_t align, const nothrow_t&);

// Single object deallocation operators
/**
 * @brief Deallocate memory for a single object
 * @param mem Pointer to memory to deallocate
 */
void operator delete(void* mem);

/**
 * @brief Deallocate memory with no-throw guarantee
 * @param mem Pointer to memory to deallocate
 */
void operator delete(void* mem, const nothrow_t&);

/**
 * @brief Deallocate memory (placement delete)
 * @param ptr Pointer to memory to deallocate
 * @param prt2 Optional placement parameter
 */
void operator delete(void* ptr, void* prt2);

/**
 * @brief Deallocate aligned memory
 * @param ptr Pointer to memory to deallocate
 * @param align Alignment value used during allocation
 */
void operator delete(void* ptr, size_t align);

/**
 * @brief Deallocate aligned memory with no-throw guarantee
 * @param ptr Pointer to memory to deallocate
 * @param align Alignment value used during allocation
 */
void operator delete(void* ptr, size_t align, const  nothrow_t&);

/**
 * @brief Deallocate aligned memory (placement delete)
 * @param ptr Pointer to memory to deallocate
 * @param align Alignment value used during allocation
 * @param prt2 Optional placement parameter
 */
void operator delete(void* ptr, size_t align, void* prt2);

// Array deallocation operators
/**
 * @brief Deallocate memory for an array of objects
 * @param mem Pointer to memory to deallocate
 */
void operator delete[](void* mem);

/**
 * @brief Deallocate array memory with no-throw guarantee
 * @param mem Pointer to memory to deallocate
 */
void operator delete[](void* mem, const nothrow_t&);

/**
 * @brief Deallocate array memory (placement delete)
 * @param ptr Pointer to memory to deallocate
 * @param prt2 Optional placement parameter
 */
void operator delete[](void* ptr, void* prt2);

/**
 * @brief Deallocate aligned array memory
 * @param ptr Pointer to memory to deallocate
 * @param align Alignment value used during allocation
 */
void operator delete[](void* ptr, size_t align);

/**
 * @brief Deallocate aligned array memory with no-throw guarantee
 * @param ptr Pointer to memory to deallocate
 * @param align Alignment value used during allocation
 */
void operator delete[](void* ptr, size_t align, const nothrow_t&) noexcept;

/**
 * @brief Deallocate aligned array memory (placement delete)
 * @param ptr Pointer to memory to deallocate
 * @param align Alignment value used during allocation
 * @param prt2 Optional placement parameter
 */
void operator delete[](void* ptr, size_t align, void* prt2);



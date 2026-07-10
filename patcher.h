#pragma once
#include "pch.h"
#include <sys/types.h>
#include "opd.h"
namespace sys {
	namespace patcher {
		/**
		 * @brief Hooks a function by replacing its entry point with a jump to a custom handler.
		 *
		 * This function patches PowerPC/CELL architecture code to redirect function calls.
		 * It works by creating two stubs:
		 * 1. A normal function stub that preserves the original function logic
		 * 2. A hook stub that jumps to the custom handler function
		 *
		 * The original code at @p addr is replaced with instructions that jump to
		 * @p jumpFunctionEntry, while the original code is moved to @p functionEntry.
		 *
		 * @param addr The address of the original function to hook.
		 * @param functionEntry The address where the original function code will be relocated.
		 * @param jumpFunctionEntry The address of the custom handler function to jump to.
		 *
		 * @return Status code indicating success or failure of the hook operation.
		 *
		 * @note This function uses both mapped (@c mapi_*) and unmapped (@c krn::*) memory
		 *       operations to ensure proper cache coherency on CELL processors.
		 * @note The stubs use PowerPC instruction encoding:
		 *       - 0x3D60xxxx: Load upper immediate (lis instruction)
		 *       - 0x616Bxxxx: OR immediate (ori instruction)
		 *       - 0x7D6903A6: Move to link register (mtctr instruction)
		 *       - 0x4E800420: Branch to count register (bctr instruction)
		 *
		 * @warning This operation directly modifies executable memory and should only
		 *          be used in appropriate contexts (kernel mode, authorized patches).
		 */
		int _hookFunction(sys_addr_t addr, uint32_t functionEntry, uint32_t jumpFunctionEntry);
#if false
		template <class ENTRY>
		int hookFunction(sys_addr_t addr, ENTRY functionEntry, ENTRY jumpFunctionEntry) {
			return _hookFunction(addr, 
				(uint32_t) * (int**)(functionEntry),
				(uint32_t) * (int**)(jumpFunctionEntry));
		}
#endif
		template <typename F1, typename F2>
		int hookFunction(sys_addr_t addr, F1 functionEntry, F2 jumpFunctionEntry) {
			return _hookFunction(addr, 
				(uint32_t)((void*)functionEntry), 
				(uint32_t)((void*)jumpFunctionEntry));
		}

		/// @brief Creates a PowerPC branch instruction at the specified address.
		/// 
		/// This function generates a PowerPC branch instruction that redirects execution
		/// to a target function. It encodes the branch offset into a branch instruction
		/// and synchronizes the instruction cache to ensure the change takes effect.
		/// 
		/// @param ea The effective address where the branch instruction will be written.
		/// @param bl A pointer to the target address for the branch operation.
		/// 
		/// @details The function performs the following operations:
		///   - Calculates the offset between the target and the instruction location
		///   - Encodes a PowerPC branch instruction (0x48000000 | offset)
		///   - Sets the link bit (LSB = 1) to maintain link register behavior
		///   - Flushes the data cache and synchronizes instruction cache using
		///     __dcbst(), __sync(), and __isync() intrinsics
		/// 
		/// @note This function targets PowerPC architecture and manipulates low-level
		///       instruction encoding. The offset is masked to 0x03FFFFFC to ensure
		///       the value fits within the 24-bit signed branch offset field.
		void branch(sys_addr_t ea, void* functionBaseOpd);

		int redirect(uint32_t address, void* target);

		int replace(uint32_t address, void* overrider);
	}
}
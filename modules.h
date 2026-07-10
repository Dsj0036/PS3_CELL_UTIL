#pragma once
#include "_ns.h"
#include <sysutil/sysutil_gamecontent.h>
#include <sysutil/sysutil_common.h>
#include <sysutil/sysutil_sysconf.h>
#include <sysutil/sysutil_game_exec.h>
#include <cell/sysmodule.h>


_SYS_NS
namespace modules {
	/// <summary>
	/// Load a PRX
	/// </summary>
	/// <param name="identifier">ID identifying the PRX</param>
	/// <returns>
	/// CELL_OK: normal termination. 
	/// CELL_SYSMODULE_ERROR_UNKNOWN: Tried to load an unknown PRX
	/// CELL_SYSMODULE_ERROR_FATAL: Loading failed.
	/// </returns>
	CellError load(uint16_t identifier) {
		return cellSysmoduleLoadModule(identifier);
	}

	/// Unloads the PRX specified with id. 
	/// CELL_OK will return even when the unload is attempted on a PRX that is already unloaded. 
	CellError unload(uint16_t identifier) {
		return cellSysmoduleLoadModule(identifier);
	}

	/// <summary>
	/// This functions returns whether or not the PRX specified with id is loaded. 
	/// Depending on the dependency relationship between modules, it is possible for the PRX specified with
	///	id to have already been unloaded when another module was unloaded.In such cases,
	///	CELL_SYSMODULE_ERROR_UNLOADED will return.
	/// </summary>
	/// <returns>CELL_SYSMODULE_ERROR_FATAL: Unexpected error
	/// CELL_SYSMODULE_ERROR_UNKNOWN: Unknown PRX
	/// CELL_SYSMODULE_ERROR_UNLOADED: PRX not loaded
	/// </returns>
	CellError is_loaded(uint16_t identifier) {
		return cellSysmoduleIsLoaded(identifier);
	}
	CellError finalize_service()
	{
		return cellSysmoduleFinalize();
	}
}

_SYS_ENS


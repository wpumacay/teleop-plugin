#include <simKeyboard.hpp>

#include <simLib/simLib.h>

// NOLINTNEXTLINE
static LIBRARY simLib;

SIM_DLLEXPORT auto simInit(SSimInit* info) -> int {
    simLib = loadSimLibrary(info->coppeliaSimLibPath);
    if (simLib == nullptr) {
        simAddLog(info->pluginName, sim_verbosity_errors,
                  "Couldn't find or correctly load the CoppeliaSim library. "
                  "Cannot start the plugin.");
        return 0;
    }

    if (getSimProcAddresses(simLib) == 0) {
        simAddLog(info->pluginName, sim_verbosity_errors,
                  "could not find all required functions in the CoppeliaSim "
                  "library. Cannot start the plugin.");
        unloadSimLibrary(simLib);
        return 0;
    }

    simAddLog(info->pluginName, sim_verbosity_infos,
              "Successfully initialized plugin");

    return 3;
}

SIM_DLLEXPORT auto simMsg(SSimMsg* info) -> void {}

SIM_DLLEXPORT auto simCleanup() -> void { unloadSimLibrary(simLib); }

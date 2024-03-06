#include <simKeyboard.hpp>

#include <simLib/simLib.h>

#include <GLFW/glfw3.h>

#include <iostream>

#define PLUGIN_VERSION 6

// NOLINTNEXTLINE
static LIBRARY simLib;

static GLFWwindow* g_window = nullptr;

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

    if (glfwInit() != GLFW_TRUE) {
        return 0;
    }

    g_window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (g_window == nullptr) {
        glfwTerminate();
        return 0;
    }

    std::cout << "Hello World!" << std::endl;

    return PLUGIN_VERSION;
}

SIM_DLLEXPORT auto simMsg(SSimMsg* info) -> void {}

SIM_DLLEXPORT auto simCleanup() -> void { unloadSimLibrary(simLib); }

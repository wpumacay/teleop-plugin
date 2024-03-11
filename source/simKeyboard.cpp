#include <simKeyboard.hpp>

#include <simLib/simLib.h>

#include <GLFW/glfw3.h>

#include <iostream>
#include <thread>

#define PLUGIN_VERSION 6

// NOLINTNEXTLINE
static LIBRARY simLib;

static std::thread g_thread;

static GLFWwindow* g_window = nullptr;

auto worker_fcn() -> void {
    if(g_window == nullptr) {
        return;
    }

    glfwSetKeyCallback(g_window, [](GLFWwindow* window, int key, int scancode,
                                    int action, int mods) {
        if (action == GLFW_PRESS || action == GLFW_REPEAT) {
            std::cout << "Key pressed: " << key << std::endl;
        }

        if(key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    });

    while (glfwWindowShouldClose(g_window) == GLFW_FALSE) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(g_window);
        glfwPollEvents();
    }
}

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

    g_thread = std::thread(&worker_fcn);
    // Should move the join to the cleanup function
    g_thread.join();
    glfwTerminate();

    return PLUGIN_VERSION;
}

SIM_DLLEXPORT auto simMsg(SSimMsg* info) -> void {}

SIM_DLLEXPORT auto simCleanup() -> void { 
    unloadSimLibrary(simLib);
}

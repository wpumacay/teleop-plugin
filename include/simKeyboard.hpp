#pragma once

#include <simLib/simExp.h>
#include <simLib/simTypes.h>

SIM_DLLEXPORT auto simInit(SSimInit *) -> int;
SIM_DLLEXPORT auto simMsg(SSimMsg *) -> void;
SIM_DLLEXPORT auto simCleanup() -> void;

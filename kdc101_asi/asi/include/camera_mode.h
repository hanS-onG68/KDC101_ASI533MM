#pragma once

#include "log.h"
#include <memory>
#include "ASICamera2.h"

class GetDllFunc;

class AsiCameraMode {
public:
    AsiCameraMode() { LOG_INFO("Class AsiCameraMode init."); }
    virtual ~AsiCameraMode() { LOG_INFO("Class AsiCameraMode delete."); }
    int CameraModeOperate(GetDllFunc &DllFuncsPtr, std::shared_ptr<ASI_CAMERA_INFO> cameraInfo);
    bool IsGetDllFuncCameraMode(GetDllFunc &DllFuncsPtr, HMODULE hDll);
private:
protected:
};
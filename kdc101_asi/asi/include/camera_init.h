#pragma once

#include "log.h"
#include <memory>
#include "ASICamera2.h"

class GetDllFunc;

class AsiCameraInit {
public:
    AsiCameraInit() { LOG_INFO("Class AsiCameraInit init."); }
    virtual ~AsiCameraInit() { LOG_INFO("Class AsiCameraInit delete."); }
    int InitCamera(GetDllFunc &DllFuncsPtr, std::shared_ptr<ASI_CAMERA_INFO> cameraInfo, int *width, int *height, int cameraIndex);
    bool IsGetDllFuncInit(GetDllFunc &DllFuncsPtr, HMODULE hDll);
private:
protected:
};
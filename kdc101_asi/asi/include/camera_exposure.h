#pragma once

#include "log.h"
#include <memory>
#include "ASICamera2.h"

class GetDllFunc;

class AsiCameraExposure {
public:
    AsiCameraExposure() { LOG_INFO("Class AsiCameraExposure init."); }
    virtual ~AsiCameraExposure() { LOG_INFO("Class AsiCameraExposure delete."); }
    int ImageCapture(GetDllFunc &DllFuncsPtr, std::shared_ptr<ASI_CAMERA_INFO> cameraInfo, int width, int height);
    bool IsGetDllFuncExposure(GetDllFunc &DllFuncsPtr, HMODULE hDll);
private:
protected:
};
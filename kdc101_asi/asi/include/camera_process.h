#pragma once

struct ImageInfos {
    int width;   // 图像宽度
    int height;  // 图像高度
};

class AsiCameraInit;
class AsiCameraMode;
class AsiCameraExposure;

class CameraProcess {
public:
    CameraProcess();
    ~CameraProcess();
    bool IsCameraFunctionNormal(ASI_GetDllFunc &DllFuncsPtr, std::shared_ptr<ASI_CAMERA_INFO> cameraInfo, CameraProcess &camera, int cameraIndex);
    bool IsGetDllFunc(ASI_GetDllFunc &DllFuncsPtr, CameraProcess &camera, HMODULE hDll);
    int CameraAction(ASI_GetDllFunc &DllFuncsPtr, CameraProcess &camera);
private:
    AsiCameraInit cameraInit;
    AsiCameraMode cameraMode;
    AsiCameraExposure cameraExposure;
    ImageInfos imageInfo;
};

FARPROC GetProcAddressChecked(HMODULE hModule, const char *funcName);
#include <iostream>
#include <vector>
#include <memory>
#include "ASICamera2.h"
#include "log.h"
#include "asi_func.h"
#include "asi_convert.h"
#include "camera_init.h"
#include "camera_mode.h"
#include "camera_exposure.h"
#include "camera_process.h"

HMODULE DownLoadDll()
{
    const char *dllPath = "ASICamera2.dll";
    HMODULE hDll = NULL;

    try {
        // 1. 转换路径
        int stringLength = MultiByteToWideChar(CP_ACP, 0, dllPath, -1, nullptr, 0);
        if (stringLength == 0) {
            DWORD error = GetLastError();
            LOG_ERROR("[ERROR] Path conversion failed. Error: {}", error);
            return NULL;
        }

        // 2. 使用智能指针自动管理内存（C++11以上）
        auto wideDllPath = std::make_unique<wchar_t[]>(stringLength);
        if (MultiByteToWideChar(CP_ACP, 0, dllPath, -1, wideDllPath.get(), stringLength) == 0) {
            DWORD error = GetLastError();
            LOG_ERROR("[ERROR] Path conversion failed. Error: {}", error);
            return NULL;
        }

        // 3. 加载DLL
        hDll = LoadLibraryW(wideDllPath.get());
        if (hDll == NULL) {
            DWORD error = GetLastError();
            LOG_ERROR("[ERROR] Failed to load DLL: {}. Error: {}", dllPath, error);
        } else {
            LOG_INFO("Successfully loaded DLL: {}", dllPath);
        }
    } catch (const std::exception &e) {
        LOG_ERROR("[ERROR] Exception occurred while loading DLL: {}", e.what());
    }

    return hDll;
}

FARPROC GetProcAddressChecked(HMODULE hModule, const char *funcName)
{
    if (hModule == NULL) {
        printf("[Fail] hModule is null pointer!\n");
        LOG_INFO("[Fail] hModule is null pointer!\n");
        return NULL;
    }
    FARPROC proc = GetProcAddress(hModule, funcName);
    if (proc == NULL) {
        LOG_ERROR("Failed to find function: %s, err info:%lu \n", funcName, GetLastError());
    }
    return proc;
}

void CloseCamera(ASI_GetDllFunc &DllFuncsPtr, std::shared_ptr<ASI_CAMERA_INFO> cameraInfo)
{
    ASI_ERROR_CODE res = DllFuncsPtr.ASICloseCamera(cameraInfo->CameraID);
    if (res != ASI_SUCCESS) {
        LOG_ERROR("fail to close camera, CameraID = {}, Err.Code = {}", cameraInfo->CameraID, ASIErrorCodeToString(res));
        return;
    }
    LOG_INFO("close camera successfully, CameraID = {}", cameraInfo->CameraID);
    return;
}

/******************************* 类 CameraProcess *******************************/
CameraProcess::CameraProcess(): cameraInit(AsiCameraInit()), cameraMode(AsiCameraMode()), cameraExposure(AsiCameraExposure()) {
    imageInfo.width = 0;
    imageInfo.height = 0;
    LOG_INFO("class CameraProcess init.");
}

CameraProcess::~CameraProcess() {
    LOG_INFO("class CameraProcess delete.");
}

bool CameraProcess::IsGetDllFunc(ASI_GetDllFunc &DllFuncsPtr, CameraProcess &camera, HMODULE hDll)
{
    if (camera.cameraInit.IsGetDllFuncInit(DllFuncsPtr, hDll)       || 
        camera.cameraMode.IsGetDllFuncCameraMode(DllFuncsPtr, hDll) || 
        camera.cameraExposure.IsGetDllFuncExposure(DllFuncsPtr, hDll)
    ) {
        return FALSE;
    }
    return TRUE;
}

bool CameraProcess::IsCameraFunctionNormal(ASI_GetDllFunc &DllFuncsPtr, std::shared_ptr<ASI_CAMERA_INFO> cameraInfo, CameraProcess &camera, int cameraIndex)
{
    // 相机初始化
    if (camera.cameraInit.InitCamera(DllFuncsPtr, cameraInfo, &(camera.imageInfo.width), &(camera.imageInfo.height), cameraIndex)) {
        LOG_ERROR("camera init fail.");
        return FALSE;
    }

    // 相机模式 相关
    if (camera.cameraMode.CameraModeOperate(DllFuncsPtr, cameraInfo)) {
        LOG_ERROR("camera mode operate fail.");
        return FALSE;
    }

    // 图像处理 相关
    if (camera.cameraExposure.ImageCapture(DllFuncsPtr, cameraInfo, camera.imageInfo.width, camera.imageInfo.height)) {
        LOG_ERROR("camera exposure fail.");
        return FALSE;
    }
    return TRUE;
}

int CameraProcess::CameraAction(ASI_GetDllFunc &DllFuncsPtr, CameraProcess &camera) {
    HMODULE hDll = DownLoadDll(); // 加载DLL
    if (hDll == NULL) {
        LOG_ERROR("fail to load DLL, func = {}", __func__);
        return -1;
    }
    if (camera.IsGetDllFunc(DllFuncsPtr, camera, hDll)) {
        LOG_ERROR("fail to get function address from DLL, func = {}", __func__);
        FreeLibrary(hDll); // 卸载DLL
        return -1;
    }

    int numOfConnectedCameras = DllFuncsPtr.ASIGetNumOfConnectedCameras(); // 得到连接的相机的数量
    LOG_INFO("number of connected cameras is {}", numOfConnectedCameras);

    std::vector<std::shared_ptr<ASI_CAMERA_INFO>> cameraInfos;
    cameraInfos.reserve(numOfConnectedCameras);

    for (int i = 0; i < numOfConnectedCameras; i++) { // i表示相机的序号: 遍历所有相机
        auto cameraInfo = std::make_shared<ASI_CAMERA_INFO>();

        if (!camera.IsCameraFunctionNormal(DllFuncsPtr, cameraInfo, camera, i)) {
            CloseCamera(DllFuncsPtr, cameraInfo);
            continue;
        }
        CloseCamera(DllFuncsPtr, cameraInfo);

        cameraInfos.push_back(cameraInfo);
    }
    FreeLibrary(hDll); // 卸载DLL
    return 0;
}
#include "camera_mode.h"
#include "asi_func.h"
#include "asi_convert.h"
#include <map>
#include <algorithm>
#include <string>
#include <memory>


bool AsiCameraMode::IsGetDllFuncCameraMode(ASI_GetDllFunc &DllFuncsPtr, HMODULE hDll)
{
    DllFuncsPtr.ASIGetCameraSupportMode = (ASIGetCameraSupportMode_Func)GetProcAddressChecked(hDll, "ASIGetCameraSupportMode");
    DllFuncsPtr.ASISetCameraMode        = (ASISetCameraMode_Func)GetProcAddressChecked(hDll, "ASISetCameraMode");
    DllFuncsPtr.ASIGetCameraMode        = (ASIGetCameraMode_Func)GetProcAddressChecked(hDll, "ASIGetCameraMode");
    if (DllFuncsPtr.ASIGetCameraSupportMode == NULL || DllFuncsPtr.ASISetCameraMode == NULL || DllFuncsPtr.ASIGetCameraMode == NULL) {
        LOG_ERROR("Essential functions missing in DLL, func = {}", __func__);
        return FALSE;
    }
    return TRUE;
}

std::map<ASI_CAMERA_MODE, std::string> ASIPrintCameraMode(ASI_CAMERA_MODE *supportedCameraMode, int length)
{
    std::map<ASI_CAMERA_MODE, std::string> mp;
    for (int i = 0; i < length; i++) {
        ASI_CAMERA_MODE mode = supportedCameraMode[i];
        if (mode == ASI_MODE_END) {
            break;
        }
        LOG_INFO("support mode: {}", ASICameraModeToString(mode));
        mp[mode] = ASICameraModeToString(mode);
    }
    std::for_each(
        mp.begin(),
        mp.end(),
        [](const auto &pair) {
            std::cout << "ASI_CAMERA_MODE: " << pair.first << ", ASICameraModeToStr: " << pair.second << std::endl;
        });
    return mp;
}

int AsiCameraMode::CameraModeOperate(ASI_GetDllFunc &DllFuncsPtr, std::shared_ptr<ASI_CAMERA_INFO> cameraInfo)
{
    LOG_INFO("Enter CameraModeOperate for CameraID = {}", cameraInfo->CameraID);
    ASI_SUPPORTED_MODE supportedMode = {
        .SupportedCameraMode = new { ASI_MODE_END }
    };
    ASI_SUPPORTED_MODE* supportedMode = new ASI_SUPPORTED_MODE();
    if (!supportedMode) {
        LOG_ERROR("fail to new supportedMode pointer!");
        return -1;
    }
    ASI_ERROR_CODE res = DllFuncsPtr.ASIGetCameraSupportMode(cameraInfo->CameraID, supportedMode); // 获取相机支持的所有模式
    if (res != ASI_SUCCESS) {
        LOG_ERROR("fail to get camera support mode, CameraID = {}, Err.Code = {}", cameraInfo->CameraID, ASIErrorCodeToString(res));
        return -1;
    }
    LOG_INFO("get camera support mode successfully, CameraID = {}, supportedMode ", cameraInfo->CameraID);
    std::map<ASI_CAMERA_MODE, std::string> mp = ASIPrintCameraMode(supportedMode->SupportedCameraMode, 16);  // 16:SupportedCameraMode的长度, 该值需通过ASIGetCameraSupportMode等SDK函数实际获取
    ASI_CAMERA_MODE mode = ASI_MODE_NORMAL;
    if (mp.count(mode)) {
        ASI_ERROR_CODE res = DllFuncsPtr.ASISetCameraMode(cameraInfo->CameraID, mode); // 设置模式
        if (res != ASI_SUCCESS) {
            LOG_ERROR("fail to set camera mode, CameraID = {}, Err.Code = {}", cameraInfo->CameraID, ASIErrorCodeToString(res));
            return -1;
        }
        LOG_INFO("set camera mode successfully, CameraID = {}, mode = {}", cameraInfo->CameraID, ASICameraModeToString(mode));

        ASI_CAMERA_MODE curMode;
        ASI_ERROR_CODE res = DllFuncsPtr.ASIGetCameraMode(cameraInfo->CameraID, &curMode); // 获取当前相机所处的相机模式
        if (res != ASI_SUCCESS) {
            LOG_ERROR("fail to get camera mode, CameraID = {}, Err.Code = {}", cameraInfo->CameraID, ASIErrorCodeToString(res));
            return -1;
        }
        LOG_INFO("get camera mode successfully, CameraID = {}, mode = {}", cameraInfo->CameraID, ASICameraModeToString(curMode));
    }
    return 0;
}
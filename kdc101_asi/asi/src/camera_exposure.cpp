#include "camera_exposure.h"
#include "asi_func.h"
#include "asi_opencv.h"
#include "asi_convert.h"


bool AsiCameraExposure::IsGetDllFuncExposure(ASI_GetDllFunc &DllFuncsPtr, HMODULE hDll)
{
    DllFuncsPtr.ASIStartExposure   = (ASIStartExposure_Func)GetProcAddressChecked(hDll, "ASIStartExposure");
    DllFuncsPtr.ASIGetExpStatus    = (ASIGetExpStatus_Func)GetProcAddressChecked(hDll, "ASIGetExpStatus");
    DllFuncsPtr.ASIGetDataAfterExp = (ASIGetDataAfterExp_Func)GetProcAddressChecked(hDll, "ASIGetDataAfterExp");
    DllFuncsPtr.ASIStopExposure    = (ASIStopExposure_Func)GetProcAddressChecked(hDll, "ASIStopExposure");
    DllFuncsPtr.ASICloseCamera     = (ASICloseCamera_Func)GetProcAddressChecked(hDll, "ASICloseCamera");
    DllFuncsPtr.ASISetControlValue = (ASISetControlValue_Func)GetProcAddressChecked(hDll, "ASISetControlValue");
    if (DllFuncsPtr.ASIStartExposure == NULL   || DllFuncsPtr.ASIGetExpStatus == NULL || DllFuncsPtr.ASISetControlValue == NULL ||
        DllFuncsPtr.ASIGetDataAfterExp == NULL || DllFuncsPtr.ASIStopExposure == NULL || DllFuncsPtr.ASICloseCamera == NULL
    ) {
        LOG_ERROR("Essential functions missing in DLL, func = {}", __func__);
        return FALSE;
    }
    return TRUE;
}

int SetControlValue(ASI_GetDllFunc &DllFuncsPtr, std::shared_ptr<ASI_CAMERA_INFO> cameraInfo)
{
    std::vector<std::pair<ASI_CONTROL_TYPE, int>> setControlTypes = {
        { ASI_CONTROL_TYPE::ASI_EXPOSURE, 100000 },     // 设置控制类型 = ASI_EXPOSURE 的值, 32 <= val <= 2000000000, DefaultValue = 10000（单位us， 1秒 = 1 000 000 us）
        { ASI_CONTROL_TYPE::ASI_GAIN    , 200     },    // 设置控制类型 = ASI_GAIN 的值, 0 <= val <= 600, DefaultValue = 200
        { ASI_CONTROL_TYPE::ASI_OFFSET  , 1       }     // 设置控制类型 = ASI_OFFSET 的值, 0 <= val <= 100, DefaultValue = 1
    };
    for (auto it : setControlTypes) {
        ASI_ERROR_CODE res = DllFuncsPtr.ASISetControlValue(cameraInfo->CameraID, it.first, it.second, ASI_BOOL::ASI_TRUE);  // ASI_FALSE\ASI_TRUE: 是否让相机硬件或 SDK 自动调整该参数的值，以优化图像质量或适应环境变化。
        if (res != ASI_SUCCESS) {
            LOG_ERROR("fail to start control value, CameraID = {}, Err.Code = {}", cameraInfo->CameraID, ASIErrorCodeToString(res));
            return -1;
        }
        LOG_INFO("start control value successfully, CameraID = {}, control_type = {}, value = {}", cameraInfo->CameraID, ASIControlTypeToString(it.first), it.second);
    }
    
    return 0;
}

int AsiCameraExposure::ImageCapture(ASI_GetDllFunc &DllFuncsPtr, std::shared_ptr<ASI_CAMERA_INFO> cameraInfo, int width, int height)
{
    LOG_INFO("start exposure, CameraID = {}", cameraInfo->CameraID);
    // if (SetControlValue(DllFuncsPtr, cameraInfo)) {   // 设置多个控制类型的值
    //     LOG_ERROR("fail to set control value, CameraID = {}", cameraInfo->CameraID);
    //     return -1;
    // }

    ASI_ERROR_CODE res = DllFuncsPtr.ASIStartExposure(cameraInfo->CameraID, ASI_BOOL::ASI_FALSE); // 开始单张曝光, ASI_TRUE:这表示进行一次暗场曝光, ASI_FALSE:表示进行一次正常的曝光
    if (res != ASI_SUCCESS) {
        LOG_ERROR("fail to start exposure, CameraID = {}, Err.Code = {}", cameraInfo->CameraID, ASIErrorCodeToString(res));
        return -1;
    }
    LOG_INFO("start exposure successfully, CameraID = {}", cameraInfo->CameraID);

    ASI_EXPOSURE_STATUS expStatus = ASI_EXP_IDLE;
    do {
        res = DllFuncsPtr.ASIGetExpStatus(cameraInfo->CameraID, &expStatus); // 得到单张曝光的状态
        if (res != ASI_SUCCESS) {
            LOG_ERROR("fail to get exposure status, CameraID = {}, Err.Code = {}", cameraInfo->CameraID, ASIErrorCodeToString(res));
            return -1;
        }
        
        if (expStatus == ASI_EXP_FAILED) {
            LOG_ERROR("exposure fail");
            return -1;
        }
    } while (expStatus == ASI_EXP_WORKING);
    LOG_INFO("get exposure status successfully, CameraID = {}, expStatus = {}", cameraInfo->CameraID, ASIExposureStatusToString(expStatus));

    if (expStatus == ASI_EXP_SUCCESS) {
        const long buffSize = width * height;  /* RAW8 和Y8: bufSize >= image_width*image_height; RAW16: bufSize >= image_width*image_height *2，RGB24:bufSiz >= image_width*image_height *3 */
        unsigned char *bufferData = new unsigned char[buffSize]();
        if (bufferData == NULL) {
            LOG_ERROR("fail to allocate memory for bufferData, CameraID = {}, buffSize = {}", cameraInfo->CameraID, buffSize);
            return -1;
        }
        res = DllFuncsPtr.ASIGetDataAfterExp(cameraInfo->CameraID, bufferData, buffSize); // 单张曝光成功后读取图像
        if (res != ASI_SUCCESS) {
            LOG_ERROR("fail to get data after exposure, CameraID = {}, Err.Code = {}", cameraInfo->CameraID, ASIErrorCodeToString(res));
            delete[] bufferData;
            return -1;
        }
        LOG_INFO("get data after exposure successfully, CameraID = {}", cameraInfo->CameraID);
        
        OpenCvHandle(bufferData, width, height);  // 图片化处理

        delete[] bufferData;
        bufferData = NULL;
    } else {
        LOG_ERROR("exposure fail, Err.Code = = {}", ASIErrorCodeToString(res));
        return -1;
    }

    res = DllFuncsPtr.ASIStopExposure(cameraInfo->CameraID); // 中止曝光
    if (res != ASI_SUCCESS) {
        LOG_ERROR("fail to stop exposure, CameraID = {}, Err.Code = {}", cameraInfo->CameraID, ASIErrorCodeToString(res));
        return -1;
    }
    LOG_INFO("stop exposure successfully, CameraID = {}", cameraInfo->CameraID);

    return 0;
}

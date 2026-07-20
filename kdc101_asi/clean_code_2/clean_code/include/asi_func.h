#ifndef __ASI_FUNC_H__
#define __ASI_FUNC_H__

#include <iostream>
#include <windows.h>
#include <memory>
#include "ASICamera2.h"

typedef int int32_t;

typedef int (*ASIGetNumOfConnectedCameras_Func)();
typedef ASI_ERROR_CODE (*ASIGetCameraProperty_Func)(ASI_CAMERA_INFO *pASICameraInfo, int iCameraIndex);
typedef ASI_ERROR_CODE (*ASIOpenCamera_Func)(int iCameraID);
typedef ASI_ERROR_CODE (*ASIInitCamera_Func)(int iCameraID);
typedef ASI_ERROR_CODE (*ASIGetNumOfControls_Func)(int iCameraID, int * piNumberOfControls);
typedef ASI_ERROR_CODE (*ASIGetControlCaps_Func)(int iCameraID, int iControlIndex, ASI_CONTROL_CAPS * pControlCaps);
typedef ASI_ERROR_CODE (*ASISetROIFormat_Func)(int iCameraID, int iWidth, int iHeight, int iBin, ASI_IMG_TYPE Img_type);
typedef ASI_ERROR_CODE (*ASIGetROIFormat_Func)(int iCameraID, int *piWidth, int *piHeight, int *piBin, ASI_IMG_TYPE *pImg_type);
typedef ASI_ERROR_CODE (*ASISetStartPos_Func)(int iCameraID, int iStartX, int iStartY);
typedef ASI_ERROR_CODE (*ASIGetControlValue_Func)(int iCameraID, ASI_CONTROL_TYPE ControlType, long *plValue, ASI_BOOL *pbAuto);
typedef ASI_ERROR_CODE (*ASISetControlValue_Func)(int iCameraID, ASI_CONTROL_TYPE ControlType, long lValue, ASI_BOOL bAuto);
typedef ASI_ERROR_CODE (*ASIStartExposure_Func)(int iCameraID, ASI_BOOL bIsDark);
typedef ASI_ERROR_CODE (*ASIStopExposure_Func)(int iCameraID);
typedef ASI_ERROR_CODE (*ASIGetExpStatus_Func)(int iCameraID, ASI_EXPOSURE_STATUS *pExpStatus);
typedef ASI_ERROR_CODE (*ASIGetDataAfterExp_Func)(int iCameraID, unsigned char* pBuffer, long lBuffSize);
typedef ASI_ERROR_CODE (*ASICloseCamera_Func)(int iCameraID);
typedef ASI_ERROR_CODE (*ASISetCameraMode_Func)(int iCameraID, ASI_CAMERA_MODE mode);
typedef ASI_ERROR_CODE (*ASIGetCameraMode_Func)(int iCameraID, ASI_CAMERA_MODE* mode);
typedef ASI_ERROR_CODE (*ASIGetCameraSupportMode_Func)(int iCameraID, ASI_SUPPORTED_MODE* pSupportedMode);

typedef class GetDllFunc {
public:
    // 构造函数
    GetDllFunc() {
        std::cout << "----------------------GetDllFunc begin----------------------" << std::endl;
    }
    virtual ~GetDllFunc() {
        std::cout << "----------------------GetDllFunc end----------------------" << std::endl;
    }

    ASIGetNumOfConnectedCameras_Func ASIGetNumOfConnectedCameras;
    ASIGetCameraProperty_Func ASIGetCameraProperty;
    ASIOpenCamera_Func ASIOpenCamera;
    ASIInitCamera_Func ASIInitCamera;
    ASIGetNumOfControls_Func ASIGetNumOfControls;
    ASIGetControlCaps_Func ASIGetControlCaps;
    ASISetROIFormat_Func ASISetROIFormat;
    ASIGetROIFormat_Func ASIGetROIFormat;
    ASISetStartPos_Func ASISetStartPos;

    ASIGetControlValue_Func ASIGetControlValue;
    ASISetControlValue_Func ASISetControlValue;

    ASIGetCameraSupportMode_Func ASIGetCameraSupportMode;
    ASISetCameraMode_Func ASISetCameraMode;
    ASIGetCameraMode_Func ASIGetCameraMode;

    ASIStartExposure_Func ASIStartExposure;
    ASIGetExpStatus_Func ASIGetExpStatus;
    ASIGetDataAfterExp_Func ASIGetDataAfterExp;
    ASIStopExposure_Func ASIStopExposure;
    ASICloseCamera_Func ASICloseCamera;
} ASI_GetDllFunc;

typedef struct AsiROI {
    int width;              // 图像宽度
    int height;             // 图像高度
    int x;                  // x轴的起始位置
    int y;                  // y轴的起始位置
    int bin;                // NxN 像素合并值
    ASI_IMG_TYPE imgType;  // 图像格式
} AsiROI;

typedef int (*DllFunc)(ASI_GetDllFunc&, HMODULE);
FARPROC GetProcAddressChecked(HMODULE hModule, const char *funcName);
int camera_main();
int CameraGetDllFunc(ASI_GetDllFunc &DllFuncsPtr, HMODULE hDll);
int GetCameraProperty(ASI_GetDllFunc &DllFuncsPtr, std::shared_ptr<ASI_CAMERA_INFO> cameraInfo, int i);
void CloseCamera(ASI_GetDllFunc &DllFuncsPtr, std::shared_ptr<ASI_CAMERA_INFO> cameraInfo);
int InitCamera(ASI_GetDllFunc &DllFuncsPtr, std::shared_ptr<ASI_CAMERA_INFO> cameraInfo, AsiROI &roiInfo);
int CameraModeOperate(ASI_GetDllFunc &DllFuncsPtr, std::shared_ptr<ASI_CAMERA_INFO> cameraInfo);
int ImageCapture(ASI_GetDllFunc &DllFuncsPtr, std::shared_ptr<ASI_CAMERA_INFO> cameraInfo, AsiROI &roiInfo);
HMODULE DownLoadDll();

#endif
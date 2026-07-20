
#include "camera_init.h"
#include "asi_func.h"
#include "asi_convert.h"


bool AsiCameraInit::IsGetDllFuncInit(GetDllFunc &DllFuncsPtr, HMODULE hDll)
{
    DllFuncsPtr.ASIGetNumOfConnectedCameras = (ASIGetNumOfConnectedCameras_Func)GetProcAddressChecked(hDll, "ASIGetNumOfConnectedCameras");
    DllFuncsPtr.ASIGetCameraProperty        = (ASIGetCameraProperty_Func)GetProcAddressChecked(hDll, "ASIGetCameraProperty");
    DllFuncsPtr.ASIOpenCamera               = (ASIOpenCamera_Func)GetProcAddressChecked(hDll, "ASIOpenCamera");
    DllFuncsPtr.ASIInitCamera               = (ASIInitCamera_Func)GetProcAddressChecked(hDll, "ASIInitCamera");
    DllFuncsPtr.ASIGetNumOfControls         = (ASIGetNumOfControls_Func)GetProcAddressChecked(hDll, "ASIGetNumOfControls");
    DllFuncsPtr.ASIGetControlCaps           = (ASIGetControlCaps_Func)GetProcAddressChecked(hDll, "ASIGetControlCaps");
    DllFuncsPtr.ASISetROIFormat             = (ASISetROIFormat_Func)GetProcAddressChecked(hDll, "ASISetROIFormat");
    DllFuncsPtr.ASIGetROIFormat             = (ASIGetROIFormat_Func)GetProcAddressChecked(hDll, "ASIGetROIFormat");
    DllFuncsPtr.ASISetStartPos              = (ASISetStartPos_Func)GetProcAddressChecked(hDll, "ASISetStartPos");
    DllFuncsPtr.ASIGetControlValue          = (ASIGetControlValue_Func)GetProcAddressChecked(hDll, "ASIGetControlValue");
    if (DllFuncsPtr.ASIGetNumOfConnectedCameras == NULL || DllFuncsPtr.ASIGetCameraProperty == NULL || DllFuncsPtr.ASIOpenCamera == NULL     ||
        DllFuncsPtr.ASIInitCamera == NULL               || DllFuncsPtr.ASIGetNumOfControls == NULL  || DllFuncsPtr.ASIGetControlCaps == NULL ||
        DllFuncsPtr.ASISetROIFormat == NULL             || DllFuncsPtr.ASISetStartPos == NULL       || DllFuncsPtr.ASIGetROIFormat == NULL   ||
        DllFuncsPtr.ASIGetControlValue == NULL
    ) {
        LOG_ERROR("Essential functions missing in DLL, func = {}", __func__);
        return FALSE;
    }
    return TRUE;
}

int GetControlCaps(ASI_GetDllFunc &DllFuncsPtr, std::shared_ptr<ASI_CAMERA_INFO> cameraInfo, int numberOfControls)
{
    ASI_CONTROL_CAPS controlCaps;
    for (int n = 0; n < numberOfControls; ++n) {  // numberOfControls: 指定ID相机的控制类型的数量
        ASI_ERROR_CODE res = DllFuncsPtr.ASIGetControlCaps(cameraInfo->CameraID, n, &controlCaps);  // 得到特定序号的控制类型的内容
        if (res != ASI_SUCCESS) {
            LOG_ERROR("fail to get control caps, CameraID = {}, controlIndex = {}, Err.Code = {}!", cameraInfo->CameraID, n, ASIErrorCodeToString(res));
            return -1;
        }
        LOG_INFO("control index = {}, its info is:\n"
                 " Name = {},\n Description = {},\n MaxValue = {},\n MinValue = {},\n DefaultValue = {},\n"
                 "(0:ASI_FALSE)IsAutoSupported = {},\n (0:ASI_FALSE)IsWritable = {},\n ControlType = {}",
                 n, controlCaps.Name, controlCaps.Description, controlCaps.MaxValue, controlCaps.MinValue, controlCaps.DefaultValue,
                 int(controlCaps.IsAutoSupported), int(controlCaps.IsWritable), ASIControlTypeToString(controlCaps.ControlType));
        long value;
        ASI_BOOL autoAdjust = ASI_TRUE;
        res = DllFuncsPtr.ASIGetControlValue(cameraInfo->CameraID, controlCaps.ControlType, &value, &autoAdjust); // 得到指定ID相机的某控制类型的值
        if (res != ASI_SUCCESS) {
            LOG_ERROR("fail to get control value, CameraID = {}, controlIndex = {}, Err.Code = {}!", cameraInfo->CameraID, n, ASIErrorCodeToString(res));
            return -1;
        }
        LOG_INFO("get control value successfully, controlIndex = {}, ControlType = {}, value = {}", n, ASIControlTypeToString(controlCaps.ControlType), value);
    }
    return 0;
}

int GetCameraInfo(GetDllFunc &DllFuncsPtr, std::shared_ptr<ASI_CAMERA_INFO> cameraInfo, int i)
{
    // 直接使用智能指针的 get() 方法获取原始指针
    ASI_ERROR_CODE res = DllFuncsPtr.ASIGetCameraProperty(cameraInfo.get(), i); // 得到相机的信息，包括ID、名称、分辨率等
    if (res != ASI_SUCCESS) {
        LOG_ERROR("fail to get camera info,  Err.Code = {}", ASIErrorCodeToString(res));
        return -1;
    }

    LOG_INFO("get camera info successfully, camera info is:\n Name = {},\n Id = {},\n MaxHeight = {},\n MaxWidth = {},\n (0:ASI_FALSE)IsColorCam = {},\n"
             " (0:ASI_BAYER_RG, 1:ASI_BAYER_BG, 2:ASI_BAYER_GR, 3:ASI_BAYER_GB)BayerPattern = {},\n"
             " PixelSize = {},\n (0:ASI_FALSE)MechanicalShutter = {},\n (0:ASI_FALSE)ST4Port = {},\n (0:ASI_FALSE)IsCoolerCam = {},\n "
             "(0:ASI_FALSE)IsUSB3Host = {},\n (0:ASI_FALSE)IsUSB3Camera = {},\n ElecPerADU = {},\n BitDepth = {},\n "
             "(0:ASI_FALSE)IsTriggerCam = {},\n Unused = {}",
             cameraInfo->Name, cameraInfo->CameraID, cameraInfo->MaxHeight, cameraInfo->MaxWidth,
             int(cameraInfo->IsColorCam), int(cameraInfo->BayerPattern),
             cameraInfo->PixelSize, int(cameraInfo->MechanicalShutter), int(cameraInfo->ST4Port),
             int(cameraInfo->IsCoolerCam), int(cameraInfo->IsUSB3Host), int(cameraInfo->IsUSB3Camera),
             cameraInfo->ElecPerADU, cameraInfo->BitDepth, int(cameraInfo->IsTriggerCam), cameraInfo->Unused);
    std::cout << "cameraInfo->SupportedBins = ";
    std::copy(std::begin(cameraInfo->SupportedBins), std::end(cameraInfo->SupportedBins), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << "\ncameraInfo->SupportedVideoFormat = ";
    std::copy(std::begin(cameraInfo->SupportedVideoFormat), std::end(cameraInfo->SupportedVideoFormat), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << "\n";
    return 0;
}

int AsiCameraInit::InitCamera(GetDllFunc &DllFuncsPtr, std::shared_ptr<ASI_CAMERA_INFO> cameraInfo, int *width, int *height, int cameraIndex)
{
    if (GetCameraInfo(DllFuncsPtr, cameraInfo, cameraIndex)) {
        return -1;
    }

    ASI_ERROR_CODE res = DllFuncsPtr.ASIOpenCamera(cameraInfo->CameraID);  // 打开相机
    if (res != ASI_SUCCESS) {
        LOG_ERROR("fail to open camera, CameraID = {}, Err.Code = {}!", cameraInfo->CameraID, ASIErrorCodeToString(res));
        return -1;
    }
    LOG_INFO("open camera successfully, camear id = {}", cameraInfo->CameraID);

    res = DllFuncsPtr.ASIInitCamera(cameraInfo->CameraID);  // 初始化指定ID的相机
    if (res != ASI_SUCCESS) {
        LOG_ERROR("fail to init camera, CameraID = {}, Err.Code = {}!", cameraInfo->CameraID, ASIErrorCodeToString(res));
        return -1;
    }
    LOG_INFO("init camera successfully, camear id = {}", cameraInfo->CameraID);

    int numberOfControls = 0;
    res = DllFuncsPtr.ASIGetNumOfControls(cameraInfo->CameraID, &numberOfControls);  // 得到指定ID相机的控制类型的数量
    if (res != ASI_SUCCESS) {
        LOG_ERROR("fail to get num of controls, CameraID = {}, Err.Code = {}!", cameraInfo->CameraID, ASIErrorCodeToString(res));
        return -1;
    }
    LOG_INFO("get num of controls successfully, camear id = {},  the num of controls is {}", cameraInfo->CameraID, numberOfControls);

    if (GetControlCaps(DllFuncsPtr, cameraInfo, numberOfControls)) {  // 具体每种控制类型的内容
        return -1;
    }

    int bin;
    ASI_IMG_TYPE imgType;
    res = DllFuncsPtr.ASIGetROIFormat(cameraInfo->CameraID, width, height, &bin, &imgType);
    if (res != ASI_SUCCESS) {
        LOG_ERROR("fail to get ROI Format, CameraID = {}, Err.Code = {}", cameraInfo->CameraID, ASIErrorCodeToString(res));
        return -1;
    }
    LOG_INFO("get ROI Format successfully, CameraID = {}, width = {}, height = {}, bin = {}, imgType = {}", cameraInfo->CameraID, *width, *height, bin, int(imgType));

    res = DllFuncsPtr.ASISetROIFormat(cameraInfo->CameraID, *width, *height, bin, imgType);
    if (res != ASI_SUCCESS) {
        LOG_ERROR("fail to set ROI Format, CameraID = {}, Err.Code = {}", cameraInfo->CameraID, ASIErrorCodeToString(res));
        return -1;
    }
    LOG_INFO("set ROI Format successfully, CameraID = {}, width = {}, height = {}, bin = {}, imgType = {}", cameraInfo->CameraID, *width, *height, bin, int(imgType));

    int startX = 0;  // (3008 - *width) / 2;   // startX = (maxWidth - setWidth) / 2, MaxHeight = 3008
    int startY = 0;  // (3008 - *height) / 2;  // startY = (maxheight - setHeight) / 2, MaxWidth = 3008
    res = DllFuncsPtr.ASISetStartPos(cameraInfo->CameraID, startX, startY);
    if (res != ASI_SUCCESS) {
        LOG_ERROR("fail to set start position, CameraID = {}, Err.Code = {}", cameraInfo->CameraID, ASIErrorCodeToString(res));
        return -1;
    }
    LOG_INFO("set start position successfully, CameraID = {}, startX = {}, startY = {}", cameraInfo->CameraID, startX, startY);
    return 0;
}
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <map>
#include <vector>
#include <utility> // 包含 std::pair
#include <fstream>
#include "ASICamera2.h"
#include <memory>
#include "log.h"
#include "asi_func.h"
#include "asi_opencv.h"
#include "asi_convert.h"

std::map<ASI_CAMERA_MODE, std::string> ASIPrintCameraMode(ASI_CAMERA_MODE *supportedCameraMode)
{
    size_t length = sizeof(supportedCameraMode) / sizeof(supportedCameraMode[0]);
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

HMODULE DownLoadDll()
{
    const char *dllPath = "./../../../asi/sdk/libs/ASICamera2.dll";  
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

int GetDllFuncInit(ASI_GetDllFunc &DllFuncsPtr, HMODULE hDll)
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
    if (DllFuncsPtr.ASIGetNumOfConnectedCameras == NULL || DllFuncsPtr.ASIGetCameraProperty == NULL || DllFuncsPtr.ASIOpenCamera == NULL     ||
        DllFuncsPtr.ASIInitCamera == NULL               || DllFuncsPtr.ASIGetNumOfControls == NULL  || DllFuncsPtr.ASIGetControlCaps == NULL ||
        DllFuncsPtr.ASISetROIFormat == NULL             || DllFuncsPtr.ASISetStartPos == NULL       || DllFuncsPtr.ASIGetROIFormat == NULL
    ) {
        LOG_ERROR("Essential functions missing in DLL");
        return -1;
    }
    return 0;
}

int GetDllFuncControlValue(ASI_GetDllFunc &DllFuncsPtr, HMODULE hDll)
{
    DllFuncsPtr.ASIGetControlValue = (ASIGetControlValue_Func)GetProcAddressChecked(hDll, "ASIGetControlValue");
    DllFuncsPtr.ASISetControlValue = (ASISetControlValue_Func)GetProcAddressChecked(hDll, "ASISetControlValue");
    if (DllFuncsPtr.ASIGetControlValue == NULL || DllFuncsPtr.ASISetControlValue == NULL) {
        LOG_ERROR("Essential functions missing in DLL");
        return -1;
    }
    return 0;
}

int GetDllFuncCameraMode(ASI_GetDllFunc &DllFuncsPtr, HMODULE hDll)
{
    DllFuncsPtr.ASIGetCameraSupportMode = (ASIGetCameraSupportMode_Func)GetProcAddressChecked(hDll, "ASIGetCameraSupportMode");
    DllFuncsPtr.ASISetCameraMode        = (ASISetCameraMode_Func)GetProcAddressChecked(hDll, "ASISetCameraMode");
    DllFuncsPtr.ASIGetCameraMode        = (ASIGetCameraMode_Func)GetProcAddressChecked(hDll, "ASIGetCameraMode");
    if (DllFuncsPtr.ASIGetCameraSupportMode == NULL || DllFuncsPtr.ASISetCameraMode == NULL || DllFuncsPtr.ASIGetCameraMode == NULL) {
        LOG_ERROR("Essential functions missing in DLL");
        return -1;
    }
    return 0;
}

int GetDllFuncExposureOperate(ASI_GetDllFunc &DllFuncsPtr, HMODULE hDll)
{
    DllFuncsPtr.ASIStartExposure   = (ASIStartExposure_Func)GetProcAddressChecked(hDll, "ASIStartExposure");
    DllFuncsPtr.ASIGetExpStatus    = (ASIGetExpStatus_Func)GetProcAddressChecked(hDll, "ASIGetExpStatus");
    DllFuncsPtr.ASIGetDataAfterExp = (ASIGetDataAfterExp_Func)GetProcAddressChecked(hDll, "ASIGetDataAfterExp");
    DllFuncsPtr.ASIStopExposure    = (ASIStopExposure_Func)GetProcAddressChecked(hDll, "ASIStopExposure");
    DllFuncsPtr.ASICloseCamera     = (ASICloseCamera_Func)GetProcAddressChecked(hDll, "ASICloseCamera");
    if (DllFuncsPtr.ASIStartExposure == NULL   || DllFuncsPtr.ASIGetExpStatus == NULL ||
        DllFuncsPtr.ASIGetDataAfterExp == NULL || DllFuncsPtr.ASIStopExposure == NULL || DllFuncsPtr.ASICloseCamera == NULL
    ) {
        LOG_ERROR("Essential functions missing in DLL");
        return -1;
    }
    return 0;
}

int CameraGetDllFunc(ASI_GetDllFunc &DllFuncsPtr, HMODULE hDll)
{
    std::vector<DllFunc> funcs = {
        GetDllFuncInit,            // 初始化相关
        GetDllFuncControlValue,    // 读取和设置控件的值
        GetDllFuncCameraMode,      // 相机模式
        GetDllFuncExposureOperate  // 曝光相关操作
    };

    try {
        std::for_each(funcs.begin(), funcs.end(), [&DllFuncsPtr, hDll](DllFunc func) {
            if (func(DllFuncsPtr, hDll)) {
                throw std::runtime_error("DLL function initialization failed");
            }
        });
    } catch (const std::exception& e) {
        return -1;
    }
    return 0;
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

int GetCameraProperty(ASI_GetDllFunc &DllFuncsPtr, std::shared_ptr<ASI_CAMERA_INFO> cameraInfo, int i)
{
    // 直接使用智能指针的 get() 方法获取原始指针
    ASI_ERROR_CODE res = DllFuncsPtr.ASIGetCameraProperty(cameraInfo.get(), i); // 得到相机的信息，包括ID、名称、分辨率等
    if (res != ASI_SUCCESS) {
        LOG_ERROR("fail to get camera info,  Err.Code = {}", ASIErrorCodeToString(res));
        return -1;
    }
    LOG_INFO("get camera info successfully, camear id = {}", cameraInfo->CameraID);

    LOG_INFO("Camera info is:\n Name = {},\n Id = {},\n MaxHeight = {},\n MaxWidth = {},\n (0:ASI_FALSE)IsColorCam = {},\n"
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

int InitCamera(ASI_GetDllFunc &DllFuncsPtr, std::shared_ptr<ASI_CAMERA_INFO> cameraInfo, AsiROI &roiInfo)
{
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

    res = DllFuncsPtr.ASIGetROIFormat(cameraInfo->CameraID, &roiInfo.width, &roiInfo.height, &roiInfo.bin, &roiInfo.imgType);
    if (res != ASI_SUCCESS) {
        LOG_ERROR("fail to get ROI Format, CameraID = {}, Err.Code = {}", cameraInfo->CameraID, ASIErrorCodeToString(res));
        return -1;
    }
    LOG_INFO("get ROI Format successfully before setting, CameraID = {}, width = {}, height = {}, bin = {}, imgType = {}", cameraInfo->CameraID, roiInfo.width, roiInfo.height, roiInfo.bin, int(roiInfo.imgType));

    res = DllFuncsPtr.ASISetROIFormat(cameraInfo->CameraID, roiInfo.width, roiInfo.height, roiInfo.bin, roiInfo.imgType);
    if (res != ASI_SUCCESS) {
        LOG_ERROR("fail to set ROI Format, CameraID = {}, Err.Code = {}", cameraInfo->CameraID, ASIErrorCodeToString(res));
        return -1;
    }
    LOG_INFO("set ROI Format successfully, CameraID = {}, width = {}, height = {}, bin = {}, imgType = {}", cameraInfo->CameraID, roiInfo.width, roiInfo.height, roiInfo.bin, int(roiInfo.imgType));

    res = DllFuncsPtr.ASIGetROIFormat(cameraInfo->CameraID, &roiInfo.width, &roiInfo.height, &roiInfo.bin, &roiInfo.imgType);
    if (res != ASI_SUCCESS) {
        LOG_ERROR("fail to get ROI Format, CameraID = {}, Err.Code = {}", cameraInfo->CameraID, ASIErrorCodeToString(res));
        return -1;
    }
    LOG_INFO("get ROI Format successfully after setting, CameraID = {}, width = {}, height = {}, bin = {}, imgType = {}", cameraInfo->CameraID, roiInfo.width, roiInfo.height, roiInfo.bin, int(roiInfo.imgType));


    // int startX = 0;  // (3008 - *width) / 2;   // startX = (maxWidth - setWidth) / 2, MaxHeight = 3008
    // int startY = 0;  // (3008 - *height) / 2;  // startY = (maxheight - setHeight) / 2, MaxWidth = 3008
    res = DllFuncsPtr.ASISetStartPos(cameraInfo->CameraID, roiInfo.x, roiInfo.y);
    if (res != ASI_SUCCESS) {
        LOG_ERROR("fail to set start position, CameraID = {}, Err.Code = {}", cameraInfo->CameraID, ASIErrorCodeToString(res));
        return -1;
    }
    LOG_INFO("set start position successfully, CameraID = {}, startX = {}, startY = {}", cameraInfo->CameraID, roiInfo.x, roiInfo.y);
    return 0;
}

int CameraModeOperate(ASI_GetDllFunc &DllFuncsPtr, std::shared_ptr<ASI_CAMERA_INFO> cameraInfo)
{
    ASI_SUPPORTED_MODE supportedMode;
    ASI_ERROR_CODE res = DllFuncsPtr.ASIGetCameraSupportMode(cameraInfo->CameraID, &supportedMode); // 获取相机支持的所有模式
    if (res != ASI_SUCCESS) {
        LOG_ERROR("fail to get camera support mode, CameraID = {}, Err.Code = {}", cameraInfo->CameraID, ASIErrorCodeToString(res));
        return -1;
    }
    std::map<ASI_CAMERA_MODE, std::string> mp = ASIPrintCameraMode(supportedMode.SupportedCameraMode);
    ASI_CAMERA_MODE mode = ASI_MODE_NORMAL;
    if (mp.count(mode)) {
        res = DllFuncsPtr.ASISetCameraMode(cameraInfo->CameraID, mode); // 设置模式
        if (res != ASI_SUCCESS) {
            LOG_ERROR("fail to set camera mode, CameraID = {}, Err.Code = {}", cameraInfo->CameraID, ASIErrorCodeToString(res));
            return -1;
        }
        LOG_INFO("set camera mode successfully, CameraID = {}, mode = {}", cameraInfo->CameraID, ASICameraModeToString(mode));

        ASI_CAMERA_MODE curMode;
        res = DllFuncsPtr.ASIGetCameraMode(cameraInfo->CameraID, &curMode); // 获取当前相机所处的相机模式
        if (res != ASI_SUCCESS) {
            LOG_ERROR("fail to get camera mode, CameraID = {}, Err.Code = {}", cameraInfo->CameraID, ASIErrorCodeToString(res));
            return -1;
        }
        LOG_INFO("get camera mode successfully, CameraID = {}, mode = {}", cameraInfo->CameraID, ASICameraModeToString(curMode));
    }
    return 0;
}

int SetControlValue(ASI_GetDllFunc &DllFuncsPtr, std::shared_ptr<ASI_CAMERA_INFO> cameraInfo)
{
    std::vector<std::pair<ASI_CONTROL_TYPE, int>> setControlTypes = {
        { ASI_CONTROL_TYPE::ASI_EXPOSURE, 1000000 },     // 设置控制类型 = ASI_EXPOSURE 的值, 32 <= val <= 2000000000, DefaultValue = 10000（单位us， 1秒 = 1 000 000 us）
        { ASI_CONTROL_TYPE::ASI_GAIN    , 100     },    // 设置控制类型 = ASI_GAIN 的值, 0 <= val <= 600, DefaultValue = 200
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

int ImageCapture(ASI_GetDllFunc &DllFuncsPtr, std::shared_ptr<ASI_CAMERA_INFO> cameraInfo, AsiROI &roiInfo)
{
    if (SetControlValue(DllFuncsPtr, cameraInfo)) {   // 设置多个控制类型的值
        LOG_ERROR("fail to set control value, CameraID = {}", cameraInfo->CameraID);
        return -1;
    }

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
        const long buffSize = roiInfo.width * roiInfo.height;  /* RAW8 和Y8: bufSize >= image_width*image_height; RAW16: bufSize >= image_width*image_height *2，RGB24:bufSiz >= image_width*image_height *3 */
        unsigned char *bufferData = new unsigned char[buffSize]();
        res = DllFuncsPtr.ASIGetDataAfterExp(cameraInfo->CameraID, bufferData, buffSize); // 单张曝光成功后读取图像
        if (res != ASI_SUCCESS) {
            LOG_ERROR("fail to get data after exposure, CameraID = {}, Err.Code = {}", cameraInfo->CameraID, ASIErrorCodeToString(res));
            return -1;
        }
        LOG_INFO("get data after exposure successfully, CameraID = {}", cameraInfo->CameraID);
        
        OpenCvHandle(bufferData, roiInfo);  // 图片化处理

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

int CameraAction(ASI_GetDllFunc &DllFuncsPtr)
{
    HMODULE hDll = DownLoadDll(); // 加载DLL
    if (hDll == NULL) {
        return -1;
    }
    if(CameraGetDllFunc(DllFuncsPtr, hDll)) {
        LOG_ERROR("fail to get DLL functions");
        FreeLibrary(hDll); // 卸载DLL
        return -1;
    }

    int numOfConnectedCameras = DllFuncsPtr.ASIGetNumOfConnectedCameras(); // 得到连接的相机的数量
    LOG_INFO("number of connected cameras is {}", numOfConnectedCameras);

    std::vector<std::shared_ptr<ASI_CAMERA_INFO>> cameraInfos;
    cameraInfos.reserve(numOfConnectedCameras);

    for (int i = 0; i < numOfConnectedCameras; i++) {                 // i表示相机的序号: 遍历所有相机
        auto cameraInfo = std::make_shared<ASI_CAMERA_INFO>();

        if (GetCameraProperty(DllFuncsPtr, cameraInfo, i)) {          // 得到相机的信息，包括ID、名称、分辨率等
            CloseCamera(DllFuncsPtr, cameraInfo);
            continue;
        }

        AsiROI roiInfo = {
            .width  = 0,
            .height = 0,
            .x      = 0,
            .y      = 0,
            .bin    = 1,
            .imgType = ASI_IMG_RAW8
        };
        
        if (InitCamera(DllFuncsPtr, cameraInfo, roiInfo)) {   // 相机初始化
            CloseCamera(DllFuncsPtr, cameraInfo);
            continue;
        }

        if (CameraModeOperate(DllFuncsPtr, cameraInfo)) {             // 相机模式 相关
            CloseCamera(DllFuncsPtr, cameraInfo);
            continue;
        }

        if (ImageCapture(DllFuncsPtr, cameraInfo, roiInfo)) {   // 图像处理 相关
            CloseCamera(DllFuncsPtr, cameraInfo);
            continue;
        }
        CloseCamera(DllFuncsPtr, cameraInfo);

        cameraInfos.push_back(cameraInfo);
    }
    FreeLibrary(hDll); // 卸载DLL
    return 0;
}

int camera_main()
{
    Log::init("my_app.log"); // 初始化日志

    auto DllFuncsPtr = std::make_unique<ASI_GetDllFunc>();
    int res = CameraAction(*DllFuncsPtr);
    LOG_INFO("CameraAction result is: {}", res == 0 ? "Success" : "Fail");
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <inttypes.h> // 定义 PRId32 等宏
#include "tlmc_xa_native_api.h"
#include "tlmc_func.h"
#include "ASICamera2.h"
#include "asi_func.h"
// #include "camera_main.h"

// 句柄释放
void UnloadDllFunctions(DllFunctions* pFuncs) {
    if (pFuncs == NULL) {
        printf("%s: pFuncs is null pointer !\n", __func__);
        return;
    }
    
    // 卸载DLL库
    if (pFuncs->hDll != NULL) {
        FreeLibrary(pFuncs->hDll);
        pFuncs->hDll = NULL;
    }

    // 重要：将结构体内所有函数指针重置为NULL，防止“悬空指针”
    memset(pFuncs, 0, sizeof(DllFunctions));
    printf("[Success] DLL unloaded and resources cleaned.\n");
}

// 主加载函数
int LoadDllFunctions(DllFunctions* pFuncs, const char* dllPath) {
    if (pFuncs == NULL) {
        printf("%s: pFuncs is null pointer !\n", __func__);
        return InvalidParameter;
    }

    // 初始化解构体，将所有指针置NULL
    memset(pFuncs, 0, sizeof(DllFunctions));

    // 加载DLL
    int stringLength = MultiByteToWideChar(CP_ACP, 0, dllPath, -1, nullptr, 0);
    wchar_t* wideDllPath = new wchar_t[stringLength];
    MultiByteToWideChar(CP_ACP, 0, dllPath, -1, wideDllPath, stringLength);
    pFuncs->hDll = LoadLibraryW(wideDllPath);
    if (pFuncs->hDll == NULL) {
        fprintf(stderr, "[ERROR] Failed to load DLL: %s\n", dllPath);
        return FileLoadFailed;
    }

    // 逐个获取DLL中的函数地址，并赋值给结构体成员
    pFuncs->TLMC_Startup = (TLMC_Startup_Func)GetProcAddressChecked(pFuncs->hDll, "TLMC_Startup");
    pFuncs->TLMC_Shutdown = (TLMC_Shutdown_Func)GetProcAddressChecked(pFuncs->hDll, "TLMC_Shutdown");
    pFuncs->TLMC_Open = (TLMC_Open_Func)GetProcAddressChecked(pFuncs->hDll, "TLMC_Open");
    pFuncs->TLMC_Close = (TLMC_Close_Func)GetProcAddressChecked(pFuncs->hDll, "TLMC_Close");

    pFuncs->TLMC_Home = (TLMC_Home_Func)GetProcAddressChecked(pFuncs->hDll, "TLMC_Home");
    pFuncs->TLMC_Move = (TLMC_Move_Func)GetProcAddressChecked(pFuncs->hDll, "TLMC_Move");
    pFuncs->TLMC_PZ_GetPosition = (TLMC_PZ_GetPosition_Func)GetProcAddressChecked(pFuncs->hDll, "TLMC_PZ_GetPosition");
    pFuncs->TLMC_GetPositionCounter = (TLMC_GetPositionCounter_Func)GetProcAddressChecked(pFuncs->hDll, "TLMC_GetPositionCounter");
    pFuncs->TLMC_SetMoveAbsoluteParams = (TLMC_SetMoveAbsoluteParams_Func)GetProcAddressChecked(pFuncs->hDll, "TLMC_SetMoveAbsoluteParams");
    pFuncs->TLMC_GetMoveRelativeParams = (TLMC_GetMoveRelativeParams_Func)GetProcAddressChecked(pFuncs->hDll, "TLMC_GetMoveRelativeParams");
    pFuncs->TLMC_SetMoveRelativeParams = (TLMC_SetMoveRelativeParams_Func)GetProcAddressChecked(pFuncs->hDll, "TLMC_SetMoveRelativeParams");
    pFuncs->TLMC_RegisterNotificationHandler = (TLMC_RegisterNotificationHandler_Func)GetProcAddressChecked(pFuncs->hDll, "TLMC_RegisterNotificationHandler");
    pFuncs->TLMC_UnregisterNotificationHandler = (TLMC_UnregisterNotificationHandler_Func)GetProcAddressChecked(pFuncs->hDll, "TLMC_UnregisterNotificationHandler");
    pFuncs->TLMC_GetMoveAbsoluteParams = (TLMC_GetMoveAbsoluteParams_Func)GetProcAddressChecked(pFuncs->hDll, "TLMC_GetMoveAbsoluteParams");
    pFuncs->TLMC_GetStatusItem = (TLMC_GetStatusItem_Func)GetProcAddressChecked(pFuncs->hDll, "TLMC_GetStatusItem");
    pFuncs->TLMC_GetUniversalStatus = (TLMC_GetUniversalStatus_Func)GetProcAddressChecked(pFuncs->hDll, "TLMC_GetUniversalStatus");
    pFuncs->TLMC_SetStageAxisParams = (TLMC_SetStageAxisParams_Func)GetProcAddressChecked(pFuncs->hDll, "TLMC_SetStageAxisParams");
    pFuncs->TLMC_ConvertFromDeviceToPhysical = (TLMC_ConvertFromDeviceToPhysical_Func)GetProcAddressChecked(pFuncs->hDll, "TLMC_ConvertFromDeviceToPhysical");

    // 检查是否有任何一个必需函数加载失败
    if (pFuncs->TLMC_Startup == NULL || pFuncs->TLMC_Shutdown == NULL || pFuncs->TLMC_PZ_GetPosition == NULL ||
        pFuncs->TLMC_Open == NULL || pFuncs->TLMC_Close == NULL || pFuncs->TLMC_ConvertFromDeviceToPhysical == NULL ||
        pFuncs->TLMC_GetPositionCounter == NULL || pFuncs->TLMC_GetStatusItem == NULL || pFuncs->TLMC_GetUniversalStatus == NULL ||
        pFuncs->TLMC_SetMoveAbsoluteParams == NULL || pFuncs->TLMC_GetMoveAbsoluteParams == NULL ||
        pFuncs->TLMC_GetMoveRelativeParams == NULL || pFuncs->TLMC_SetMoveRelativeParams == NULL ||
        pFuncs->TLMC_Home == NULL || pFuncs->TLMC_Move == NULL || pFuncs->TLMC_SetStageAxisParams == NULL ||
        pFuncs->TLMC_RegisterNotificationHandler == NULL || pFuncs->TLMC_UnregisterNotificationHandler == NULL) {
        fprintf(stderr, "[ERROR] Essential functions missing in DLL.\n");
        UnloadDllFunctions(pFuncs);
        return MissKeyFunctions;
    }

    printf("[Success] DLL loaded and functions resolved successfully.\n");
    return SuccessLoad;
}

// ShutDown设备
void TLMC_ShutDownDevice(DllFunctions* pFuncs)
{
    if (pFuncs == NULL) {
        printf("%s: pFuncs is null pointer!\n", __func__);
        return;
    }
    if (pFuncs->TLMC_Shutdown != NULL) {
        TLMC_ResultCode_Type resCode = pFuncs->TLMC_Shutdown();
        printf("[%s] The XA API has been shutdown!\n", (resCode == TLMC_ResultCode::TLMC_Success) ? "Success" : "Fail");
        pFuncs->TLMC_Shutdown = NULL;
    }
    return;
}

// Close设备
void TLMC_CloseDevice(DllFunctions* pFuncs, TLMC_DeviceHandle hDeviceHandle)
{
    if (pFuncs == NULL) {
        printf("%s: pFuncs is null pointer !\n", __func__);
        return;
    }
    if (pFuncs->TLMC_Close != NULL) {
        TLMC_ResultCode_Type resCode = pFuncs->TLMC_Close(hDeviceHandle);
        printf("[%s] The device control session handled by hDll is now closed.\n", (resCode == TLMC_ResultCode::TLMC_Success) ? "Success" : "Fail");
        pFuncs->TLMC_Close = NULL;
    }
    return;
}

void FreeAll(DllFunctions* pFuncs, TLMC_DeviceHandle hDeviceHandle)
{
    if (pFuncs == NULL) {
        printf("%s: pFuncs is null pointer!\n", __func__);
        return;
    }
    TLMC_CloseDevice(pFuncs, hDeviceHandle);
    TLMC_ShutDownDevice(pFuncs);
    UnloadDllFunctions(pFuncs);
    free(pFuncs);
    printf("[Success]%s: free all resource!\n", __func__);
}

int IsTlmcSuccess(DllFunctions *myDll, TLMC_ResultCode_Type resultCode, TLMC_DeviceHandle hDeviceHandle, const char *actionInfo, const char *printfInfo)
{
    if (resultCode == TLMC_ResultCode::TLMC_Success) {
        printf("[Success][%s] to %s\n", actionInfo, printfInfo);
        return TlmcSuccess;
    }
    printf("[Fail][%s] to [%s]. Error code: %d\n", actionInfo, printfInfo, resultCode);
    FreeAll(myDll, hDeviceHandle);
    return TlmcFail;
}

/* ①归位--->>>②获取位置--->>>③设置移动距离--->>>④移动对应距离--->>>⑤获取位置--->>>⑥设置反向移动距离--->>>⑦移动对应距离--->>>⑧获取位置 */
int Action(DllFunctions *myDll, TLMC_DeviceHandle hDeviceHandle, int32_t distance, const char *info)
{
    printf("    --------Begin %s--------    \n", __func__);
    // TLMC_Home: 归位
    TLMC_ResultCode_Type resultCode = myDll->TLMC_Home(hDeviceHandle, TLMC_InfiniteWait);
    if (IsTlmcSuccess(myDll, resultCode, hDeviceHandle, info, "home device") == TlmcFail) {
        return TlmcFail;
    }
    Sleep(1000);  // 睡眠1秒

    // 获取位置
    struct TLMC_UniversalStatus universalStatus;
    resultCode = myDll->TLMC_GetUniversalStatus(hDeviceHandle, &universalStatus, TLMC_InfiniteWait);
    if (IsTlmcSuccess(myDll, resultCode, hDeviceHandle, info, "get universal status after home") == TlmcFail) {
        return TlmcFail;
    }
    printf("[Success][Parameters]after home, universal status is: position = %" PRId32 ", motorCurrent = %" PRId16 "\n", universalStatus.position, universalStatus.motorCurrent);

    // move
    const int32_t param =  distance;
    resultCode = myDll->TLMC_Move(hDeviceHandle, TLMC_MoveMode::TLMC_MoveMode_Relative, distance, TLMC_InfiniteWait);  // 等待最大时长：TLMC_InfiniteWait
    if (IsTlmcSuccess(myDll, resultCode, hDeviceHandle, info, "move device forward") == TlmcFail) {
        return TlmcFail;
    }
    Sleep(1000); // 1秒
    // 获取位置
    resultCode = myDll->TLMC_GetUniversalStatus(hDeviceHandle, &universalStatus, TLMC_InfiniteWait);
    if (IsTlmcSuccess(myDll, resultCode, hDeviceHandle, info, "get universal status after move") == TlmcFail) {
        return TlmcFail;
    }
    printf("[Success][Parameters]after move, universal status is: position = %" PRId32 ", motorCurrent = %" PRId16 "\n", universalStatus.position, universalStatus.motorCurrent);

    // // 再次move
    // resultCode = myDll->TLMC_Move(hDeviceHandle, TLMC_MoveMode::TLMC_MoveMode_Relative, -2 * param, TLMC_InfiniteWait);  // 等待最大时长：TLMC_InfiniteWait
    // if (IsTlmcSuccess(myDll, resultCode, hDeviceHandle, info, "move device reverse again") == TlmcFail) {
    //     return TlmcFail;
    // }
    // Sleep(1000); // 1秒
    // // 获取位置
    // resultCode = myDll->TLMC_GetUniversalStatus(hDeviceHandle, &universalStatus, TLMC_InfiniteWait);
    // if (IsTlmcSuccess(myDll, resultCode, hDeviceHandle, info, "get universal status after move again!") == TlmcFail) {
    //     return TlmcFail;
    // }
    // printf("[Success][Parameters]after move again, universal status is: position = %" PRId32 ", motorCurrent = %" PRId16 "\n", universalStatus.position, universalStatus.motorCurrent);

    // 归位
    // resultCode = myDll->TLMC_Move(hDeviceHandle, TLMC_MoveMode::TLMC_MoveMode_Relative, param, TLMC_InfiniteWait);  // 等待最大时长：TLMC_InfiniteWait
    // if (IsTlmcSuccess(myDll, resultCode, hDeviceHandle, info, "move device reverse again") == TlmcFail) {
    //     return TlmcFail;
    // }
    // resultCode = myDll->TLMC_Home(hDeviceHandle, TLMC_InfiniteWait);
    // if (IsTlmcSuccess(myDll, resultCode, hDeviceHandle, info, "home device") == TlmcFail) {
    //     return TlmcFail;
    // }

    camera_main(); // 相机开始作业

    printf("    --------End %s--------    \n", __func__);
    return TlmcSuccess;
}

/* 业务处理函数入口 */
int TlmcCtrl(int32_t inputNum) {
    printf("-----------------Begin %s!-----------------\n", __func__);

    // 在栈上声明一个管理结构体
    DllFunctions *myDll = (DllFunctions*)malloc(sizeof(DllFunctions));
    if (myDll == NULL) {
        printf("[Fail]malloc DllFunctions fail!\n");
        return -1;
    }

    const char *dllFilePath = "./../../../kdc101/sdk/libs/tlmc_xa_native.dll"; // dll文件路径: 相对于exe文件
    TLMC_DeviceHandle hDeviceHandle;

    // 加载myDll结构体相关的钩子
    if (LoadDllFunctions(myDll, dllFilePath) != SuccessLoad) {
        printf("[Fail] to initialize DLL API. Error code: %d\n", LoadDllFunctions(myDll, dllFilePath));
        free(myDll);
        return TlmcFail;
    }
    printf("[Success] load dll functions.\n");

    // TLMC_Startup
    if (myDll->TLMC_Startup(NULL) != TLMC_ResultCode::TLMC_Success) {
        printf("[Fail] to startup device. Error code: %d\n", myDll->TLMC_Startup(NULL));
        UnloadDllFunctions(myDll);
        free(myDll);
        return TlmcFail;
    }
    printf("[Success] to startup devices\n");

    // TLMC_Open
    if (myDll->TLMC_Open("27271559", NULL, TLMC_OperatingMode::TLMC_OperatingMode_Default, &hDeviceHandle) != TLMC_ResultCode::TLMC_Success) {
        printf("[Fail] to open device. Error code: %d\n", myDll->TLMC_Open("27271559", NULL, TLMC_OperatingMode::TLMC_OperatingMode_Default, &hDeviceHandle));
        TLMC_ShutDownDevice(myDll);
        UnloadDllFunctions(myDll);
        free(myDll);
        return TlmcFail;
    }
    printf("[Success] to open devices\n");

    if (Action(myDll, hDeviceHandle, inputNum, "--action1--") == TlmcFail) {
        printf("[Fail][--action1--] action is fail!\n");
        return TlmcFail;
    }
    
    FreeAll(myDll, hDeviceHandle);
    printf("-----------------End %s!-----------------\n", __func__);
    return TlmcSuccess;
}
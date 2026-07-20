#ifndef TLMC_FUNC_TYPE_H
#define TLMC_FUNC_TYPE_H

#include <stdio.h>
#include <windows.h>
#include "tlmc_xa_native_api.h"

#define TlmcSuccess 0
#define TlmcFail 1

typedef TLMC_ResultCode_Type (__stdcall *TLMC_AddUserMessageToLog_Func)(const char* pUserMessage);
typedef TLMC_ResultCode_Type (__stdcall *TLMC_PZ_SetPosition_Func)(const TLMC_DeviceHandle hDevice, const int16_t position);
typedef TLMC_ResultCode_Type (__stdcall *TLMC_Open_Func)(const char* pDevice, const char* pTransport, const TLMC_OperatingMode_Type operatingModes, TLMC_DeviceHandle* pDeviceHandle);
typedef TLMC_ResultCode_Type (__stdcall *TLMC_Close_Func)(const TLMC_DeviceHandle hDevice);
typedef TLMC_ResultCode_Type (__stdcall *TLMC_Startup_Func)(const char* pSettings);
typedef TLMC_ResultCode_Type (__stdcall *TLMC_Shutdown_Func)();
typedef TLMC_ResultCode_Type (__stdcall *TLMC_Home_Func)(const TLMC_DeviceHandle hDevice, const long long maxWaitInMilliseconds);
typedef TLMC_ResultCode_Type (__stdcall *TLMC_Move_Func)(const TLMC_DeviceHandle hDevice, const TLMC_MoveMode_Type mode, const int32_t param, const long long maxWaitInMilliseconds);
typedef TLMC_ResultCode_Type (__stdcall *TLMC_ConvertFromPhysicalToDevice_Func)(const TLMC_DeviceHandle hDevice, const TLMC_ScaleType_Type scaleType, const TLMC_Unit_Type unit, const double physicalValue, int64_t* pDeviceValue);
typedef TLMC_ResultCode_Type (__stdcall *TLMC_PZ_GetPosition_Func)(const TLMC_DeviceHandle hDevice, int16_t* pPosition, const long long maxWaitInMilliseconds);
typedef TLMC_ResultCode_Type (__stdcall *TLMC_GetPositionCounter_Func)(const TLMC_DeviceHandle hDevice, int32_t* pPositionCounter, const long long maxWaitInMilliseconds);
typedef TLMC_ResultCode_Type (__stdcall *TLMC_SetMoveAbsoluteParams_Func)(const TLMC_DeviceHandle hDevice, const struct TLMC_MoveAbsoluteParams* pParams);
typedef TLMC_ResultCode_Type (__stdcall *TLMC_GetMoveRelativeParams_Func)(const TLMC_DeviceHandle hDevice, struct TLMC_MoveRelativeParams* pParams, const long long maxWaitInMilliseconds);
typedef TLMC_ResultCode_Type (__stdcall *TLMC_SetMoveRelativeParams_Func)(const TLMC_DeviceHandle hDevice, const struct TLMC_MoveRelativeParams* pParams);
typedef TLMC_ResultCode_Type (__stdcall *TLMC_GetMoveAbsoluteParams_Func)(const TLMC_DeviceHandle hDevice, struct TLMC_MoveAbsoluteParams* pParams, const long long maxWaitInMilliseconds);
typedef TLMC_ResultCode_Type (__stdcall *TLMC_RegisterNotificationHandler_Func)(const TLMC_DeviceHandle hDevice, TLMC_NotificationHandler handlerFn, uintptr_t userData);
typedef TLMC_ResultCode_Type (__stdcall *TLMC_UnregisterNotificationHandler_Func)(const TLMC_DeviceHandle hDevice, TLMC_NotificationHandler handlerFn);
typedef TLMC_ResultCode_Type (__stdcall *TLMC_GetStatusItem_Func)(const TLMC_DeviceHandle hDevice, const TLMC_StatusItemId_Type statusItemId, struct TLMC_StatusItem* pDestination);
typedef TLMC_ResultCode_Type (__stdcall *TLMC_GetUniversalStatus_Func)(const TLMC_DeviceHandle hDevice, struct TLMC_UniversalStatus* pUniversalStatus, const long long maxWaitInMilliseconds);
typedef TLMC_ResultCode_Type (__stdcall *TLMC_SetStageAxisParams_Func)(const TLMC_DeviceHandle hDevice, const struct TLMC_StageAxisParams* pParams);
typedef TLMC_ResultCode_Type (__stdcall *TLMC_ConvertFromDeviceToPhysical_Func)(const TLMC_DeviceHandle hDevice, const TLMC_ScaleType_Type scaleType, const int64_t deviceValue, double* pPhysicalValue, TLMC_Unit_Type* pUnit);
#pragma pack(push, 1)
    typedef struct {
        HMODULE hDll;  // 句柄

        // 添加需要的接口：
        // TLMC_AddUserMessageToLog_Func TLMC_AddUserMessageToLog; // 日志接口
        TLMC_Startup_Func TLMC_Startup;
        TLMC_Shutdown_Func TLMC_Shutdown;
        TLMC_Open_Func TLMC_Open;
        TLMC_Close_Func TLMC_Close;

        TLMC_Home_Func TLMC_Home;
        TLMC_Move_Func TLMC_Move;
        
        TLMC_ConvertFromPhysicalToDevice_Func TLMC_ConvertFromPhysicalToDevice;
        TLMC_ConvertFromDeviceToPhysical_Func TLMC_ConvertFromDeviceToPhysical;

        TLMC_PZ_SetPosition_Func TLMC_PZ_SetPosition;
        TLMC_PZ_GetPosition_Func TLMC_PZ_GetPosition;  // 获取当前的位置
        TLMC_GetPositionCounter_Func TLMC_GetPositionCounter;
        TLMC_SetMoveAbsoluteParams_Func TLMC_SetMoveAbsoluteParams;
        TLMC_GetMoveRelativeParams_Func TLMC_GetMoveRelativeParams;
        TLMC_SetMoveRelativeParams_Func TLMC_SetMoveRelativeParams;
        TLMC_GetMoveAbsoluteParams_Func TLMC_GetMoveAbsoluteParams;

        TLMC_RegisterNotificationHandler_Func TLMC_RegisterNotificationHandler; // 注册通知回调函数
        TLMC_UnregisterNotificationHandler_Func TLMC_UnregisterNotificationHandler;

        TLMC_GetStatusItem_Func TLMC_GetStatusItem;
        TLMC_GetUniversalStatus_Func TLMC_GetUniversalStatus;

        TLMC_SetStageAxisParams_Func TLMC_SetStageAxisParams;
    } DllFunctions;
#pragma pack(pop)

typedef enum LoadError {
    SuccessLoad      = 0,    /* 加载DLL成功 */
    InvalidParameter = -1,   /* 无效参数检查 */
    FileLoadFailed   = -2,   /* 加载DLL失败 */
    MissKeyFunctions = -3,   /* 关键函数缺失 */
} LoadDllFunctionsErr;

// LoadDllFunctions: 尝试加载DLL并初始化DllFunctions结构体
// UnloadDllFunctions: 安全地卸载DLL并清理结构体
// TLMC_ShutDownDevice: shutdown设备
// TLMC_CloseDevice: close设备
// TLMC_ShutDownDevice、TLMC_CloseDevice、UnloadDllFunctions的组合
int LoadDllFunctions(DllFunctions* pFuncs, const char* dllPath);
void UnloadDllFunctions(DllFunctions* pFuncs);
void TLMC_ShutDownDevice(DllFunctions* pFuncs);
void TLMC_CloseDevice(DllFunctions* pFuncs, TLMC_DeviceHandle hDeviceHandle);
void FreeAll(DllFunctions* pFuncs, TLMC_DeviceHandle hDeviceHandle);

int Action(DllFunctions *myDll, TLMC_DeviceHandle hDeviceHandle, int32_t distance, const char *info);
void MonitorWork(const TLMC_DeviceHandle hDevice, DllFunctions* myDll);
int TlmcCtrl(int inputNum);

#endif
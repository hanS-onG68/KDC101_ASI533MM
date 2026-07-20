#ifndef _TLMC_XA_NATIVE_API_H
#define _TLMC_XA_NATIVE_API_H

#ifdef __cplusplus
    #include <climits>
    #include <cstddef>
    #include <cstdint>
#else
    #include <limits.h>
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdint.h>
#endif

#if (CHAR_BIT != 8)
#error "Your system does not have 8-bit wide characters (CHAR_BIT must be 8)."
#endif

#ifdef _WIN32
    #ifdef TLMC_XA_NATIVE_API_STATIC
        #define TLMC_XA_EXPORT
    #else
        #ifdef TLMC_XA_NATIVE_API_DYNAMIC
            #define TLMC_XA_EXPORT __declspec(dllexport)
        #else
            #define TLMC_XA_EXPORT __declspec(dllimport)
        #endif
    #endif
#else
    #ifdef TLMC_XA_NATIVE_API_DYNAMIC
        #define TLMC_XA_EXPORT __attribute__ ((visibility ("default")))
    #else
        #define TLMC_XA_EXPORT
    #endif

    #define __stdcall
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __cplusplus
    typedef enum class TLMC_AnalogMonitorMotorChannel : uint16_t
#else
    typedef enum TLMC_AnalogMonitorMotorChannel
#endif
    {
        TLMC_AnalogMonitorMotorChannel_1 = 0x0001,
        TLMC_AnalogMonitorMotorChannel_2 = 0x0002
    } TLMC_AnalogMonitorMotorChannels;

#ifdef __cplusplus
    typedef enum class TLMC_AnalogMonitorNumber : uint16_t
#else
    typedef enum TLMC_AnalogMonitorNumber
#endif
    {
        TLMC_AnalogueMonitorNumber_1 = 0x0001,
        TLMC_AnalogueMonitorNumber_2 = 0x0002
    } TLMC_AnalogMonitorNumbers;

#ifdef __cplusplus
    typedef enum class TLMC_AnalogMonitorSystemVariable : uint16_t
#else
    typedef enum TLMC_AnalogMonitorSystemVariable
#endif
    {
        TLMC_AnalogMonitorSystemVariable_PositionError = 0x0001,
        TLMC_AnalogMonitorSystemVariable_Position = 0x0002,
        TLMC_AnalogMonitorSystemVariable_MotorCurrentPhaseA = 0x0003,
        TLMC_AnalogMonitorSystemVariable_MotorCurrentPhaseB = 0x0004,
        TLMC_AnalogMonitorSystemVariable_MotorCurrentPhaseC = 0x0005,
        TLMC_AnalogMonitorSystemVariable_MotorCurrent = 0x0006
    } TLMC_AnalogMonitorSystemVariables;

#ifdef __cplusplus
    typedef enum class TLMC_AuxIoPortMode : uint16_t
#else
    typedef enum TLMC_AuxIoPortMode
#endif
    {
        TLMC_AuxIoPortMode_None = 0x0000,
        TLMC_AuxIoPortMode_SoftwareControlled = 0x0001,
        TLMC_AuxIoPortMode_EncoderOutput = 0x0002
    } TLMC_AuxIoPortModes;

#ifdef __cplusplus
    typedef enum class TLMC_AuxIoPortNumber : uint16_t
#else
    typedef enum TLMC_AuxIoPortNumber
#endif
    {
        TLMC_AuxIoPortNumber_None = 0x0000,
        TLMC_AuxIoPortNumber_Port1 = 0x0001,
        TLMC_AuxIoPortNumber_Port2 = 0x0002,
        TLMC_AuxIoPortNumber_Port3 = 0x0004
    } TLMC_AuxIoPortNumbers;

#ifdef __cplusplus
    typedef enum class TLMC_BowIndex : uint16_t
#else
    typedef enum TLMC_BowIndex
#endif
    {
        TLMC_BowIndex_Trapezoidal = 0,
        TLMC_BowIndex_SCurve1 = 1,
        TLMC_BowIndex_SCurve2 = 2,
        TLMC_BowIndex_SCurve3 = 3,
        TLMC_BowIndex_SCurve4 = 4,
        TLMC_BowIndex_SCurve5 = 5,
        TLMC_BowIndex_SCurve6 = 6,
        TLMC_BowIndex_SCurve7 = 7,
        TLMC_BowIndex_SCurve8 = 8,
        TLMC_BowIndex_SCurve9 = 9,
        TLMC_BowIndex_SCurve10 = 10,
        TLMC_BowIndex_SCurve11 = 11,
        TLMC_BowIndex_SCurve12 = 12,
        TLMC_BowIndex_SCurve13 = 13,
        TLMC_BowIndex_SCurve14 = 14,
        TLMC_BowIndex_SCurve15 = 15,
        TLMC_BowIndex_SCurve16 = 16,
        TLMC_BowIndex_SCurve17 = 17,
        TLMC_BowIndex_SCurve18 = 18
    } TLMC_BowIndices;

#ifdef __cplusplus
    typedef enum class TLMC_ButtonMode : uint16_t
#else
    typedef enum TLMC_ButtonMode
#endif
    {
        TLMC_ButtonMode_Jog = 0x0001,
        TLMC_ButtonMode_PresetPosition = 0x0002
    } TLMC_ButtonModes;

#ifdef __cplusplus
    typedef enum class TLMC_CalibrationState : uint8_t
#else
    typedef enum TLMC_CalibrationState
#endif
    {
        TLMC_CalibrationState_Unknown = 0x00,
        TLMC_CalibrationState_FileNotPresent = 0x01,
        TLMC_CalibrationState_Active = 0x02,
        TLMC_CalibrationState_Inactive = 0x03
    } TLMC_CalibrationStates;


#ifdef __cplusplus
    typedef enum class TLMC_ConnectedProductAxisType : uint16_t
#else
    typedef enum TLMC_ConnectedProductAxisType
#endif
    {
        TLMC_ConnectedProductAxisType_Unknown = 0,
        TLMC_ConnectedProductAxisType_Single = 1,
        TLMC_ConnectedProductAxisType_Rotary = 2,
        TLMC_ConnectedProductAxisType_X = 3,
        TLMC_ConnectedProductAxisType_Y = 4,
        TLMC_ConnectedProductAxisType_Z = 5,
        TLMC_ConnectedProductAxisType_Pitch = 6,
        TLMC_ConnectedProductAxisType_Roll = 7,
        TLMC_ConnectedProductAxisType_Yaw = 8,
        TLMC_ConnectedProductAxisType_Goniometer = 9
    } TLMC_ConnectedProductAxisTypes;

#ifdef __cplusplus
    typedef enum class TLMC_ConnectedProductMovementType : uint16_t
#else
    typedef enum TLMC_ConnectedProductMovementType
#endif
    {
        TLMC_ConnectedProductMovementType_Unknown = 0,
        TLMC_ConnectedProductMovementType_Linear = 1,
        TLMC_ConnectedProductMovementType_RotaryContinuous = 2,
        TLMC_ConnectedProductMovementType_RotaryFixedRange = 3
    } TLMC_ConnectedProductMovementTypes;

#ifdef __cplusplus
    typedef enum class TLMC_CurrentLoopPhase : uint16_t
#else
    typedef enum TLMC_CurrentLoopPhase
#endif
    {
        TLMC_CurrentLoopPhase_A = 0x0000,
        TLMC_CurrentLoopPhase_B = 0x0001,
        TLMC_CurrentLoopPhase_AB = 0x0002
    } TLMC_CurrentLoopPhases;

#ifdef __cplusplus
    typedef enum class TLMC_CurrentLoopScenario : uint16_t
#else
    typedef enum TLMC_CurrentLoopScenario
#endif
    {
        TLMC_CurrentLoopScenario_Single = 0x0000,
        TLMC_CurrentLoopScenario_Normal = 0x0001,
        TLMC_CurrentLoopScenario_Settled = 0x0002
    } TLMC_CurrentLoopScenarios;

#ifdef __cplusplus
    typedef enum class TLMC_DcPidUpdateFilter : uint16_t
#else
    typedef enum TLMC_DcPidUpdateFilter
#endif
    {
        TLMC_DcPidUpdateFilter_None = 0x0000,
        TLMC_DcPidUpdateFilter_IntegralLimit = 0x0001,
        TLMC_DcPidUpdateFilter_Derivative = 0x0002,
        TLMC_DcPidUpdateFilter_Integral = 0x0004,
        TLMC_DcPidUpdateFilter_Proportional = 0x0008,
        TLMC_DcPidUpdateFilter_All = (TLMC_DcPidUpdateFilter_IntegralLimit | TLMC_DcPidUpdateFilter_Derivative | TLMC_DcPidUpdateFilter_Integral | TLMC_DcPidUpdateFilter_Proportional)
    } TLMC_DcPidUpdateFilters;

#ifdef __cplusplus
    typedef enum class TLMC_DeviceFamily : uint8_t
#else
    typedef enum TLMC_DeviceFamily
#endif
    {
        TLMC_DeviceFamily_ThorlabsMotionControl = 0
    } TLMC_DeviceFamilies;

#ifdef __cplusplus
    typedef enum class TLMC_DeviceListChange : uint8_t
#else
    typedef enum TLMC_DeviceListChange
#endif
    {
        TLMC_DeviceListChange_EntryAdded = 0,
        TLMC_DeviceListChange_EntryRemoved = 1
    } TLMC_DeviceListChanges;

#ifdef __cplusplus
    typedef enum class TLMC_DeviceType : uint32_t
#else
    typedef enum TLMC_DeviceType_Type
#endif
    {
        TLMC_DeviceType_Bbd30xBaseUnit = 0,
        TLMC_DeviceType_Bbd30xLogicalChannel = 1,
        TLMC_DeviceType_Bpc301 = 2,
        TLMC_DeviceType_Bpc30xBaseUnit = 3,
        TLMC_DeviceType_Bpc30xLogicalChannel = 4,
        TLMC_DeviceType_Bsc20xBaseUnit = 5,
        TLMC_DeviceType_Bsc20xLogicalChannel = 6,
        TLMC_DeviceType_Kbd101 = 7,
        TLMC_DeviceType_Kdc101 = 8,
        TLMC_DeviceType_Kpz101 = 9,
        TLMC_DeviceType_Kst101 = 10,
        TLMC_DeviceType_Kst201 = 11,
        TLMC_DeviceType_Tbd001 = 12,
        TLMC_DeviceType_LinearTranslationStage = 13,
        TLMC_DeviceType_Bsc20xv4LogicalChannel = 14,
        TLMC_DeviceType_Bsc201 = 15,
        TLMC_DeviceType_Bsc201v4 = 16,
        TLMC_DeviceType_Kpc101 = 17
    } TLMC_DeviceTypes;

#ifdef __cplusplus
    typedef enum class TLMC_DigitalInput : uint32_t
#else
    typedef enum TLMC_DigitalInput
#endif
    {
        TLMC_DigitalInput_None = 0x00000000,
        TLMC_DigitalInput_1 = 0x00000001,
        TLMC_DigitalInput_2 = 0x00000002,
        TLMC_DigitalInput_3 = 0x00000004,
        TLMC_DigitalInput_4 = 0x00000008,
        TLMC_DigitalInput_All = (TLMC_DigitalInput_1 | TLMC_DigitalInput_2 | TLMC_DigitalInput_3 | TLMC_DigitalInput_4)
    } TLMC_DigitalInputs;

#ifdef __cplusplus
    typedef enum class TLMC_DigitalOutput : uint8_t
#else
    typedef enum TLMC_DigitalOutput
#endif
    {
        TLMC_DigitalOutput_None = 0x00,
        TLMC_DigitalOutput_1 = 0x01,
        TLMC_DigitalOutput_2 = 0x02,
        TLMC_DigitalOutput_3 = 0x04,
        TLMC_DigitalOutput_4 = 0x08,
        TLMC_DigitalOutput_All = (TLMC_DigitalOutput_1 | TLMC_DigitalOutput_2 | TLMC_DigitalOutput_3 | TLMC_DigitalOutput_4)
    } TLMC_DigitalOutputs;

#ifdef __cplusplus
    typedef enum class TLMC_EnableState : uint8_t
#else
    typedef enum TLMC_EnableState
#endif
    {
        TLMC_Enabled = 0x01,
        TLMC_Disabled = 0x02
    } TLMC_EnableStates;

#ifdef __cplusplus
    typedef enum class TLMC_EndOfMoveMessagesMode : uint8_t
#else
    typedef enum TLMC_EndOfMoveMessagesMode
#endif
    {
        TLMC_EndOfMoveMessagesMode_Enabled = 0x01,
        TLMC_EndOfMoveMessagesMode_Disabled = 0x02
    } TLMC_EndOfMoveMessagesModes;

#ifdef __cplusplus
    typedef enum class TLMC_HardLimitOperatingMode : uint16_t
#else
    typedef enum TLMC_HardLimitOperatingMode
#endif
    {
        TLMC_HardLimitOperatingMode_SwitchIgnored = 0x0001,
        TLMC_HardLimitOperatingMode_SwitchContactMakes = 0x0002,
        TLMC_HardLimitOperatingMode_SwitchContactBreaks = 0x0003,
        TLMC_HardLimitOperatingMode_SwitchContactMakesWhenHoming = 0x0004,
        TLMC_HardLimitOperatingMode_SwitchContactBreaksWhenHoming = 0x0005,
        TLMC_HardLimitOperatingMode_SwitchUseIndexMarkForHoming = 0x0006,
        TLMC_HardLimitOperatingMode_SwitchesSwapped = 0x0080
    } TLMC_HardLimitOperatingModes;

#ifdef __cplusplus
    typedef enum class TLMC_HomeDirection : uint16_t
#else
    typedef enum TLMC_HomeDirection
#endif
    {
        TLMC_HomeDirection_Forward = 0x0001,
        TLMC_HomeDirection_Reverse = 0x0002
    } TLMC_HomeDirections;

#ifdef __cplusplus
    typedef enum class TLMC_HomeLimitSwitch : uint16_t
#else
    typedef enum TLMC_HomeLimitSwitch
#endif
    {
        TLMC_HomeLimitSwitch_Reverse = 0x0001,
        TLMC_HomeLimitSwitch_Forward = 0x0004
    } TLMC_HomeLimitSwitches;

#ifdef __cplusplus
    typedef enum class TLMC_IoPortMode : uint16_t
#else
    typedef enum TLMC_IoPortMode
#endif
    {
        TLMC_IoPortMode_DigitalInput = 0x0000,
        TLMC_IoPortMode_DigitalOutput = 0x0001,
        TLMC_IoPortMode_AnalogOutput = 0x0002
    } TLMC_IoPortModes;

#ifdef __cplusplus
    typedef enum class TLMC_IoPortNumber : uint16_t
#else
    typedef enum TLMC_IoPortNumber
#endif
    {
        TLMC_IoPortNumber_Port1 = 0x0001,
        TLMC_IoPortNumber_Port2 = 0x0002,
        TLMC_IoPortNumber_Port3 = 0x0003
    } TLMC_IoPortNumbers;

#ifdef __cplusplus
    typedef enum class TLMC_IoPortSource : uint16_t
#else
    typedef enum TLMC_IoPortSource
#endif
    {
        TLMC_IoPortSource_Software = 0x0000,
        TLMC_IoPortSource_Channel1 = 0x0001,
        TLMC_IoPortSource_Channel2 = 0x0002,
        TLMC_IoPortSource_Channel3 = 0x0003
    } TLMC_IoPortSources;

#ifdef __cplusplus
    typedef enum class TLMC_IoPositionTriggerEnableState : uint8_t
#else
    typedef enum TLMC_IoPositionTriggerEnableState
#endif
    {
        TLMC_IoPositionTriggerEnableState_Armed = 0x01,
        TLMC_IoPositionTriggerEnableState_Canceled = 0x02
    } TLMC_IoPositionTriggerEnableStates;


#ifdef __cplusplus
    typedef enum class TLMC_IoTriggerInMode : uint16_t
#else
    typedef enum TLMC_IoTriggerInMode
#endif
    {
        TLMC_IoTriggerInMode_Disabled = 0x0000,
        TLMC_IoTriggerInMode_GeneralPurpose = 0x0001,
        TLMC_IoTriggerInMode_TriggersRelativeMove = 0x0002,
        TLMC_IoTriggerInMode_TriggersAbsoluteMove = 0x0003,
        TLMC_IoTriggerInMode_TriggersHomeMove = 0x0004
    } TLMC_IoTriggerInModes;

#ifdef __cplusplus
    typedef enum class TLMC_IoTriggerInSource : uint16_t
#else
    typedef enum TLMC_IoTriggerInSource
#endif
    {
        TLMC_IoTriggerInSource_Software = 0x0000,
        TLMC_IoTriggerInSource_BNC1 = 0x0001,
        TLMC_IoTriggerInSource_BNC2 = 0x0002,
        TLMC_IoTriggerInSource_BNC3 = 0x0003
    } TLMC_IoTriggerInSources;

#ifdef __cplusplus
    typedef enum class TLMC_IoTriggerOutMode : uint16_t
#else
    typedef enum TLMC_IoTriggerOutMode
#endif
    {
        TLMC_IoTriggerOutMode_GeneralPurpose = 0x000A,
        TLMC_IoTriggerOutMode_ActiveDuringMotion = 0x000B,
        TLMC_IoTriggerOutMode_ActiveAtMaxVelocity = 0x000C,
        TLMC_IoTriggerOutMode_PulsedInForwardDirection = 0x000D,
        TLMC_IoTriggerOutMode_PulsedInReverseDirection = 0x000E,
        TLMC_IoTriggerOutMode_PulsedInBothDirections = 0x000F,
        TLMC_IoTriggerOutMode_ActiveAtForwardLimit = 0x0010,
        TLMC_IoTriggerOutMode_ActiveAtReverseLimit = 0x0011,
        TLMC_IoTriggerOutMode_ActiveAtBothLimits = 0x0012
    } TLMC_IoTriggerOutModes;

#ifdef __cplusplus
    typedef enum class TLMC_IoTriggerPolarity : uint16_t
#else
    typedef enum TLMC_IoTriggerPolarity
#endif
    {
        TLMC_IoTriggerPolarity_ActiveIsLogicHigh = 0x0001,
        TLMC_IoTriggerPolarity_ActiveIsLogicLow = 0x0002
    } TLMC_IoTriggerPolarities;

#ifdef __cplusplus
    typedef enum class TLMC_JogMode : uint16_t
#else
    typedef enum TLMC_JogMode
#endif
    {
        TLMC_JogMode_Continuous = 0x0001,
        TLMC_JogMode_SingleStep = 0x0002
    } TLMC_JogModes;

#ifdef __cplusplus
    typedef enum class TLMC_JogStopMode : uint16_t
#else
    typedef enum TLMC_JogStopMode
#endif
    {
        TLMC_JogStopMode_Immediate = 0x0001,
        TLMC_JogStopMode_Profiled = 0x0002
    } TLMC_JogStopModes;

#ifdef __cplusplus
    typedef enum class TLMC_JoystickDirectionSense : uint16_t
#else
    typedef enum TLMC_JoystickDirectionSense
#endif
    {
        TLMC_JoystickDirectionSense_Positive = 0x0001,
        TLMC_JoystickDirectionSense_Negative = 0x0002
    } TLMC_JoystickDirectionSenses;

#ifdef __cplusplus
    typedef enum class TLMC_KcubeMmiJoystickGear : uint16_t
#else
    typedef enum TLMC_KcubeMmiJoystickGear
#endif
    {
        TLMC_KcubeMmiJoystickGear_High = 0x0001,
        TLMC_KcubeMmiJoystickGear_Medium = 0x0002,
        TLMC_KcubeMmiJoystickGear_Low = 0x0003
    } TLMC_KcubeMmiJoystickGears;


#ifdef __cplusplus
    typedef enum class TLMC_KcubeIoTriggerMode : uint16_t
#else
    typedef enum TLMC_KcubeIoTriggerMode
#endif
    {
        TLMC_KcubeIoTriggerMode_Disabled = 0x0000,
        TLMC_KcubeIoTriggerMode_GeneralPurposeInput = 0x0001,
        TLMC_KcubeIoTriggerMode_InputTriggersRelativeMove = 0x0002,
        TLMC_KcubeIoTriggerMode_InputTriggersAbsoluteMove = 0x0003,
        TLMC_KcubeIoTriggerMode_InputTriggersHomeMove = 0x0004,
        TLMC_KcubeIoTriggerMode_GeneralPurposeOutput = 0x000A,
        TLMC_KcubeIoTriggerMode_OutputActiveDuringMotion = 0x000B,
        TLMC_KcubeIoTriggerMode_OutputActiveAtMaxVelocity = 0x000C,
        TLMC_KcubeIoTriggerMode_OutputPulsedInForwardDirection = 0x000D,
        TLMC_KcubeIoTriggerMode_OutputPulsedInReverseDirection = 0x000E,
        TLMC_KcubeIoTriggerMode_OutputPulsedInBothDirections = 0x000F
    } TLMC_KcubeIoTriggerModes;


#ifdef __cplusplus
    typedef enum class TLMC_KcubeIoTriggerPolarity : uint16_t
#else
    typedef enum TLMC_KcubeIoTriggerPolarity
#endif
    {
        TLMC_KcubeIoTriggerPolarity_ActiveIsLogicHigh = 0x0001,
        TLMC_KcubeIoTriggerPolarity_ActiveIsLogicLow = 0x0002
    } TLMC_KcubeIoTriggerPolarities;

#ifdef __cplusplus
    typedef enum class TLMC_KcubeMmiJoystickDirectionSense : uint16_t
#else
    typedef enum TLMC_KcubeMmiJoystickDirectionSense
#endif
    {
        TLMC_KcubeMmiJoystickDirectionSense_Disabled = 0x0000,
        TLMC_KcubeMmiJoystickDirectionSense_Normal = 0x0001,
        TLMC_KcubeMmiJoystickDirectionSense_Inverted = 0x0002
    } TLMC_KcubeMmiJoystickDirectionSenses;

#ifdef __cplusplus
    typedef enum class TLMC_KcubeMmiJoystickMode : uint16_t
#else
    typedef enum TLMC_KcubeMmiJoystickMode
#endif
    {
        TLMC_KcubeMmiJoystickMode_ControlsVelocity = 0x0001,
        TLMC_KcubeMmiJoystickMode_Jogs = 0x0002,
        TLMC_KcubeMmiJoystickMode_GoesToPosition = 0x0003
    } TLMC_KcubeMmiJoystickModes;

#ifdef __cplusplus
    typedef enum class TLMC_KcubeMmiLockState : uint8_t
#else
    typedef enum TLMC_KcubeMmiLockState
#endif
    {
        TLMC_KcubeMmiLockState_Locked = 0x01,
        TLMC_KcubeMmiLockState_Unlocked = 0x02
    } TLMC_KcubeMmiLockStates;

#ifdef __cplusplus
    typedef enum class TLMC_LcdKnobMode : uint16_t
#else
    typedef enum TLMC_LcdKnobMode
#endif
    {
        TLMC_LcdKnobMode_Velocity = 0x0001,
        TLMC_LcdKnobMode_Jog = 0x0002
    } TLMC_LcdKnobModes;

#ifdef __cplusplus
    typedef enum class TLMC_LogLevel : uint16_t
#else
    typedef enum TLMC_LogLevel
#endif
    {
        TLMC_LogLevel_Critical = 0x0002,
        TLMC_LogLevel_Error = 0x0003,
        TLMC_LogLevel_Warning = 0x0004,
        TLMC_LogLevel_Information = 0x0005
    } TLMC_LogLevels;


#ifdef __cplusplus
    typedef enum class TLMC_LogCategoryFilter : uint32_t
#else
    typedef enum TLMC_LogCategoryFilter
#endif
    {
        TLMC_LogCategoryFilter_User = 0x00000001,
        TLMC_LogCategoryFilter_Internal = 0x00000002,
        TLMC_LogCategoryFilter_Communication = 0x00000004,
        TLMC_LogCategoryFilter_NativeApi = 0x00000008,
        TLMC_LogCategoryFilter_All = 0xFFFFFFFF
    } TLMC_LogCategoryFilters;

#ifdef __cplusplus
    typedef enum class TLMC_MoveMode : uint8_t
#else
    typedef enum TLMC_MoveMode
#endif
    {
        TLMC_MoveMode_Absolute = 0,
        TLMC_MoveMode_AbsoluteToProgrammedPosition = 1,
        TLMC_MoveMode_Relative = 2,
        TLMC_MoveMode_RelativeByProgrammedDistance = 3,
        TLMC_MoveMode_ContinuousForward = 4,
        TLMC_MoveMode_ContinuousReverse = 5,
        TLMC_MoveMode_JogForward = 6,
        TLMC_MoveMode_JogReverse = 7
    } TLMC_MoveModes;

#ifdef __cplusplus
    typedef enum class TLMC_NotificationId : int32_t
#else
    typedef enum TLMC_NotificationId
#endif
    {
        TLMC_NotificationId_AnalogMonitorConfigurationParamsChanged = 0,
        TLMC_NotificationId_AuxIoPortModeChanged = 1,
        TLMC_NotificationId_AuxIoSoftwareStatesChanged = 2,
        TLMC_NotificationId_BowIndexChanged = 3,
        TLMC_NotificationId_CurrentLoopParamsChanged = 4,
        TLMC_NotificationId_DcPidParamsChanged = 5,
        TLMC_NotificationId_DigitalInputsChanged = 6,
        TLMC_NotificationId_DigitalOutputsChanged = 7,
        TLMC_NotificationId_EncoderCounterChanged = 8,
        TLMC_NotificationId_GeneralMoveParamsChanged = 9,
        TLMC_NotificationId_HardwareInfoChanged = 10,
        TLMC_NotificationId_HomeParamsChanged = 11,
        TLMC_NotificationId_IoConfigurationParamsChanged = 12,
        TLMC_NotificationId_IoPositionTriggerEnableStateChanged = 13,
        TLMC_NotificationId_IoTriggerParamsChanged = 14,
        TLMC_NotificationId_JogParamsChanged = 15,
        TLMC_NotificationId_JoystickParamsChanged = 16,
        TLMC_NotificationId_KcubeIoTriggerParamsChanged = 17,
        TLMC_NotificationId_KcubeMmiLockStateChanged = 18,
        TLMC_NotificationId_KcubeMmiParamsChanged = 19,
        TLMC_NotificationId_KcubePositionTriggerParamsChanged = 20,
        TLMC_NotificationId_LcdDisplayParamsChanged = 21,
        TLMC_NotificationId_LcdMoveParamsChanged = 22,
        TLMC_NotificationId_LimitSwitchParamsChanged = 23,
        TLMC_NotificationId_MotorOutputParamsChanged = 24,
        TLMC_NotificationId_MoveAbsoluteParamsChanged = 25,
        TLMC_NotificationId_MoveRelativeParamsChanged = 26,
        TLMC_NotificationId_PiezoMaxOutputVoltageParamsChanged = 27,
        TLMC_NotificationId_PiezoMaxTravelChanged = 28,
        TLMC_NotificationId_PiezoOutputVoltageChanged = 29,
        TLMC_NotificationId_PiezoOutputVoltageControlSourceChanged = 30,
        TLMC_NotificationId_PiezoOutputWaveformParamsChanged = 31,
        TLMC_NotificationId_PiezoPositionChanged = 32,
        TLMC_NotificationId_PiezoPositionControlModeChanged = 33,
        TLMC_NotificationId_PiezoPositionLoopParamsChanged = 34,
        TLMC_NotificationId_PiezoSlewRateParamsChanged = 35,
        TLMC_NotificationId_PiezoStatusChanged = 36,
        TLMC_NotificationId_PiezoStatusBitsChanged = 37,
        TLMC_NotificationId_PositionCounterChanged = 38,
        TLMC_NotificationId_PositionLoopParamsChanged = 39,
        TLMC_NotificationId_PowerParamsChanged = 40,
        TLMC_NotificationId_ProfileModeParamsChanged = 41,
        TLMC_NotificationId_RichResponseChanged = 42,
        TLMC_NotificationId_StageAxisParamsChanged = 43,
        TLMC_NotificationId_StepperStatusChanged = 44,
        TLMC_NotificationId_TrackSettleParamsChanged = 45,
        TLMC_NotificationId_TriggerParamsForDcBrushlessChanged = 46,
        TLMC_NotificationId_UniversalStatusChanged = 47,
        TLMC_NotificationId_UniversalStatusBitsChanged = 48,
        TLMC_NotificationId_VelocityParamsChanged = 49,
        TLMC_NotificationId_StatusItemChanged = 50,
        TLMC_NotificationId_SettingItemChanged = 51,
        TLMC_NotificationId_ConnectedProductChanged = 52,
        TLMC_NotificationId_StepperLoopParamsChanged = 53,
        TLMC_NotificationId_AdcInputsChanged = 54,
        TLMC_NotificationId_TriggerParamsForStepperChanged = 55,
        TLMC_NotificationId_ResponseChanged = 56,
        TLMC_NotificationId_ButtonParamsChanged = 57,
        TLMC_NotificationId_PotentiometerParamsChanged = 58,
        TLMC_NotificationId_CalibrationStateChanged = 59,
        TLMC_NotificationId_PiezoKpcIoSettingsChanged = 60,
        TLMC_NotificationId_PiezoKpcIoTriggerParamsChanged = 61,
        TLMC_NotificationId_PiezoKpcMmiParamsChanged = 62,
    } TLMC_NotificationIds;

#ifdef __cplusplus
    typedef enum class TLMC_OperatingMode : uint32_t
#else
    typedef enum TLMC_OperatingMode
#endif
    {
        TLMC_OperatingMode_StatusPushedByController = 0x00000000,
        TLMC_OperatingMode_ManualStatusPolling = 0x00000001,
        TLMC_OperatingMode_AutomaticStatusPolling = 0x00000002,
        TLMC_OperatingMode_DoNotChangeStatusPollingMode = 0x00000004,

        TLMC_OperatingMode_SendEndOfMoveMessages = 0x00000100,
        TLMC_OperatingMode_DoNotSendEndOfMoveMessages = 0x00000200,

        TLMC_OperatingMode_DoNotLoadParamsOnConnect = 0x00010000,
        TLMC_OperatingMode_DoNotSendDisconnectOnFinalClose = 0x00020000,
        TLMC_OperatingMode_DoNotAutoSetConnectedProduct = 0x00040000,
        TLMC_OperatingMode_DoNotSendNoFlashProgrammingOnConnect = 0x00080000,
        TLMC_OperatingMode_DoNotAutoCalibrate = 0x00100000,

        TLMC_OperatingMode_Apt = (TLMC_OperatingMode_StatusPushedByController | TLMC_OperatingMode_SendEndOfMoveMessages),
        TLMC_OperatingMode_Kinesis = (TLMC_OperatingMode_AutomaticStatusPolling | TLMC_OperatingMode_SendEndOfMoveMessages),
        TLMC_OperatingMode_Default = TLMC_OperatingMode_Apt,
        TLMC_OperatingMode_Expert = (
            TLMC_OperatingMode_DoNotChangeStatusPollingMode | TLMC_OperatingMode_DoNotLoadParamsOnConnect |
            TLMC_OperatingMode_DoNotSendDisconnectOnFinalClose | TLMC_OperatingMode_DoNotAutoSetConnectedProduct |
            TLMC_OperatingMode_DoNotSendNoFlashProgrammingOnConnect)
    } TLMC_OperatingModes;

#ifdef __cplusplus
    typedef enum class TLMC_ParameterGroupId : uint16_t
#else
    typedef enum TLMC_ParameterGroupId
#endif
    {
        TLMC_ParameterGroupId_Unspecified = 0x0000,
        TLMC_ParameterGroupId_JogParams = 0x0416,
        TLMC_ParameterGroupId_LimitSwitchParams = 0x0423,
        TLMC_ParameterGroupId_GenMoveParams = 0x043A,
        TLMC_ParameterGroupId_HomeParams = 0x0440,
        TLMC_ParameterGroupId_JoystickParams = 0x04E6,
        TLMC_ParameterGroupId_BowIndex = 0x04F4,
        TLMC_ParameterGroupId_StepperLoopParams = 0x0529
    } TLMC_ParameterGroupIds;


#ifdef __cplusplus
    typedef enum class TLMC_PositionLoopScenario : uint16_t
#else
    typedef enum TLMC_PositionLoopScenario
#endif
    {
        TLMC_PositionLoopScenario_Single = 0x0000,
        TLMC_PositionLoopScenario_Stationary = 0x0001,
        TLMC_PositionLoopScenario_Accelerating = 0x0002,
        TLMC_PositionLoopScenario_AtConstantVelocity = 0x0003
    } TLMC_PositionLoopScenarios;

#ifdef __cplusplus
    typedef enum class TLMC_ProfileMode : uint16_t
#else
    typedef enum TLMC_ProfileMode
#endif
    {
        TLMC_ProfileMode_Trapezoidal = 0x0000,
        TLMC_ProfileMode_VelocityContouring = 0x0001,
        TLMC_ProfileMode_SCurve = 0x0002,
        TLMC_ProfileMode_ElectronicGear = 0x0003
    } TLMC_ProfileModes;

#ifdef __cplusplus
    typedef enum class TLMC_PZ_KpcAnalogInputSource : uint16_t
#else
    typedef enum TLMC_PZ_KpcAnalogInputSource
#endif
    {
        TLMC_PZ_KpcAnalogInputSource_Disabled = 0x0000,
        TLMC_PZ_KpcAnalogInputSource_HubInputA = 0x0001,
        TLMC_PZ_KpcAnalogInputSource_HubInputB = 0x0002,
        TLMC_PZ_KpcAnalogInputSource_External = 0x0003
    } TLMC_PZ_KpcAnalogInputSources;

#ifdef __cplusplus
    typedef enum class TLMC_PZ_KpcIoTriggerMode : uint16_t
#else
    typedef enum TLMC_PZ_KpcIoTriggerMode
#endif
    {
        TLMC_PZ_KpcIoTriggerMode_Disabled = 0x0000,
        TLMC_PZ_KpcIoTriggerMode_GeneralPurposeInput = 0x0001,
        TLMC_PZ_KpcIoTriggerMode_InputTriggersVoltagePositionStepUp = 0x0002,
        TLMC_PZ_KpcIoTriggerMode_InputTriggersVoltagePositionStepDown = 0x0003,
        TLMC_PZ_KpcIoTriggerMode_GeneralPurposeOutput = 0x000A,
        TLMC_PZ_KpcIoTriggerMode_OutputActiveStrainGaugeLessThanLowerLimit = 0x000B,
        TLMC_PZ_KpcIoTriggerMode_OutputActiveStrainGaugeMoreThanLowerLimit = 0x000C,
        TLMC_PZ_KpcIoTriggerMode_OutputActiveStrainGaugeLessThanUpperLimit = 0x000D,
        TLMC_PZ_KpcIoTriggerMode_OutputActiveStrainGaugeMoreThanUpperLimit = 0x000E,
        TLMC_PZ_KpcIoTriggerMode_OutputActiveStrainGaugeWithinLimits = 0x000F
    } TLMC_PZ_KpcIoTriggerModes;

#ifdef __cplusplus
    typedef enum class TLMC_PZ_KpcMmiJoystickDirectionSense : uint16_t
#else
    typedef enum TLMC_PZ_KpcMmiJoystickDirectionSense
#endif
    {
        TLMC_PZ_KpcMmiJoystickDirectionSense_Disabled = 0x0000,
        TLMC_PZ_KpcMmiJoystickDirectionSense_Normal = 0x0001,
        TLMC_PZ_KpcMmiJoystickDirectionSense_Invert = 0x0002
    } TLMC_PZ_KpcMmiJoystickDirectionSenses;


#ifdef __cplusplus
    typedef enum class TLMC_PZ_KpcMmiJoystickMode : uint16_t
#else
    typedef enum TLMC_PZ_KpcMmiJoystickMode
#endif
    {
        TLMC_PZ_KpcMmiJoystickMode_ControlsVoltagePosition = 0x0001,
        TLMC_PZ_KpcMmiJoystickMode_Jogs = 0x0002,
        TLMC_PZ_KpcMmiJoystickMode_GoesToVoltagePosition = 0x0003
    } TLMC_PZ_KpcMmiJoystickModes;


#ifdef __cplusplus
    typedef enum class TLMC_PZ_KpcMonitorOutputMode : uint16_t
#else
    typedef enum TLMC_PZ_KpcMonitorOutputMode
#endif
    {
        TLMC_PZ_KpcMonitorOutputMode_Software = 0x0000,
        TLMC_PZ_KpcMonitorOutputMode_HighVoltage = 0x0001,
        TLMC_PZ_KpcMonitorOutputMode_Position = 0x0002
    } TLMC_PZ_KpcMonitorOutputModes;

#ifdef __cplusplus
    typedef enum class TLMC_PZ_KpcStrainGaugeOption : uint16_t
#else
    typedef enum TLMC_PZ_KpcStrainGaugeOption
#endif
    {
        TLMC_PZ_KpcStrainGaugeOption_Position = 0x0000,
        TLMC_PZ_KpcStrainGaugeOption_Force = 0x0001,
    } TLMC_PZ_KpcStrainGaugeOptions;

#ifdef __cplusplus
    typedef enum class TLMC_PZ_KpcVoltageRange : uint16_t
#else
    typedef enum TLMC_PZ_KpcVoltageRange
#endif
    {
        TLMC_PZ_KpcVoltageRange_75Volts = 0x4B,
        TLMC_PZ_KpcVoltageRange_150Volts = 0x96
    } TLMC_PZ_KpcVoltageRanges;


#ifdef __cplusplus
    typedef enum class TLMC_PZ_OutputVoltageControlSource : uint16_t
#else
    typedef enum TLMC_PZ_OutputVoltageControlSource
#endif
    {
        TLMC_PZ_OutputVoltageControlSource_SoftwareOnly = 0x0000,
        TLMC_PZ_OutputVoltageControlSource_ExternalSignal = 0x0001,
        TLMC_PZ_OutputVoltageControlSource_Knob = 0x0002
    } TLMC_PZ_OutputVoltageControlSources;

#ifdef __cplusplus
    typedef enum class TLMC_PZ_OutputWaveformOperatingMode : uint16_t
#else
    typedef enum TLMC_PZ_OutputWaveformOperatingMode
#endif
    {
        TLMC_PZ_OutputWaveformOperatingMode_Continuous = 0x0001,
        TLMC_PZ_OutputWaveformOperatingMode_FixedNumberOfCycles = 0x0002,
        TLMC_PZ_OutputWaveformOperatingMode_OutputTriggerEnabled = 0x0004,
        TLMC_PZ_OutputWaveformOperatingMode_InputTriggerEnabled = 0x0008,
        TLMC_PZ_OutputWaveformOperatingMode_OutputTriggerRisingEdge = 0x0010,
        TLMC_PZ_OutputWaveformOperatingMode_InputTriggerRisingEdge = 0x0020,
        TLMC_PZ_OutputWaveformOperatingMode_OutputGated = 0x0040,
        TLMC_PZ_OutputWaveformOperatingMode_TriggerRepeats = 0x0080
    } TLMC_PZ_OutputWaveformOperatingModes;

#ifdef __cplusplus
    typedef enum class TLMC_PZ_StatusBit : uint32_t
#else
    typedef enum TLMC_PZ_StatusBit
#endif
    {
        TLMC_PZ_StatusBit_ActuatorConnected = 0x00000001,
        TLMC_PZ_StatusBit_Zeroed = 0x00000010,
        TLMC_PZ_StatusBit_Zeroing = 0x00000020,
        TLMC_PZ_StatusBit_ExternalStrainGaugeConnected = 0x00000100,
        TLMC_PZ_StatusBit_ClosedLoopPositionControl = 0x00000400,
        TLMC_PZ_StatusBit_VoltageAmplifierOverTemperature = 0x00000800,
        TLMC_PZ_StatusBit_MaxOutputVoltageLow = 0x00001000,
        TLMC_PZ_StatusBit_PositionUnderTravel = 0x00001000,
        TLMC_PZ_StatusBit_MaxOutputVoltageMedium = 0x00002000,
        TLMC_PZ_StatusBit_PositionOverTravel = 0x00002000,
        TLMC_PZ_StatusBit_MaxOutputVoltageHigh = 0x00004000,
        TLMC_PZ_StatusBit_DigitalInput1 = 0x00100000,
        TLMC_PZ_StatusBit_DigitalInput2 = 0x00200000,
        TLMC_PZ_StatusBit_DigitalInput3 = 0x00400000,
        TLMC_PZ_StatusBit_DigitalInput4 = 0x00800000,
        TLMC_PZ_StatusBit_DigitalInput5 = 0x01000000,
        TLMC_PZ_StatusBit_DigitalInput6 = 0x02000000,
        TLMC_PZ_StatusBit_DigitalInput7 = 0x04000000,
        TLMC_PZ_StatusBit_DigitalInput8 = 0x08000000,
        TLMC_PZ_StatusBit_PowerOk = 0x10000000,
        TLMC_PZ_StatusBit_Active = 0x20000000,
        TLMC_PZ_StatusBit_Error = 0x40000000,
        TLMC_PZ_StatusBit_Enabled = 0x80000000
    } TLMC_PZ_StatusBits;

#ifdef __cplusplus
    typedef enum class TLMC_PZ_PositionControlMode : uint8_t
#else
    typedef enum TLMC_PZ_PositionControlMode
#endif
    {
        TLMC_PZ_PositionControlMode_OpenLoop = 0x01,
        TLMC_PZ_PositionControlMode_ClosedLoop = 0x02,
        TLMC_PZ_PositionControlMode_OpenLoopSmooth = 0x03,
        TLMC_PZ_PositionControlMode_ClosedLoopSmooth = 0x04
    } TLMC_PZ_PositionControlModes;

#ifdef __cplusplus
    typedef enum class TLMC_PZ_VoltageLimit : uint16_t
#else
    typedef enum TLMC_PZ_VoltageLimit
#endif
    {
        TLMC_PZ_VoltageLimit_75Volts = 0x0002,
        TLMC_PZ_VoltageLimit_100Volts = 0x0004,
        TLMC_PZ_VoltageLimit_150Volts = 0x0008
    } TLMC_PZ_VoltageLimits;

#ifdef __cplusplus
    typedef enum class TLMC_RackBayNumber : uint16_t
#else
    typedef enum TLMC_RackBayNumber
#endif
    {
        TLMC_RackBayNumber_1 = 0x0000,
        TLMC_RackBayNumber_2 = 0x0001,
        TLMC_RackBayNumber_3 = 0x0002,
        TLMC_RackBayNumber_4 = 0x0003,
        TLMC_RackBayNumber_5 = 0x0004,
        TLMC_RackBayNumber_6 = 0x0005,
        TLMC_RackBayNumber_7 = 0x0006,
        TLMC_RackBayNumber_8 = 0x0007,
        TLMC_RackBayNumber_9 = 0x0008,
        TLMC_RackBayNumber_10 = 0x0009,
        TLMC_RackBayNumber_11 = 0x000A,
        TLMC_RackBayNumber_12 = 0x000B
    } TLMC_RackBayNumbers;

#ifdef __cplusplus
    typedef enum class TLMC_RackBayOccupiedState : uint16_t
#else
    typedef enum TLMC_RackBayOccupiedState
#endif
    {
        TLMC_RackBayState_Occupied = 0x0001,
        TLMC_RackBayState_Empty = 0x0002
    } TLMC_RackBayOccupiedStates;

#ifdef __cplusplus
    typedef enum class TLMC_ResultCode : uint16_t
#else
    typedef enum TLMC_ResultCode
#endif
    {
        TLMC_Success = 0,
        TLMC_FunctionNotSupported = 1,
        TLMC_DeviceNotFound = 2,
        TLMC_DeviceNotSupported = 3,
        TLMC_Timeout = 4,
        TLMC_Fail = 5,
        TLMC_InsufficientFirmware = 6,
        TLMC_AlreadyStarted = 7,
        TLMC_StartRequired = 8,
        TLMC_AllocationError = 9,
        TLMC_InternalError = 10,
        TLMC_InvalidHandle = 11,
        TLMC_InvalidArgument = 12,
        TLMC_ItemIsReadOnly = 13,
        TLMC_LoadParamsError = 14,
        TLMC_TransportError = 15,
        TLMC_TransportClosed = 16,
        TLMC_TransportNotAvailable = 17,
        TLMC_SharingModeNotAvailable = 18,
        TLMC_NotInitialized = 19,
        TLMC_NoFreeHandles = 20,
        TLMC_VerificationFailure = 21,
        TLMC_DataNotLoaded = 22,
        TLMC_ConnectedProductNotSupported = 23,
        TLMC_SimulationCreationError = 24,
        TLMC_ConnectedProductNotSet = 25,
        TLMC_CalibrationFileNotPresent = 26
    } TLMC_ResultCodes;

#ifdef __cplusplus
    typedef enum class TLMC_ScaleType : uint16_t
#else
    typedef enum TLMC_ScaleType
#endif
    {
        TLMC_ScaleType_None = 0,
        TLMC_ScaleType_Distance = 1,
        TLMC_ScaleType_Velocity = 2,
        TLMC_ScaleType_Acceleration = 3,
        TLMC_ScaleType_Voltage = 4,
        TLMC_ScaleType_Brightness = 5,
        TLMC_ScaleType_Time = 6,
        TLMC_ScaleType_Deceleration = 7,
        TLMC_ScaleType_Jerk = 8,
        TLMC_ScaleType_RescaledProportion = 9,
        TLMC_ScaleType_SlewRate = 10,
        TLMC_ScaleType_Force = 11,
        TLMC_ScaleType_NormalizedStrainGauge = 12,
        TLMC_ScaleType_RescaledVoltage = 13,
        TLMC_ScaleType_RescaledDistance = 14
    } TLMC_ScaleTypes;

#ifdef __cplusplus
    typedef enum class TLMC_SoftLimitOperatingMode : uint16_t
#else
    typedef enum TLMC_SoftLimitOperatingMode
#endif
    {
        TLMC_SoftLimitOperatingMode_FeatureNotSupported = 0x0000,
        TLMC_SoftLimitOperatingMode_Ignored = 0x0001,
        TLMC_SoftLimitOperatingMode_StopImmediate = 0x0002,
        TLMC_SoftLimitOperatingMode_StopProfiled = 0x0003,
        TLMC_SoftLimitOperatingMode_RestrictMoves = 0x0004,
        TLMC_SoftLimitOperatingMode_FilterWheelConnected = 0x0040,
        TLMC_SoftLimitOperatingMode_RotationalStageConnected = 0x0080
    } TLMC_SoftLimitOperatingModes;

#ifdef __cplusplus
    typedef enum class TLMC_StageAxisId : uint16_t
#else
    typedef enum TLMC_StageAxisId
#endif
    {
        TLMC_StageAxisId_Unknown = 0x0001,
        TLMC_StageAxisId_Rotary = 0x0003,
        TLMC_StageAxisId_X = 0x0010,
        TLMC_StageAxisId_Y = 0x0011,
        TLMC_StageAxisId_Single = 0x0012
    } TLMC_StageAxisIds;

#ifdef __cplusplus
    typedef enum class TLMC_StageProductId : uint16_t
#else
    typedef enum TLMC_StageProductId
#endif
    {
        TLMC_StageProductId_Unknown = 0x0001,
        TLMC_StageProductId_MLS203_X = 0x0010,
        TLMC_StageProductId_MLS203_Y = 0x0011,
        TLMC_StageProductId_DDS = 0x0012,
        TLMC_StageProductId_DDR = 0x0075
    } TLMC_StageProductIds;

#ifdef __cplusplus
    typedef enum class TLMC_StatusItemId : int32_t
#else
    typedef enum TLMC_StatusItemId
#endif
    {
        TLMC_StatusItemId_Active = 0,
        TLMC_StatusItemId_ActuatorConnected = 1,
        TLMC_StatusItemId_BusOvercurrent = 2,
        TLMC_StatusItemId_BusCurrentFault = 3,
        TLMC_StatusItemId_BusVoltageFault = 4,
        TLMC_StatusItemId_ClockwiseHardLimit = 5,
        TLMC_StatusItemId_CounterclockwiseHardLimit = 6,
        TLMC_StatusItemId_ClockwiseSoftLimit = 7,
        TLMC_StatusItemId_CommutationError = 8,
        TLMC_StatusItemId_Connected = 9,
        TLMC_StatusItemId_CounterclockwiseSoftLimit = 10,
        TLMC_StatusItemId_ClosedLoopPositionControl = 11,
        TLMC_StatusItemId_DigitalInput1 = 12,
        TLMC_StatusItemId_DigitalInput2 = 13,
        TLMC_StatusItemId_DigitalInput3 = 14,
        TLMC_StatusItemId_DigitalInput4 = 15,
        TLMC_StatusItemId_DigitalInput5 = 16,
        TLMC_StatusItemId_DigitalInput6 = 17,
        TLMC_StatusItemId_DigitalInput7 = 18,
        TLMC_StatusItemId_DigitalInput8 = 19,
        TLMC_StatusItemId_E2PROMFailure = 20,
        TLMC_StatusItemId_Enabled = 21,
        TLMC_StatusItemId_EncoderCount = 22,
        TLMC_StatusItemId_EncoderFault = 23,
        TLMC_StatusItemId_Error = 24,
        TLMC_StatusItemId_ExternalStrainGaugeConnected = 25,
        TLMC_StatusItemId_Homing = 26,
        TLMC_StatusItemId_HomingFailed = 27,
        TLMC_StatusItemId_Homed = 28,
        TLMC_StatusItemId_Initializing = 29,
        TLMC_StatusItemId_InstrumentError = 30,
        TLMC_StatusItemId_Interlock = 31,
        TLMC_StatusItemId_IonBusVoltage = 32,
        TLMC_StatusItemId_IonInstructionError = 33,
        TLMC_StatusItemId_IonCommutationError = 34,
        TLMC_StatusItemId_IonOvercurrent = 35,
        TLMC_StatusItemId_IonOvertemperature = 36,
        TLMC_StatusItemId_IonReceiveTimeout = 37,
        TLMC_StatusItemId_IonInterlockOpen = 38,
        TLMC_StatusItemId_IonPhaseInitializationFailed = 39,
        TLMC_StatusItemId_JoggingClockwise = 40,
        TLMC_StatusItemId_JoggingCounterclockwise = 41,
        TLMC_StatusItemId_MotorCurrent = 42,
        TLMC_StatusItemId_MotorOvercurrent = 43,
        TLMC_StatusItemId_MovingClockwise = 44,
        TLMC_StatusItemId_MovingCounterclockwise = 45,
        TLMC_StatusItemId_OutputVoltage = 46,
        TLMC_StatusItemId_Overcurrent = 47,
        TLMC_StatusItemId_Overload = 48,
        TLMC_StatusItemId_Overtemperature = 49,
        TLMC_StatusItemId_PhaseInitializationFailure = 50,
        TLMC_StatusItemId_Position = 51,
        TLMC_StatusItemId_PositionError = 52,
        TLMC_StatusItemId_PowerOk = 53,
        TLMC_StatusItemId_Settled = 54,
        TLMC_StatusItemId_Tracking = 55,
        TLMC_StatusItemId_UnrecognisedError = 56,
        TLMC_StatusItemId_Velocity = 57,
        TLMC_StatusItemId_VelocityLimitExceeded = 58,
        TLMC_StatusItemId_Zeroed = 59,
        TLMC_StatusItemId_Zeroing = 60,
        TLMC_StatusItemId_PositionUnderTravel = 61,
        TLMC_StatusItemId_PositionOverTravel = 62,
        TLMC_StatusItemId_ZeroingFailure = 63
    } TLMC_StatusItemIds;

#ifdef __cplusplus
    typedef enum class TLMC_StepperLoopMode : uint16_t
#else
    typedef enum TLMC_StepperLoopMode
#endif
    {
        TLMC_StepperLoopMode_Open = 0x0001,
        TLMC_StepperLoopMode_Closed = 0x0002,
    } TLMC_StepperLoopModes;

#ifdef __cplusplus
    typedef enum class TLMC_StepperStatusBit : uint32_t
#else
    typedef enum TLMC_StepperStatusBit
#endif
    {
        TLMC_StepperStatusBit_ClockwiseHardLimit = 0x00000001,
        TLMC_StepperStatusBit_CounterclockwiseHardLimit = 0x00000002,
        TLMC_StepperStatusBit_MovingClockwise = 0x00000010,
        TLMC_StepperStatusBit_MovingCounterclockwise = 0x00000020,
        TLMC_StepperStatusBit_JoggingClockwise = 0x00000040,
        TLMC_StepperStatusBit_JoggingCounterclockwise = 0x00000080,
        TLMC_StepperStatusBit_Homing = 0x00000200,
        TLMC_StepperStatusBit_Homed = 0x00000400,
        TLMC_StepperStatusBit_DigitalInput1 = 0x00100000,
        TLMC_StepperStatusBit_DigitalInput2 = 0x00200000,
        TLMC_StepperStatusBit_Enabled = 0x80000000
    } TLMC_StepperStatusBits;

#ifdef __cplusplus
    typedef enum class TLMC_SettingStringFormat : uint8_t
#else
    typedef enum TLMC_SettingStringFormat
#endif
    {
        TLMC_SettingStringFormat_SemiStructured = 0x00,
        TLMC_SettingStringFormat_Json = 0x01
    } TLMC_SettingStringFormats;

#ifdef __cplusplus
    typedef enum class TLMC_StopMode : uint8_t
#else
    typedef enum TLMC_StopMode
#endif
    {
        TLMC_StopMode_Immediate = 1,
        TLMC_StopMode_Profiled = 2
    } TLMC_StopModes;

#ifdef __cplusplus
    enum class TLMC_TriggerModesForDcBrushless : uint8_t
#else
    enum TLMC_TriggerModesForDcBrushless
#endif
    {
        TLMC_TriggerModesForDcBrushless_InputActiveIsLogicHigh = 0x01,
        TLMC_TriggerModesForDcBrushless_InputTriggersRelativeMove = 0x02,
        TLMC_TriggerModesForDcBrushless_InputTriggersAbsoluteMove = 0x04,
        TLMC_TriggerModesForDcBrushless_InputTriggersHomeMove = 0x08,
        TLMC_TriggerModesForDcBrushless_OutputActiveIsLogicHigh = 0x10,
        TLMC_TriggerModesForDcBrushless_OutputActiveDuringMotion = 0x20,
        TLMC_TriggerModesForDcBrushless_OutputActiveWhenMotionComplete = 0x40,
        TLMC_TriggerModesForDcBrushless_OutputActiveAtMaxVelocity = 0x80
    };

#ifdef __cplusplus
    enum class TLMC_TriggerModesForStepper : uint8_t
#else
    enum TLMC_TriggerModesForStepper
#endif
    {
        TLMC_TriggerModesForStepper_None = 0x00,
        TLMC_TriggerModesForStepper_InputTriggerEnabled = 0x01,
        TLMC_TriggerModesForStepper_OutputTriggerEnabled = 0x02,
        TLMC_TriggerModesForStepper_OutputTriggerFollowsInputTrigger = 0x04,
        TLMC_TriggerModesForStepper_OutputActiveUntilMoveEnd = 0x08,
        TLMC_TriggerModesForStepper_InputTriggersRelativeMove = 0x10,
        TLMC_TriggerModesForStepper_InputTriggersAbsoluteMove = 0x20,
        TLMC_TriggerModesForStepper_InputTriggersHomeMove = 0x40,
        TLMC_TriggerModesForStepper_OutputTriggerSoftwareInitiated = 0x80
    };

#ifdef __cplusplus
    typedef enum class TLMC_Unit : uint16_t
#else
    typedef enum TLMC_Unit
#endif
    {
        TLMC_Unit_Unspecified = 0,
        TLMC_Unit_Millimetres = 1,
        TLMC_Unit_Degrees = 2,
        TLMC_Unit_Radians = 3,
        TLMC_Unit_Cycles = 4,
        TLMC_Unit_Micrometres = 5,
        TLMC_Unit_Volts = 6,
        TLMC_Unit_EncoderCounts = 7,
        TLMC_Unit_EncoderCountsPerCycle = 8,
        TLMC_Unit_EncoderCountsPerCyclePerCycle = 9,
        TLMC_Unit_Minutes = 10,
        TLMC_Unit_Microseconds = 11,
        TLMC_Unit_MillimetresPerSecondPerSecondPerSecond = 12,
        TLMC_Unit_Percentage = 13,
        TLMC_Unit_VoltsPerMillisecond = 14,
        TLMC_Unit_Milliseconds = 15,
        TLMC_Unit_Hertz = 16,
        TLMC_Unit_Newtons = 17
    } TLMC_Units;

#ifdef __cplusplus
    typedef enum class TLMC_UniversalStatusBit : uint32_t
#else
    typedef enum TLMC_UniversalStatusBit
#endif
    {
        TLMC_UniversalStatusBit_ClockwiseHardLimit = 0x00000001,
        TLMC_UniversalStatusBit_CounterclockwiseHardLimit = 0x00000002,
        TLMC_UniversalStatusBit_ClockwiseSoftLimit = 0x00000004,
        TLMC_UniversalStatusBit_CounterclockwiseSoftLimit = 0x00000008,
        TLMC_UniversalStatusBit_MovingClockwise = 0x00000010,
        TLMC_UniversalStatusBit_MovingCounterclockwise = 0x00000020,
        TLMC_UniversalStatusBit_JoggingClockwise = 0x00000040,
        TLMC_UniversalStatusBit_JoggingCounterclockwise = 0x00000080,
        TLMC_UniversalStatusBit_Connected = 0x00000100,
        TLMC_UniversalStatusBit_Homing = 0x00000200,
        TLMC_UniversalStatusBit_Homed = 0x00000400,
        TLMC_UniversalStatusBit_Initializing = 0x00000800,
        TLMC_UniversalStatusBit_Tracking = 0x00001000,
        TLMC_UniversalStatusBit_Settled = 0x00002000,
        TLMC_UniversalStatusBit_PositionError = 0x00004000,
        TLMC_UniversalStatusBit_InstrumentError = 0x00008000,
        TLMC_UniversalStatusBit_Interlock = 0x00010000,
        TLMC_UniversalStatusBit_Overtemperature = 0x00020000,
        TLMC_UniversalStatusBit_BusVoltageFault = 0x00040000,
        TLMC_UniversalStatusBit_CommutationError = 0x00080000,
        TLMC_UniversalStatusBit_DigitalInput1 = 0x00100000,
        TLMC_UniversalStatusBit_DigitalInput2 = 0x00200000,
        TLMC_UniversalStatusBit_DigitalInput3 = 0x00400000,
        TLMC_UniversalStatusBit_DigitalInput4 = 0x00800000,
        TLMC_UniversalStatusBit_Overload = 0x01000000,
        TLMC_UniversalStatusBit_EncoderFault = 0x02000000,
        TLMC_UniversalStatusBit_Overcurrent = 0x04000000,
        TLMC_UniversalStatusBit_BusCurrentFault = 0x08000000,
        TLMC_UniversalStatusBit_PowerOk = 0x10000000,
        TLMC_UniversalStatusBit_Active = 0x20000000,
        TLMC_UniversalStatusBit_Error = 0x40000000,
        TLMC_UniversalStatusBit_Enabled = 0x80000000
    } TLMC_UniversalStatusBits;

#ifdef __cplusplus
    typedef enum class TLMC_ValueType : uint8_t
#else
    typedef enum TLMC_ValueType
#endif
    {
        TLMC_ValueType_int64 = 0,
        TLMC_ValueType_bool = 1,
        TLMC_ValueType_string = 2
    } TLMC_ValueTypes;

#ifdef __cplusplus
    typedef TLMC_AnalogMonitorNumber TLMC_AnalogMonitorNumber_Type;
    typedef TLMC_AnalogMonitorMotorChannel TLMC_AnalogMonitorMotorChannel_Type;
    typedef TLMC_AnalogMonitorSystemVariable TLMC_AnalogMonitorSystemVariable_Type;
    typedef TLMC_AuxIoPortMode TLMC_AuxIoPortMode_Type;
    typedef TLMC_AuxIoPortNumber TLMC_AuxIoPortNumber_Type;
    typedef TLMC_BowIndex TLMC_BowIndex_Type;
    typedef TLMC_ButtonMode TLMC_ButtonMode_Type;
    typedef TLMC_CalibrationState TLMC_CalibrationState_Type;
    typedef TLMC_ConnectedProductAxisType TLMC_ConnectedProductAxisType_Type;
    typedef TLMC_ConnectedProductMovementType TLMC_ConnectedProductMovementType_Type;
    typedef TLMC_RackBayNumber TLMC_RackBayNumber_Type;
    typedef TLMC_RackBayOccupiedState TLMC_RackBayOccupiedState_Type;
    typedef TLMC_CurrentLoopPhase TLMC_CurrentLoopPhase_Type;
    typedef TLMC_CurrentLoopScenario TLMC_CurrentLoopScenario_Type;
    typedef TLMC_DcPidUpdateFilter TLMC_DcPidUpdateFilter_Type;
    typedef TLMC_DeviceFamily TLMC_DeviceFamily_Type;
    typedef TLMC_DeviceListChange TLMC_DeviceListChange_Type;
    typedef TLMC_DeviceType TLMC_DeviceType_Type;
    typedef TLMC_DigitalInput TLMC_DigitalInput_Type;
    typedef TLMC_DigitalOutput TLMC_DigitalOutput_Type;
    typedef TLMC_EnableState TLMC_EnableState_Type;
    typedef TLMC_EndOfMoveMessagesMode TLMC_EndOfMoveMessagesMode_Type;
    typedef TLMC_HardLimitOperatingMode TLMC_HardLimitOperatingMode_Type;
    typedef TLMC_HomeDirection TLMC_HomeDirection_Type;
    typedef TLMC_HomeLimitSwitch TLMC_HomeLimitSwitch_Type;
    typedef TLMC_IoPortMode TLMC_IoPortMode_Type;
    typedef TLMC_IoPortNumber TLMC_IoPortNumber_Type;
    typedef TLMC_IoPortSource TLMC_IoPortSource_Type;
    typedef TLMC_IoPositionTriggerEnableState TLMC_IoPositionTriggerEnableState_Type;
    typedef TLMC_IoTriggerInMode TLMC_IoTriggerInMode_Type;
    typedef TLMC_IoTriggerInSource TLMC_IoTriggerInSource_Type;
    typedef TLMC_IoTriggerOutMode TLMC_IoTriggerOutMode_Type;
    typedef TLMC_IoTriggerPolarity TLMC_IoTriggerPolarity_Type;
    typedef TLMC_JogMode TLMC_JogMode_Type;
    typedef TLMC_JogStopMode TLMC_JogStopMode_Type;
    typedef TLMC_JoystickDirectionSense TLMC_JoystickDirectionSense_Type;
    typedef TLMC_KcubeIoTriggerMode TLMC_KcubeIoTriggerMode_Type;
    typedef TLMC_KcubeIoTriggerPolarity TLMC_KcubeIoTriggerPolarity_Type;
    typedef TLMC_KcubeMmiLockState TLMC_KcubeMmiLockState_Type;
    typedef TLMC_KcubeMmiJoystickDirectionSense TLMC_KcubeMmiJoystickDirectionSense_Type;
    typedef TLMC_KcubeMmiJoystickGear TLMC_KcubeMmiJoystickGear_Type;
    typedef TLMC_KcubeMmiJoystickMode TLMC_KcubeMmiJoystickMode_Type;
    typedef TLMC_LcdKnobMode TLMC_LcdKnobMode_Type;
    typedef TLMC_LogLevel TLMC_LogLevel_Type;
    typedef TLMC_LogCategoryFilter TLMC_LogCategoryFilter_Type;
    typedef TLMC_MoveMode TLMC_MoveMode_Type;
    typedef TLMC_NotificationId TLMC_NotificationId_Type;
    typedef TLMC_OperatingMode TLMC_OperatingMode_Type;
    typedef TLMC_ParameterGroupId TLMC_ParameterGroupId_Type;
    typedef TLMC_PZ_KpcAnalogInputSource TLMC_PZ_KpcAnalogInputSource_Type;
    typedef TLMC_PZ_KpcIoTriggerMode TLMC_PZ_KpcIoTriggerMode_Type;
    typedef TLMC_PZ_KpcMmiJoystickDirectionSense TLMC_PZ_KpcMmiJoystickDirectionSense_Type;
    typedef TLMC_PZ_KpcMmiJoystickMode TLMC_PZ_KpcMmiJoystickMode_Type;
    typedef TLMC_PZ_KpcMonitorOutputMode TLMC_PZ_KpcMonitorOutputMode_Type;
    typedef TLMC_PZ_KpcStrainGaugeOption TLMC_PZ_KpcStrainGaugeOption_Type;
    typedef TLMC_PZ_KpcVoltageRange TLMC_PZ_KpcVoltageRange_Type;
    typedef TLMC_PZ_OutputVoltageControlSource TLMC_PZ_OutputVoltageControlSource_Type;
    typedef TLMC_PZ_OutputWaveformOperatingMode TLMC_PZ_OutputWaveformOperatingMode_Type;
    typedef TLMC_PZ_StatusBit TLMC_PZ_StatusBit_Type;
    typedef TLMC_PZ_VoltageLimit TLMC_PZ_VoltageLimit_Type;
    typedef TLMC_PositionLoopScenario TLMC_PositionLoopScenario_Type;
    typedef TLMC_ProfileMode TLMC_ProfileMode_Type;
    typedef TLMC_PZ_PositionControlMode TLMC_PZ_PositionControlMode_Type;
    typedef TLMC_RackBayNumber TLMC_RackBayNumber_Type;
    typedef TLMC_RackBayOccupiedState TLMC_RackBayOccupiedState_Type;
    typedef TLMC_ResultCode TLMC_ResultCode_Type;
    typedef TLMC_ScaleType TLMC_ScaleType_Type;
    typedef TLMC_SettingStringFormat TLMC_SettingStringFormat_Type;
    typedef TLMC_SoftLimitOperatingMode TLMC_SoftLimitOperatingMode_Type;
    typedef TLMC_StageAxisId TLMC_StageAxisId_Type;
    typedef TLMC_StageProductId TLMC_StageProductId_Type;
    typedef TLMC_StatusItemId TLMC_StatusItemId_Type;
    typedef TLMC_StepperLoopMode TLMC_StepperLoopMode_Type;
    typedef TLMC_StepperStatusBit TLMC_StepperStatusBit_Type;
    typedef TLMC_StopMode TLMC_StopMode_Type;
    typedef TLMC_TriggerModesForDcBrushless TLMC_TriggerModesForDcBrushless_Type;
    typedef TLMC_TriggerModesForStepper TLMC_TriggerModesForStepper_Type;
    typedef TLMC_Unit TLMC_Unit_Type;
    typedef TLMC_UniversalStatusBit TLMC_UniversalStatusBit_Type;
    typedef TLMC_ValueType TLMC_ValueType_Type;
#else
    typedef uint16_t TLMC_AnalogMonitorNumber_Type;
    typedef uint16_t TLMC_AnalogMonitorMotorChannel_Type;
    typedef uint16_t TLMC_AnalogMonitorSystemVariable_Type;
    typedef uint16_t TLMC_AuxIoPortMode_Type;
    typedef uint16_t TLMC_AuxIoPortNumber_Type;
    typedef uint16_t TLMC_BowIndex_Type;
    typedef uint16_t TLMC_ButtonMode_Type;
    typedef uint16_t TLMC_CalibrationState_Type;
    typedef uint16_t TLMC_RackBayNumber_Type;
    typedef uint16_t TLMC_RackBayOccupiedState_Type;
    typedef uint16_t TLMC_ConnectedProductAxisType_Type;
    typedef uint16_t TLMC_ConnectedProductMovementType_Type;
    typedef uint16_t TLMC_CurrentLoopPhase_Type;
    typedef uint16_t TLMC_CurrentLoopScenario_Type;
    typedef uint16_t TLMC_DcPidUpdateFilter_Type;
    typedef uint8_t TLMC_DeviceFamily_Type;
    typedef uint8_t TLMC_DeviceListChange_Type;
    typedef uint32_t TLMC_DeviceType_Type;
    typedef uint16_t TLMC_DigitalInput_Type;
    typedef uint8_t TLMC_DigitalOutput_Type;
    typedef uint8_t TLMC_EnableState_Type;
    typedef uint8_t TLMC_EndOfMoveMessagesMode_Type;
    typedef uint16_t TLMC_HardLimitOperatingMode_Type;
    typedef uint16_t TLMC_HomeDirection_Type;
    typedef uint16_t TLMC_HomeLimitSwitch_Type;
    typedef uint16_t TLMC_IoPortMode_Type;
    typedef uint16_t TLMC_IoPortNumber_Type;
    typedef uint16_t TLMC_IoPortSource_Type;
    typedef uint8_t TLMC_IoPositionTriggerEnableState_Type;
    typedef uint16_t TLMC_IoTriggerInMode_Type;
    typedef uint16_t TLMC_IoTriggerInSource_Type;
    typedef uint16_t TLMC_IoTriggerOutMode_Type;
    typedef uint16_t TLMC_IoTriggerPolarity_Type;
    typedef uint16_t TLMC_JogMode_Type;
    typedef uint16_t TLMC_JogStopMode_Type;
    typedef uint16_t TLMC_JoystickDirectionSense_Type;
    typedef uint16_t TLMC_KcubeIoTriggerMode_Type;
    typedef uint16_t TLMC_KcubeIoTriggerPolarity_Type;
    typedef uint16_t TLMC_KcubeMmiJoystickDirectionSense_Type;
    typedef uint16_t TLMC_KcubeMmiJoystickGear_Type;
    typedef uint16_t TLMC_KcubeMmiJoystickMode_Type;
    typedef uint8_t TLMC_KcubeMmiLockState_Type;
    typedef uint16_t TLMC_LcdKnobMode_Type;
    typedef uint16_t TLMC_LogLevel_Type;
    typedef uint32_t TLMC_LogCategoryFilter_Type;
    typedef uint8_t TLMC_MoveMode_Type;
    typedef int32_t TLMC_NotificationId_Type;
    typedef uint32_t TLMC_OperatingMode_Type;
    typedef uint16_t TLMC_ParameterGroupId_Type;
    typedef uint16_t TLMC_PZ_KpcAnalogInputSource_Type;
    typedef uint16_t TLMC_PZ_KpcIoTriggerMode_Type;
    typedef uint16_t TLMC_PZ_KpcMmiJoystickDirectionSense_Type;
    typedef uint16_t TLMC_PZ_KpcMmiJoystickMode_Type;
    typedef uint16_t TLMC_PZ_KpcMonitorOutputMode_Type;
    typedef uint16_t TLMC_PZ_KpcStrainGaugeOption_Type;
    typedef uint16_t TLMC_PZ_KpcVoltageRange_Type;
    typedef uint16_t TLMC_PZ_OutputVoltageControlSource_Type;
    typedef uint16_t TLMC_PZ_OutputWaveformOperatingMode_Type;
    typedef uint32_t TLMC_PZ_StatusBit_Type;
    typedef uint16_t TLMC_PZ_VoltageLimit_Type;
    typedef uint16_t TLMC_PositionLoopScenario_Type;
    typedef uint16_t TLMC_ProfileMode_Type;
    typedef uint16_t TLMC_PZ_PositionControlMode_Type;
    typedef uint16_t TLMC_RackBayNumber_Type;
    typedef uint16_t TLMC_RackBayOccupiedState_Type;
    typedef uint16_t TLMC_ResultCode_Type;
    typedef uint16_t TLMC_ScaleType_Type;
    typedef uint8_t TLMC_SettingStringFormat_Type;
    typedef uint16_t TLMC_SoftLimitOperatingMode_Type;
    typedef uint16_t TLMC_StageAxisId_Type;
    typedef uint16_t TLMC_StageProductId_Type;
    typedef int32_t TLMC_StatusItemId_Type;
    typedef uint16_t TLMC_StepperLoopMode_Type;
    typedef uint32_t TLMC_StepperStatusBit_Type;
    typedef uint8_t TLMC_StopMode_Type;
    typedef uint8_t TLMC_TriggerModesForDcBrushless_Type;
    typedef uint8_t TLMC_TriggerModesForStepper_Type;
    typedef uint16_t TLMC_Unit_Type;
    typedef uint32_t TLMC_UniversalStatusBit_Type;
    typedef uint8_t TLMC_ValueType_Type;
#endif

#pragma pack(push, 1)
    union TLMC_Value
    {
        int64_t int64Value;
        bool boolValue;
        char string[24];
    };

    struct TLMC_ApiVersion
    {
        uint16_t major;
        uint16_t minor;
        uint16_t patch;
        uint32_t build;
        char prereleaseLabel[32];
        char displayString[64];
    };

    struct TLMC_AnalogMonitorConfigurationParams
    {
        TLMC_AnalogMonitorMotorChannel_Type motorChannel;
        TLMC_AnalogMonitorSystemVariable_Type systemVariable;
        int32_t scale;
        int32_t offset;
    };

    struct TLMC_AnalogMonitorConfigurationParamsChangedNotificationData
    {
        TLMC_AnalogMonitorNumber_Type monitorNumber;
    };

    struct TLMC_AuxIoPortModeChangedNotificationData
    {
        TLMC_AuxIoPortNumber_Type portNumber;
    };

    struct TLMC_ButtonParams
    {
        TLMC_ButtonMode_Type buttonMode;
        int32_t position1;
        int32_t position2;
        uint16_t timeout1Milliseconds;
        uint16_t timeout2Milliseconds;
    };

    struct TLMC_ConnectedProductInfo
    {
        char productName[64];
        char partNumber[16];
        TLMC_ConnectedProductAxisType_Type axisType;
        TLMC_ConnectedProductMovementType_Type movementType;
        TLMC_Unit_Type unitType;
        double distanceScaleFactor;
        double velocityScaleFactor;
        double accelerationScaleFactor;
        double minPosition;
        double maxPosition;
        double maxVelocity;
        double maxAcceleration;
    };

    struct TLMC_CurrentLoopParams
    {
        TLMC_CurrentLoopPhase_Type phase;
        uint16_t proportional;
        uint16_t integral;
        uint16_t integralLimit;
        uint16_t integralDeadBand;
        uint16_t feedForward;
    };

    struct TLMC_CurrentLoopParamsChangedNotificationData
    {
        TLMC_CurrentLoopScenario_Type scenario;
    };

    struct TLMC_DcPidParams
    {
        uint32_t proportional;
        uint32_t integral;
        uint32_t derivative;
        uint32_t integralLimit;
        TLMC_DcPidUpdateFilter_Type filterControl;
    };

    struct TLMC_DeviceInfo
    {
        TLMC_DeviceFamily_Type deviceFamily;
        TLMC_DeviceType_Type deviceType;
        char partNumber[8];
        char device[64];
        char transport[128];
        char parentDevice[64];
        char deviceTypeDescription[256];
    };

    struct TLMC_FirmwareVersion
    {
        uint8_t minorVersion;
        uint8_t interimVersion;
        uint8_t majorVersion;
        uint8_t reserved;
    };

    struct TLMC_GeneralMoveParams
    {
        int32_t backlashDistance;
    };

    struct TLMC_HardwareInfo
    {
        uint32_t serialNumber;
        char partNumber[8];
        uint16_t type;
        struct TLMC_FirmwareVersion firmwareVersion;
        char notes[48];
        char deviceDependantData[12];
        uint16_t hardwareVersion;
        uint16_t modificationState;
        uint16_t numChannels;
    };

    struct TLMC_HomeParams
    {
        TLMC_HomeDirection_Type direction;
        TLMC_HomeLimitSwitch_Type limitSwitch;
        uint32_t velocity;
        int32_t offsetDistance;
    };

    struct TLMC_IoConfigurationParams
    {
        TLMC_IoPortMode_Type mode;
        TLMC_IoPortSource_Type triggerOutSource;
    };

    struct TLMC_IoConfigurationParamsChangedNotificationData
    {
        TLMC_IoPortNumber_Type portNumber;
    };

    struct TLMC_IoTriggerParams
    {
        TLMC_IoTriggerInMode_Type triggerInMode;
        TLMC_IoTriggerPolarity_Type triggerInPolarity;
        TLMC_IoTriggerInSource_Type triggerInSource;
        TLMC_IoTriggerOutMode_Type triggerOutMode;
        TLMC_IoTriggerPolarity_Type triggerOutPolarity;
        int32_t triggerOutForwardStartPosition;
        int32_t triggerOutForwardInterval;
        int32_t triggerOutForwardNumberOfPulses;
        int32_t triggerOutReverseStartPosition;
        int32_t triggerOutReverseInterval;
        int32_t triggerOutReverseNumberOfPulses;
        uint32_t triggerOutPulseWidth;
        uint32_t triggerOutNumberOfCycles;
        int8_t reserved[8];
    };

    struct TLMC_JogParams
    {
        TLMC_JogMode_Type mode;
        int32_t stepSize;
        uint32_t minVelocity;
        uint32_t acceleration;
        uint32_t maxVelocity;
        TLMC_JogStopMode_Type stopMode;
    };

    struct TLMC_JoystickParams
    {
        uint32_t lowGearMaxVelocity;
        uint32_t highGearMaxVelocity;
        uint32_t lowGearAcceleration;
        uint32_t highGearAcceleration;
        TLMC_JoystickDirectionSense_Type directionSense;
    };

    struct TLMC_KcubeIoTriggerParams
    {
        TLMC_KcubeIoTriggerMode_Type trigger1Mode;
        TLMC_KcubeIoTriggerPolarity_Type trigger1Polarity;
        TLMC_KcubeIoTriggerMode_Type trigger2Mode;
        TLMC_KcubeIoTriggerPolarity_Type trigger2Polarity;
        int8_t reserved[12];
    };

    struct TLMC_StepperLoopParams
    {
        TLMC_StepperLoopMode_Type loopMode;
        int32_t proportional;
        int32_t integral;
        int32_t differential;
        int32_t outputClip;
        int32_t outputTolerance;
        uint32_t microstepsPerEncoderCount;
        uint8_t reserved[8];
    };

    struct TLMC_KcubeMmiParams
    {
        TLMC_KcubeMmiJoystickMode_Type joystickMode;
        uint32_t joystickMaxVelocity;
        uint32_t joystickAcceleration;
        TLMC_KcubeMmiJoystickDirectionSense_Type joystickDirectionSense;
        int32_t presetPosition1;
        int32_t presetPosition2;
        uint16_t displayBrightness;
        uint16_t displayTimeout;
        uint16_t displayDimLevel;
        int32_t presetPosition3;
        uint16_t joystickSensitivity;
        int8_t reserved[2];
    };

    struct TLMC_KcubePositionTriggerParams
    {
        int32_t forwardStartPosition;
        uint32_t forwardInterval;
        uint32_t forwardNumberOfPulses;
        int32_t reverseStartPosition;
        uint32_t reverseInterval;
        uint32_t reverseNumberOfPulses;
        uint32_t pulseWidth;
        uint32_t numberOfCycles;
        int8_t reserved[12];
    };

    struct TLMC_LcdDisplayParams
    {
        int16_t knobSensitivity;
        uint16_t displayBrightness;
        uint16_t displayTimeout;
        uint16_t displayDimLevel;
        uint8_t reserved[20];
    };

    struct TLMC_LcdMoveParams
    {
        TLMC_LcdKnobMode_Type knobMode;
        int32_t jogStepSize;
        int32_t acceleration;
        int32_t maxVelocity;
        TLMC_JogStopMode_Type jogStopMode;
        int32_t presetPosition[3];
        uint8_t reserved[20];
    };

    struct TLMC_LimitSwitchParams
    {
        TLMC_HardLimitOperatingMode_Type clockwiseHardLimitOperatingMode;
        TLMC_HardLimitOperatingMode_Type counterclockwiseHardLimitOperatingMode;
        int32_t clockwiseSoftLimit;
        int32_t counterclockwiseSoftLimit;
        TLMC_SoftLimitOperatingMode_Type softLimitOperatingMode;
    };

    struct TLMC_MotorOutputParams
    {
        uint16_t continuousCurrentLimit;
        uint16_t energyLimit;
        uint16_t motorLimit;
        uint16_t motorBias;
        int8_t reserved[4];
    };

    struct TLMC_MoveAbsoluteParams
    {
        int32_t absolutePosition;
    };

    struct TLMC_MoveRelativeParams
    {
        int32_t relativeDistance;
    };

    struct TLMC_Notification
    {
        TLMC_NotificationId_Type id;
        uintptr_t data;
        uint32_t dataLength;
    };

    struct TLMC_PositionLoopParams
    {
        uint16_t proportional;
        uint16_t integral;
        uint32_t integralLimit;
        uint16_t derivative;
        uint16_t servoCycles;
        uint16_t scale;
        uint16_t velocityFeedForward;
        uint16_t accelerationFeedForward;
        uint32_t errorLimit;
    };

    struct TLMC_PositionLoopParamsChangedNotificationData
    {
        TLMC_PositionLoopScenario_Type scenario;
    };

    struct TLMC_PotentiometerParams
    {
        uint16_t deflection0;
        int32_t velocity1;
        uint16_t deflection1;
        int32_t velocity2;
        uint16_t deflection2;
        int32_t velocity3;
        uint16_t deflection3;
        int32_t velocity4;
    };

    struct TLMC_PowerParams
    {
        uint16_t restFactor;
        uint16_t moveFactor;
    };

    struct TLMC_ProfileModeParams
    {
        TLMC_ProfileMode_Type mode;
        uint32_t jerk;
        int8_t reserved[4];
    };

    struct TLMC_PZ_KpcIoSettingsParams
    {
        uint16_t voltageLimit;
        TLMC_PZ_KpcAnalogInputSource_Type analogInputSource;
        uint16_t filterCutOffFrequency;
        TLMC_PZ_KpcVoltageRange_Type voltageRange;
        uint16_t forceSense;
        TLMC_PZ_KpcStrainGaugeOption_Type strainGaugeOption;
    };

    struct TLMC_PZ_KpcMmiParams
    {
        TLMC_PZ_KpcMmiJoystickMode_Type joystickMode;
        TLMC_KcubeMmiJoystickGear_Type joystickGear;
        uint16_t joystickVoltageStepSize;
        uint16_t joystickPositionStepSize;
        TLMC_PZ_KpcMmiJoystickDirectionSense_Type joystickDirectionSense;
        uint16_t presetVoltage1;
        uint16_t presetVoltage2;
        uint16_t presetPosition1;
        uint16_t presetPosition2;
        uint16_t displayBrightness;
        uint16_t displayTimeout;
        uint16_t displayDimLevel;
        uint8_t reserved[8];
    };

    struct TLMC_PZ_KpcIoTriggerParams
    {
        TLMC_PZ_KpcIoTriggerMode_Type trigger1Mode;
        TLMC_KcubeIoTriggerPolarity_Type trigger1Polarity;
        TLMC_PZ_KpcIoTriggerMode_Type trigger2Mode;
        TLMC_KcubeIoTriggerPolarity_Type trigger2Polarity;
        int32_t strainGaugeLowerLimit;
        int32_t strainGaugeUpperLimit;
        uint16_t smoothingSamples;
        TLMC_PZ_KpcMonitorOutputMode_Type monitorOutputMode;
        uint16_t monitorFilterCutOffFrequency;
        int16_t monitorOutputSoftwareValue;
        int8_t reserved[6];
    };

    struct TLMC_PZ_OutputWaveformParams
    {
        TLMC_PZ_OutputWaveformOperatingMode_Type mode;
        uint16_t numberOfSamplesPerCycle;
        int32_t numberOfCycles;
        int32_t interSampleDelay;
        int32_t preCycleDelay;
        int32_t postCycleDelay;
        uint16_t outputTriggerStartIndex;
        int32_t outputTriggerWidth;
        uint16_t numberOfSamplesBetweenTriggerRepetition;
    };

    struct TLMC_PZ_OutputWaveformLookupTableSample
    {
        uint16_t index;
        int16_t voltage;
    };

    struct TLMC_PZ_MaxOutputVoltageParams
    {
        uint16_t maxOutputVoltage;
        TLMC_PZ_VoltageLimit_Type voltageLimit;
    };

    struct TLMC_PZ_OutputVoltageControlSourceParams
    {
        TLMC_PZ_OutputVoltageControlSource_Type source;
    };

    struct TLMC_PZ_PositionLoopParams
    {
        uint16_t proportional;
        uint16_t integral;
    };

    struct TLMC_PZ_Status
    {
        int16_t outputVoltage;
        int16_t position;
        TLMC_PZ_StatusBit_Type statusBits;
    };

    struct TLMC_PZ_SlewRateParams
    {
        uint16_t openLoopSlewRate;
        uint16_t closedLoopSlewRate;
    };

    struct TLMC_RichResponse
    {
        uint16_t messageId;
        uint16_t code;
        char notes[64];
    };

    struct TLMC_Response
    {
        uint16_t messageId;
        uint16_t code;
    };

    struct TLMC_AdcInputs
    {
        uint16_t adcInput1;
        uint16_t adcInput2;
    };

    struct TLMC_Setting
    {
        TLMC_ValueType_Type valueType;
        bool isValueSet;
        union TLMC_Value value;
        TLMC_ScaleType_Type scaleType;
        TLMC_Unit_Type unitType;

        char name[128];
        char displayName[128];

        bool isReadOnly;
        bool hasDiscreteValues;
        bool hasMin;
        bool hasMax;
        union TLMC_Value minValue;
        union TLMC_Value maxValue;
    };

    struct TLMC_SettingItemChangedNotificationData
    {
        char settingName[128];
    };

    struct TLMC_StageAxisParams
    {
        TLMC_StageProductId_Type productId;
        TLMC_StageAxisId_Type axisId;
        char partNumber[16];
        uint32_t serialNumber;
        uint32_t countsPerUnit;
        int32_t minPosition;
        int32_t maxPosition;
        uint32_t maxAcceleration;
        uint32_t maxDeceleration;
        uint32_t maxVelocity;
        uint16_t gearboxRatio;
        int8_t reserved[22];
    };

    struct TLMC_StatusItem
    {
        TLMC_StatusItemId_Type id;
        TLMC_ValueType_Type valueType;
        union TLMC_Value value;
    };

    struct TLMC_StatusItemChangedNotificationData
    {
        uint16_t count;
        TLMC_StatusItemId_Type* ids;
    };

    struct TLMC_StepperStatus
    {
        int32_t position;
        int32_t encoderCount;
        TLMC_UniversalStatusBit_Type statusBits;
    };

    struct TLMC_TrackSettleParams
    {
        uint16_t settleTime;
        uint16_t settleWindow;
        uint16_t trackWindow;
        int8_t reserved[4];
    };

    struct TLMC_TriggerParamsForDcBrushless
    {
        TLMC_TriggerModesForDcBrushless_Type modes;
    };

    struct TLMC_TriggerParamsForStepper
    {
        TLMC_TriggerModesForStepper_Type modes;
    };

    struct TLMC_UniversalStatus
    {
        int32_t position;
        int16_t velocity;
        int16_t motorCurrent;
        TLMC_UniversalStatusBit_Type statusBits;
    };

    struct TLMC_VelocityParams
    {
        uint32_t minVelocity;
        uint32_t acceleration;
        uint32_t maxVelocity;
    };
#pragma pack(pop)

    typedef unsigned int TLMC_DeviceHandle;

    typedef void(__stdcall* TLMC_LoggingHandler)(const char* pBuffer, const unsigned int bufferLength, const uintptr_t userData);
    typedef void(__stdcall* TLMC_NotificationHandler)(const struct TLMC_Notification* pNotification, const uintptr_t userData);
    typedef void(__stdcall* TLMC_DeviceListChangeHandler)(const TLMC_DeviceListChange_Type change, const struct TLMC_DeviceInfo* pDeviceInfo, const uintptr_t userData);
    typedef void(__stdcall* TLMC_PacketHandler)(const unsigned char* pBuffer, const size_t bufferLength, const uintptr_t userData);

    static const TLMC_DeviceHandle TLMC_InvalidDevice = (TLMC_DeviceHandle)0;

    static long long TLMC_NoWait = 0;
    static long long TLMC_InfiniteWait = -1;

    static int32_t TLMC_Unused = 0;

    static uint32_t TLMC_ConnectedProductNameBufferLength = 64;

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetApiVersion(struct TLMC_ApiVersion* pApiVersion);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_Startup(const char* pSettings);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_Shutdown();

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_AddUserMessageToLog(const char* pUserMessage);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_CreateSimulation(const char* pDescription);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_RemoveSimulation(const char* pDescription);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetDeviceListItemCount(uint16_t* pCount);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetDeviceListItems(const uint16_t sourceStartIndex, const uint16_t numberOfItems, struct TLMC_DeviceInfo* pDestination, uint16_t* pNumberOfItemsCopied);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_Open(const char* pDevice, const char* pTransport, const TLMC_OperatingMode_Type operatingModes, TLMC_DeviceHandle* pDeviceHandle);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_Close(const TLMC_DeviceHandle hDevice);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetDeviceInfo(const TLMC_DeviceHandle hDevice, struct TLMC_DeviceInfo* pDeviceInfo);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_RegisterLoggingHandler(TLMC_LoggingHandler handlerFn, const TLMC_LogLevel_Type level, const TLMC_LogCategoryFilter_Type categoryFilter, uintptr_t userData);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_UnregisterLoggingHandler(TLMC_LoggingHandler handlerFn);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_RegisterDeviceListChangeHandler(TLMC_DeviceListChangeHandler handlerFn, uintptr_t userData);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_UnregisterDeviceListChangeHandler(TLMC_DeviceListChangeHandler handlerFn);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_RegisterNotificationHandler(const TLMC_DeviceHandle hDevice, TLMC_NotificationHandler handlerFn, uintptr_t userData);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_UnregisterNotificationHandler(const TLMC_DeviceHandle hDevice, TLMC_NotificationHandler handlerFn);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_RegisterPacketHandler(const TLMC_DeviceHandle hDevice, const TLMC_PacketHandler handlerFn, const uintptr_t userData);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_UnregisterPacketHandler(const TLMC_DeviceHandle hDevice, const TLMC_PacketHandler handlerFn);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_Disconnect(const TLMC_DeviceHandle hDevice);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_WritePacket(const TLMC_DeviceHandle hDevice, const unsigned char* pBuffer, const unsigned int count);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SendNoFlashProgramming(const TLMC_DeviceHandle hDevice);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SendYesFlashProgramming(const TLMC_DeviceHandle hDevice);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetFirmwareVersionInfo(const TLMC_DeviceHandle hDevice, struct TLMC_FirmwareVersion* pDeviceFirmwareVersion, struct TLMC_FirmwareVersion* pRequiredFirmwareVersion);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_LoadParams(const TLMC_DeviceHandle hDevice);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_RequestStatus(const TLMC_DeviceHandle hDevice, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_RestoreFactoryDefaults(const TLMC_DeviceHandle hDevice);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetRichResponse(const TLMC_DeviceHandle hDevice, struct TLMC_RichResponse* pRichResponse);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetSetting(const TLMC_DeviceHandle hDevice, const char* pSettingName, struct TLMC_Setting* pDestination, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetSettingCount(const TLMC_DeviceHandle hDevice, uint16_t* pCount);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetSettingDiscreteValues(const TLMC_DeviceHandle hDevice, const char* pSettingName, char* pBuffer,
        const unsigned int bufferLength, unsigned int* pResultLength);
    TLMC_XA_EXPORT char __stdcall TLMC_GetSettingDisplayNamePathSeparator();
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetSettings(const TLMC_DeviceHandle hDevice, const uint16_t sourceStartIndex, const uint16_t numberOfItems,
        struct TLMC_Setting* pDestination, uint16_t* pNumberOfItemsCopied);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetSettingsAsString(const TLMC_DeviceHandle hDevice, char* pBuffer, const unsigned int bufferLength,
        unsigned int* pResultLength, const TLMC_SettingStringFormat_Type requiredFormat, const bool includeReadOnlyItems);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetSetting(const TLMC_DeviceHandle hDevice, const char* pSettingName, const union TLMC_Value* pNewValue);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetSettingsFromString(const TLMC_DeviceHandle hDevice, const char* pSettings);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetStatusItem(const TLMC_DeviceHandle hDevice, const TLMC_StatusItemId_Type statusItemId, struct TLMC_StatusItem* pDestination);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetStatusItemCount(const TLMC_DeviceHandle hDevice, uint16_t* pCount);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetStatusItems(const TLMC_DeviceHandle hDevice, const uint16_t sourceStartIndex, const uint16_t numberOfItems,
        struct TLMC_StatusItem* pDestination, uint16_t* pNumberOfItemsCopied);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetStatusMode(const TLMC_DeviceHandle hDevice, const TLMC_OperatingMode_Type newMode);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetEndOfMoveMessagesMode(const TLMC_DeviceHandle hDevice, const TLMC_EndOfMoveMessagesMode_Type newMode);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetConnectedProduct(const TLMC_DeviceHandle hDevice, char* pBuffer, const unsigned int bufferLength);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetConnectedProductInfo(const TLMC_DeviceHandle hDevice, struct TLMC_ConnectedProductInfo* pProductInfo);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetConnectedProductsSupported(const TLMC_DeviceHandle hDevice, char* pBuffer, const unsigned int bufferLength,
        unsigned int* pResultLength);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetConnectedProduct(const TLMC_DeviceHandle hDevice, const char* pProductName);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetConnectedProductInfo(const TLMC_DeviceHandle hDevice, const struct TLMC_ConnectedProductInfo* pProductInfo);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_Home(const TLMC_DeviceHandle hDevice, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_Identify(const TLMC_DeviceHandle hDevice);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_RackIdentify(const TLMC_DeviceHandle hDevice, const uint8_t channel);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_Move(const TLMC_DeviceHandle hDevice, const TLMC_MoveMode_Type mode, const int32_t param, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_PersistParams(const TLMC_DeviceHandle hDevice, const TLMC_ParameterGroupId_Type parameterGroupId);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_Stop(const TLMC_DeviceHandle hDevice, const TLMC_StopMode_Type mode, const long long maxWaitInMilliseconds);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_ConvertFromDeviceToPhysical(const TLMC_DeviceHandle hDevice, const TLMC_ScaleType_Type scaleType,
        const int64_t deviceValue, double* pPhysicalValue, TLMC_Unit_Type* pUnit);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_ConvertFromPhysicalToDevice(const TLMC_DeviceHandle hDevice, const TLMC_ScaleType_Type scaleType,
        const TLMC_Unit_Type unit, const double physicalValue, int64_t* pDeviceValue);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetPreferredPhysicalUnit(const TLMC_DeviceHandle hDevice, const TLMC_ScaleType_Type scaleType, TLMC_Unit_Type* pUnit);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_ActivateCalibration(const TLMC_DeviceHandle hDevice);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_DeactivateCalibration(const TLMC_DeviceHandle hDevice);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetCalibrationState(const TLMC_DeviceHandle hDevice, TLMC_CalibrationState_Type* pState);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetActuatorType(const TLMC_DeviceHandle hDevice, const uint16_t actuatorType);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetAdcInputs(const TLMC_DeviceHandle hDevice, struct TLMC_AdcInputs* pStates, const long long maxWaitInMilliseconds);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetAnalogMonitorConfigurationParams(const TLMC_DeviceHandle hDevice, const TLMC_AnalogMonitorNumber_Type monitorNumber,
        struct TLMC_AnalogMonitorConfigurationParams* pParams, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetAnalogMonitorConfigurationParams(const TLMC_DeviceHandle hDevice, const TLMC_AnalogMonitorNumber_Type monitorNumber,
        const struct TLMC_AnalogMonitorConfigurationParams* pParams);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetAuxIoPortMode(const TLMC_DeviceHandle hDevice, const TLMC_AuxIoPortNumber_Type portNumber,
        TLMC_AuxIoPortMode_Type* pMode, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetAuxIoPortMode(const TLMC_DeviceHandle hDevice, const TLMC_AuxIoPortNumber_Type portNumbers,
        const TLMC_AuxIoPortMode_Type newMode);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetAuxIoSoftwareStates(const TLMC_DeviceHandle hDevice, uint16_t* pSoftwareStates, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetAuxIoSoftwareStates(const TLMC_DeviceHandle hDevice, const uint16_t newSoftwareStates);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetBowIndex(const TLMC_DeviceHandle hDevice, TLMC_BowIndex_Type* pBowIndex, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetBowIndex(const TLMC_DeviceHandle hDevice, const TLMC_BowIndex_Type newBowIndex);

    TLMC_XA_EXPORT TLMC_ResultCode_Type TLMC_GetButtonParams(const TLMC_DeviceHandle hDevice, struct TLMC_ButtonParams* pParams, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type TLMC_SetButtonParams(const TLMC_DeviceHandle hDevice, const struct TLMC_ButtonParams* pParams);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetCurrentLoopParams(const TLMC_DeviceHandle hDevice, const TLMC_CurrentLoopScenario_Type scenario,
        struct TLMC_CurrentLoopParams* pParams, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetCurrentLoopParams(const TLMC_DeviceHandle hDevice, const TLMC_CurrentLoopScenario_Type scenario,
        const struct TLMC_CurrentLoopParams* pParams);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetDcPidParams(const TLMC_DeviceHandle hDevice, struct TLMC_DcPidParams* pParams, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetDcPidParams(const TLMC_DeviceHandle hDevice, const struct TLMC_DcPidParams* pParams);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetDigitalInputStates(const TLMC_DeviceHandle hDevice, TLMC_DigitalInput_Type* pStates, const long long maxWaitInMilliseconds);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetDigitalOutputStates(const TLMC_DeviceHandle hDevice, TLMC_DigitalOutput_Type* pStates, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetDigitalOutputStates(const TLMC_DeviceHandle hDevice, const TLMC_DigitalOutput_Type newStates);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetEnableState(const TLMC_DeviceHandle hDevice, TLMC_EnableState_Type* pEnableState, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetEnableState(const TLMC_DeviceHandle hDevice, const TLMC_EnableState_Type newEnableState, const long long verificationMaxWaitInMilliseconds);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetEncoderCounter(const TLMC_DeviceHandle hDevice, int32_t* pEncoderCounter, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetEncoderCounter(const TLMC_DeviceHandle hDevice, const int32_t newEncoderCounter);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetGeneralMoveParams(const TLMC_DeviceHandle hDevice, struct TLMC_GeneralMoveParams* pParams, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetGeneralMoveParams(const TLMC_DeviceHandle hDevice, const struct TLMC_GeneralMoveParams* pParams);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetHardwareInfo(const TLMC_DeviceHandle hDevice, struct TLMC_HardwareInfo* pInfo, const long long maxWaitInMilliseconds);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetHomeParams(const TLMC_DeviceHandle hDevice, struct TLMC_HomeParams* pParams, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetHomeParams(const TLMC_DeviceHandle hDevice, const struct TLMC_HomeParams* pParams);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetIoConfigurationNumberOfPortsSupported(const TLMC_DeviceHandle hDevice, uint8_t* pNumberOfPorts);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetIoConfigurationParams(const TLMC_DeviceHandle hDevice, const TLMC_IoPortNumber_Type portNumber,
        struct TLMC_IoConfigurationParams* pParams, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetIoConfigurationParams(const TLMC_DeviceHandle hDevice, const TLMC_IoPortNumber_Type portNumber,
        const struct TLMC_IoConfigurationParams* pParams);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetIoPositionTriggerEnableState(const TLMC_DeviceHandle hDevice, TLMC_IoPositionTriggerEnableState_Type* pEnableState, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetIoPositionTriggerEnableState(const TLMC_DeviceHandle hDevice, const TLMC_IoPositionTriggerEnableState_Type newEnableState, const long long verificationMaxWaitInMilliseconds);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetIoTriggerParams(const TLMC_DeviceHandle hDevice, struct TLMC_IoTriggerParams* pParams, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetIoTriggerParams(const TLMC_DeviceHandle hDevice, const struct TLMC_IoTriggerParams* pParams);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetJogParams(const TLMC_DeviceHandle hDevice, struct TLMC_JogParams* pParams, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetJogParams(const TLMC_DeviceHandle hDevice, const struct TLMC_JogParams* pParams);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetJoystickParams(const TLMC_DeviceHandle hDevice, struct TLMC_JoystickParams* pParams, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetJoystickParams(const TLMC_DeviceHandle hDevice, const struct TLMC_JoystickParams* pParams);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetKcubeIoTriggerParams(const TLMC_DeviceHandle hDevice, struct TLMC_KcubeIoTriggerParams* pParams, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetKcubeIoTriggerParams(const TLMC_DeviceHandle hDevice, const struct TLMC_KcubeIoTriggerParams* pParams);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetKcubeMmiLockState(const TLMC_DeviceHandle hDevice, TLMC_KcubeMmiLockState_Type* pLockState, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetKcubeMmiLockState(const TLMC_DeviceHandle hDevice, const TLMC_KcubeMmiLockState_Type newLockState);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetKcubeMmiParams(const TLMC_DeviceHandle hDevice, struct TLMC_KcubeMmiParams* pParams, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetKcubeMmiParams(const TLMC_DeviceHandle hDevice, const struct TLMC_KcubeMmiParams* pParams);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetKcubePositionTriggerParams(const TLMC_DeviceHandle hDevice, struct TLMC_KcubePositionTriggerParams* pParams, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetKcubePositionTriggerParams(const TLMC_DeviceHandle hDevice, const struct TLMC_KcubePositionTriggerParams* pParams);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_PZ_GetKpcIoSettingsParams(const TLMC_DeviceHandle hDevice, struct TLMC_PZ_KpcIoSettingsParams* pParams, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_PZ_SetKpcIoSettingsParams(const TLMC_DeviceHandle hDevice, const struct TLMC_PZ_KpcIoSettingsParams* pParams);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_PZ_GetKpcMmiParams(const TLMC_DeviceHandle hDevice, struct TLMC_PZ_KpcMmiParams* pParams, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_PZ_SetKpcMmiParams(const TLMC_DeviceHandle hDevice, const struct TLMC_PZ_KpcMmiParams* pParams);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_PZ_GetKpcIoTriggerParams(const TLMC_DeviceHandle hDevice, struct TLMC_PZ_KpcIoTriggerParams* pParams, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_PZ_SetKpcIoTriggerParams(const TLMC_DeviceHandle hDevice, const struct TLMC_PZ_KpcIoTriggerParams* pParams);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetLcdDisplayParams(const TLMC_DeviceHandle hDevice, struct TLMC_LcdDisplayParams* pParams, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetLcdDisplayParams(const TLMC_DeviceHandle hDevice, const struct TLMC_LcdDisplayParams* pParams);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetLcdMoveParams(const TLMC_DeviceHandle hDevice, struct TLMC_LcdMoveParams* pParams, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetLcdMoveParams(const TLMC_DeviceHandle hDevice, const struct TLMC_LcdMoveParams* pParams);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetLimitSwitchParams(const TLMC_DeviceHandle hDevice, struct TLMC_LimitSwitchParams* pParams, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetLimitSwitchParams(const TLMC_DeviceHandle hDevice, const struct TLMC_LimitSwitchParams* pParams);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetMotorOutputParams(const TLMC_DeviceHandle hDevice, struct TLMC_MotorOutputParams* pParams, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetMotorOutputParams(const TLMC_DeviceHandle hDevice, const struct TLMC_MotorOutputParams* pParams);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetMoveAbsoluteParams(const TLMC_DeviceHandle hDevice, struct TLMC_MoveAbsoluteParams* pParams, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetMoveAbsoluteParams(const TLMC_DeviceHandle hDevice, const struct TLMC_MoveAbsoluteParams* pParams);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetMoveRelativeParams(const TLMC_DeviceHandle hDevice, struct TLMC_MoveRelativeParams* pParams, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetMoveRelativeParams(const TLMC_DeviceHandle hDevice, const struct TLMC_MoveRelativeParams* pParams);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetPositionCounter(const TLMC_DeviceHandle hDevice, int32_t* pPositionCounter, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetPositionCounter(const TLMC_DeviceHandle hDevice, const int32_t newPositionCounter);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetPositionLoopParams(const TLMC_DeviceHandle hDevice, const TLMC_PositionLoopScenario_Type scenario,
        struct TLMC_PositionLoopParams* pParams, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetPositionLoopParams(const TLMC_DeviceHandle hDevice, const TLMC_PositionLoopScenario_Type scenario,
        const struct TLMC_PositionLoopParams* pParams);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetPotentiometerParams(const TLMC_DeviceHandle hDevice, struct TLMC_PotentiometerParams* pParams, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetPotentiometerParams(const TLMC_DeviceHandle hDevice, const struct TLMC_PotentiometerParams* pParams);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetPowerParams(const TLMC_DeviceHandle hDevice, struct TLMC_PowerParams* pParams, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetPowerParams(const TLMC_DeviceHandle hDevice, const struct TLMC_PowerParams* pParams);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetProfileModeParams(const TLMC_DeviceHandle hDevice, struct TLMC_ProfileModeParams* pParams, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetProfileModeParams(const TLMC_DeviceHandle hDevice, const struct TLMC_ProfileModeParams* pParams);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_PZ_GetMaxOutputVoltageParams(const TLMC_DeviceHandle hDevice, struct TLMC_PZ_MaxOutputVoltageParams* pParams, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_PZ_SetMaxOutputVoltage(const TLMC_DeviceHandle hDevice, const uint16_t newMaxOutputVoltage);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_PZ_GetMaxTravel(const TLMC_DeviceHandle hDevice, uint16_t* pMaxTravel, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_PZ_SetMaxTravel(const TLMC_DeviceHandle hDevice, const uint16_t newMaxTravel);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_PZ_GetOutputVoltage(const TLMC_DeviceHandle hDevice, int16_t* pOutputVoltage, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_PZ_SetOutputVoltage(const TLMC_DeviceHandle hDevice, const int16_t newOutputVoltage);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_PZ_GetOutputVoltageControlSourceParams(const TLMC_DeviceHandle hDevice, struct TLMC_PZ_OutputVoltageControlSourceParams* pParams, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_PZ_SetOutputVoltageControlSourceParams(const TLMC_DeviceHandle hDevice, const struct TLMC_PZ_OutputVoltageControlSourceParams* pParams);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_PZ_SetOutputWaveformLookupTableSample(const TLMC_DeviceHandle hDevice, struct TLMC_PZ_OutputWaveformLookupTableSample* pSample);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_PZ_GetOutputWaveformParams(const TLMC_DeviceHandle hDevice, struct TLMC_PZ_OutputWaveformParams* pParams, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_PZ_SetOutputWaveformParams(const TLMC_DeviceHandle hDevice, const struct TLMC_PZ_OutputWaveformParams* pParams);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_PZ_StartOutputWaveform(const TLMC_DeviceHandle hDevice);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_PZ_StopOutputWaveform(const TLMC_DeviceHandle hDevice);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_PZ_GetPosition(const TLMC_DeviceHandle hDevice, int16_t* pPosition, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_PZ_SetPosition(const TLMC_DeviceHandle hDevice, const int16_t position);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_PZ_GetPositionControlMode(const TLMC_DeviceHandle hDevice, TLMC_PZ_PositionControlMode_Type* pControlMode, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_PZ_SetPositionControlMode(const TLMC_DeviceHandle hDevice, const TLMC_PZ_PositionControlMode_Type newControlMode, const long long verificationMaxWaitInMilliseconds);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_PZ_GetPositionLoopParams(const TLMC_DeviceHandle hDevice, struct TLMC_PZ_PositionLoopParams* pParams, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_PZ_SetPositionLoopParams(const TLMC_DeviceHandle hDevice, const struct TLMC_PZ_PositionLoopParams* pParams);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_PZ_GetSlewRateParams(const TLMC_DeviceHandle hDevice, struct TLMC_PZ_SlewRateParams* pParams, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_PZ_SetSlewRateParams(const TLMC_DeviceHandle hDevice, const struct TLMC_PZ_SlewRateParams* pParams);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_PZ_GetStatus(const TLMC_DeviceHandle hDevice, struct TLMC_PZ_Status* pPiezoStatus, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_PZ_GetStatusBits(const TLMC_DeviceHandle hDevice, TLMC_PZ_StatusBit_Type* pPiezoStatusBits, const long long maxWaitInMilliseconds);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_PZ_SetZero(const TLMC_DeviceHandle hDevice, const long long maxWaitInMilliseconds);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetRackBayOccupiedState(const TLMC_DeviceHandle hDevice, const TLMC_RackBayNumber_Type bayNumber,
        TLMC_RackBayOccupiedState_Type* pState, const long long maxWaitInMilliseconds);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetStageAxisParams(const TLMC_DeviceHandle hDevice, struct TLMC_StageAxisParams* pParams, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetStageAxisParams(const TLMC_DeviceHandle hDevice, const struct TLMC_StageAxisParams* pParams);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetStepperLoopParams(const TLMC_DeviceHandle hDevice, struct TLMC_StepperLoopParams* pParams, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetStepperLoopParams(const TLMC_DeviceHandle hDevice, const struct TLMC_StepperLoopParams* pParams);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetStepperStatus(const TLMC_DeviceHandle hDevice, struct TLMC_StepperStatus* pStepperStatus, const long long maxWaitInMilliseconds);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetTrackSettleParams(const TLMC_DeviceHandle hDevice, struct TLMC_TrackSettleParams* pParams, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetTrackSettleParams(const TLMC_DeviceHandle hDevice, const struct TLMC_TrackSettleParams* pParams);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetTriggerParamsForDcBrushless(const TLMC_DeviceHandle hDevice, struct TLMC_TriggerParamsForDcBrushless* pParams, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetTriggerParamsForDcBrushless(const TLMC_DeviceHandle hDevice, const struct TLMC_TriggerParamsForDcBrushless* pParams);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetTriggerParamsForStepper(const TLMC_DeviceHandle hDevice, struct TLMC_TriggerParamsForStepper* pParams, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetTriggerParamsForStepper(const TLMC_DeviceHandle hDevice, const struct TLMC_TriggerParamsForStepper* pParams);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetUniversalStatus(const TLMC_DeviceHandle hDevice, struct TLMC_UniversalStatus* pUniversalStatus, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetUniversalStatusBits(const TLMC_DeviceHandle hDevice, TLMC_UniversalStatusBit_Type* pUniversalStatusBits, const long long maxWaitInMilliseconds);

    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_GetVelocityParams(const TLMC_DeviceHandle hDevice, struct TLMC_VelocityParams* pParams, const long long maxWaitInMilliseconds);
    TLMC_XA_EXPORT TLMC_ResultCode_Type __stdcall TLMC_SetVelocityParams(const TLMC_DeviceHandle hDevice, const struct TLMC_VelocityParams* pParams);
#ifdef __cplusplus
}
#endif

#endif

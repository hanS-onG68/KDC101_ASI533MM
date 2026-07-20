#include <iostream>
#include <ASICamera2.h>

const char *ASIErrorCodeToString(ASI_ERROR_CODE err)
{
    switch (err) {
        case ASI_SUCCESS:                      return "ASI_SUCCESS";
        case ASI_ERROR_INVALID_INDEX:          return "ASI_ERROR_INVALID_INDEX";           // no camera connected or index value out of boundary
        case ASI_ERROR_INVALID_ID:             return "ASI_ERROR_INVALID_ID";              // invalid ID
        case ASI_ERROR_INVALID_CONTROL_TYPE:   return "ASI_ERROR_INVALID_CONTROL_TYPE";    // invalid control type
        case ASI_ERROR_CAMERA_CLOSED:          return "ASI_ERROR_CAMERA_CLOSED";           // camera didn't open
        case ASI_ERROR_CAMERA_REMOVED:         return "ASI_ERROR_CAMERA_REMOVED";          // failed to find the camera, maybe the camera has been removed
        case ASI_ERROR_INVALID_PATH:           return "ASI_ERROR_INVALID_PATH";            // cannot find the path of the file
        case ASI_ERROR_INVALID_FILEFORMAT:     return "ASI_ERROR_INVALID_FILEFORMAT";
        case ASI_ERROR_INVALID_SIZE:           return "ASI_ERROR_INVALID_SIZE";            // wrong video format size
        case ASI_ERROR_INVALID_IMGTYPE:        return "ASI_ERROR_INVALID_IMGTYPE";         // unsupported image formate
        case ASI_ERROR_OUTOF_BOUNDARY:         return "ASI_ERROR_OUTOF_BOUNDARY";          // the startpos is out of boundary
        case ASI_ERROR_TIMEOUT:                return "ASI_ERROR_TIMEOUT";                 // timeout
        case ASI_ERROR_INVALID_SEQUENCE:       return "ASI_ERROR_INVALID_SEQUENCE";        // stop capture first
        case ASI_ERROR_BUFFER_TOO_SMALL:       return "ASI_ERROR_BUFFER_TOO_SMALL";        // buffer size is not big enough
        case ASI_ERROR_VIDEO_MODE_ACTIVE:      return "ASI_ERROR_VIDEO_MODE_ACTIVE";
        case ASI_ERROR_EXPOSURE_IN_PROGRESS:   return "ASI_ERROR_EXPOSURE_IN_PROGRESS";
        case ASI_ERROR_GENERAL_ERROR:          return "ASI_ERROR_GENERAL_ERROR";           // general error, eg: value is out of valid range
        case ASI_ERROR_INVALID_MODE:           return "ASI_ERROR_INVALID_MODE";            // the current mode is wrong
        case ASI_ERROR_GPS_NOT_SUPPORTED:      return "ASI_ERROR_GPS_NOT_SUPPORTED";       // this camera do not support GPS
        case ASI_ERROR_GPS_VER_ERR:            return "ASI_ERROR_GPS_VER_ERR";             // the FPGA GPS ver is too low
        case ASI_ERROR_GPS_FPGA_ERR:           return "ASI_ERROR_GPS_FPGA_ERR";            // failed to read or write data to FPGA
        case ASI_ERROR_GPS_PARAM_OUT_OF_RANGE: return "ASI_ERROR_GPS_PARAM_OUT_OF_RANGE";  // start line or end line out of range, should make them between 0 ~ MaxHeight - 1
        case ASI_ERROR_GPS_DATA_INVALID:       return "ASI_ERROR_GPS_DATA_INVALID";        // GPS has not yet found the satellite or FPGA cannot read GPS data
        default:                               return "ASI_ERROR_END";
    }
}
const char *ASIControlTypeToString(ASI_CONTROL_TYPE type)
{
    switch (type) {
        case ASI_GAIN:                   return "ASI_GAIN";
        case ASI_EXPOSURE:               return "ASI_EXPOSURE";
        case ASI_GAMMA:                  return "ASI_GAMMA";
        case ASI_WB_R:                   return "ASI_WB_R";
        case ASI_WB_B:                   return "ASI_WB_B";
        case ASI_OFFSET:                 return "ASI_OFFSET";
        case ASI_BANDWIDTHOVERLOAD:      return "ASI_BANDWIDTHOVERLOAD";
        case ASI_OVERCLOCK:              return "ASI_OVERCLOCK";
        case ASI_TEMPERATURE:            return "ASI_TEMPERATURE";             // return 10*temperature
        case ASI_FLIP:                   return "ASI_FLIP";
        case ASI_AUTO_MAX_GAIN:          return "ASI_AUTO_MAX_GAIN";
        case ASI_AUTO_MAX_EXP:           return "ASI_AUTO_MAX_EXP";            // micro second
        case ASI_AUTO_TARGET_BRIGHTNESS: return "ASI_AUTO_TARGET_BRIGHTNESS";  // target brightness
        case ASI_HARDWARE_BIN:           return "ASI_HARDWARE_BIN";
        case ASI_HIGH_SPEED_MODE:        return "ASI_HIGH_SPEED_MODE";
        case ASI_COOLER_POWER_PERC:      return "ASI_COOLER_POWER_PERC";
        case ASI_TARGET_TEMP:            return "ASI_TARGET_TEMP";             // not need *10
        case ASI_COOLER_ON:              return "ASI_COOLER_ON";
        case ASI_MONO_BIN:               return "ASI_MONO_BIN";                // lead to less grid at software bin mode for color camera
        case ASI_FAN_ON:                 return "ASI_FAN_ON";
        case ASI_PATTERN_ADJUST:         return "ASI_PATTERN_ADJUST";
        case ASI_ANTI_DEW_HEATER:        return "ASI_ANTI_DEW_HEATER";
        case ASI_FAN_ADJUST:             return "ASI_FAN_ADJUST";
        case ASI_PWRLED_BRIGNT:          return "ASI_PWRLED_BRIGNT";
        case ASI_USBHUB_RESET:           return "ASI_USBHUB_RESET";
        case ASI_GPS_SUPPORT:            return "ASI_GPS_SUPPORT";
        case ASI_GPS_START_LINE:         return "ASI_GPS_START_LINE";
        case ASI_GPS_END_LINE:           return "ASI_GPS_END_LINE";
        case ASI_ROLLING_INTERVAL:       return "ASI_ROLLING_INTERVAL";
        default:                         return "UNKNOWN";
    }
}

const char *ASICameraModeToString(ASI_CAMERA_MODE mode)
{
    switch (mode) {
        case ASI_MODE_NORMAL:          return "ASI_MODE_NORMAL";
        case ASI_MODE_TRIG_SOFT_EDGE:  return "ASI_MODE_TRIG_SOFT_EDGE";
        case ASI_MODE_TRIG_RISE_EDGE:  return "ASI_MODE_TRIG_RISE_EDGE";
        case ASI_MODE_TRIG_FALL_EDGE:  return "ASI_MODE_TRIG_FALL_EDGE";
        case ASI_MODE_TRIG_SOFT_LEVEL: return "ASI_MODE_TRIG_SOFT_LEVEL";
        case ASI_MODE_TRIG_HIGH_LEVEL: return "ASI_MODE_TRIG_HIGH_LEVEL";
        case ASI_MODE_TRIG_LOW_LEVEL:  return "ASI_MODE_TRIG_LOW_LEVEL";
        default:                       return "ASI_MODE_NORMAL";
    }
}

const char *ASIExposureStatusToString(ASI_EXPOSURE_STATUS status)
{
    switch (status) {
        case ASI_EXP_IDLE:     return "ASI_EXP_IDLE";     // idle states, you can start exposure now
        case ASI_EXP_WORKING:  return "ASI_EXP_WORKING";  // exposing
        case ASI_EXP_SUCCESS:  return "ASI_EXP_SUCCESS";  // exposure finished and waiting for download
        default:               return "ASI_EXP_FAILED";   // exposure failed, you need to start exposure again
    }
}

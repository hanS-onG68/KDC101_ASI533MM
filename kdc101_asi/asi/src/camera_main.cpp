#include <iostream>
#include <memory>
#include "ASICamera2.h"
#include "log.h"
#include "asi_func.h"
#include "camera_init.h"
#include "camera_mode.h"
#include "camera_exposure.h"
#include "camera_process.h"
#include "camera.h"
#include "camera_main.h"

int camera_main()
{
    Log::init("my_app.log"); // 初始化日志

    auto DllFuncsPtr = std::make_unique<ASI_GetDllFunc>();
    AsiCamera camera;
    CameraProcess cameraProcess;
    int res = camera.CameraCoreFunc(*DllFuncsPtr, cameraProcess);
    LOG_INFO("CameraAction result is: {}", res == 0 ? "Success" : "Fail");
    return 0;
}
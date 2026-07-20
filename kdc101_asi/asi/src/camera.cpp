#include <memory>
#include "log.h"
#include "ASICamera2.h"
#include "asi_func.h"
#include "camera_init.h"
#include "camera_mode.h"
#include "camera_exposure.h"
#include "camera_process.h"
#include "camera.h"

/******************************* 类 AsiCamera *******************************/
AsiCamera::AsiCamera(): cameraPtr(std::make_unique<CameraProcess>()) {
    LOG_INFO("class AsiCamera init.");
}

AsiCamera::~AsiCamera() {
    LOG_INFO("class AsiCamera delete.");
}

int AsiCamera::CameraCoreFunc(ASI_GetDllFunc &DllFuncsPtr, CameraProcess &camera) {
    int res = cameraPtr->CameraAction(DllFuncsPtr, camera);
    LOG_INFO("CameraCoreFunc is {}", res ? "Fail" : "Success");
    return res;
}
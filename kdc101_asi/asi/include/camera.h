#pragma once

class CameraProcess;

class AsiCamera {
public:
    AsiCamera();
    ~AsiCamera();
    int CameraCoreFunc(ASI_GetDllFunc &DllFuncsPtr, CameraProcess &camera);
private:
    std::unique_ptr<CameraProcess> cameraPtr;
protected:

};
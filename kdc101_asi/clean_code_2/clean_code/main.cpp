#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <functional>
#include <iostream>
#include <Windows.h>
#include <thread>
#include <filesystem>
#include <chrono>
#include <unordered_map>
#include <system_error>
#include "asi_func.h"
#include "tlmc_func.h"
#include "log.h"

using NumberCallback = std::function<void(double)>;   // 表示一个返回值为void，并接受1个 int 类型参数的函数

class SenderWidget : public QWidget {
public:
    SenderWidget(NumberCallback callback = nullptr, QWidget *parent = nullptr) : QWidget(parent), callBackFunc(callback) {
        setWindowTitle("Sender");  // 窗口的名字
        resize(400, 150);  // 窗口的大小（长*宽）

        layout = new QGridLayout(this);  // 网格布局

        sendBox = new QLineEdit(this);  // 单行输入框
        sendBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        
        QPushButton *sendButton = new QPushButton("Send", this);  // 名字为Send的按钮
        sendButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);  // 水平方向尽可能扩展，垂直方向固定

        messageDisplay = new QLabel("Message will appear here.\n", this);  // 显示信息为："Message will appear here.\n(tips:10000 == 5.2093 degrees)\n"的标签
        messageDisplay->setStyleSheet("border: 2px solid red; background-color: white;");

        myLabel = new QLabel(this);
        myLabel->setStyleSheet("border: 2px solid red; background-color: white;");  // 水平方向尽可能扩展，垂直方向固定
        
        // 将各个组件加入到布局管理器中
        layout->addWidget(sendButton, 0, 0);
        layout->addWidget(sendBox, 0, 1);
        layout->addWidget(messageDisplay, 1, 0); 
        layout->addWidget(myLabel, 1, 1);

        connect(sendButton, &QPushButton::clicked, this, TextHandleFunc);
    }
private slots:
    void TextHandleFunc() {
        QString message = sendBox->text();
        if (!message.isEmpty()) {
            messageDisplay->setText("Sent: " + message + "°");
            myLabel->setText("Current angle: " + QString::number(message.toDouble(), 'f', 4) + "°");
            num = message.toDouble();
            sendBox->clear();
                
            // 调用回调函数
            if (this->callBackFunc) {
                this->callBackFunc(num);
            }
        }
    }
private:
    QLineEdit *sendBox;
    QLabel *messageDisplay;
    QLabel *myLabel;
    QPushButton *sendButton;
    double num = 0.0;
    NumberCallback callBackFunc;
    QGridLayout *layout;
};

bool isDirectoryEmpty(const std::string& path) {
    namespace fs = std::filesystem;
    try {
        // 检查路径是否存在且是目录
        if (!fs::exists(path) || !fs::is_directory(path)) {
            std::cerr << "路径不存在或不是目录" << std::endl;
            return false;
        }
        
        // begin() == end() 表示目录为空
        return fs::begin(fs::directory_iterator(path)) == 
               fs::end(fs::directory_iterator(path));
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "错误: " << e.what() << std::endl;
        return false;
    }
}

bool IsInitAsiCameraResource(ASI_GetDllFunc &DllFuncsPtr, HMODULE hDll, std::shared_ptr<ASI_CAMERA_INFO> cameraInfo, AsiROI &roiInfo) {
    if(CameraGetDllFunc(DllFuncsPtr, hDll)) {
        LOG_ERROR("fail to get DLL functions");
        FreeLibrary(hDll); // 卸载DLL
        return false;
    }

    int numOfConnectedCameras = DllFuncsPtr.ASIGetNumOfConnectedCameras(); // 得到连接的相机的数量
    LOG_INFO("number of connected cameras is {}", numOfConnectedCameras);

    if (GetCameraProperty(DllFuncsPtr, cameraInfo, 0)) { // 得到相机的信息，包括ID、名称、分辨率等
        CloseCamera(DllFuncsPtr, cameraInfo);
        return false;
    }

    if (InitCamera(DllFuncsPtr, cameraInfo, roiInfo)) { // 相机初始化
        CloseCamera(DllFuncsPtr, cameraInfo);
        return false;
    }

    if (CameraModeOperate(DllFuncsPtr, cameraInfo)) { // 相机模式 相关
        CloseCamera(DllFuncsPtr, cameraInfo);
        return false;
    }

    return true;
}

bool IsInitKDC101Resource(DllFunctions *myDll, TLMC_DeviceHandle &hDeviceHandle) {
    // 加载myDll结构体相关的钩子
    if (LoadDllFunctions(myDll) != SuccessLoad) {
        printf("[Fail] to initialize DLL API. Error code: %d\n", LoadDllFunctions(myDll));
        free(myDll);
        return false;
    }
    LOG_INFO("[Success] load dll functions.\n");

    // TLMC_Startup
    if (myDll->TLMC_Startup(NULL) != TLMC_ResultCode::TLMC_Success) {
        printf("[Fail] to startup device. Error code: %d\n", myDll->TLMC_Startup(NULL));
        UnloadDllFunctions(myDll);
        free(myDll);
        return false;
    }
    LOG_INFO("[Success] to startup devices\n");

    // TLMC_Open
    if (myDll->TLMC_Open("27271559", NULL, TLMC_OperatingMode::TLMC_OperatingMode_Default, &hDeviceHandle) != TLMC_ResultCode::TLMC_Success) {
        printf("[Fail] to open device. Error code: %d\n", myDll->TLMC_Open("27271559", NULL, TLMC_OperatingMode::TLMC_OperatingMode_Default, &hDeviceHandle));
        TLMC_ShutDownDevice(myDll);
        UnloadDllFunctions(myDll);
        free(myDll);
        return false;
    }
    LOG_INFO("[Success] to open devices\n");
    return true;
}

bool IsKDC101WithAsiCamera(DllFunctions *myDll, TLMC_DeviceHandle &hDeviceHandle, int32_t distance, ASI_GetDllFunc &DllFuncsPtr, std::shared_ptr<ASI_CAMERA_INFO> cameraInfo, AsiROI &roiInfo) {
    int res = KDC101Action(myDll, hDeviceHandle, distance);
    if (res == TlmcFail) {
        LOG_ERROR("[Fail]KDC101 action is fail!");
        return false;
    }
    res = ImageCapture(DllFuncsPtr, cameraInfo, roiInfo);  // 图像处理 相关
    if (res) {
        CloseCamera(DllFuncsPtr, cameraInfo);
        LOG_ERROR("[Fail]AsiCamera action is fail!");
        return false;
    }

    return true;
}

double getAlignedAngle(DllFunctions *myDll, TLMC_DeviceHandle &hDeviceHandle, ASI_GetDllFunc &DllFuncsPtr, std::shared_ptr<ASI_CAMERA_INFO> cameraInfo, AsiROI &roiInfo) {
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    std::tm tm_now = *std::localtime(&time_t_now);
    char date_buf[32] = {0};
    strftime(date_buf, sizeof(date_buf), "%Y-%m-%d", &tm_now);
    std::string date_str(date_buf);
    // 创建日期文件夹，父目录不存在也会自动创建
    std::filesystem::path capture_dir = "C:/Users/admin/Desktop/Capture/";
    std::filesystem::path today_dir = capture_dir / date_str;
    if (!std::filesystem::exists(today_dir.string())) {
        std::error_code ec;
        std::filesystem::create_directories(today_dir.string(), ec); // 创建日期文件夹
    }
    std::unordered_map<std::string, double> alignedAngleMap = {};  // 今天的对准角度记录，键为日期字符串，值为对准角度（作为零点位）

    for (double angle = 0.0; angle <= 10.0; angle += 1) {
        std::cout << "[Info]Angle: " << angle << "°" << std::endl; 
        double temp = angle * 1919.6450;  // 输入的角度值inputNum转换成步进电机的脉冲数
        int32_t distance = static_cast<int>(std::round(temp)); 
        int res = IsKDC101WithAsiCamera(myDll, hDeviceHandle, distance, DllFuncsPtr, cameraInfo, roiInfo);
        if (!res) {
            std::cout << "[Success]socket is ok" << std::endl;
            if (!isDirectoryEmpty(today_dir.string())) {
                alignedAngleMap[today_dir.string()] = angle;
                std::cout << "[Info]Aligned angle saved: " << angle << "°" << std::endl;
                return angle;  // 找到第一个有效角度后退出循环
            } else {
                std::cout << "[Warning]Directory is empty, no angle saved." << std::endl;
            }
        }
    }
    return 0.0;  // 如果没有找到，返回默认值0.0
}

int main(int argc, char *argv[]) {
    #ifdef Q_OS_WIN
    SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
    #endif
    
    /*************************************************** 相机相关的初始化 ****************************************************/
    Log::init("my_app.log"); // 初始化日志
    auto DllFuncsPtr = std::make_unique<ASI_GetDllFunc>();
    auto cameraInfo = std::make_shared<ASI_CAMERA_INFO>();
    AsiROI roiInfo = {
        .width = 0,
        .height = 0,
        .x = 0,
        .y = 0,
        .bin = 1,
        .imgType = ASI_IMG_RAW8
    };
    HMODULE hDll = DownLoadDll(); // 加载DLL
    if (hDll == NULL) {
        LOG_ERROR("Failed to load DLL");
        return -1;
    }
    bool res = IsInitAsiCameraResource(*DllFuncsPtr, hDll, cameraInfo, roiInfo);  // 判断相机资源初始化是否ok
    LOG_INFO("Camera initialization result is: {}", res ? "Success" : "Fail");
    if (res == false) {
        LOG_ERROR("[Fail]Failed to initialize camera resource");
        return -1; // 如果相机初始化失败，退出程序
    }
    LOG_INFO("[Success]Camera resource initialized successfully");

    /*************************************************** 转台相关的初始化 ****************************************************/
    // 在栈上声明一个管理结构体
    DllFunctions *myDll = (DllFunctions*)malloc(sizeof(DllFunctions));
    if (myDll == NULL) {
        LOG_ERROR("[Fail]malloc DllFunctions fail!\n");
        return -1;
    }
    TLMC_DeviceHandle hDeviceHandle;
    res = IsInitKDC101Resource(myDll, hDeviceHandle);
    if (res == false) {
        LOG_ERROR("[Fail]Failed to initialize KDC101 resource");
        return -1; // 如果相机初始化失败，退出程序
    }
    LOG_INFO("[Success]KDC101 resource initialized successfully");

    double baseAngle = getAlignedAngle(myDll, hDeviceHandle, *DllFuncsPtr, cameraInfo, roiInfo);
    LOG_INFO("Today's aligned angle is: {}°", baseAngle);
    
    NumberCallback func = [&myDll, &hDeviceHandle, &DllFuncsPtr, &cameraInfo, &roiInfo, &baseAngle](double num) {
        std::cout << "[Info]Number received from user send: " << num << std::endl;
        num += baseAngle;               // 将用户输入的角度加上今天的对准角度，得到实际角度
        double temp = num * 1919.6450;  // 输入的角度值inputNum转换成步进电机的脉冲数
        int distance = static_cast<int>(std::round(temp)); 
        int res = IsKDC101WithAsiCamera(myDll, hDeviceHandle, distance, *DllFuncsPtr, cameraInfo, roiInfo);
        if (res == true) {
            std::cout << "[Success]KDC101 and AsiCamera action is ok" << std::endl;
        }
    };

    QApplication app(argc, argv);
    SenderWidget window(func);
    window.show();

    app.exec();

    /* 清理资源 */
    CloseCamera(*DllFuncsPtr, cameraInfo);
    FreeLibrary(hDll); // 卸载DLL
    FreeAll(myDll, hDeviceHandle);

    return 0;
}
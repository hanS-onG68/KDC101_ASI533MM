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
#include "socket.h"

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

int main(int argc, char *argv[]) {
    #ifdef Q_OS_WIN
    SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
    #endif

    QApplication app(argc, argv);

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

    for (double angle = 0.0; angle <= 360.0; angle += 0.5) {
        std::cout << "[Info]Angle: " << angle << "°" << std::endl;
        int res = socket(&angle);
        if (!res) {
            std::cout << "[Success1]socket is ok" << std::endl;
            if (!isDirectoryEmpty(today_dir.string())) {
                alignedAngleMap[today_dir.string()] = angle;
                std::cout << "[Info]Aligned angle saved: " << angle << "°" << std::endl;
                break;  // 找到第一个有效角度后退出循环
            } else {
                std::cout << "[Warning]Directory is empty, no angle saved." << std::endl;
            }
        }
    }

    NumberCallback func = [&today_dir, &alignedAngleMap](double num) {
        std::cout << "[Info]Number received from user send: " << num << std::endl;
        num += alignedAngleMap[today_dir.string()];  // 将用户输入的角度加上今天的对准角度，得到实际角度
        int res = socket(&num);
        if (!res) {
            std::cout << "[Success2]socket is ok" << std::endl;
        }
    };
    
    SenderWidget window(func);
    window.show();

    return app.exec();
}
#include <vector>
#include <filesystem>
#include <chrono>
#include <system_error>
#include <sstream>
#include "opencv2/opencv.hpp"
#include "asi_opencv.h"
#include "log.h"
#include "asi_find_center.h"
#include "asi_func.h"

void OpenCvHandle(unsigned char *bufferData, const AsiROI& roiInfo)
{
    // 1. 定义图像参数（这些值需通过ASIGetROIFormat等SDK函数实际获取）
    LOG_INFO("img info: width = {}, height = {}", roiInfo.width, roiInfo.height);

    // 2. 创建 OpenCV Mat 对象，直接使用数据缓冲区
    // 注意：此Mat与原始数据共享内存，修改Mat会修改原始数据。若需独立，使用 .clone()
    cv::Mat rawMat(roiInfo.height, roiInfo.width, CV_8UC1, bufferData);  // ASI_IMG_RAW8 是单通道的Bayer格式, CV_8UC1对应 8位深度，单通道
    LOG_INFO("Create an OpenCV Mat object");

    // 可选但推荐：克隆数据以避免后续操作修改原始缓冲区
    cv::Mat imageToProcess = rawMat.clone();

    // // 3. 关键：对Bayer格式进行去马赛克，转换为BGR图像（单色相机不需要进行该处理）
    // cv::Mat colorMat;
    // // 注意：COLOR_BayerBG2BGR 是示例，必须根据相机传感器的实际Bayer模式选择正确的转换代码
    // // 可选模式: COLOR_BayerBG2BGR, COLOR_BayerGB2BGR, COLOR_BayerRG2BGR, COLOR_BayerGR2BGR, COLOR_BayerBG2BGR_VNG, COLOR_BayerGB2BGR_VNG, ... (VNG等是更高级的插值方法)
    // cv::cvtColor(rawMat, colorMat, cv::COLOR_BayerRG2BGR);
    // LOG_INFO("Demosaic the Bayer format and convert it to a BGR image.");

    // 4. （可选）图像后处理
    // 例如对比度拉伸、自动白平衡、降噪等，可根据需要添加
    // cv::normalize(imageToProcess, imageToProcess, 0, 255, cv::NORM_MINMAX);
    // LOG_INFO("Image post-processing.");

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
    if (isAligned(imageToProcess, roiInfo) == true) {
    // if (true) {
        // 5. 保存图像, 生成带时间戳的文件名
        // auto now = std::chrono::system_clock::now();
        // auto time_t_now = std::chrono::system_clock::to_time_t(now);
        // std::tm tm_now = *std::localtime(&time_t_now);
        // char date_buf[32] = {0};
        // strftime(date_buf, sizeof(date_buf), "%Y-%m-%d", &tm_now);
        // std::string date_str(date_buf);
        // // 创建日期文件夹，父目录不存在也会自动创建
        // std::filesystem::path capture_dir = "C:/Users/admin/Desktop/Capture/";
        // std::filesystem::path today_dir = capture_dir / date_str;
        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
        std::string filename = today_dir.string() + "/" + std::to_string(timestamp) + ".png";
        cv::imwrite(filename, imageToProcess); // 保存为PNG
        // 或者 cv::imwrite("output_image.jpg", colorMat); // 保存为JPEG
        LOG_INFO("Aligned image saved.");

        // 6. （可选）显示图像
        cv::imshow("ASI Image", imageToProcess);
        LOG_INFO("Showing image.");

        cv::waitKey(0); // 等待按键关闭窗口
        cv::destroyAllWindows();
    } else {
        LOG_INFO("Image is not aligned!");
    }
    LOG_INFO("{} end.", __func__);
}
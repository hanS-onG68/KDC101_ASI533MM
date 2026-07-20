#include "opencv2/opencv.hpp"
#include <vector>
#include <cmath>
#include <algorithm>
#include <filesystem>
#include <chrono>
#include "log.h"
#include "asi_find_center.h"
#include "asi_func.h"

using namespace cv;
using namespace std;

// sigma剪切统计，计算背景的均值、中位数、标准差（和photutils sigma_clipped_stats逻辑一致）
void sigmaClippedStats(const Mat &gray, float sigma, int max_iter, 
                       float &out_mean, float &out_median, float &out_std) {
    vector<float> pixels;
    for (int y = 0; y < gray.rows; y++) {
        for (int x = 0; x < gray.cols; x++) {
            pixels.push_back(gray.at<uchar>(y, x));
        }
    }

    float mean, std;
    float lower, upper;
    for (int iter = 0; iter < max_iter; iter++) {
        if (pixels.empty()) break;
        // 计算均值和标准差
        mean = 0;
        for (float p : pixels) mean += p;
        mean /= pixels.size();
        float var = 0;
        for (float p : pixels) var += (p - mean) * (p - mean);
        std = sqrt(var / pixels.size());
        // 剪切 outliers
        lower = mean - sigma * std;
        upper = mean + sigma * std;
        vector<float> new_pixels;
        for (float p : pixels) {
            if (p >= lower && p <= upper) new_pixels.push_back(p);
        }
        if (new_pixels.size() == pixels.size()) break; // 收敛退出
        pixels.swap(new_pixels);
    }

    // 计算中位数
    sort(pixels.begin(), pixels.end());
    if (pixels.size() % 2 == 0) {
        out_median = (pixels[pixels.size()/2 - 1] + pixels[pixels.size()/2]) / 2;
    } else {
        out_median = pixels[pixels.size()/2];
    }
    out_mean = mean;
    out_std = std;
}

// 计算灰度质心（和photutils centroid_com逻辑一致）
Point2f computeCentroid(const Mat &img_no_bg) {
    double m00 = 0, m10 = 0, m01 = 0;
    for (int y = 0; y < img_no_bg.rows; y++) {
        for (int x = 0; x < img_no_bg.cols; x++) {
            double val = img_no_bg.at<uchar>(y, x);
            if (val > 0) { // 只统计有效光源像素
                m00 += val;
                m10 += x * val;
                m01 += y * val;
            }
        }
    }
    if (m00 < 1e-6) return Point2f(-1, -1); // 无光源
    return Point2f(m10 / m00, m01 / m00);
}

// 主判断函数
bool isFiberAligned(const Mat &src_img, Rect roi_rect, float threshold_pixel = 3.0) {
    // 1. 裁剪光源ROI区域
    Mat roi = src_img(roi_rect);
    // ROI区域的预期几何中心
    Point2f expect_center(roi_rect.width / 2.0f, roi_rect.height / 2.0f);

    // 2. sigma剪切计算背景
    float mean, median, std;
    sigmaClippedStats(roi, 3.0f, 5, mean, median, std);
    // 减去背景
    Mat roi_no_bg;
    roi.convertTo(roi_no_bg, CV_8UC1, 1, -median);

    // 3. 检测光源，计算质心：这里简单处理直接取全ROI的灰度质心，有多个光源可以再加阈值分割
    Point2f actual_center = computeCentroid(roi_no_bg);
    if (actual_center.x < 0) {
        LOG_INFO("No valid light source detected.\n"); //  未检测到有效光源
        return false;
    }

    // 4. 计算偏移量
    float dx = actual_center.x - expect_center.x;
    float dy = actual_center.y - expect_center.y;
    float offset = sqrt(dx*dx + dy*dy);
    LOG_INFO("Light source centroid: (%.2f, %.2f), offset: %.2f pixel\n", actual_center.x, actual_center.y, offset);

    // 5. 判断是否对准
    return offset < threshold_pixel;
}

// 测试入口
// int main() {
//     auto now = std::chrono::system_clock::now();
//     auto time_t_now = std::chrono::system_clock::to_time_t(now);
//     std::tm tm_now = *std::localtime(&time_t_now);
//     char date_buf[32] = {0};
//     strftime(date_buf, sizeof(date_buf), "%Y-%m-%d", &tm_now);
//     std::string date_str(date_buf);
//     // 创建日期文件夹，父目录不存在也会自动创建
//     std::filesystem::path capture_dir = "C:/Users/admin/Desktop/Capture/";
//     std::filesystem::path today_dir = capture_dir / date_str ;
//     // 5. 保存图像, 生成带时间戳的文件名
//     auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    
//     std::string filename = today_dir.string() + "/" + std::to_string(timestamp) + ".png";
//     cout << filename << endl;
    // Mat img = imread("C:/Users/admin/Desktop/Capture/1782867983967.png", IMREAD_GRAYSCALE);
    // if (img.empty()) {
    //     printf("读取图像失败\n");
    //     return -1;
    // }
    // // 替换成你实际的ROI坐标
    // Rect roi_rect(0, 0, 3008, 3008); 
    // bool aligned = isFiberAligned(img, roi_rect, 3.0f);
    // if (aligned) {
    //     printf("Align the optical fiber with the center of the light source.\n");
    // } else {
    //     printf("The optical fiber is off-center and needs to be adjusted.\n");
    // }
//     return 0;
// }

bool isAligned(const Mat& img, const AsiROI& roiInfo) {
    // Mat img = imread(img_file, IMREAD_GRAYSCALE);
    // if (img.empty()) {
    //     printf("read img_file fail\n");
    //     return false;
    // }
    // 替换成你实际的ROI坐标
    Rect roi_rect(roiInfo.x, roiInfo.y, roiInfo.width, roiInfo.height); 
    bool aligned = isFiberAligned(img, roi_rect, 3.0f);
    if (aligned) {
        LOG_INFO("Align the optical fiber with the center of the light source.\n");
        return true;
    }
    LOG_INFO("The optical fiber is off-center and needs to be adjusted.\n");
    return false;
}

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <vector>
#include <cmath>
#include <numeric>
#include "asi_check_aligned.h"

class BackgroundSubtractor {
public:
    // 方法1：角区域估计背景（最常用）
    static std::tuple<double, double> estimateFromCorners(const cv::Mat &frame, int corner_size = 100, bool show_details = true) {
        // ASI533MM: 3008x3008 全分辨率
        int width = frame.cols;  // 3008
        int height = frame.rows; // 3008
        std::cout << "图像尺寸: " << width << "x" << height << std::endl;

        // 确保角区域大小合理: 不能太大（避免包含光斑），不能太小（样本不够）
        corner_size = std::min(corner_size, std::min(width, height) / 4); // 最大752
        corner_size = std::max(corner_size, 50);                          // 最小50

        // 定义四个角区域（留有边距，避免边缘效应）
        int margin = 10; // 边缘留白，避免传感器边缘异常像素

        std::vector<cv::Rect> corners = {
            cv::Rect(margin, margin, corner_size, corner_size),                                              // 左上角=0
            cv::Rect(width - corner_size - margin, margin, corner_size, corner_size),                        // 右上角=1
            cv::Rect(margin, height - corner_size - margin, corner_size, corner_size),                       // 左下角=2
            cv::Rect(width - corner_size - margin, height - corner_size - margin, corner_size, corner_size)  // 右下角=3
        };

        // 验证所有角区域都在图像范围内
        for (const auto &corner : corners) {
            if (corner.x < 0 || corner.y < 0 || corner.x + corner.width > width || corner.y + corner.height > height) {
                std::cerr << "错误: 角区域超出图像范围" << std::endl;
                return {0.0, 0.0};
            }
        }

        // 计算每个角的统计信息
        std::vector<double> corner_means;
        std::vector<double> corner_stds;

        for (size_t i = 0; i < corners.size(); i++) {
            cv::Mat roi = frame(corners[i]);
            cv::Scalar mean, stddev;
            cv::meanStdDev(roi, mean, stddev);

            corner_means.push_back(mean[0]);
            corner_stds.push_back(stddev[0]);

            if (show_details) {
                std::cout << "角" << i << " (" << corners[i].x << "," << corners[i].y << "): 均值=" << mean[0] << ", 标准差=" << stddev[0] << std::endl;
            }
        }

        // 检查四个角的一致性（如果不一致，说明光照不均匀或有光污染）
        double mean_of_means = std::accumulate(corner_means.begin(), corner_means.end(), 0.0) / corner_means.size();
        double std_of_means = 0.0;
        for (double m : corner_means) {
            std_of_means += (m - mean_of_means) * (m - mean_of_means);
        }
        std_of_means = std::sqrt(std_of_means / corner_means.size());

        // 去除异常角区域（如果某个角的均值偏离其他角超过2倍标准差）
        double total_mean = 0;
        double total_std = 0;
        int valid_corners = 0;

        for (size_t i = 0; i < corners.size(); i++) {
            if (std::abs(corner_means[i] - mean_of_means) <= 2 * std_of_means || corner_means.size() <= 2) {
                total_mean += corner_means[i];
                total_std += corner_stds[i];
                valid_corners++;
            }
            else if (show_details) {
                std::cout << "角" << i << " 被排除（异常值）" << std::endl;
            }
        }

        if (valid_corners == 0) {
            std::cerr << "错误: 所有角区域都被排除" << std::endl;
            return {0.0, 0.0};
        }

        double bg_mean = total_mean / valid_corners;
        double bg_std = total_std / valid_corners;

        if (show_details) {
            std::cout << "\n=== 背景估计（角区域法） ===" << std::endl;
            std::cout << "图像尺寸: " << width << "x" << height << std::endl;
            std::cout << "角区域大小: " << corner_size << "x" << corner_size
                      << " (总样本: " << (corner_size * corner_size * valid_corners)
                      << " 像素)" << std::endl;
            std::cout << "有效角数量: " << valid_corners << "/4" << std::endl;
            std::cout << "背景均值: " << std::fixed << std::setprecision(2) << bg_mean << std::endl;
            std::cout << "背景标准差: " << std::setprecision(2) << bg_std << std::endl;
            
            std::cout << "角间差异: " << std::setprecision(2) << std_of_means
                      << " (" << (mean_of_means > 0 ? std_of_means / mean_of_means * 100 : 0)
                      << "%)" << std::endl;

            // 推荐阈值
            std::cout << "\n推荐阈值:" << std::endl;
            std::cout << "  保守 (均值+5σ): " << (bg_mean + 5 * bg_std) << std::endl;
            std::cout << "  标准 (均值+3σ): " << (bg_mean + 3 * bg_std) << std::endl;
            std::cout << "  宽松 (均值+2σ): " << (bg_mean + 2 * bg_std) << std::endl;

            // 检测背景质量
            if (std_of_means / mean_of_means > 0.2) {
                std::cout << "\n⚠️ 警告: 背景不均匀（角间差异>20%），可能存在杂散光" << std::endl;
            }
            if (bg_std > 10) {
                std::cout << "⚠️ 警告: 背景噪声较大（σ>" << bg_std << "），建议降低增益" << std::endl;
            }
        }

        return {bg_mean, bg_std};
    }

    // 方法2：全局直方图估计（适用于均匀背景）
    static double estimateFromHistogram(const cv::Mat& frame, bool show_details = true) {
        // 计算直方图
        int histSize = 256;
        float range[] = {0, 256};
        const float* histRange = {range};
        cv::Mat hist;
        cv::calcHist(&frame, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange);
        
        // 找到直方图的第一个峰值（通常是背景）
        double max_val = 0;
        int peak_bin = 0;
        
        // 跳过可能的零值
        for (int i = 1; i < 200; i++) {  // 只查找0-200范围，避免光斑峰
            if (hist.at<float>(i) > max_val) {
                max_val = hist.at<float>(i);
                peak_bin = i;
            }
        }
        
        // 背景均值近似为直方图峰值位置
        double bg_mean = peak_bin;
        
        if (show_details) {
            std::cout << "=== 背景估计（直方图法） ===" << std::endl;
            std::cout << "直方图峰值位于灰度值: " << peak_bin << std::endl;
            std::cout << "估计背景均值: " << bg_mean << std::endl;
        }
        
        return bg_mean;
    }
    
    // 方法3：最小强度估计（适用于暗背景）
    static double estimateFromMinimum(const cv::Mat& frame, bool show_details = true) {
        double min_val, max_val;
        cv::Point min_loc, max_loc;
        cv::minMaxLoc(frame, &min_val, &max_val, &min_loc, &max_loc);
        
        // 使用1%分位数作为背景（避免单个坏点的影响）
        cv::Mat flat = frame.reshape(1, 1);
        cv::Mat sorted;
        cv::sort(flat, sorted, cv::SORT_ASCENDING);
        
        int idx = sorted.cols * 0.01;  // 1%分位数
        double bg_mean = sorted.at<unsigned char>(0, idx);
        
        if (show_details) {
            std::cout << "=== 背景估计（最小值法） ===" << std::endl;
            std::cout << "图像最小值: " << min_val << std::endl;
            std::cout << "1%分位数（背景估计）: " << bg_mean << std::endl;
        }
        
        return bg_mean;
    }
    
    // 方法4：中值滤波估计背景（适用于不均匀背景）
    static cv::Mat estimateBackgroundMap(const cv::Mat& frame, int kernel_size = 51, bool show_details = true) {
        // 使用大核中值滤波估计背景
        cv::Mat background;
        cv::medianBlur(frame, background, kernel_size);
        
        if (show_details) {
            std::cout << "=== 背景估计（中值滤波法） ===" << std::endl;
            std::cout << "滤波核大小: " << kernel_size << "x" << kernel_size << std::endl;
            
            double bg_mean = cv::mean(background)[0];
            std::cout << "背景图均值: " << bg_mean << std::endl;
        }
        
        return background;
    }
    
    // 方法5：形态学开运算估计背景
    static cv::Mat estimateBackgroundMorph(const cv::Mat& frame, int kernel_size = 31, bool show_details = true) {
        cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, 
                                                   cv::Size(kernel_size, kernel_size));
        cv::Mat background;
        cv::morphologyEx(frame, background, cv::MORPH_OPEN, kernel);
        
        if (show_details) {
            std::cout << "=== 背景估计（形态学法） ===" << std::endl;
            std::cout << "结构元素大小: " << kernel_size << "x" << kernel_size << std::endl;
            
            double bg_mean = cv::mean(background)[0];
            std::cout << "背景图均值: " << bg_mean << std::endl;
        }
        
        return background;
    }
};

class SpotAreaCalculator {
public:
    // 方法1：基于自适应阈值的轮廓检测（推荐）
    static double calculateByContour(const cv::Mat& frame, double threshold_ratio = 0.3, bool show_details = true) {
        // 找到图像峰值
        double min_val, max_val;
        cv::Point min_loc, max_loc;
        cv::minMaxLoc(frame, &min_val, &max_val, &min_loc, &max_loc);
        
        if (max_val < 10) {
            if (show_details) std::cout << "光斑太暗，无法检测" << std::endl;
            return 0.0;
        }
        
        // 计算自适应阈值
        double threshold = max_val * threshold_ratio;
        threshold = std::max(threshold, 5.0);  // 最小阈值5
        threshold = std::min(threshold, 250.0); // 最大阈值250
        
        if (show_details) {
            std::cout << "峰值强度: " << max_val << std::endl;
            std::cout << "使用阈值: " << threshold << " (峰值的 " 
                      << (threshold_ratio * 100) << "%)" << std::endl;
        }
        
        // 二值化
        cv::Mat binary;
        cv::threshold(frame, binary, threshold, 255, cv::THRESH_BINARY);
        
        // 形态学操作：去除噪声，连接断裂区域
        cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3));
        cv::Mat cleaned;
        cv::morphologyEx(binary, cleaned, cv::MORPH_CLOSE, kernel);
        cv::morphologyEx(cleaned, cleaned, cv::MORPH_OPEN, kernel);
        
        // 查找轮廓
        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(cleaned, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        
        if (contours.empty()) {
            if (show_details) std::cout << "未找到轮廓" << std::endl;
            return 0.0;
        }
        
        // 找到包含峰值点的最大轮廓
        double max_area = 0;
        int best_idx = -1;
        
        for (size_t i = 0; i < contours.size(); i++) {
            double area = cv::contourArea(contours[i]);
            cv::Rect bbox = cv::boundingRect(contours[i]);
            
            // 检查是否包含峰值点
            if (bbox.contains(max_loc) && area > max_area) {
                max_area = area;
                best_idx = i;
            }
        }
        
        // 如果没有包含峰值的轮廓，选择最大的轮廓
        if (best_idx < 0 && !contours.empty()) {
            auto it = std::max_element(contours.begin(), contours.end(),
                [](const auto& a, const auto& b) {
                    return cv::contourArea(a) < cv::contourArea(b);
                });
            best_idx = std::distance(contours.begin(), it);
            max_area = cv::contourArea(contours[best_idx]);
        }
        
        if (show_details && best_idx >= 0) {
            cv::Rect bbox = cv::boundingRect(contours[best_idx]);
            std::cout << "光斑边界框: " << bbox.width << "x" << bbox.height 
                      << " @ (" << bbox.x << "," << bbox.y << ")" << std::endl;
            std::cout << "光斑面积: " << max_area << " 像素" << std::endl;
            
            // 计算等效直径
            double diameter = std::sqrt(4 * max_area / CV_PI);
            std::cout << "等效直径: " << diameter << " 像素" << std::endl;
        }
        
        return max_area;
    }
    
    // 方法2：基于固定阈值的像素计数（适用于明确知道阈值的情况）
    static double calculateByThreshold(const cv::Mat& frame, double threshold, bool show_details = true) {
        cv::Mat binary;
        cv::threshold(frame, binary, threshold, 255, cv::THRESH_BINARY);
        
        int non_zero = cv::countNonZero(binary);
        
        if (show_details) {
            std::cout << "固定阈值: " << threshold << std::endl;
            std::cout << "高于阈值的像素数: " << non_zero << std::endl;
        }
        
        return static_cast<double>(non_zero);
    }
    
    // 方法3：基于峰值邻域的积分（适用于极小光斑）
    static double calculateByPeakRegion(const cv::Mat& frame, double intensity_ratio = 0.5, bool show_details = true) {
        double min_val, max_val;
        cv::Point min_loc, max_loc;
        cv::minMaxLoc(frame, &min_val, &max_val, &min_loc, &max_loc);
        
        if (max_val < 10) return 0.0;
        
        // 从峰值开始，找出所有高于峰值一定比例的连通像素
        double threshold = max_val * intensity_ratio;
        cv::Mat binary;
        cv::threshold(frame, binary, threshold, 255, cv::THRESH_BINARY);
        
        // 使用洪水填充从峰值点开始
        cv::Mat mask = cv::Mat::zeros(frame.rows + 2, frame.cols + 2, CV_8UC1);
        cv::Mat filled = binary.clone();
        
        // 在峰值点进行洪水填充
        cv::floodFill(filled, mask, max_loc, cv::Scalar(128), nullptr, 
                     cv::Scalar(0), cv::Scalar(0), 
                     cv::FLOODFILL_FIXED_RANGE | cv::FLOODFILL_MASK_ONLY);
        
        // 计算mask中的像素数
        int spot_pixels = cv::countNonZero(mask(cv::Rect(1, 1, frame.cols, frame.rows)));
        
        if (show_details) {
            std::cout << "峰值邻域法" << std::endl;
            std::cout << "峰值: " << max_val << " @ (" << max_loc.x << "," << max_loc.y << ")" << std::endl;
            std::cout << "使用阈值比例: " << intensity_ratio << std::endl;
            std::cout << "检测到的像素数: " << spot_pixels << std::endl;
        }
        
        return static_cast<double>(spot_pixels);
    }
    
    // 方法4：高斯拟合（最精确，适用于圆形光斑）
    static std::tuple<double, bool> calculateByGaussianFit(const cv::Mat& frame, bool show_details = true) {
        // 1. 估计背景
        double bg_level, bg_std;  // 背景的均值、标准差
        std::tie(bg_level, bg_std) = BackgroundSubtractor::estimateFromCorners(frame, 100, show_details);

        // 2. 创建背景减除图像
        cv::Mat bg_subtracted;
        frame.convertTo(bg_subtracted, CV_32F);     // 将图像从整数类型转为浮点类型，以便进行精确的减法、加法等运算
        bg_subtracted -= bg_level;                  // 减去背景值
        bg_subtracted = cv::max(bg_subtracted, 0);  // 裁剪负值

        // 3. 找到减除背景后的峰值
        double min_val, max_val;
        cv::Point min_loc, max_loc;  // 减除背景后的最小、最大灰度值的位置
        cv::minMaxLoc(bg_subtracted, &min_val, &max_val, &min_loc, &max_loc);

        double min_val1, max_val1;
        cv::Point min_loc1, max_loc1;  // 减除背景前的最小、最大灰度值的位置
        cv::minMaxLoc(frame, &min_val1, &max_val1, &min_loc1, &max_loc1);
        
        if (max_val < 10) {
            std::cout << "背景扣除后峰值过小 (" << max_val << ")，无法拟合" << std::endl;
            return {0.0, false};
        }
        
        // 提取峰值周围区域用于拟合
        int roi_size = 21;        // 21x21区域: 21×21 是一个经验上的折中：足够大以包含光斑核心，又足够小以避免太多无关背景。
        int half = roi_size / 2;
        
        int x_start = std::max(0, max_loc.x - half);
        int y_start = std::max(0, max_loc.y - half);
        int x_end = std::min(frame.cols, max_loc.x + half + 1);
        int y_end = std::min(frame.rows, max_loc.y + half + 1);
        
        cv::Mat roi = bg_subtracted(cv::Rect(x_start, y_start, x_end - x_start, y_end - y_start));
        
        // 准备高斯拟合数据
        std::vector<cv::Point2d> points;
        std::vector<double> values;
        
        for (int y = 0; y < roi.rows; y++) {
            for (int x = 0; x < roi.cols; x++) {
                double val = roi.at<unsigned char>(y, x);
                if (val > max_val * 0.1) {  // 只用高于峰值10%的点
                    points.push_back(cv::Point2d(x, y));
                    values.push_back(std::log(std::max(val, 1.0)));
                }
            }
        }
        
        if (points.size() < 10) {
            if (show_details) std::cout << "数据点不足，无法进行高斯拟合" << std::endl;
            return {calculateByContour(frame, 0.3, false), false};
        }
        
        // 简化的2D高斯拟合：ln(I) = ln(A) - ((x-x0)²/(2σx²) + (y-y0)²/(2σy²))
        // 这里使用简化的方法：分别拟合x和y方向
        
        // 计算加权中心（一阶矩）
        double sum_w = 0, sum_wx = 0, sum_wy = 0;
        for (size_t i = 0; i < points.size(); i++) {
            double w = std::exp(values[i]);
            sum_w += w;
            sum_wx += w * points[i].x;
            sum_wy += w * points[i].y;
        }
        
        double cx = sum_wx / sum_w;
        double cy = sum_wy / sum_w;
        double dx = cx - frame.cols / 2.0;
        double dy = cy - frame.rows / 2.0;

        
        // 计算sigma（二阶矩）
        double sum_wx2 = 0, sum_wy2 = 0;
        for (size_t i = 0; i < points.size(); i++) {
            double w = std::exp(values[i]);
            sum_wx2 += w * (points[i].x - cx) * (points[i].x - cx);
            sum_wy2 += w * (points[i].y - cy) * (points[i].y - cy);
        }
        
        double sigma_x = std::sqrt(sum_wx2 / sum_w);
        double sigma_y = std::sqrt(sum_wy2 / sum_w);
        // 防止奇异（最小 sigma 设为 0.5 像素）
        if (sigma_x < 0.5) sigma_x = 0.5;
        if (sigma_y < 0.5) sigma_y = 0.5;
        
        // 高斯光束面积 = π * wx * wy，其中 w = 2σ（半径）
        double wx = 2 * sigma_x;  // 1/e²半径
        double wy = 2 * sigma_y;
        double gaussian_area = CV_PI * wx * wy;
        
        // 或者使用FWHM面积：π * FWHM_x * FWHM_y / (4 * ln(2))
        double fwhm_x = 2 * sigma_x * std::sqrt(2 * std::log(2));
        double fwhm_y = 2 * sigma_y * std::sqrt(2 * std::log(2));
        double fwhm_area = CV_PI * fwhm_x * fwhm_y / (4 * std::log(2));

        double ratio = std::min(sigma_x, sigma_y) / std::max(sigma_x, sigma_y);
        double sigma_avg = (sigma_x + sigma_y) / 2.0;
        double dist = std::sqrt(dx*dx + dy*dy);
        double score = calculateScore(max_val, sigma_avg, ratio, dist);
        
        if (show_details) {
            std::cout << "\n=== 高斯拟合法 ===" << std::endl;
            std::cout << "中心: (" << (cx + x_start) << ", " << (cy + y_start) << ")" << std::endl;
            std::cout << "原始峰值强度: " << max_val1 << ", 背景扣除后峰值强度: "<< max_val << std::endl;
            std::cout << "σx: " << sigma_x << ", σy: " << sigma_y << " 像素" << std::endl;
            std::cout << "1/e²半径: wx=" << wx << ", wy=" << wy << " 像素" << std::endl;
            std::cout << "高斯面积(1/e²): " << gaussian_area << " 像素²" << std::endl;
            std::cout << "FWHM面积: " << fwhm_area << " 像素²" << std::endl;
            std::cout << "得分: " << score << ", 是否对准: " <<(score >= 85 ? "Yes": "No") <<std::endl;
        }        
        return {gaussian_area, score >= 85};
    }
    
    // 方法5：多阈值综合（最稳定，推荐用于实际应用）
    static double calculateRobust(const cv::Mat& frame, bool show_details = true) {
        double min_val, max_val;
        cv::Point min_loc, max_loc;
        cv::minMaxLoc(frame, &min_val, &max_val, &min_loc, &max_loc);
        
        if (max_val < 10) return 0.0;
        
        // 使用多个阈值比例计算面积，取中位数
        std::vector<double> thresholds = {0.1, 0.2, 0.3, 0.4, 0.5};
        std::vector<double> areas;
        
        for (double ratio : thresholds) {
            double thresh = max_val * ratio;
            if (thresh < 5) thresh = 5;
            
            cv::Mat binary;
            cv::threshold(frame, binary, thresh, 255, cv::THRESH_BINARY);
            
            std::vector<std::vector<cv::Point>> contours;
            cv::findContours(binary, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
            
            double max_contour_area = 0;
            for (const auto& contour : contours) {
                cv::Rect bbox = cv::boundingRect(contour);
                if (bbox.contains(max_loc)) {
                    double area = cv::contourArea(contour);
                    if (area > max_contour_area) {
                        max_contour_area = area;
                    }
                }
            }
            
            if (max_contour_area > 0) {
                areas.push_back(max_contour_area);
            }
            
            if (show_details) {
                std::cout << "阈值比例 " << ratio << " (实际阈值=" << thresh 
                          << "): 面积=" << max_contour_area << std::endl;
            }
        }
        
        if (areas.empty()) return 0.0;
        
        // 计算中位数
        std::sort(areas.begin(), areas.end());
        double median_area = areas[areas.size() / 2];
        
        if (show_details) {
            std::cout << "多阈值综合结果: " << median_area << " 像素² (中位数)" << std::endl;
        }
        
        return median_area;
    }
};

// 便捷函数：直接计算光斑面积
// double calculateSpotArea(const cv::Mat& frame, int method = 5, bool show_details = true) {   // 默认使用鲁棒方法
//     switch (method) {
//         case 1:
//             return SpotAreaCalculator::calculateByContour(frame, 0.3, show_details);
//         case 2:
//             return SpotAreaCalculator::calculateByThreshold(frame, 50, show_details);
//         case 3:
//             return SpotAreaCalculator::calculateByPeakRegion(frame, 0.5, show_details);
//         case 4:
//             return SpotAreaCalculator::calculateByGaussianFit(frame, show_details);
//         case 5:
//             return SpotAreaCalculator::calculateRobust(frame, show_details);
//         default:
//             return SpotAreaCalculator::calculateRobust(frame, show_details);
//     }
// }

double calculateScore(double peak, double sigma_avg, double ratio, double dist) {
    // 1. 峰值强度（40 分）：越高越好，目标 100~120
    double peak_score = 40 * (peak - 20) / 80.0; // 20 < peak < 100
    if (peak >= 100) {
        peak_score = 40;
    }
    std::cout << "峰值强度得分（占40分）: " << peak_score << std::endl;

    // 2. 光斑尺寸（25 分）：σ 越小越好，目标 σ ≤ 6.5 像素
    double sigma_score = 25 * (1.0 - (sigma_avg - 6.5) / 8.5);  // 6.5 < sigma_avg < 15
    if (sigma_avg <= 6.5) {
        sigma_score = 25;
    }
    std::cout << "光斑尺寸得分（占25分）: " << sigma_score << std::endl;

    // 3. 圆度（25 分）：σx/σy 越接近 1 越好
    //double ratio = std::min(sigma_x, sigma_y) / std::max(sigma_x, sigma_y);
    double radio_score = 25 * ratio;
    std::cout << "光斑圆度得分（占25分）: " << radio_score << std::endl;

    // 4. 中心偏移（10 分）：距离中心越近越好
    double max_dist = 500;  // 最大容忍偏移
    double dist_score = 10 * (1.0 - std::min(dist, max_dist) / max_dist);  // dist > 10
    if (dist <= 10) {
        dist_score = 10;
    }
    std::cout << "中心偏移得分（占10分）: " << dist_score << std::endl;
    return (peak_score + sigma_score + radio_score + dist_score);
}

// 使用示例
bool isAligned(cv::Mat frame) {
    std::cout << "=== 光斑面积计算 ===" << std::endl;
    std::cout << "图像尺寸: " << frame.cols << "x" << frame.rows << std::endl;
    
    double area;
    bool isAligned;
    std::tie(area, isAligned)= SpotAreaCalculator::calculateByGaussianFit(frame, true);     // 高斯拟合法
    
    // 转换为物理尺寸（如果知道像素尺寸）
    double pixel_size_um = 3.76;  // ASI533MM像素尺寸
    double area_um2 = area * pixel_size_um * pixel_size_um;
    double diameter_um = std::sqrt(4 * area_um2 / CV_PI);
    
    std::cout << "\n=== 物理尺寸 ===" << std::endl;
    std::cout << "像素面积: " << area << " 像素²" << std::endl;
    std::cout << "物理面积: " << area_um2 << " μm²" << std::endl;
    std::cout << "等效直径: " << diameter_um << " μm" << std::endl;
    
    return isAligned;
}
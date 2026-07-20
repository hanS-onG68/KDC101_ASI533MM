#pragma once

struct AlignmentMetrics {
    double peak_intensity;          // 峰值强度 (0-255)
    double total_power;             // 总光功率（像素值总和）
    double spot_area;               // 光斑面积（像素数）
    double circularity;             // 圆度 (0-1, 1为完美圆形)
    double centroid_x, centroid_y;  // 光斑质心
    double uniformity;              // 能量分布均匀性
    bool is_aligned;                // 综合判断结果
    double score;                   // 对准评分 (0-100)
};

bool isAligned(cv::Mat frame);
double calculateScore(double peak, double sigma_avg, double ratio, double dist);
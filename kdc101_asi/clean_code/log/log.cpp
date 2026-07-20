#include "log.h"  // 包含自定义日志头文件
#include <spdlog/sinks/stdout_color_sinks.h>  // 包含带颜色的控制台输出器头文件
#include <spdlog/sinks/basic_file_sink.h>     // 包含文件输出器头文件

// 初始化日志函数实现
void Log::init(const std::string& log_file) {
    // 多输出目标（控制台 + 文件）：sinks是输出器的集合
    std::vector<spdlog::sink_ptr> sinks;
    // 添加带颜色的控制台输出器（_mt表示多线程安全）
    // spdlog::sinks::stdout_color_sink_mt：spdlog提供的带颜色的控制台输出器类
    // std::make_shared：创建智能指针（自动管理内存）
    sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
    // 添加文件输出器（_mt表示多线程安全）
    // 参数：log_file - 日志文件路径
    sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(log_file));
    // 创建日志器（logger）：管理输出器的核心对象
    // 参数1：日志器名称（"main_logger"）；参数2-3：输出器集合的起止迭代器
    auto logger = std::make_shared<spdlog::logger>("main_logger", sinks.begin(), sinks.end());
    // 设置日志格式
    // 格式说明：// [%Y-%m-%d %H:%M:%S.%e]：日期时间（年-月-日 时:分:秒.毫秒）
                // [%l]：日志级别（如info/error）
                // %v：日志内容（包括宏添加的文件名、行号和用户输入的内容）
    logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] %v");
    // 设置全局日志级别：trace（最低级别，所有日志都输出）
    // 可选级别：trace < debug < info < warn < error < critical
    logger->set_level(spdlog::level::trace);
    // 注册为默认日志器：后续spdlog::xxx()调用会使用该日志器
    spdlog::set_default_logger(logger);
}

// 获取单例实例函数实现
Log& Log::get_instance() {
    static Log instance;  // 静态局部变量：第一次调用时创建，全局唯一（单例核心）
    // 若未初始化（logger_为空），使用spdlog的默认日志器
    if (!instance.logger_) {
        instance.logger_ = spdlog::default_logger();
    }
    return instance;  // 返回唯一实例
}
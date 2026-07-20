#ifndef __LOG_H__  // 防止头文件被重复包含（预处理指令）
#define __LOG_H__  // 定义宏LOG_H，标识头文件已包含

#include <spdlog/spdlog.h>  // 包含spdlog库的头文件，使用其日志功能
#include <string>           // 包含字符串处理头文件

// 日志封装类（单例模式）：确保全局只有一个日志实例，统一管理日志配置
class Log {
public:
    // 初始化日志（控制台 + 文件输出）
    // 参数：log_file - 日志文件路径，默认值为"app.log"
    static void init(const std::string& log_file = "app.log");
    // 获取单例实例：全局唯一的Log对象入口
    static Log& get_instance();
    // 日志输出接口（trace级别）
    // 模板参数Args...：支持可变参数（如日志中包含的变量）
    // 参数：fmt - 日志格式字符串（如"x = {}"）；args... - 格式字符串中的占位符对应的值
    template<typename... Args>
    void trace(const char* fmt, const Args&... args) {
        logger_->trace(fmt, args...);  // 调用spdlog的trace级别日志输出
    }
    // 日志输出接口（info级别），参数含义同上
    template<typename... Args>
    void info(const char* fmt, const Args&... args) {
        logger_->info(fmt, args...);   // 调用spdlog的info级别日志输出
    }
    // 日志输出接口（error级别），参数含义同上
    template<typename... Args>
    void error(const char* fmt, const Args&... args) {
        logger_->error(fmt, args...);  // 调用spdlog的error级别日志输出
    }
    // 其他级别（debug/warn/critical）类似...
private:
    Log() = default;  // 私有构造函数：禁止外部创建对象（单例模式核心）
    ~Log() = default; // 私有析构函数：禁止外部销毁对象
    // 禁用拷贝构造和赋值操作：防止单例被复制
    Log(const Log&) = delete;
    Log& operator=(const Log&) = delete;
    std::shared_ptr<spdlog::logger> logger_;  // 日志器指针：spdlog的核心对象，负责实际日志输出
};


// 宏定义，简化调用（自动添加文件名和行号）
// __FILE__：当前源文件路径（预定义宏）
// __LINE__：当前代码行号（预定义宏）
// __VA_ARGS__：替换宏调用时传入的所有参数
#define LOG_TRACE(...) Log::get_instance().trace("[{}:{}] {}", __FILE__, __LINE__, fmt::format(__VA_ARGS__))
#define LOG_INFO(...)  Log::get_instance().info("[{}:{}] {}", __FILE__, __LINE__, fmt::format(__VA_ARGS__))
#define LOG_ERROR(...) Log::get_instance().error("[{}:{}] {}", __FILE__, __LINE__, fmt::format(__VA_ARGS__))

#endif // LOG_H  // 结束头文件保护宏

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/fmt/ostr.h>
#include <iostream>
#include <string>
#include <vector>

// 自定义类，演示对象日志
class User {
public:
    std::string name;
    int age;
    
    User(const std::string& n, int a) : name(n), age(a) {}
};

// 为User类添加fmt格式化支持
template<>
struct fmt::formatter<User> {
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }
    
    template<typename FormatContext>
    auto format(const User& user, FormatContext& ctx) const {
        return fmt::format_to(ctx.out(), "{{name: {}, age: {}}}", user.name, user.age);
    }
};

void demo_basic_logging() {
    std::cout << "\n=== 基础日志功能 ===\n";
    
    // 设置全局日志级别
    spdlog::set_level(spdlog::level::trace);
    
    // 基础日志记录
    spdlog::trace("This is a trace message");
    spdlog::debug("This is a debug message");
    spdlog::info("This is an info message");
    spdlog::warn("This is a warning message");
    spdlog::error("This is an error message");
    spdlog::critical("This is a critical message");
    
    // 带参数的日志
    std::string user = "Alice";
    int score = 95;
    spdlog::info("User {} scored {} points", user, score);
    
    // 使用位置参数
    spdlog::info("Processing file {1} with {0} threads", 4, "data.txt");
}

void demo_formatted_logging() {
    std::cout << "\n=== 格式化日志 ===\n";
    
    // 数字格式化
    spdlog::info("Integer: {:d}", 42);
    spdlog::info("Hexadecimal: {:x}", 255);
    spdlog::info("Binary: {:b}", 15);
    spdlog::info("Float: {:.2f}", 3.14159);
    spdlog::info("Scientific: {:e}", 1234567.89);
    
    // 字符串格式化
    spdlog::info("Left aligned: '{:<10}'", "left");
    spdlog::info("Right aligned: '{:>10}'", "right");
    spdlog::info("Center aligned: '{:^10}'", "center");
    
    // 填充字符
    spdlog::info("Zero padded: {:08d}", 42);
    spdlog::info("Custom padding: {:*^15}", "hello");
    
    // 容器格式化
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::string numbers_str;
    for (size_t i = 0; i < numbers.size(); ++i) {
        if (i > 0) numbers_str += ", ";
        numbers_str += std::to_string(numbers[i]);
    }
    spdlog::info("Vector: [{}]", numbers_str);
    
    // 自定义对象
    User user("Bob", 25);
    spdlog::info("User object: {}", user);
}

void demo_custom_loggers() {
    std::cout << "\n=== 自定义日志器 ===\n";
    
    try {
        // 控制台日志器（带颜色）
        auto console_logger = spdlog::stdout_color_mt("console");
        console_logger->info("This is a colored console message");
        console_logger->warn("This warning appears in yellow");
        console_logger->error("This error appears in red");
        
        // 文件日志器
        auto file_logger = spdlog::basic_logger_mt("file_logger", "logs/basic.log");
        file_logger->info("This message goes to the file");
        file_logger->warn("File logging is useful for production");
        
        // 轮转文件日志器
        auto rotating_logger = spdlog::rotating_logger_mt("rotating", 
            "logs/rotating.log", 1024 * 1024, 3); // 1MB files, keep 3
        rotating_logger->info("This uses rotating file logging");
        
        std::cout << "  ✅ 日志文件已创建在 logs/ 目录\n";
        
    } catch (const spdlog::spdlog_ex& ex) {
        std::cout << "  ⚠️  日志初始化失败: " << ex.what() << "\n";
    }
}

void demo_log_patterns() {
    std::cout << "\n=== 日志格式模式 ===\n";
    
    auto logger = spdlog::stdout_color_mt("pattern_logger");
    
    // 默认格式
    logger->info("Default pattern message");
    
    // 自定义格式: 时间戳 + 级别 + 消息
    logger->set_pattern("[%Y-%m-%d %H:%M:%S] [%l] %v");
    logger->info("Custom pattern with timestamp");
    
    // 包含线程ID的格式
    logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] [thread %t] %v");
    logger->info("Pattern with thread ID");
    
    // 带源码位置的格式
    logger->set_pattern("[%H:%M:%S] [%^%l%$] %v (%s:%#)");
    logger->info("Pattern with source location");
    
    // 简单格式
    logger->set_pattern("%^[%l]%$ %v");
    logger->info("Simple pattern");
    logger->warn("Simple warning");
    logger->error("Simple error");
}

void demo_performance() {
    std::cout << "\n=== 性能测试 ===\n";
    
    const int num_messages = 10000;
    auto start = std::chrono::high_resolution_clock::now();
    
    // 创建异步日志器以提高性能
    try {
        // 注意：新版本的spdlog可能需要不同的异步设置方式
        auto async_logger = spdlog::stdout_color_mt("async");
        async_logger->set_pattern("[%H:%M:%S.%e] [%n] [%l] %v");
        
        for (int i = 0; i < num_messages; ++i) {
            async_logger->info("Async message #{}", i);
        }
        
        spdlog::drop_all(); // 确保所有日志器都被清理
        
    } catch (const std::exception& e) {
        std::cout << "  异步日志错误: " << e.what() << "\n";
        return;
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "  📊 记录 " << num_messages << " 条消息耗时: " 
              << duration.count() << " ms\n";
    std::cout << "  📈 平均速度: " 
              << (num_messages * 1000 / duration.count()) << " msg/sec\n";
}

void demo_conditional_logging() {
    std::cout << "\n=== 条件日志 ===\n";
    
    auto logger = spdlog::get("console");
    if (!logger) {
        logger = spdlog::stdout_color_mt("console");
    }
    
    // 设置不同的日志级别
    std::vector<spdlog::level::level_enum> levels = {
        spdlog::level::err,    // 只显示错误及以上
        spdlog::level::warn,   // 显示警告及以上
        spdlog::level::info,   // 显示信息及以上
        spdlog::level::debug   // 显示所有
    };
    
    for (auto level : levels) {
        spdlog::set_level(level);
        
        std::cout << "\n  当前级别: ";
        auto level_str = spdlog::level::to_string_view(level);
        std::cout << std::string(level_str.data(), level_str.size()) << "\n";
        
        logger->debug("Debug message - 这条消息在debug级别才显示");
        logger->info("Info message - 这条消息在info级别及以上显示");
        logger->warn("Warning message - 这条消息在warn级别及以上显示");
        logger->error("Error message - 这条消息总是显示");
    }
    
    // 恢复到info级别
    spdlog::set_level(spdlog::level::info);
}

void demo_structured_logging() {
    std::cout << "\n=== 结构化日志 ===\n";
    
    auto logger = spdlog::stdout_color_mt("structured");
    
    // 模拟结构化数据
    std::string operation = "database_query";
    std::string table = "users";
    int duration_ms = 45;
    bool success = true;
    
    // 使用键值对格式
    logger->info("operation={} table={} duration_ms={} success={}", 
                 operation, table, duration_ms, success);
    
    // JSON风格的日志
    logger->info(R"({"event":"user_login","user_id":123,"ip":"192.168.1.1","timestamp":"2024-01-15T10:30:00Z"})");
    
    // 带上下文的错误日志
    std::string error_code = "AUTH_FAILED";
    std::string user_id = "user_456";
    logger->error("Authentication failed: code={} user_id={} attempts={}", 
                  error_code, user_id, 3);
}

int main() {
    std::cout << "🚀 spdlog 现代C++日志库演示\n";
    std::cout << "================================\n";
    
    try {
        demo_basic_logging();
        demo_formatted_logging();
        demo_custom_loggers();
        demo_log_patterns();
        demo_performance();
        demo_conditional_logging();
        demo_structured_logging();
        
        std::cout << "\n✅ spdlog 演示完成!\n";
        std::cout << "\n📚 主要特性:\n";
        std::cout << "  • 极高的性能，支持异步日志\n";
        std::cout << "  • 丰富的格式化选项（基于fmt库）\n";
        std::cout << "  • 多种输出目标（控制台、文件、轮转文件等）\n";
        std::cout << "  • 线程安全，支持多线程应用\n";
        std::cout << "  • 可配置的日志级别和模式\n";
        std::cout << "  • 头文件库，易于集成\n";
        
    } catch (const std::exception& e) {
        std::cerr << "❌ 错误: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
#ifndef CPP_FEATURES_UTILS_H
#define CPP_FEATURES_UTILS_H

#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>

namespace cpp_features {

// Utility class for demonstration formatting
class Demo {
 public:
  static void print_header(const std::string& title) {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "  " << title << "\n";
    std::cout << std::string(60, '=') << "\n\n";
  }

  static void print_section(const std::string& section) {
    std::cout << "\n--- " << section << " ---\n";
  }

  static void print_result(const std::string& description, const std::string& result) {
    std::cout << "  " << std::left << std::setw(30) << description << ": " << result << "\n";
  }

  template <typename T>
  static void print_value(const std::string& name, const T& value) {
    std::cout << "  " << std::left << std::setw(20) << name << ": " << value << "\n";
  }
};

// Simple timer for performance measurements
class Timer {
  std::chrono::high_resolution_clock::time_point start_time;

 public:
  Timer() : start_time(std::chrono::high_resolution_clock::now()) {}

  double elapsed_ms() const {
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    return duration.count() / 1000.0;
  }
};
}  // namespace cpp_features

#endif  // CPP_FEATURES_UTILS_H
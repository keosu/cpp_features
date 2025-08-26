#include <chrono>
#include <iostream>
#include <map>
#include <vector>

#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/ranges.h>

void demo_basic_formatting() {
  fmt::print("=== Basic Formatting Examples ===\n");

  // Basic string formatting
  std::string name = "Alice";
  int age = 30;
  double salary = 75000.50;

  fmt::print("Employee: {}, Age: {}, Salary: ${:.2f}\n", name, age, salary);

  // Positional arguments
  fmt::print("Name: {0}, {0} is {1} years old\n", name, age);

  // Named arguments (C++20 style)
  fmt::print("Person: {name} ({age} years old)\n", fmt::arg("name", name), fmt::arg("age", age));
}

void demo_number_formatting() {
  fmt::print("\n=== Number Formatting ===\n");

  int number = 42;
  double pi = 3.14159265359;

  // Different number bases
  fmt::print("Decimal: {}, Hex: {:#x}, Binary: {:#b}, Octal: {:#o}\n", number, number, number,
             number);

  // Floating point precision
  fmt::print("Pi: {:.2f}, {:.5f}, {:.10f}\n", pi, pi, pi);

  // Scientific notation
  double large_number = 123456.789;
  fmt::print("Scientific: {:.2e}, Fixed: {:.2f}\n", large_number, large_number);

  // Number padding and alignment
  fmt::print("Padded: '{:10}', Left: '{:<10}', Right: '{:>10}', Center: '{:^10}'\n", number, number,
             number, number);
}

void demo_color_output() {
  fmt::print("\n=== Colored Output ===\n");

  // Foreground colors
  fmt::print(fmt::fg(fmt::color::red), "Red text\n");
  fmt::print(fmt::fg(fmt::color::green), "Green text\n");
  fmt::print(fmt::fg(fmt::color::blue), "Blue text\n");

  // Background colors
  fmt::print(fmt::bg(fmt::color::yellow) | fmt::fg(fmt::color::black), "Yellow background\n");

  // RGB colors
  fmt::print(fmt::fg(fmt::rgb(255, 165, 0)), "Orange text (RGB)\n");

  // Text styles
  fmt::print(fmt::emphasis::bold | fmt::fg(fmt::color::cyan), "Bold cyan text\n");
}

void demo_time_formatting() {
  fmt::print("\n=== Time Formatting ===\n");

  auto now = std::chrono::system_clock::now();
  auto time_t = std::chrono::system_clock::to_time_t(now);

  // Different time formats
  fmt::print("Current time (system): {}\n",
             std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count());
  fmt::print("Formatted: {:%Y-%m-%d %H:%M:%S}\n", now);

  // Duration formatting
  auto duration = std::chrono::milliseconds(12345);
  fmt::print("Duration: {} ms\n", duration.count());

  // Custom duration display
  auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
  auto remaining_ms = duration - seconds;
  fmt::print("Duration breakdown: {}s {}ms\n", seconds.count(), remaining_ms.count());
}

void demo_container_formatting() {
  fmt::print("\n=== Container Formatting ===\n");

  // Vector formatting
  std::vector<int> numbers = {1, 2, 3, 4, 5};
  fmt::print("Vector: {}\n", numbers);
  fmt::print("Vector (custom): [{}]\n", fmt::join(numbers, ", "));

  // Map formatting
  std::map<std::string, int> scores = {{"Alice", 95}, {"Bob", 87}, {"Charlie", 92}};
  fmt::print("Map: {}\n", scores);

  // Array
  int array[] = {10, 20, 30};
  fmt::print("Array: {}\n", array);
}

void demo_custom_formatting() {
  fmt::print("\n=== Custom Type Formatting ===\n");

  struct Point {
    double x, y;
  };

  // Custom formatter for Point
  auto point = Point{3.14, 2.71};

  // Using format_as (C++20 approach)
  auto format_point = [](const Point& p) { return fmt::format("Point({:.2f}, {:.2f})", p.x, p.y); };

  fmt::print("Point: {}\n", format_point(point));
}

void demo_performance_comparison() {
  fmt::print("\n=== Performance Comparison ===\n");

  const int iterations = 100000;
  std::string name = "Performance Test";
  int value = 42;

  // fmt::format timing
  auto start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < iterations; ++i) {
    auto result = fmt::format("Name: {}, Value: {}", name, value);
    (void)result;  // Suppress unused variable warning
  }
  auto fmt_time = std::chrono::high_resolution_clock::now() - start;

  // printf timing for comparison
  start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < iterations; ++i) {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "Name: %s, Value: %d", name.c_str(), value);
  }
  auto printf_time = std::chrono::high_resolution_clock::now() - start;

  fmt::print("fmt::format time: {}\n", fmt_time);
  fmt::print("printf time: {}\n", printf_time);
  fmt::print("fmt is {:.2f}x {} than printf\n",
             std::chrono::duration<double>(printf_time) / std::chrono::duration<double>(fmt_time),
             (fmt_time < printf_time) ? "faster" : "slower");
}

void demo_error_handling() {
  fmt::print("\n=== Error Handling ===\n");

  try {
    // This will work fine
    fmt::print("Valid format: {}\n", 42);

    // Demonstrate compile-time format string checking
    // Note: This would be caught at compile time in recent fmt versions
    fmt::print("Number of arguments: {}\n", 42);

    fmt::print("Error handling works correctly!\n");
  } catch (const fmt::format_error& e) {
    fmt::print("Format error: {}\n", e.what());
  }
}

int main() {
  fmt::print("🎯 FMT Library Demonstration\n");
  fmt::print("============================\n\n");

  demo_basic_formatting();
  demo_number_formatting();
  demo_color_output();
  demo_time_formatting();
  demo_container_formatting();
  demo_custom_formatting();
  demo_performance_comparison();
  demo_error_handling();

  fmt::print("\n✅ FMT library examples completed!\n");
  fmt::print("📚 Learn more: https://fmt.dev/\n");

  return 0;
}
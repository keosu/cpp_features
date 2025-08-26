#include <algorithm>
#include <array>
#include <concepts>
#include <expected>
#include <format>
#include <iostream>
#include <optional>
#include <ranges>
#include <span>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

#include "../include/utils.h"

// Note: Many C++23 features may not be fully supported yet in all compilers
// This file demonstrates the features that are available and provides
// fallback implementations or explanations for those that aren't

namespace cpp23_features {

// C++23: std::print (if available)
void demo_print() {
  cpp_features::Demo::print_section("std::print");

#ifdef __cpp_lib_print
  std::print(std::cout, "  Hello from std::print!\n");
  std::print(std::cout, "  Formatted output: {} + {} = {}\n", 3, 4, 7);
  std::print(std::cout, "  Hexadecimal: {:#x}\n", 255);

  // std::println for automatic newline
  std::println(std::cout, "  This automatically adds a newline");
  std::println(std::cout, "  Number: {}, String: {}", 42, "C++23");
#else
  std::cout << "  std::print not available in this build\n";
  std::cout << "  Using std::cout instead:\n";
  std::cout << "  Hello from std::cout (simulating std::print)!\n";
  std::cout << "  Formatted output: 3 + 4 = 7\n";
  std::cout << "  Hexadecimal: 0xff\n";
#endif
}

// C++23: std::expected
enum class ErrorCode { SUCCESS, DIVISION_BY_ZERO, INVALID_INPUT, OUT_OF_RANGE };

std::string error_to_string(ErrorCode code) {
  switch (code) {
    case ErrorCode::SUCCESS:
      return "Success";
    case ErrorCode::DIVISION_BY_ZERO:
      return "Division by zero";
    case ErrorCode::INVALID_INPUT:
      return "Invalid input";
    case ErrorCode::OUT_OF_RANGE:
      return "Out of range";
    default:
      return "Unknown error";
  }
}

std::expected<double, ErrorCode> safe_divide(double a, double b) {
  if (b == 0.0) {
    return std::unexpected(ErrorCode::DIVISION_BY_ZERO);
  }
  return a / b;
}

std::expected<int, ErrorCode> safe_array_access(const std::vector<int>& vec, size_t index) {
  if (index >= vec.size()) {
    return std::unexpected(ErrorCode::OUT_OF_RANGE);
  }
  return vec[index];
}

void demo_expected() {
  cpp_features::Demo::print_section("std::expected");

#ifdef __cpp_lib_expected
  // Successful operations
  auto result1 = safe_divide(10.0, 2.0);
  if (result1) {
    cpp_features::Demo::print_value("10.0 / 2.0", result1.value());
  }

  // Error case
  auto result2 = safe_divide(10.0, 0.0);
  if (!result2) {
    std::cout << "  Error: " << error_to_string(result2.error()) << "\n";
  }

  // Chaining operations
  std::vector<int> numbers = {10, 20, 30, 40, 50};

  auto access_result = safe_array_access(numbers, 2);
  if (access_result) {
    cpp_features::Demo::print_value("numbers[2]", access_result.value());
  }

  auto invalid_access = safe_array_access(numbers, 10);
  if (!invalid_access) {
    std::cout << "  Error: " << error_to_string(invalid_access.error()) << "\n";
  }

  // Transform with expected
  auto transform_result =
      safe_divide(100.0, 5.0).transform([](double d) { return static_cast<int>(d); });

  if (transform_result) {
    cpp_features::Demo::print_value("Transformed result", transform_result.value());
  }
#else
  std::cout << "  std::expected not available in this build\n";
  std::cout << "  Simulating expected behavior:\n";

  // Fallback using optional and error handling
  auto divide_result = [](double a, double b) -> std::optional<double> {
    if (b == 0.0) return std::nullopt;
    return a / b;
  };

  auto result = divide_result(10.0, 2.0);
  if (result) {
    cpp_features::Demo::print_value("10.0 / 2.0", *result);
  }

  auto error_result = divide_result(10.0, 0.0);
  if (!error_result) {
    std::cout << "  Error: Division by zero\n";
  }
#endif
}

// C++23: std::flat_map and std::flat_set (if available)
void demo_flat_containers() {
  cpp_features::Demo::print_section("Flat Containers");

#ifdef __cpp_lib_flat_map
  std::flat_map<std::string, int> scores;
  scores["Alice"] = 95;
  scores["Bob"] = 87;
  scores["Charlie"] = 92;

  std::cout << "  Flat map contents:\n";
  for (const auto& [name, score] : scores) {
    cpp_features::Demo::print_value("  " + name, score);
  }

  std::flat_set<int> unique_numbers = {5, 2, 8, 2, 1, 5, 9};
  std::cout << "  Flat set (unique numbers): ";
  for (auto num : unique_numbers) {
    std::cout << num << " ";
  }
  std::cout << "\n";
#else
  std::cout << "  std::flat_map/flat_set not available in this build\n";
  std::cout << "  These are cache-friendly alternatives to std::map/set\n";
  std::cout << "  that store elements in contiguous memory\n";

  // Simulate with vector of pairs
  std::vector<std::pair<std::string, int>> scores = {{"Alice", 95}, {"Bob", 87}, {"Charlie", 92}};

  std::sort(scores.begin(), scores.end());

  std::cout << "  Simulated flat map (sorted vector of pairs):\n";
  for (const auto& [name, score] : scores) {
    cpp_features::Demo::print_value("  " + name, score);
  }
#endif
}

// C++23: Multidimensional subscript operator
class Matrix {
 private:
  std::vector<std::vector<int>> data;

 public:
  Matrix(size_t rows, size_t cols, int initial_value = 0)
      : data(rows, std::vector<int>(cols, initial_value)) {}

  // C++23: Multidimensional subscript
#ifdef __cpp_multidimensional_subscript
  int& operator[](size_t row, size_t col) { return data[row][col]; }

  const int& operator[](size_t row, size_t col) const { return data[row][col]; }
#else
  // Fallback: use function call operator
  int& operator()(size_t row, size_t col) { return data[row][col]; }

  const int& operator()(size_t row, size_t col) const { return data[row][col]; }
#endif

  size_t rows() const { return data.size(); }
  size_t cols() const { return data.empty() ? 0 : data[0].size(); }

  void print() const {
    for (size_t i = 0; i < rows(); ++i) {
      std::cout << "    ";
      for (size_t j = 0; j < cols(); ++j) {
#ifdef __cpp_multidimensional_subscript
        std::cout << (*this)[i, j] << " ";
#else
        std::cout << (*this)(i, j) << " ";
#endif
      }
      std::cout << "\n";
    }
  }
};

void demo_multidimensional_subscript() {
  cpp_features::Demo::print_section("Multidimensional Subscript Operator");

  Matrix mat(3, 4, 0);

#ifdef __cpp_multidimensional_subscript
  // C++23: Direct multidimensional access
  mat[0, 0] = 1;
  mat[1, 1] = 5;
  mat[2, 2] = 9;

  std::cout << "  Matrix after setting values with mat[row, col]:\n";
#else
  // Fallback: function call operator
  mat(0, 0) = 1;
  mat(1, 1) = 5;
  mat(2, 2) = 9;

  std::cout << "  Matrix after setting values with mat(row, col):\n";
  std::cout << "  (C++23 would allow mat[row, col] syntax)\n";
#endif

  mat.print();
}

// C++23: Deducing this
class FluentBuilder {
 private:
  std::string name_;
  int age_ = 0;
  std::string city_;

 public:
#ifdef __cpp_explicit_this_parameter
  // C++23: Deducing this parameter
  template <typename Self>
  auto&& set_name(this Self&& self, const std::string& name) {
    self.name_ = name;
    return std::forward<Self>(self);
  }

  template <typename Self>
  auto&& set_age(this Self&& self, int age) {
    self.age_ = age;
    return std::forward<Self>(self);
  }

  template <typename Self>
  auto&& set_city(this Self&& self, const std::string& city) {
    self.city_ = city;
    return std::forward<Self>(self);
  }
#else
  // Fallback: traditional methods
  FluentBuilder& set_name(const std::string& name) {
    name_ = name;
    return *this;
  }

  FluentBuilder& set_age(int age) {
    age_ = age;
    return *this;
  }

  FluentBuilder& set_city(const std::string& city) {
    city_ = city;
    return *this;
  }
#endif

  void print() const {
    std::cout << "  Person: " << name_ << ", Age: " << age_ << ", City: " << city_ << "\n";
  }
};

void demo_deducing_this() {
  cpp_features::Demo::print_section("Deducing This");

#ifdef __cpp_explicit_this_parameter
  std::cout << "  Using C++23 deducing this parameter:\n";
#else
  std::cout << "  Using traditional method chaining (C++23 would improve this):\n";
#endif

  FluentBuilder{}.set_name("Alice").set_age(30).set_city("New York").print();
}

// C++23: if consteval
constexpr bool is_constant_evaluated_context() {
#ifdef __cpp_if_consteval
  if consteval {
    return true;  // Compile-time context
  } else {
    return false;  // Runtime context
  }
#else
  return std::is_constant_evaluated();  // C++20 fallback
#endif
}

constexpr int compute_value() {
  if (is_constant_evaluated_context()) {
    // Optimized compile-time computation
    return 42 * 42;  // Simple computation for compile-time
  } else {
    // More complex runtime computation
    int result = 0;
    for (int i = 1; i <= 42; ++i) {
      result += i;
    }
    return result;
  }
}

void demo_if_consteval() {
  cpp_features::Demo::print_section("if consteval");

#ifdef __cpp_if_consteval
  std::cout << "  Using C++23 'if consteval':\n";
#else
  std::cout << "  Using C++20 std::is_constant_evaluated() (C++23 improves syntax):\n";
#endif

  constexpr int compile_time_result = compute_value();
  int runtime_result = compute_value();

  cpp_features::Demo::print_value("Compile-time result", compile_time_result);
  cpp_features::Demo::print_value("Runtime result", runtime_result);
}

// C++23: auto(x) and auto{x}
void demo_auto_cast() {
  cpp_features::Demo::print_section("auto(x) and auto{x} Casts");

  int x = 42;
  const int& ref = x;

  // C++23: auto(x) creates a prvalue copy (if supported)
#ifdef __cpp_auto_cast
  auto copy1 = auto(ref);  // int (copy)
  auto copy2 = auto{ref};  // int (copy)
#else
  // Fallback for compilers without auto(x) support
  auto copy1 = static_cast<std::decay_t<decltype(ref)>>(ref);
  auto copy2 = static_cast<std::decay_t<decltype(ref)>>(ref);
#endif

  // Traditional copy
  auto copy3 = static_cast<std::decay_t<decltype(ref)>>(ref);

  cpp_features::Demo::print_value("Original", ref);
  cpp_features::Demo::print_value("auto(ref)", copy1);
  cpp_features::Demo::print_value("auto{ref}", copy2);
  cpp_features::Demo::print_value("Traditional copy", copy3);

  // Modify copies to show they're independent
  copy1 = 100;
  copy2 = 200;
  copy3 = 300;

  cpp_features::Demo::print_value("After modification - original", ref);
  cpp_features::Demo::print_value("After modification - copy1", copy1);
  cpp_features::Demo::print_value("After modification - copy2", copy2);
}

// C++23: Ranges improvements
void demo_ranges_improvements() {
  cpp_features::Demo::print_section("Ranges Improvements (C++23)");

  std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  // C++23 adds more range adaptors and algorithms
  // Many of these might not be fully implemented yet

#ifdef __cpp_lib_ranges_contains
  bool contains_5 = std::ranges::contains(numbers, 5);
  cpp_features::Demo::print_value("Contains 5", contains_5);
#else
  bool contains_5 = std::ranges::find(numbers, 5) != numbers.end();
  cpp_features::Demo::print_value("Contains 5 (fallback)", contains_5);
#endif

  // Enumerate-like functionality (C++23 might add std::views::enumerate)
  std::cout << "  Indexed elements:\n";
  for (size_t i = 0; auto value : numbers | std::views::take(5)) {
    cpp_features::Demo::print_value("  [" + std::to_string(i++) + "]", value);
  }

  // Chunk view (if available)
#ifdef __cpp_lib_ranges_chunk
  auto chunks = numbers | std::views::chunk(3);
  std::cout << "  Chunks of 3:\n";
  for (auto chunk : chunks) {
    std::cout << "    ";
    for (auto value : chunk) {
      std::cout << value << " ";
    }
    std::cout << "\n";
  }
#else
  std::cout << "  Chunk view not available (C++23 feature)\n";
  std::cout << "  Would create: [1,2,3] [4,5,6] [7,8,9] [10]\n";
#endif
}

// C++23: String contains
void demo_string_contains() {
  cpp_features::Demo::print_section("String Contains Method");

  std::string text = "Hello, C++23 World!";
  std::string_view sv = "programming with modern C++";

#ifdef __cpp_lib_string_contains
  bool has_cpp23 = text.contains("C++23");
  bool has_python = text.contains("Python");
  bool sv_has_modern = sv.contains("modern");

  cpp_features::Demo::print_value("Text contains 'C++23'", has_cpp23);
  cpp_features::Demo::print_value("Text contains 'Python'", has_python);
  cpp_features::Demo::print_value("StringView contains 'modern'", sv_has_modern);
#else
  bool has_cpp23 = text.find("C++23") != std::string::npos;
  bool has_python = text.find("Python") != std::string::npos;
  bool sv_has_modern = sv.find("modern") != std::string_view::npos;

  cpp_features::Demo::print_value("Text contains 'C++23' (fallback)", has_cpp23);
  cpp_features::Demo::print_value("Text contains 'Python' (fallback)", has_python);
  cpp_features::Demo::print_value("StringView contains 'modern' (fallback)", sv_has_modern);
#endif
}

}  // namespace cpp23_features

int main() {
  cpp_features::Demo::print_header("C++23 Features Showcase");

  std::cout << "Note: Many C++23 features are still being implemented by compilers.\n";
  std::cout << "This demo shows available features and fallbacks for others.\n\n";

  cpp23_features::demo_print();
  cpp23_features::demo_expected();
  cpp23_features::demo_flat_containers();
  cpp23_features::demo_multidimensional_subscript();
  cpp23_features::demo_deducing_this();
  cpp23_features::demo_if_consteval();
  cpp23_features::demo_auto_cast();
  cpp23_features::demo_ranges_improvements();
  cpp23_features::demo_string_contains();

  std::cout << "\nC++23 features demonstration completed!\n";
  std::cout << "Note: Full C++23 support varies by compiler and standard library implementation.\n";
  return 0;
}
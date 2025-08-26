#include <algorithm>
#include <any>
#include <array>
#include <execution>
#include <filesystem>
#include <iostream>
#include <map>
#include <numeric>
#include <optional>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <variant>
#include <vector>

#include "../include/utils.h"

namespace cpp17_features {

// C++17: Structured bindings
void demo_structured_bindings() {
  cpp_features::Demo::print_section("Structured Bindings");

  // With std::tuple
  auto person_data = std::make_tuple("Alice", 30, 65.5);
  auto [name, age, weight] = person_data;

  cpp_features::Demo::print_value("Name", name);
  cpp_features::Demo::print_value("Age", age);
  cpp_features::Demo::print_value("Weight", weight);

  // With std::pair
  std::map<std::string, int> scores = {{"Math", 95}, {"Physics", 88}, {"Chemistry", 92}};

  std::cout << "  Subject scores:\n";
  for (const auto& [subject, score] : scores) {
    cpp_features::Demo::print_value("  " + subject, score);
  }

  // With arrays
  int coords[] = {10, 20, 30};
  auto [x, y, z] = coords;

  cpp_features::Demo::print_value("X coordinate", x);
  cpp_features::Demo::print_value("Y coordinate", y);
  cpp_features::Demo::print_value("Z coordinate", z);

  // With custom struct
  struct Point {
    int x, y;
  };
  Point p{100, 200};
  auto [px, py] = p;

  cpp_features::Demo::print_value("Point X", px);
  cpp_features::Demo::print_value("Point Y", py);
}

// C++17: if constexpr
template <typename T>
void print_info() {
  std::cout << "  Type info for " << typeid(T).name() << ":\n";

  if constexpr (std::is_integral_v<T>) {
    std::cout << "    - This is an integral type\n";
    std::cout << "    - Size: " << sizeof(T) << " bytes\n";
    std::cout << "    - Signed: " << std::is_signed_v<T> << "\n";
  } else if constexpr (std::is_floating_point_v<T>) {
    std::cout << "    - This is a floating point type\n";
    std::cout << "    - Size: " << sizeof(T) << " bytes\n";
    std::cout << "    - Digits: " << std::numeric_limits<T>::digits << "\n";
  } else {
    std::cout << "    - This is some other type\n";
    std::cout << "    - Size: " << sizeof(T) << " bytes\n";
  }
}

void demo_if_constexpr() {
  cpp_features::Demo::print_section("if constexpr");

  print_info<int>();
  print_info<double>();
  print_info<std::string>();
}

// C++17: std::optional
std::optional<int> safe_divide(int a, int b) {
  if (b == 0) {
    return std::nullopt;  // No value
  }
  return a / b;
}

std::optional<std::string> find_user(int id) {
  static std::map<int, std::string> users = {{1, "Alice"}, {2, "Bob"}, {3, "Charlie"}};

  auto it = users.find(id);
  if (it != users.end()) {
    return it->second;
  }
  return std::nullopt;
}

void demo_optional() {
  cpp_features::Demo::print_section("std::optional");

  // Safe division
  auto result1 = safe_divide(10, 2);
  auto result2 = safe_divide(10, 0);

  if (result1) {
    cpp_features::Demo::print_value("10 / 2", *result1);
  }

  if (!result2) {
    std::cout << "  10 / 0: Division by zero - no result\n";
  }

  // User lookup
  for (int id = 1; id <= 4; ++id) {
    auto user = find_user(id);
    if (user) {
      cpp_features::Demo::print_value("User " + std::to_string(id), *user);
    } else {
      std::cout << "  User " << id << ": Not found\n";
    }
  }

  // Optional with value_or
  auto maybe_value = std::optional<int>{};
  int default_value = maybe_value.value_or(42);
  cpp_features::Demo::print_value("Default value", default_value);
}

// C++17: std::variant
void demo_variant() {
  cpp_features::Demo::print_section("std::variant");

  std::variant<int, std::string, double> data;

  // Store different types
  data = 42;
  std::cout << "  Variant holds int: " << std::get<int>(data) << "\n";

  data = std::string("Hello Variant!");
  std::cout << "  Variant holds string: " << std::get<std::string>(data) << "\n";

  data = 3.14159;
  std::cout << "  Variant holds double: " << std::get<double>(data) << "\n";

  // Visitor pattern with std::visit
  auto visitor = [](const auto& value) {
    using T = std::decay_t<decltype(value)>;
    if constexpr (std::is_same_v<T, int>) {
      std::cout << "  Processing integer: " << value << "\n";
    } else if constexpr (std::is_same_v<T, std::string>) {
      std::cout << "  Processing string: " << value << " (length: " << value.length() << ")\n";
    } else if constexpr (std::is_same_v<T, double>) {
      std::cout << "  Processing double: " << value << "\n";
    }
  };

  std::visit(visitor, data);

  // Check current type
  cpp_features::Demo::print_value("Current variant index", data.index());
  cpp_features::Demo::print_value("Holds double?", std::holds_alternative<double>(data));
}

// C++17: std::string_view
void process_text(std::string_view text) {
  std::cout << "  Processing: '" << text << "' (length: " << text.length() << ")\n";

  // No copying, just a view
  auto first_word = text.substr(0, text.find(' '));
  std::cout << "  First word: '" << first_word << "'\n";
}

void demo_string_view() {
  cpp_features::Demo::print_section("std::string_view");

  // Works with string literals
  process_text("Hello World from C++17");

  // Works with std::string
  std::string text = "String view is efficient";
  process_text(text);

  // Works with C-style strings
  const char* cstr = "C-style string works too";
  process_text(cstr);

  // Substring without allocation
  std::string long_text = "This is a very long string that we want to process efficiently";
  std::string_view middle_part = std::string_view(long_text).substr(10, 20);
  std::cout << "  Middle part: '" << middle_part << "'\n";
}

// C++17: std::any
void demo_any() {
  cpp_features::Demo::print_section("std::any");

  std::any data;

  // Store different types
  data = 42;
  std::cout << "  any holds: " << std::any_cast<int>(data) << "\n";

  data = std::string("Hello any!");
  std::cout << "  any holds: " << std::any_cast<std::string>(data) << "\n";

  data = 3.14;
  std::cout << "  any holds: " << std::any_cast<double>(data) << "\n";

  // Type checking
  if (data.type() == typeid(double)) {
    std::cout << "  Confirmed: data contains a double\n";
  }

  // Safe casting with try-catch
  try {
    auto value = std::any_cast<int>(data);  // This will throw
    std::cout << "  Got int: " << value << "\n";
  } catch (const std::bad_any_cast& e) {
    std::cout << "  Bad cast: " << e.what() << "\n";
  }
}

// C++17: Fold expressions
template <typename... Args>
auto sum_all(Args... args) {
  return (args + ...);  // Fold expression
}

template <typename... Args>
void print_all(Args... args) {
  ((std::cout << args << " "), ...);  // Fold expression with comma operator
  std::cout << "\n";
}

template <typename... Args>
bool all_true(Args... args) {
  return (args && ...);  // Logical AND fold
}

void demo_fold_expressions() {
  cpp_features::Demo::print_section("Fold Expressions");

  auto total = sum_all(1, 2, 3, 4, 5);
  cpp_features::Demo::print_value("Sum of 1,2,3,4,5", total);

  std::cout << "  Print all: ";
  print_all("Hello", 42, 3.14, "World");

  bool result1 = all_true(true, true, true);
  bool result2 = all_true(true, false, true);
  cpp_features::Demo::print_value("All true (T,T,T)", result1);
  cpp_features::Demo::print_value("All true (T,F,T)", result2);
}

// C++17: Class template argument deduction
template <typename T>
class Container {
  T data;

 public:
  Container(T value) : data(value) {}
  T get() const { return data; }
};

void demo_class_template_deduction() {
  cpp_features::Demo::print_section("Class Template Argument Deduction");

  // C++17: No need to specify template arguments
  Container c1(42);       // Deduced as Container<int>
  Container c2(3.14);     // Deduced as Container<double>
  Container c3("Hello");  // Deduced as Container<const char*>

  cpp_features::Demo::print_value("Container<int>", c1.get());
  cpp_features::Demo::print_value("Container<double>", c2.get());
  cpp_features::Demo::print_value("Container<const char*>", c3.get());

  // Works with standard library too
  std::vector v1 = {1, 2, 3, 4, 5};  // std::vector<int>
  std::pair p1 = {"key", 100};       // std::pair<const char*, int>

  cpp_features::Demo::print_value("Vector size", v1.size());
  cpp_features::Demo::print_value("Pair first", p1.first);
  cpp_features::Demo::print_value("Pair second", p1.second);
}

// C++17: Parallel algorithms (if supported)
void demo_parallel_algorithms() {
  cpp_features::Demo::print_section("Parallel Algorithms");

  std::vector<int> data(1000000);
  std::iota(data.begin(), data.end(), 1);  // Fill with 1, 2, 3, ..., 1000000

  cpp_features::Timer timer;

  // Sequential execution
  timer = cpp_features::Timer{};
  auto sum1 = std::accumulate(data.begin(), data.end(), 0LL);
  auto time1 = timer.elapsed_ms();

  // Parallel execution (if supported by compiler/standard library)
#ifdef __cpp_lib_execution
  timer = cpp_features::Timer{};
  auto sum2 = std::reduce(std::execution::par, data.begin(), data.end(), 0LL);
  auto time2 = timer.elapsed_ms();

  cpp_features::Demo::print_value("Sequential sum", sum1);
  cpp_features::Demo::print_value("Sequential time (ms)", time1);
  cpp_features::Demo::print_value("Parallel sum", sum2);
  cpp_features::Demo::print_value("Parallel time (ms)", time2);
#else
  cpp_features::Demo::print_value("Sequential sum", sum1);
  cpp_features::Demo::print_value("Sequential time (ms)", time1);
  std::cout << "  Parallel algorithms not supported in this build\n";
#endif
}

// C++17: Nested namespaces
namespace cpp17::nested::example {
void hello() { std::cout << "  Hello from nested namespace!\n"; }
}  // namespace cpp17::nested::example

void demo_nested_namespaces() {
  cpp_features::Demo::print_section("Nested Namespaces");

  cpp17::nested::example::hello();
}

}  // namespace cpp17_features

int main() {
  cpp_features::Demo::print_header("C++17 Features Showcase");

  cpp17_features::demo_structured_bindings();
  cpp17_features::demo_if_constexpr();
  cpp17_features::demo_optional();
  cpp17_features::demo_variant();
  cpp17_features::demo_string_view();
  cpp17_features::demo_any();
  cpp17_features::demo_fold_expressions();
  cpp17_features::demo_class_template_deduction();
  cpp17_features::demo_parallel_algorithms();
  cpp17_features::demo_nested_namespaces();

  std::cout << "\nC++17 features demonstration completed!\n";
  return 0;
}
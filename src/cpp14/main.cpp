#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <vector>

#include "../include/utils.h"

namespace cpp14_features {

// C++14: Return type deduction
auto calculate_factorial(int n) {
  if (n <= 1) return 1;
  return n * calculate_factorial(n - 1);
}

// C++14: Return type deduction with different return types
// Note: All return paths must have the same type
auto get_value(bool flag) {
  if (flag) {
    return 42;  // int
  } else {
    return 24;  // int (not double)
  }
}

// Fix: Explicit return type when needed
double get_numeric_value(bool flag) {
  if (flag) {
    return 42;  // int converted to double
  } else {
    return 3.14;  // double
  }
}

void demo_return_type_deduction() {
  cpp_features::Demo::print_section("Return Type Deduction");

  auto result1 = calculate_factorial(5);
  auto result2 = get_value(true);
  auto result3 = get_numeric_value(false);

  cpp_features::Demo::print_value("factorial(5)", result1);
  cpp_features::Demo::print_value("get_value(true)", result2);
  cpp_features::Demo::print_value("get_numeric_value(false)", result3);
}

void demo_generic_lambdas() {
  cpp_features::Demo::print_section("Generic Lambdas");

  // Generic lambda - works with any type
  auto generic_printer = [](const auto& value) {
    std::cout << "  Value: " << value << " (type size: " << sizeof(value) << " bytes)\n";
  };

  // Use with different types
  generic_printer(42);
  generic_printer(3.14);
  generic_printer("Hello C++14!");

  // Generic lambda for binary operations
  auto generic_add = [](const auto& a, const auto& b) -> auto { return a + b; };

  cpp_features::Demo::print_value("42 + 58", generic_add(42, 58));
  cpp_features::Demo::print_value("3.14 + 2.86", generic_add(3.14, 2.86));

  std::string str1 = "Hello ";
  std::string str2 = "World!";
  cpp_features::Demo::print_value("String concat", generic_add(str1, str2));

  // Generic lambda with perfect forwarding
  auto generic_processor = [](auto&& value) {
    using T = std::decay_t<decltype(value)>;
    std::cout << "  Processing " << typeid(T).name() << ": " << std::forward<decltype(value)>(value)
              << "\n";
  };

  int x = 100;
  generic_processor(x);        // lvalue
  generic_processor(200);      // rvalue
  generic_processor("C++14");  // string literal
}

}  // namespace cpp14_features

// C++14: Variable templates (must be at global scope)
template <typename T>
constexpr T pi = T(3.1415926535897932385);

// Variable template for type traits
template <typename T>
constexpr bool is_integral_v = std::is_integral<T>::value;

namespace cpp14_features {

void demo_variable_templates() {
  cpp_features::Demo::print_section("Variable Templates");

  // Usage of global variable templates
  auto pi_float = pi<float>;
  auto pi_double = pi<double>;
  auto pi_long_double = pi<long double>;

  cpp_features::Demo::print_value("pi<float>", pi_float);
  cpp_features::Demo::print_value("pi<double>", pi_double);
  std::cout << "  pi<long double>: " << pi_long_double << "\n";

  cpp_features::Demo::print_value("is_integral_v<int>", is_integral_v<int>);
  cpp_features::Demo::print_value("is_integral_v<float>", is_integral_v<float>);
}

// C++14: Binary literals and digit separators
void demo_binary_literals() {
  cpp_features::Demo::print_section("Binary Literals and Digit Separators");

  // Binary literals
  auto binary1 = 0b1010;      // 10 in decimal
  auto binary2 = 0B11110000;  // 240 in decimal

  // Digit separators for readability
  auto large_number = 1'000'000;  // 1 million
  auto binary_with_sep = 0b1111'0000'1010'0101;
  auto hex_with_sep = 0xFF'AB'CD'EF;

  cpp_features::Demo::print_value("0b1010", binary1);
  cpp_features::Demo::print_value("0B11110000", binary2);
  cpp_features::Demo::print_value("1'000'000", large_number);
  cpp_features::Demo::print_value("binary with separators", binary_with_sep);
  std::cout << "  hex with separators: 0x" << std::hex << hex_with_sep << std::dec << "\n";
}

// C++14: Improved constexpr
constexpr int fibonacci(int n) {
  if (n <= 1) return n;

  int a = 0, b = 1;
  for (int i = 2; i <= n; ++i) {
    int temp = a + b;
    a = b;
    b = temp;
  }
  return b;
}

void demo_improved_constexpr() {
  cpp_features::Demo::print_section("Improved constexpr");

  // Can now use loops and more complex logic in constexpr functions
  constexpr int fib_10 = fibonacci(10);
  constexpr int fib_15 = fibonacci(15);

  cpp_features::Demo::print_value("fibonacci(10) [constexpr]", fib_10);
  cpp_features::Demo::print_value("fibonacci(15) [constexpr]", fib_15);

  // Runtime calculation for comparison
  cpp_features::Timer timer;
  int runtime_fib = fibonacci(20);
  cpp_features::Demo::print_value("fibonacci(20) [runtime]", runtime_fib);
  cpp_features::Demo::print_value("Time taken (ms)", timer.elapsed_ms());
}

// C++14: std::make_unique (finally!)
class Resource {
 private:
  std::string name;
  int id;

 public:
  Resource(const std::string& n, int i) : name(n), id(i) {
    std::cout << "  Resource created: " << name << " (id: " << id << ")\n";
  }

  ~Resource() { std::cout << "  Resource destroyed: " << name << " (id: " << id << ")\n"; }

  void info() const { std::cout << "  Resource info: " << name << " (id: " << id << ")\n"; }
};

void demo_make_unique() {
  cpp_features::Demo::print_section("std::make_unique");

  // C++14: make_unique is now available (was missing in C++11)
  auto resource1 = std::make_unique<Resource>("Primary", 1);
  auto resource2 = std::make_unique<Resource>("Secondary", 2);

  resource1->info();
  resource2->info();

  // Move semantics
  auto resource3 = std::move(resource1);
  if (!resource1) {
    std::cout << "  resource1 is now nullptr after move\n";
  }

  resource3->info();
}

// C++14: std::integer_sequence and std::index_sequence
template <typename T, T... ints>
void print_sequence(std::integer_sequence<T, ints...>) {
  std::cout << "  Sequence: ";
  // C++14 way to print parameter pack
  auto dummy = {0, ((std::cout << ints << ' '), 0)...};
  (void)dummy;  // Suppress unused variable warning
  std::cout << "\n";
}

void demo_integer_sequence() {
  cpp_features::Demo::print_section("std::integer_sequence");

  // Create sequences
  using seq1 = std::make_integer_sequence<int, 5>;  // 0,1,2,3,4
  using seq2 = std::make_index_sequence<3>;         // 0,1,2

  print_sequence(seq1{});
  print_sequence(seq2{});
}

// C++14: decltype(auto)
template <typename Container>
decltype(auto) get_element(Container&& container, std::size_t index) {
  return std::forward<Container>(container)[index];
}

void demo_decltype_auto() {
  cpp_features::Demo::print_section("decltype(auto)");

  std::vector<int> vec = {10, 20, 30, 40, 50};

  // decltype(auto) preserves exact type and value category
  decltype(auto) element = get_element(vec, 2);  // Returns int&
  element = 99;                                  // Modifies the original vector

  cpp_features::Demo::print_value("Modified element", vec[2]);

  // Compare with auto
  auto element_copy = get_element(vec, 3);  // Returns int (copy)
  element_copy = 88;                        // Does NOT modify the original vector

  cpp_features::Demo::print_value("Original element", vec[3]);
  cpp_features::Demo::print_value("Copy value", element_copy);
}

}  // namespace cpp14_features

int main() {
  cpp_features::Demo::print_header("C++14 Features Showcase");

  cpp14_features::demo_return_type_deduction();
  cpp14_features::demo_generic_lambdas();
  cpp14_features::demo_variable_templates();
  cpp14_features::demo_binary_literals();
  cpp14_features::demo_improved_constexpr();
  cpp14_features::demo_make_unique();
  cpp14_features::demo_integer_sequence();
  cpp14_features::demo_decltype_auto();

  std::cout << "\nC++14 features demonstration completed!\n";
  return 0;
}
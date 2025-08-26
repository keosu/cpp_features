#include <algorithm>
#include <array>
#include <bit>
#include <compare>
#include <concepts>
#include <coroutine>
#include <format>
#include <iostream>
#include <numbers>
#include <numeric>
#include <ranges>
#include <span>
#include <string>
#include <type_traits>
#include <vector>

#include "../include/utils.h"

namespace cpp20_features {

// C++20: Concepts
template <typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

template <typename T>
concept Addable = requires(T a, T b) {
  a + b;
};

template <Numeric T>
T add_numbers(T a, T b) {
  return a + b;
}

template <typename Container>
concept HasSize = requires(Container c) {
  c.size();
  typename Container::size_type;
};

template <HasSize Container>
void print_container_info(const Container& container) {
  std::cout << "  Container size: " << container.size() << "\n";
  std::cout << "  Container type size: " << sizeof(typename Container::size_type) << " bytes\n";
}

void demo_concepts() {
  cpp_features::Demo::print_section("Concepts");

  // Numeric concept
  auto int_result = add_numbers(10, 20);
  auto double_result = add_numbers(3.14, 2.86);

  cpp_features::Demo::print_value("add_numbers(10, 20)", int_result);
  cpp_features::Demo::print_value("add_numbers(3.14, 2.86)", double_result);

  // HasSize concept
  std::vector<int> vec = {1, 2, 3, 4, 5};
  std::string str = "Hello Concepts!";

  std::cout << "  Vector info:\n";
  print_container_info(vec);

  std::cout << "  String info:\n";
  print_container_info(str);

  // This would cause a compile error:
  // add_numbers("hello", "world");  // std::string is not Numeric
}

// C++20: Ranges
void demo_ranges() {
  cpp_features::Demo::print_section("Ranges");

  std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  // Filter even numbers and square them
  auto even_squares = numbers | std::views::filter([](int n) { return n % 2 == 0; }) |
                      std::views::transform([](int n) { return n * n; });

  std::cout << "  Even squares: ";
  for (auto value : even_squares) {
    std::cout << value << " ";
  }
  std::cout << "\n";

  // Take first 3 elements, reverse them
  auto first_three_reversed = numbers | std::views::take(3) | std::views::reverse;

  std::cout << "  First 3 reversed: ";
  for (auto value : first_three_reversed) {
    std::cout << value << " ";
  }
  std::cout << "\n";

  // Generate infinite sequence (but only take some)
  auto infinite_odds = std::views::iota(1) | std::views::filter([](int n) { return n % 2 == 1; }) |
                       std::views::take(5);

  std::cout << "  First 5 odd numbers: ";
  for (auto value : infinite_odds) {
    std::cout << value << " ";
  }
  std::cout << "\n";
}

// C++20: std::span
void process_data(std::span<int> data) {
  std::cout << "  Processing " << data.size() << " elements: ";
  for (auto& value : data) {
    value *= 2;  // Double each value
    std::cout << value << " ";
  }
  std::cout << "\n";
}

void demo_span() {
  cpp_features::Demo::print_section("std::span");

  // Works with arrays
  int array[] = {1, 2, 3, 4, 5};
  process_data(array);

  // Works with vectors
  std::vector<int> vec = {10, 20, 30};
  process_data(vec);

  // Works with std::array
  std::array<int, 4> arr = {100, 200, 300, 400};
  process_data(arr);

  // Subspan
  std::vector<int> large_vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::span<int> middle_part = std::span(large_vec).subspan(3, 4);  // Elements 4,5,6,7

  std::cout << "  Middle part before: ";
  for (auto value : middle_part) {
    std::cout << value << " ";
  }
  std::cout << "\n";

  process_data(middle_part);
}

// C++20: Three-way comparison (spaceship operator)
class Version {
 public:
  int major, minor, patch;

  Version(int maj, int min, int p) : major(maj), minor(min), patch(p) {}

  // C++20: Default spaceship operator
  // clang-format off
  auto operator<=>(const Version& other) const = default;
  // clang-format on

  friend std::ostream& operator<<(std::ostream& os, const Version& v) {
    return os << v.major << "." << v.minor << "." << v.patch;
  }
};

void demo_three_way_comparison() {
  cpp_features::Demo::print_section("Three-way Comparison (Spaceship Operator)");

  Version v1(2, 1, 0);
  Version v2(2, 0, 5);
  Version v3(2, 1, 0);

  std::cout << "  v1: " << v1 << "\n";
  std::cout << "  v2: " << v2 << "\n";
  std::cout << "  v3: " << v3 << "\n";

  cpp_features::Demo::print_value("v1 == v3", (v1 == v3));
  cpp_features::Demo::print_value("v1 != v2", (v1 != v2));
  cpp_features::Demo::print_value("v1 > v2", (v1 > v2));
  cpp_features::Demo::print_value("v1 < v2", (v1 < v2));
  cpp_features::Demo::print_value("v1 >= v3", (v1 >= v3));
}

// C++20: std::format (if available)
void demo_format() {
  cpp_features::Demo::print_section("std::format");

#ifdef __cpp_lib_format
  std::string name = "Alice";
  int age = 30;
  double salary = 75000.50;

  auto formatted = std::format("Employee: {}, Age: {}, Salary: ${:.2f}", name, age, salary);
  std::cout << "  " << formatted << "\n";

  // Positional arguments
  auto positioned = std::format("Name: {0}, {0} is {1} years old", name, age);
  std::cout << "  " << positioned << "\n";

  // Number formatting
  auto hex_num = std::format("Hex: {:#x}, Binary: {:#b}, Decimal: {}", 255, 255, 255);
  std::cout << "  " << hex_num << "\n";
#else
  std::cout << "  std::format not available in this build\n";
  std::cout << "  Using traditional formatting:\n";
  std::cout << "  Employee: Alice, Age: 30, Salary: $75000.50\n";
#endif
}

// C++20: Mathematical constants
void demo_math_constants() {
  cpp_features::Demo::print_section("Mathematical Constants");

  using std::numbers::e_v;
  using std::numbers::ln2_v;
  using std::numbers::pi_v;
  using std::numbers::sqrt2_v;

  cpp_features::Demo::print_value("π (pi)", pi_v<double>);
  cpp_features::Demo::print_value("e (euler)", e_v<double>);
  cpp_features::Demo::print_value("√2 (sqrt2)", sqrt2_v<double>);
  cpp_features::Demo::print_value("ln(2)", ln2_v<double>);

  // Area of circle with radius 5
  double radius = 5.0;
  double area = pi_v<double> * radius * radius;
  cpp_features::Demo::print_value("Circle area (r=5)", area);
}

// C++20: Bit operations
void demo_bit_operations() {
  cpp_features::Demo::print_section("Bit Operations");

  uint32_t value = 0b11010110;

  cpp_features::Demo::print_value("Original value", value);
  cpp_features::Demo::print_value("Bit width", std::bit_width(value));
  cpp_features::Demo::print_value("Population count", std::popcount(value));
  cpp_features::Demo::print_value("Has single bit?", std::has_single_bit(value));
  cpp_features::Demo::print_value("Count leading zeros", std::countl_zero(value));
  cpp_features::Demo::print_value("Count trailing zeros", std::countr_zero(value));

  // Bit rotation
  auto rotated_left = std::rotl(value, 2);
  auto rotated_right = std::rotr(value, 2);

  cpp_features::Demo::print_value("Rotated left by 2", rotated_left);
  cpp_features::Demo::print_value("Rotated right by 2", rotated_right);

  // Endianness
  if constexpr (std::endian::native == std::endian::little) {
    std::cout << "  System endianness: Little endian\n";
  } else if constexpr (std::endian::native == std::endian::big) {
    std::cout << "  System endianness: Big endian\n";
  } else {
    std::cout << "  System endianness: Mixed endian\n";
  }
}

// C++20: Designated initializers
struct Config {
  std::string name;
  int port;
  bool enabled;
  double timeout;
};

void demo_designated_initializers() {
  cpp_features::Demo::print_section("Designated Initializers");

  // C++20: Designated initializers
  Config server_config{.name = "WebServer", .port = 8080, .enabled = true, .timeout = 30.0};

  Config client_config{.name = "Client",
                       .port = 0,  // Default port
                       .enabled = false,
                       .timeout = 10.0};

  cpp_features::Demo::print_value("Server name", server_config.name);
  cpp_features::Demo::print_value("Server port", server_config.port);
  cpp_features::Demo::print_value("Server enabled", server_config.enabled);
  cpp_features::Demo::print_value("Server timeout", server_config.timeout);

  cpp_features::Demo::print_value("Client name", client_config.name);
  cpp_features::Demo::print_value("Client enabled", client_config.enabled);
}

// C++20: Template parameter lists for lambdas
void demo_template_lambdas() {
  cpp_features::Demo::print_section("Template Parameter Lists for Lambdas");

  // C++20: Template lambdas with explicit template parameters
  auto generic_max = []<typename T>(T a, T b) -> T { return (a > b) ? a : b; };

  auto int_max = generic_max(10, 20);
  auto double_max = generic_max(3.14, 2.71);
  auto string_max = generic_max(std::string("hello"), std::string("world"));

  cpp_features::Demo::print_value("max(10, 20)", int_max);
  cpp_features::Demo::print_value("max(3.14, 2.71)", double_max);
  cpp_features::Demo::print_value("max(\"hello\", \"world\")", string_max);

  // Template lambda with multiple parameters
  auto print_pair = []<typename T, typename U>(T first, U second) {
    std::cout << "  Pair: (" << first << ", " << second << ")\n";
  };

  print_pair(42, "answer");
  print_pair(3.14, true);
}

// C++20: consteval (compile-time evaluation)
consteval int factorial_ct(int n) {
  if (n <= 1) return 1;
  return n * factorial_ct(n - 1);
}

constexpr int factorial_cx(int n) {
  if (n <= 1) return 1;
  return n * factorial_cx(n - 1);
}

void demo_consteval() {
  cpp_features::Demo::print_section("consteval");

  // consteval - MUST be evaluated at compile time
  constexpr int fact5_eval = factorial_ct(5);  // OK - compile time
  constexpr int fact6_expr = factorial_cx(6);  // OK - compile time

  cpp_features::Demo::print_value("factorial_ct(5) [consteval]", fact5_eval);
  cpp_features::Demo::print_value("factorial_cx(6) [constexpr]", fact6_expr);

  // This would work with constexpr but not with consteval:
  // int runtime_n = 4;
  // int result = factorial_cx(runtime_n);  // OK with constexpr
  // int result2 = factorial_ct(runtime_n); // ERROR with consteval

  int runtime_result = factorial_cx(4);  // Runtime evaluation
  cpp_features::Demo::print_value("factorial_cx(4) [runtime]", runtime_result);
}

// Simple coroutine example (if supported)
#ifdef __cpp_impl_coroutine
#include <coroutine>

struct SimpleGenerator {
  struct promise_type {
    int current_value;

    SimpleGenerator get_return_object() {
      return SimpleGenerator{std::coroutine_handle<promise_type>::from_promise(*this)};
    }

    std::suspend_always initial_suspend() { return {}; }
    std::suspend_always final_suspend() noexcept { return {}; }
    void unhandled_exception() {}

    std::suspend_always yield_value(int value) {
      current_value = value;
      return {};
    }

    void return_void() {}
  };

  std::coroutine_handle<promise_type> h;

  SimpleGenerator(std::coroutine_handle<promise_type> handle) : h(handle) {}

  ~SimpleGenerator() {
    if (h) h.destroy();
  }

  // Move only
  SimpleGenerator(const SimpleGenerator&) = delete;
  SimpleGenerator& operator=(const SimpleGenerator&) = delete;
  SimpleGenerator(SimpleGenerator&& other) : h(other.h) { other.h = {}; }
  SimpleGenerator& operator=(SimpleGenerator&& other) {
    if (this != &other) {
      if (h) h.destroy();
      h = other.h;
      other.h = {};
    }
    return *this;
  }

  bool next() {
    h.resume();
    return !h.done();
  }

  int value() { return h.promise().current_value; }
};

SimpleGenerator counter(int start, int end) {
  for (int i = start; i <= end; ++i) {
    co_yield i;
  }
}
#endif

void demo_coroutines() {
  cpp_features::Demo::print_section("Coroutines (Basic Example)");

#ifdef __cpp_impl_coroutine
  auto gen = counter(1, 5);

  std::cout << "  Generated values: ";
  while (gen.next()) {
    std::cout << gen.value() << " ";
  }
  std::cout << "\n";
#else
  std::cout << "  Coroutines not supported in this build\n";
  std::cout << "  Would generate: 1 2 3 4 5\n";
#endif
}

}  // namespace cpp20_features

int main() {
  cpp_features::Demo::print_header("C++20 Features Showcase");

  cpp20_features::demo_concepts();
  cpp20_features::demo_ranges();
  cpp20_features::demo_span();
  cpp20_features::demo_three_way_comparison();
  cpp20_features::demo_format();
  cpp20_features::demo_math_constants();
  cpp20_features::demo_bit_operations();
  cpp20_features::demo_designated_initializers();
  cpp20_features::demo_template_lambdas();
  cpp20_features::demo_consteval();
  cpp20_features::demo_coroutines();

  std::cout << "\nC++20 features demonstration completed!\n";
  return 0;
}
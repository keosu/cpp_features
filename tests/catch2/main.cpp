#include <algorithm>
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

// 简单的计算器类，用于演示测试
class Calculator {
 public:
  double add(double a, double b) { return a + b; }

  double subtract(double a, double b) { return a - b; }

  double multiply(double a, double b) { return a * b; }

  double divide(double a, double b) {
    if (b == 0.0) {
      throw std::invalid_argument("Division by zero");
    }
    return a / b;
  }

  bool is_even(int n) { return n % 2 == 0; }

  std::vector<int> get_factors(int n) {
    std::vector<int> factors;
    for (int i = 1; i <= n; ++i) {
      if (n % i == 0) {
        factors.push_back(i);
      }
    }
    return factors;
  }
};

// 字符串处理类
class StringProcessor {
 public:
  std::string to_upper(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
  }

  std::string reverse(const std::string& str) {
    std::string result = str;
    std::reverse(result.begin(), result.end());
    return result;
  }

  std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::string current;

    for (char c : str) {
      if (c == delimiter) {
        if (!current.empty()) {
          result.push_back(current);
          current.clear();
        }
      } else {
        current += c;
      }
    }

    if (!current.empty()) {
      result.push_back(current);
    }

    return result;
  }

  bool is_palindrome(std::string str) {
    // 转换为小写并移除空格
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);

    std::string reversed = str;
    std::reverse(reversed.begin(), reversed.end());
    return str == reversed;
  }
};

// =============================================================================
// 基础测试用例
// =============================================================================

TEST_CASE("Calculator basic operations", "[calculator]") {
  Calculator calc;

  SECTION("Addition") {
    REQUIRE(calc.add(2, 3) == 5);
    REQUIRE(calc.add(-1, 1) == 0);
    REQUIRE(calc.add(0, 0) == 0);
    REQUIRE(calc.add(1.5, 2.5) == Catch::Approx(4.0));
  }

  SECTION("Subtraction") {
    REQUIRE(calc.subtract(5, 3) == 2);
    REQUIRE(calc.subtract(0, 5) == -5);
    REQUIRE(calc.subtract(-3, -5) == 2);
  }

  SECTION("Multiplication") {
    REQUIRE(calc.multiply(3, 4) == 12);
    REQUIRE(calc.multiply(-2, 5) == -10);
    REQUIRE(calc.multiply(0, 100) == 0);
    REQUIRE(calc.multiply(1.5, 2) == Catch::Approx(3.0));
  }

  SECTION("Division") {
    REQUIRE(calc.divide(10, 2) == 5);
    REQUIRE(calc.divide(7, 2) == Catch::Approx(3.5));
    REQUIRE(calc.divide(-8, 4) == -2);

    // 测试除零异常
    REQUIRE_THROWS_AS(calc.divide(5, 0), std::invalid_argument);
    REQUIRE_THROWS_WITH(calc.divide(1, 0), "Division by zero");
  }
}

TEST_CASE("String processing operations", "[string]") {
  StringProcessor processor;

  SECTION("Convert to uppercase") {
    REQUIRE(processor.to_upper("hello") == "HELLO");
    REQUIRE(processor.to_upper("World") == "WORLD");
    REQUIRE(processor.to_upper("") == "");
    REQUIRE(processor.to_upper("123abc") == "123ABC");
  }

  SECTION("String reversal") {
    REQUIRE(processor.reverse("hello") == "olleh");
    REQUIRE(processor.reverse("") == "");
    REQUIRE(processor.reverse("a") == "a");
    REQUIRE(processor.reverse("12345") == "54321");
  }

  SECTION("String splitting") {
    auto result = processor.split("a,b,c", ',');
    std::vector<std::string> expected = {"a", "b", "c"};
    REQUIRE(result == expected);

    auto result2 = processor.split("hello world test", ' ');
    REQUIRE(result2.size() == 3);
    REQUIRE(result2[0] == "hello");
    REQUIRE(result2[2] == "test");
  }

  SECTION("Palindrome detection") {
    REQUIRE(processor.is_palindrome("racecar") == true);
    REQUIRE(processor.is_palindrome("hello") == false);
    REQUIRE(processor.is_palindrome("A man a plan a canal Panama") == true);
    REQUIRE(processor.is_palindrome("race a car") == false);
  }
}

// =============================================================================
// 参数化测试
// =============================================================================

TEST_CASE("Parameterized tests with GENERATE", "[parameterized]") {
  Calculator calc;

  SECTION("Even numbers") {
    int number = GENERATE(2, 4, 6, 8, 10, 100, -2, -4);
    REQUIRE(calc.is_even(number) == true);
  }

  SECTION("Odd numbers") {
    int number = GENERATE(1, 3, 5, 7, 9, 99, -1, -3);
    REQUIRE(calc.is_even(number) == false);
  }

  SECTION("Addition commutativity") {
    auto [a, b] = GENERATE(table<double, double>({{1, 2}, {3, 4}, {-1, 5}, {0, 0}, {2.5, 1.5}}));

    REQUIRE(calc.add(a, b) == Catch::Approx(calc.add(b, a)));
  }
}

// =============================================================================
// 匹配器测试
// =============================================================================

TEST_CASE("String matchers", "[matchers]") {
  SECTION("String content matching") {
    std::string text = "Hello World";
    REQUIRE_THAT(text, Catch::Matchers::StartsWith("Hello"));
    REQUIRE_THAT(text, Catch::Matchers::EndsWith("World"));
    // Contains 在这个版本中可能不可用，使用手动检查
    REQUIRE(text.find("lo Wo") != std::string::npos);
  }
}

// =============================================================================
// 浮点数比较测试
// =============================================================================

TEST_CASE("Floating point comparisons", "[floating_point]") {
  Calculator calc;

  SECTION("Approximate equality") {
    REQUIRE(calc.divide(1, 3) == Catch::Approx(0.33333).epsilon(0.01));
    REQUIRE(calc.multiply(0.1, 10) == Catch::Approx(1.0));
    REQUIRE(calc.divide(22, 7) == Catch::Approx(3.14159).epsilon(0.01));
  }
}

// =============================================================================
// 性能测试
// =============================================================================

TEST_CASE("Performance benchmarks", "[benchmark]") {
  StringProcessor processor;
  Calculator calc;

  BENCHMARK("String uppercase conversion") {
    return processor.to_upper("This is a test string for benchmarking purposes");
  };

  BENCHMARK("Simple arithmetic") { return calc.add(123.456, 789.123); };
}

int main(int argc, char* argv[]) {
  std::cout << "🧪 Catch2 现代C++测试框架演示\n";
  std::cout << "==============================\n\n";

  std::cout << "\n✅ Catch2 示例编译成功!\n";
  std::cout << "\n📚 Catch2 主要特性:\n";
  std::cout << "  • BDD风格的测试语法\n";
  std::cout << "  • 丰富的断言和匹配器\n";
  std::cout << "  • 参数化测试支持\n";
  std::cout << "  • 内置基准测试\n";
  std::cout << "  • 异常测试支持\n";
  std::cout << "  • 头文件库，易于集成\n";
  std::cout << "  • 详细的测试报告\n";
  std::cout << "\n要运行测试，请使用: catch2_example.exe\n";

  return 0;
}
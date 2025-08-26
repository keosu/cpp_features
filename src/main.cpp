#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "../include/utils.h"

namespace modern_cpp_showcase {

class FeatureShowcase {
 private:
  struct FeatureCategory {
    std::string name;
    std::string description;
    std::vector<std::pair<std::string, std::function<void()>>> features;
  };

  std::vector<FeatureCategory> categories;

 public:
  FeatureShowcase() { setup_categories(); }

  void run() {
    cpp_features::Demo::print_header("Modern C++ Features Interactive Showcase");

    std::cout << "Welcome to the Modern C++ Features Showcase!\n";
    std::cout << "This program demonstrates features from C++11 through C++23.\n\n";

    while (true) {
      show_main_menu();

      int choice = get_user_input("Enter your choice: ");

      if (choice == 0) {
        std::cout << "\nThank you for exploring Modern C++ features!\n";
        break;
      }

      if (choice >= 1 && choice <= static_cast<int>(categories.size())) {
        show_category_menu(choice - 1);
      } else {
        std::cout << "\nInvalid choice. Please try again.\n";
      }
    }
  }

 private:
  void setup_categories() {
    // C++11 Features
    categories.push_back(
        {"C++11 Features",
         "The foundation of modern C++ with auto, lambdas, smart pointers, and more",
         {{"Auto Keyword", []() { demo_cpp11_auto(); }},
          {"Lambda Expressions", []() { demo_cpp11_lambdas(); }},
          {"Smart Pointers", []() { demo_cpp11_smart_pointers(); }},
          {"Range-based For", []() { demo_cpp11_range_for(); }},
          {"Threading & Atomics", []() { demo_cpp11_threading(); }},
          {"All C++11 Features", []() { demo_all_cpp11(); }}}});

    // C++14 Features
    categories.push_back({"C++14 Features",
                          "Incremental improvements with generic lambdas and return type deduction",
                          {{"Generic Lambdas", []() { demo_cpp14_generic_lambdas(); }},
                           {"Return Type Deduction", []() { demo_cpp14_auto_return(); }},
                           {"Binary Literals", []() { demo_cpp14_binary_literals(); }},
                           {"Variable Templates", []() { demo_cpp14_variable_templates(); }},
                           {"std::make_unique", []() { demo_cpp14_make_unique(); }},
                           {"All C++14 Features", []() { demo_all_cpp14(); }}}});

    // C++17 Features
    categories.push_back({"C++17 Features",
                          "Major language improvements with structured bindings and std::optional",
                          {{"Structured Bindings", []() { demo_cpp17_structured_bindings(); }},
                           {"if constexpr", []() { demo_cpp17_if_constexpr(); }},
                           {"std::optional", []() { demo_cpp17_optional(); }},
                           {"std::variant", []() { demo_cpp17_variant(); }},
                           {"std::string_view", []() { demo_cpp17_string_view(); }},
                           {"Fold Expressions", []() { demo_cpp17_fold_expressions(); }},
                           {"All C++17 Features", []() { demo_all_cpp17(); }}}});

    // C++20 Features
    categories.push_back({"C++20 Features",
                          "Revolutionary changes with concepts, ranges, and coroutines",
                          {{"Concepts", []() { demo_cpp20_concepts(); }},
                           {"Ranges", []() { demo_cpp20_ranges(); }},
                           {"std::span", []() { demo_cpp20_span(); }},
                           {"Three-way Comparison", []() { demo_cpp20_spaceship(); }},
                           {"std::format", []() { demo_cpp20_format(); }},
                           {"Coroutines", []() { demo_cpp20_coroutines(); }},
                           {"All C++20 Features", []() { demo_all_cpp20(); }}}});

    // C++23 Features
    categories.push_back({"C++23 Features",
                          "Latest additions with std::expected and improved ranges",
                          {{"std::print", []() { demo_cpp23_print(); }},
                           {"std::expected", []() { demo_cpp23_expected(); }},
                           {"Flat Containers", []() { demo_cpp23_flat_containers(); }},
                           {"Deducing this", []() { demo_cpp23_deducing_this(); }},
                           {"Ranges Improvements", []() { demo_cpp23_ranges(); }},
                           {"All C++23 Features", []() { demo_all_cpp23(); }}}});

    // Comprehensive Demo
    categories.push_back({"Complete Journey",
                          "Full demonstration of all C++ standards from C++11 to C++23",
                          {{"Evolution Overview", []() { demo_cpp_evolution(); }},
                           {"Performance Comparison", []() { demo_performance_comparison(); }},
                           {"Best Practices", []() { demo_best_practices(); }},
                           {"Full Showcase", []() { demo_complete_showcase(); }}}});
  }

  void show_main_menu() {
    std::cout << "\n" << std::string(70, '=') << "\n";
    std::cout << "                    MAIN MENU\n";
    std::cout << std::string(70, '=') << "\n";

    for (size_t i = 0; i < categories.size(); ++i) {
      std::cout << std::setw(2) << (i + 1) << ". " << std::setw(20) << std::left
                << categories[i].name << " - " << categories[i].description << "\n";
    }

    std::cout << " 0. Exit\n";
    std::cout << std::string(70, '=') << "\n";
  }

  void show_category_menu(size_t category_index) {
    const auto& category = categories[category_index];

    while (true) {
      std::cout << "\n" << std::string(70, '-') << "\n";
      std::cout << "  " << category.name << "\n";
      std::cout << "  " << category.description << "\n";
      std::cout << std::string(70, '-') << "\n";

      for (size_t i = 0; i < category.features.size(); ++i) {
        std::cout << std::setw(2) << (i + 1) << ". " << category.features[i].first << "\n";
      }

      std::cout << " 0. Back to Main Menu\n";
      std::cout << std::string(70, '-') << "\n";

      int choice = get_user_input("Enter your choice: ");

      if (choice == 0) {
        break;
      }

      if (choice >= 1 && choice <= static_cast<int>(category.features.size())) {
        std::cout << "\n";
        category.features[choice - 1].second();
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore();
        std::cin.get();
      } else {
        std::cout << "\nInvalid choice. Please try again.\n";
      }
    }
  }

  int get_user_input(const std::string& prompt) {
    std::cout << prompt;
    std::string input;
    std::getline(std::cin, input);

    std::istringstream iss(input);
    int value;
    if (!(iss >> value)) {
      return -1;  // Invalid input
    }
    return value;
  }

  // Feature demonstration functions
  static void demo_cpp11_auto() {
    cpp_features::Demo::print_header("C++11 - Auto Keyword");

    auto number = 42;
    auto text = "Hello C++11";
    std::vector<int> vec = {1, 2, 3};
    auto it = vec.begin();

    cpp_features::Demo::print_value("Auto int", number);
    cpp_features::Demo::print_value("Auto text", text);
    cpp_features::Demo::print_value("Iterator value", *it);
  }

  static void demo_cpp11_lambdas() {
    cpp_features::Demo::print_header("C++11 - Lambda Expressions");

    auto square = [](int x) { return x * x; };
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    std::cout << "  Original: ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << "\n";

    std::transform(numbers.begin(), numbers.end(), numbers.begin(), square);

    std::cout << "  Squared:  ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << "\n";
  }

  static void demo_cpp11_smart_pointers() {
    cpp_features::Demo::print_header("C++11 - Smart Pointers");

    {
      // C++11 way - using constructor (make_unique is C++14)
      std::unique_ptr<int> ptr(new int(42));
      cpp_features::Demo::print_value("unique_ptr value", *ptr);
    }
    std::cout << "  unique_ptr automatically cleaned up\n";

    auto shared1 = std::make_shared<std::string>("Shared Resource");
    {
      auto shared2 = shared1;
      cpp_features::Demo::print_value("Reference count", shared1.use_count());
    }
    cpp_features::Demo::print_value("Reference count after scope", shared1.use_count());
  }

  static void demo_cpp11_range_for() {
    cpp_features::Demo::print_header("C++11 - Range-based For");

    std::vector<std::string> fruits = {"apple", "banana", "cherry"};

    std::cout << "  Fruits:\n";
    for (const auto& fruit : fruits) {
      std::cout << "    - " << fruit << "\n";
    }
  }

  static void demo_cpp11_threading() {
    cpp_features::Demo::print_header("C++11 - Threading");
    std::cout << "  Basic threading demonstration\n";
    std::cout << "  (Simplified for interactive demo)\n";
  }

  static void demo_all_cpp11() {
    std::cout << "\n🚀 Running complete C++11 demo program...\n";
    // Here you would call the actual C++11 program
    system("./bin/cpp11_features");
  }

  // C++14 demos
  static void demo_cpp14_generic_lambdas() {
    cpp_features::Demo::print_header("C++14 - Generic Lambdas");

    auto generic_printer = [](const auto& value) {
      std::cout << "  Value: " << value << " (size: " << sizeof(value) << ")\n";
    };

    generic_printer(42);
    generic_printer(3.14);
    generic_printer("Hello");
  }

  static void demo_cpp14_auto_return() {
    cpp_features::Demo::print_header("C++14 - Auto Return Type");

    auto factorial = [](int n) {
      if (n <= 1) return 1;
      int result = 1;
      for (int i = 2; i <= n; ++i) {
        result *= i;
      }
      return result;
    };

    cpp_features::Demo::print_value("5! = ", factorial(5));
  }

  static void demo_cpp14_binary_literals() {
    cpp_features::Demo::print_header("C++14 - Binary Literals");

    auto binary = 0b1010'1100;  // With digit separators
    auto large_number = 1'000'000;

    cpp_features::Demo::print_value("Binary 0b1010'1100", binary);
    cpp_features::Demo::print_value("Large number 1'000'000", large_number);
  }

}  // namespace modern_cpp_showcase

// Template needs to be at global scope
template <typename T>
constexpr T pi = T(3.1415926535897932385);

namespace modern_cpp_showcase {

static void demo_cpp14_variable_templates() {
  cpp_features::Demo::print_header("C++14 - Variable Templates");

  cpp_features::Demo::print_value("pi<float>", pi<float>);
  cpp_features::Demo::print_value("pi<double>", pi<double>);
}

static void demo_cpp14_make_unique() {
  cpp_features::Demo::print_header("C++14 - std::make_unique");

  auto resource = std::make_unique<std::vector<int>>(10, 42);
  cpp_features::Demo::print_value("Vector size", resource->size());
  cpp_features::Demo::print_value("First element", (*resource)[0]);
}

static void demo_all_cpp14() {
  std::cout << "\n🚀 Running complete C++14 demo program...\n";
  system("./bin/cpp14_features");
}

// Similar implementations for C++17, C++20, C++23...
static void demo_cpp17_structured_bindings() {
  cpp_features::Demo::print_header("C++17 - Structured Bindings");

  auto person = std::make_tuple("Alice", 30, 75.5);
  auto [name, age, weight] = person;

  cpp_features::Demo::print_value("Name", name);
  cpp_features::Demo::print_value("Age", age);
  cpp_features::Demo::print_value("Weight", weight);
}

static void demo_cpp17_if_constexpr() {
  cpp_features::Demo::print_header("C++17 - if constexpr");
  std::cout << "  Compile-time conditional compilation\n";
  std::cout << "  Enables more efficient template code\n";
}

static void demo_cpp17_optional() {
  cpp_features::Demo::print_header("C++17 - std::optional");

  auto safe_divide = [](double a, double b) -> std::optional<double> {
    if (b == 0) return std::nullopt;
    return a / b;
  };

  auto result1 = safe_divide(10, 2);
  auto result2 = safe_divide(10, 0);

  if (result1) {
    cpp_features::Demo::print_value("10 / 2", *result1);
  }

  if (!result2) {
    std::cout << "  10 / 0: Division by zero\n";
  }
}

static void demo_cpp17_variant() {
  cpp_features::Demo::print_header("C++17 - std::variant");
  std::cout << "  Type-safe union replacement\n";
}

static void demo_cpp17_string_view() {
  cpp_features::Demo::print_header("C++17 - std::string_view");
  std::cout << "  Efficient string handling without copies\n";
}

static void demo_cpp17_fold_expressions() {
  cpp_features::Demo::print_header("C++17 - Fold Expressions");
  std::cout << "  Variadic template simplification\n";
}

static void demo_all_cpp17() {
  std::cout << "\n🚀 Running complete C++17 demo program...\n";
  system("./bin/cpp17_features");
}

// C++20 demos
static void demo_cpp20_concepts() {
  cpp_features::Demo::print_header("C++20 - Concepts");
  std::cout << "  Type constraints for templates\n";
}

static void demo_cpp20_ranges() {
  cpp_features::Demo::print_header("C++20 - Ranges");
  std::cout << "  Functional programming style algorithms\n";
}

static void demo_cpp20_span() {
  cpp_features::Demo::print_header("C++20 - std::span");
  std::cout << "  Safe array/container view\n";
}

static void demo_cpp20_spaceship() {
  cpp_features::Demo::print_header("C++20 - Three-way Comparison");
  std::cout << "  Simplified comparison operators\n";
}

static void demo_cpp20_format() {
  cpp_features::Demo::print_header("C++20 - std::format");
  std::cout << "  Modern string formatting\n";
}

static void demo_cpp20_coroutines() {
  cpp_features::Demo::print_header("C++20 - Coroutines");
  std::cout << "  Asynchronous programming support\n";
}

static void demo_all_cpp20() {
  std::cout << "\n🚀 Running complete C++20 demo program...\n";
  system("./bin/cpp20_features");
}

// C++23 demos
static void demo_cpp23_print() {
  cpp_features::Demo::print_header("C++23 - std::print");
  std::cout << "  Simplified output operations\n";
}

static void demo_cpp23_expected() {
  cpp_features::Demo::print_header("C++23 - std::expected");
  std::cout << "  Error handling without exceptions\n";
}

static void demo_cpp23_flat_containers() {
  cpp_features::Demo::print_header("C++23 - Flat Containers");
  std::cout << "  Cache-friendly container alternatives\n";
}

static void demo_cpp23_deducing_this() {
  cpp_features::Demo::print_header("C++23 - Deducing this");
  std::cout << "  Simplified method chaining\n";
}

static void demo_cpp23_ranges() {
  cpp_features::Demo::print_header("C++23 - Ranges Improvements");
  std::cout << "  Enhanced range algorithms and views\n";
}

static void demo_all_cpp23() {
  std::cout << "\n🚀 Running complete C++23 demo program...\n";
  system("./bin/cpp23_features");
}

// Complete journey demos
static void demo_cpp_evolution() {
  cpp_features::Demo::print_header("C++ Evolution Timeline");

  std::cout << "  C++11 (2011): Modern C++ foundation\n";
  std::cout << "    • Auto, lambdas, smart pointers, threading\n\n";

  std::cout << "  C++14 (2014): Incremental improvements\n";
  std::cout << "    • Generic lambdas, return type deduction\n\n";

  std::cout << "  C++17 (2017): Major language improvements\n";
  std::cout << "    • Structured bindings, optional, variant\n\n";

  std::cout << "  C++20 (2020): Revolutionary changes\n";
  std::cout << "    • Concepts, ranges, coroutines, modules\n\n";

  std::cout << "  C++23 (2023): Latest refinements\n";
  std::cout << "    • std::expected, flat containers, std::print\n";
}

static void demo_performance_comparison() {
  cpp_features::Demo::print_header("Performance Evolution");
  std::cout << "  Modern C++ features often improve performance:\n";
  std::cout << "  • Move semantics reduce copying\n";
  std::cout << "  • constexpr enables compile-time computation\n";
  std::cout << "  • Ranges provide lazy evaluation\n";
  std::cout << "  • Concepts improve compile-time errors\n";
}

static void demo_best_practices() {
  cpp_features::Demo::print_header("Modern C++ Best Practices");
  std::cout << "  1. Use auto for type deduction\n";
  std::cout << "  2. Prefer smart pointers over raw pointers\n";
  std::cout << "  3. Use range-based for loops\n";
  std::cout << "  4. Embrace lambdas for local functionality\n";
  std::cout << "  5. Use std::optional instead of null checks\n";
  std::cout << "  6. Apply concepts for template constraints\n";
  std::cout << "  7. Leverage ranges for functional programming\n";
}

static void demo_complete_showcase() {
  std::cout << "\n🎉 Running ALL C++ standard demonstrations...\n\n";

  std::cout << "1. C++11 Features:\n";
  system("./bin/cpp11_features");

  std::cout << "\n2. C++14 Features:\n";
  system("./bin/cpp14_features");

  std::cout << "\n3. C++17 Features:\n";
  system("./bin/cpp17_features");

  std::cout << "\n4. C++20 Features:\n";
  system("./bin/cpp20_features");

  std::cout << "\n5. C++23 Features:\n";
  system("./bin/cpp23_features");

  std::cout << "\n🏁 Complete showcase finished!\n";
}
};  // namespace modern_cpp_showcase

}  // namespace modern_cpp_showcase

int main() {
  try {
    modern_cpp_showcase::FeatureShowcase showcase;
    showcase.run();
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
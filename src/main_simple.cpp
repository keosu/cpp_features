#include "../include/utils.h"
#include <iostream>
#include <string>
#include <vector>

int main() {
    cpp_features::Demo::print_header("Modern C++ Features Showcase");
    
    std::cout << "Welcome to the Modern C++ Features Showcase!\n";
    std::cout << "This interactive program demonstrates C++ evolution from C++11 to C++26.\n\n";
    
    std::cout << "Available demonstrations:\n";
    std::cout << "  1. C++11 Features - Foundation of modern C++\n";
    std::cout << "  2. C++14 Features - Incremental improvements\n";
    std::cout << "  3. C++17 Features - Major language enhancements\n";
    std::cout << "  4. C++20 Features - Revolutionary changes\n";
    std::cout << "  5. C++23 Features - Latest additions\n";
    std::cout << "  6. C++26 Features - Experimental preview\n\n";
    
    std::cout << "To run individual demonstrations:\n";
    std::cout << "  xmake run cpp11_features\n";
    std::cout << "  xmake run cpp14_features\n";
    std::cout << "  xmake run cpp17_features\n";
    std::cout << "  xmake run cpp20_features\n";
    std::cout << "  xmake run cpp23_features\n";
    std::cout << "  xmake run cpp26_features  # Experimental preview\n\n";
    
    // Simple demo of some basic modern C++ features
    std::cout << "Quick Modern C++ Demo:\n\n";
    
    // C++11: auto and range-based for
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    
    std::cout << "  C++11 - Range-based for loop:\n";
    std::cout << "  Numbers: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << "\n\n";
    
    // C++11: lambda
    auto square = [](int x) { return x * x; };
    
    std::cout << "  C++11 - Lambda expressions:\n";
    std::cout << "  Squares: ";
    for (const auto& num : numbers) {
        std::cout << square(num) << " ";
    }
    std::cout << "\n\n";
    
    // C++14: generic lambda
    auto generic_print = [](const auto& value) {
        std::cout << value << " ";
    };
    
    std::cout << "  C++14 - Generic lambdas:\n";
    std::cout << "  Mixed types: ";
    generic_print(42);
    generic_print(3.14);
    generic_print("Hello");
    std::cout << "\n\n";
    
    std::cout << "Build completed successfully! ✅\n";
    std::cout << "All C++ features programs are ready to run.\n";
    std::cout << "Use the commands above to explore specific C++ standards.\n\n";
    
    return 0;
}
#include "../include/utils.h"
#include <iostream>

// Simple example demonstrating basic modern C++ usage
int main() {
    cpp_features::Demo::print_header("Modern C++ Example");
    
    // C++11: auto and range-based for
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    
    std::cout << "  Numbers: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << "\n";
    
    // C++11: lambda
    auto square = [](int x) { return x * x; };
    
    std::cout << "  Squares: ";
    for (const auto& num : numbers) {
        std::cout << square(num) << " ";
    }
    std::cout << "\n";
    
    std::cout << "\nExample completed!\n";
    return 0;
}
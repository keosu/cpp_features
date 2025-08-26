# Modern C++ Features Showcase 🚀

[![C++ Standards](https://img.shields.io/badge/C%2B%2B-11%2F14%2F17%2F20%2F23-blue.svg)](https://en.cppreference.com/)
[![Build System](https://img.shields.io/badge/Build%20System-xmake-green.svg)](https://xmake.io)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/Platform-Windows%2FLinux%2FmacOS-lightgrey.svg)](#)

> 🎯 **一个全面展示C++演进历程的教学项目**  
> 从C++11的现代化基础到C++23的最新特性，通过可运行的代码示例学习现代C++

## ✨ 核心特性一览

### 🔥 **C++11 - 现代C++基石**
```cpp
// Auto类型推导 + Lambda表达式 + 智能指针
auto numbers = {1, 2, 3, 4, 5};
auto square = [](int x) { return x * x; };
auto ptr = std::make_unique<int>(42);
```

### ⚡ **C++17 - 语言重大革新**
```cpp
// 结构化绑定 + std::optional + if constexpr
auto [name, age, salary] = employee_data;
std::optional<int> maybe_value = safe_divide(10, 0);
if constexpr (std::is_integral_v<T>) { /* compile-time branch */ }
```

### 🌟 **C++20 - 革命性变化**
```cpp
// 概念约束 + 范围库 + 协程
template<std::integral T> T add(T a, T b) { return a + b; }
auto even_nums = nums | std::views::filter([](int n) { return n % 2 == 0; });
Task<int> async_compute() { co_return 42; }
```

### ✨ **C++23 - 最新进展**
```cpp
// std::expected + std::print + 扁平容器
std::expected<int, Error> result = safe_operation();
std::print("Hello {}!\n", "C++23");
std::flat_map<string, int> fast_lookup;
```

### 🚧 **C++26 - 实验性预览**
```cpp
// 反射 + 模式匹配 + 合约 (提案中)
constexpr auto members = std::meta::members_of(^MyClass);
auto result = value inspect { 0 => "zero", _ => "other" };
int divide(int a, int b) pre: b != 0 { return a/b; }
```

> ⚠️ **注意**: C++26特性仍在开发中，大部分特性为提案阶段

## 🚀 快速开始

### 1️⃣ 克隆并构建
```bash
# 克隆项目（如果从远程仓库）
git clone <repository-url>
cd cpp_features

# 构建所有程序
xmake
```

### 2️⃣ 运行演示
```bash
# 主程序 - 综合展示
xmake run modern_cpp_showcase

# 单独的C++标准演示
xmake run cpp11_features   # C++11特性
xmake run cpp17_features   # C++17特性  
xmake run cpp20_features   # C++20特性
xmake run cpp26_features   # C++26预览 (实验性)
```

### 3️⃣ 浏览源代码
- 📁 **`src/cpp11/main.cpp`** - C++11基础特性（auto, lambda, 智能指针）
- 📁 **`src/cpp17/main.cpp`** - C++17语言增强（结构化绑定, optional, variant）
- 📁 **`src/cpp20/main.cpp`** - C++20革命性特性（concepts, ranges, coroutines）
- 📁 **`src/cpp26/main.cpp`** - C++26实验预览（reflection, pattern matching, contracts）

## 📈 版本特性对比

| 📅 版本 | 🚀 核心特性 | 📊 影响级别 | 📝 示例代码 |
|---------|------------|------------|------------|
| **C++11** | Auto, Lambda, Smart Pointers | 🔴 **革命性** | `auto ptr = std::make_unique<T>();` |
| **C++14** | Generic Lambdas, Auto Return | 🟡 **增量式** | `auto func = [](auto x) { return x; };` |
| **C++17** | Structured Bindings, Optional | 🟠 **重大** | `auto [x, y] = std::make_pair(1, 2);` |
| **C++20** | Concepts, Ranges, Coroutines | 🔴 **革命性** | `std::ranges::sort(container);` |
| **C++23** | Expected, Print, Flat Maps | 🟢 **改进** | `std::print("Hello {}!\n", name);` |
| **C++26** | Reflection, Pattern Matching | 🚧 **实验** | `auto result = val inspect { 0 => "zero" };` |

## 🎆 项目亮点

✨ **全面性**: 从 C++11 到 C++23 的完整覆盖  
🛠️ **现代化**: 使用 xmake 现代构建系统  
📚 **教学导向**: 每个特性都有详细的代码示例和说明  
🚀 **即用**: 克隆即可运行，无需复杂配置  
🌐 **跨平台**: 支持 Windows/Linux/macOS  
📝 **文档完善**: 详细的 README 和代码注释  
🔍 **实用性**: 可作为学习资源或面试准备

## 🚀 Project Overview

This project demonstrates the key features introduced in modern C++ standards:

- **C++11**: Foundation of modern C++ (auto, lambdas, smart pointers, threading)
- **C++14**: Incremental improvements (generic lambdas, return type deduction)
- **C++17**: Major language enhancements (structured bindings, std::optional, std::variant)
- **C++20**: Revolutionary changes (concepts, ranges, coroutines, modules)
- **C++23**: Latest additions (std::expected, flat containers, std::print)
- **C++26**: 🚧 **Experimental Preview** (reflection, pattern matching, contracts)

## 📁 Project Structure

```
cpp_features/
├── xmake.lua                 # Build configuration
├── README.md                 # This file
├── include/
│   └── utils.h              # Common utilities for demonstrations
├── src/
│   ├── main.cpp             # Interactive showcase menu
│   ├── cpp11/
│   │   └── main.cpp         # C++11 features demonstration
│   ├── cpp14/
│   │   └── main.cpp         # C++14 features demonstration  
│   ├── cpp17/
│   │   └── main.cpp         # C++17 features demonstration
│   ├── cpp20/
│   │   └── main.cpp         # C++20 features demonstration
│   ├── cpp23/
│   │   └── main.cpp         # C++23 features demonstration
│   └── utils/               # Utility implementations
├── examples/                # Additional example code
├── tests/                   # Unit tests
└── bin/                     # Compiled binaries
```

## 🛠 Prerequisites

### Required
- **xmake**: Build system ([Download](https://xmake.io))
- **C++ Compiler**: Supporting C++23 (GCC 12+, Clang 15+, MSVC 2022+)

### Optional Dependencies
The project will automatically install these via xmake:
- **fmt**: Modern formatting library
- **range-v3**: Range library implementation

## 🔧 Building the Project

### 1. Install xmake

**Windows:**
```powershell
Invoke-Expression (Invoke-WebRequest 'https://xmake.io/psget.text' -UseBasicParsing).Content
```

**Linux/macOS:**
```bash
curl -fsSL https://xmake.io/shget.text | bash
```

### 2. Build the project

```bash
# Configure and build all targets
xmake

# Build specific target
xmake build cpp11_features
xmake build cpp17_features
xmake build modern_cpp_showcase

# Clean build
xmake clean
xmake
```

### 3. Run demonstrations

```bash
# Interactive showcase menu
xmake run modern_cpp_showcase

# Individual C++ standard demos
xmake run cpp11_features
xmake run cpp14_features
xmake run cpp17_features
xmake run cpp20_features
xmake run cpp23_features
xmake run cpp26_features   # Experimental preview

# Run examples
xmake run examples
```

## 📚 Features Demonstrated

### C++11 Features
- **Auto keyword**: Type deduction
- **Lambda expressions**: Anonymous functions
- **Smart pointers**: `unique_ptr`, `shared_ptr`, `weak_ptr`
- **Range-based for loops**: Simplified iteration
- **Move semantics**: Efficient resource management
- **Threading**: `std::thread`, `std::mutex`, `std::atomic`
- **Initializer lists**: Container initialization
- **`nullptr`**: Null pointer literal
- **`decltype`**: Type deduction
- **Variadic templates**: Template parameter packs

### C++14 Features
- **Generic lambdas**: Template lambda parameters
- **Return type deduction**: `auto` return types
- **Binary literals**: `0b1010` syntax
- **Digit separators**: `1'000'000` for readability
- **Variable templates**: Template variables
- **`std::make_unique`**: Factory function for unique_ptr
- **Extended `constexpr`**: More complex compile-time evaluation

### C++17 Features
- **Structured bindings**: `auto [a, b] = tuple`
- **`if constexpr`**: Compile-time conditionals
- **`std::optional`**: Optional values
- **`std::variant`**: Type-safe unions
- **`std::string_view`**: Non-owning string references
- **`std::any`**: Type-erased value storage
- **Fold expressions**: Variadic template operations
- **Class template argument deduction**: Automatic template parameters
- **Parallel algorithms**: `std::execution` policies
- **Nested namespaces**: `namespace A::B::C`

### C++20 Features
- **Concepts**: Template constraints and requirements
- **Ranges**: Functional programming algorithms
- **`std::span`**: Array/container views
- **Three-way comparison**: Spaceship operator (`<=>`)
- **`std::format`**: Modern string formatting
- **Coroutines**: `co_await`, `co_yield`, `co_return`
- **Modules**: `import`/`export` (where supported)
- **Mathematical constants**: `std::numbers::pi`
- **Bit operations**: `std::popcount`, `std::bit_width`
- **Designated initializers**: `{.member = value}`
- **Template lambdas**: Explicit template parameters
- **`consteval`**: Immediate functions

### C++23 Features
- **`std::print`**: Simplified output operations
- **`std::expected`**: Error handling without exceptions
- **Flat containers**: `std::flat_map`, `std::flat_set`
- **Multidimensional subscript**: `operator[](x, y)`
- **Deducing this**: Simplified CRTP and method chaining
- **`if consteval`**: Improved compile-time detection
- **`auto(x)` cast**: Explicit decay copying
- **Ranges improvements**: Additional views and algorithms
- **String contains**: `std::string::contains()`

### C++26 Features (Experimental Preview)
- **Reflection**: Compile-time type and member introspection
- **Pattern matching**: Structural matching with `inspect` expressions
- **Contracts**: Built-in precondition/postcondition assertions
- **Enhanced constexpr**: More compile-time capabilities
- **Improved modules**: Better tooling and standardization
- **Linear algebra**: Standard mathematical operations library
- **Networking**: Standard networking and socket interface
- **Advanced ranges**: Additional views and algorithms
- **Hazard pointers**: Lock-free memory reclamation

> ⚠️ **Important**: C++26 features are currently proposals and experimental. Most are not yet available in production compilers.

## 💡 Usage Examples

### Interactive Menu
The main program provides an interactive menu to explore features:

```cpp
// Run the interactive showcase
xmake run modern_cpp_showcase
```

### Individual Demonstrations
Each C++ standard has its own demonstration program:

```cpp
// C++17 structured bindings example
auto [name, age, salary] = get_employee_data();
std::cout << name << " is " << age << " years old\n";

// C++20 ranges example
auto even_squares = numbers 
    | std::views::filter([](int n) { return n % 2 == 0; })
    | std::views::transform([](int n) { return n * n; });
```

## 🔍 Compiler Support

Different compilers have varying levels of support for modern C++ features:

| Feature | GCC | Clang | MSVC |
|---------|-----|-------|------|
| C++11 | 4.8+ | 3.3+ | 2015+ |
| C++14 | 5.0+ | 3.4+ | 2015+ |
| C++17 | 7.0+ | 5.0+ | 2017+ |
| C++20 | 10.0+ | 10.0+ | 2019+ |
| C++23 | 12.0+ | 15.0+ | 2022+ |
| C++26 | 🚧 Experimental | 🚧 Experimental | 🚧 Experimental |

**Note**: C++26 is currently in development. Most features are experimental proposals and not yet available in production compilers.

## 🧪 Testing

Run the test suite to verify all features work correctly:

```bash
# Build and run tests
xmake build tests
xmake run tests
```

## 🚧 Troubleshooting

### Common Issues

1. **Compiler too old**: Ensure you have a C++23-capable compiler
2. **Missing features**: Some C++23 features may not be available in your compiler/stdlib
3. **Link errors**: Make sure all dependencies are properly installed

### Fallback Behavior
The code includes fallback implementations for features not yet supported:

```cpp
#ifdef __cpp_lib_expected
    // Use std::expected
#else
    // Fallback to std::optional or custom implementation
#endif
```

## 📖 Learning Resources

- [C++ Reference](https://cppreference.com/)
- [Modern C++ Guidelines](https://github.com/isocpp/CppCoreGuidelines)
- [C++11/14/17/20/23 Feature Overview](https://github.com/AnthonyCalandra/modern-cpp-features)

## 🤝 Contributing

Feel free to contribute by:
1. Adding more feature demonstrations
2. Improving existing examples
3. Adding support for newer compiler versions
4. Writing additional tests

## 📄 License

This project is provided as educational material for learning modern C++ features.

---

**Happy C++ Learning! 🎯**

Explore the evolution of C++ and see how the language has grown to become more expressive, safer, and more powerful with each standard revision.
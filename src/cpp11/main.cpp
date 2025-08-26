#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <functional>
#include <initializer_list>
#include <memory>
#include <mutex>
#include <thread>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "../include/utils.h"

namespace cpp11_features {

void demo_auto_keyword() {
  cpp_features::Demo::print_section("Auto Keyword");

  // Auto type deduction
  auto number = 42;           // int
  auto floating = 3.14;       // double
  auto text = "Hello C++11";  // const char*

  std::vector<int> vec = {1, 2, 3, 4, 5};
  auto it = vec.begin();  // std::vector<int>::iterator

  cpp_features::Demo::print_value("Auto int", number);
  cpp_features::Demo::print_value("Auto double", floating);
  cpp_features::Demo::print_value("Auto string", text);
  cpp_features::Demo::print_value("Vector first element", *it);
}

void demo_lambda_expressions() {
  cpp_features::Demo::print_section("Lambda Expressions");

  std::vector<int> numbers = {5, 2, 8, 1, 9, 3};

  // Simple lambda
  auto square = [](int x) { return x * x; };
  cpp_features::Demo::print_value("Square of 5", square(5));

  // Lambda with capture
  int multiplier = 3;
  auto multiply = [multiplier](int x) { return x * multiplier; };
  cpp_features::Demo::print_value("7 * 3", multiply(7));

  // Lambda for sorting
  std::sort(numbers.begin(), numbers.end(), [](int a, int b) {
    return a > b;  // Descending order
  });

  std::cout << "  Sorted (desc): ";
  for (const auto& num : numbers) {
    std::cout << num << " ";
  }
  std::cout << "\n";
}

class ResourceManager {
 private:
  std::string name;

 public:
  ResourceManager(const std::string& n) : name(n) {
    std::cout << "  Resource '" << name << "' created\n";
  }

  ~ResourceManager() { std::cout << "  Resource '" << name << "' destroyed\n"; }

  void use() { std::cout << "  Using resource '" << name << "'\n"; }
};

void demo_smart_pointers() {
  cpp_features::Demo::print_section("Smart Pointers");

  // unique_ptr
  {
    std::cout << "  unique_ptr example:\n";
    auto resource = std::make_unique<ResourceManager>("unique_resource");
    resource->use();
    // Automatically destroyed when going out of scope
  }

  // shared_ptr
  {
    std::cout << "\n  shared_ptr example:\n";
    auto resource1 = std::make_shared<ResourceManager>("shared_resource");
    {
      auto resource2 = resource1;  // Shared ownership
      cpp_features::Demo::print_value("Reference count", resource1.use_count());
      resource2->use();
    }
    cpp_features::Demo::print_value("Reference count after scope", resource1.use_count());
    resource1->use();
    // Destroyed when last shared_ptr is destroyed
  }
}

void demo_range_based_for() {
  cpp_features::Demo::print_section("Range-based For Loop");

  std::vector<std::string> fruits = {"apple", "banana", "cherry", "date"};

  std::cout << "  Fruits: ";
  for (const auto& fruit : fruits) {
    std::cout << fruit << " ";
  }
  std::cout << "\n";

  // With index (C++11 way)
  std::cout << "  With index:\n";
  for (size_t i = 0; i < fruits.size(); ++i) {
    cpp_features::Demo::print_value(std::to_string(i), fruits[i]);
  }
}

void demo_initializer_lists() {
  cpp_features::Demo::print_section("Initializer Lists");

  // Vector initialization
  std::vector<int> numbers = {1, 2, 3, 4, 5};

  // Array initialization
  std::array<double, 4> values = {1.1, 2.2, 3.3, 4.4};

  // Map initialization
  std::unordered_map<std::string, int> ages = {{"Alice", 25}, {"Bob", 30}, {"Charlie", 35}};

  std::cout << "  Vector: ";
  for (const auto& num : numbers) {
    std::cout << num << " ";
  }
  std::cout << "\n";

  std::cout << "  Ages:\n";
  for (const auto& pair : ages) {
    cpp_features::Demo::print_value(pair.first, pair.second);
  }
}

void demo_nullptr() {
  cpp_features::Demo::print_section("nullptr");

  int* ptr1 = nullptr;  // Better than NULL
  std::unique_ptr<int> ptr2 = nullptr;

  auto check_null = [](void* p) { return p == nullptr ? "null" : "not null"; };

  cpp_features::Demo::print_value("ptr1 status", check_null(ptr1));
  cpp_features::Demo::print_value("ptr2 status", check_null(ptr2.get()));
}

void demo_decltype() {
  cpp_features::Demo::print_section("decltype");

  int x = 42;
  double y = 3.14;

  // Use decltype to deduce types
  decltype(x) another_int = 100;
  decltype(y) another_double = 2.71;
  decltype(x + y) sum = x + y;  // double (int + double = double)

  cpp_features::Demo::print_value("another_int", another_int);
  cpp_features::Demo::print_value("another_double", another_double);
  cpp_features::Demo::print_value("sum (x + y)", sum);
}

std::atomic<int> counter{0};
std::mutex print_mutex;

void worker_thread(int id) {
  for (int i = 0; i < 5; ++i) {
    counter.fetch_add(1);

    {
      std::lock_guard<std::mutex> lock(print_mutex);
      std::cout << "    Thread " << id << " increment: " << counter.load() << "\n";
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

void demo_threading() {
  cpp_features::Demo::print_section("Threading and Atomics");

  counter.store(0);

  std::vector<std::thread> threads;

  // Create worker threads
  for (int i = 0; i < 3; ++i) {
    threads.emplace_back(worker_thread, i + 1);
  }

  // Wait for all threads to complete
  for (auto& t : threads) {
    t.join();
  }

  cpp_features::Demo::print_value("Final counter value", counter.load());
}

void demo_tuples() {
  cpp_features::Demo::print_section("Tuples");

  // Create tuple
  auto person = std::make_tuple("John Doe", 30, 75.5);

  // Access elements
  std::string name = std::get<0>(person);
  int age = std::get<1>(person);
  double weight = std::get<2>(person);

  cpp_features::Demo::print_value("Name", name);
  cpp_features::Demo::print_value("Age", age);
  cpp_features::Demo::print_value("Weight", weight);

  // Tuple size
  constexpr size_t tuple_size = std::tuple_size<decltype(person)>::value;
  cpp_features::Demo::print_value("Tuple size", tuple_size);
}

}  // namespace cpp11_features

int main() {
  cpp_features::Demo::print_header("C++11 Features Showcase");

  cpp11_features::demo_auto_keyword();
  cpp11_features::demo_lambda_expressions();
  cpp11_features::demo_smart_pointers();
  cpp11_features::demo_range_based_for();
  cpp11_features::demo_initializer_lists();
  cpp11_features::demo_nullptr();
  cpp11_features::demo_decltype();
  cpp11_features::demo_threading();
  cpp11_features::demo_tuples();

  std::cout << "\nC++11 features demonstration completed!\n";
  return 0;
}
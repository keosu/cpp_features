#include <fstream>
#include <iostream>
#include <map>
#include <optional>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

// 使用便捷别名
using json = nlohmann::json;

// 自定义类，演示序列化/反序列化
struct Person {
  std::string name;
  int age;
  std::vector<std::string> hobbies;
  std::optional<std::string> email;

  Person() = default;
  Person(const std::string& n, int a) : name(n), age(a) {}
};

// 为Person类定义JSON序列化
void to_json(json& j, const Person& p) {
  j = json{{"name", p.name}, {"age", p.age}, {"hobbies", p.hobbies}};
  if (p.email) {
    j["email"] = *p.email;
  }
}

// 为Person类定义JSON反序列化
void from_json(const json& j, Person& p) {
  j.at("name").get_to(p.name);
  j.at("age").get_to(p.age);
  j.at("hobbies").get_to(p.hobbies);

  // 可选字段
  if (j.contains("email")) {
    p.email = j.at("email").get<std::string>();
  }
}

void demo_basic_json_operations() {
  std::cout << "\n=== 基础JSON操作 ===\n";

  // 创建JSON对象
  json person;
  person["name"] = "Alice";
  person["age"] = 25;
  person["city"] = "New York";
  person["married"] = false;

  std::cout << "  创建的JSON: " << person.dump(2) << "\n\n";

  // 访问JSON值
  std::cout << "  姓名: " << person["name"] << "\n";
  std::cout << "  年龄: " << person["age"] << "\n";
  std::cout << "  城市: " << person["city"] << "\n";
  std::cout << "  已婚: " << person["married"] << "\n";

  // 类型检查
  std::cout << "\n  类型信息:\n";
  std::cout << "    name 是字符串: " << person["name"].is_string() << "\n";
  std::cout << "    age 是数字: " << person["age"].is_number() << "\n";
  std::cout << "    married 是布尔: " << person["married"].is_boolean() << "\n";
}

void demo_array_operations() {
  std::cout << "\n=== JSON数组操作 ===\n";

  // 创建数组
  json numbers = json::array({1, 2, 3, 4, 5});
  json fruits = {"apple", "banana", "cherry"};

  std::cout << "  数字数组: " << numbers << "\n";
  std::cout << "  水果数组: " << fruits << "\n";

  // 数组操作
  numbers.push_back(6);
  fruits[1] = "blueberry";  // 替换元素

  std::cout << "  修改后的数字数组: " << numbers << "\n";
  std::cout << "  修改后的水果数组: " << fruits << "\n";

  // 遍历数组
  std::cout << "\n  遍历数组:\n";
  for (size_t i = 0; i < numbers.size(); ++i) {
    std::cout << "    索引 " << i << ": " << numbers[i] << "\n";
  }

  // 使用迭代器
  std::cout << "\n  使用迭代器:\n";
  for (auto it = fruits.begin(); it != fruits.end(); ++it) {
    std::cout << "    " << *it << "\n";
  }
}

void demo_nested_json() {
  std::cout << "\n=== 嵌套JSON结构 ===\n";

  json company = {
      {"name", "Tech Corp"},
      {"founded", 2010},
      {"address", {{"street", "123 Tech Street"}, {"city", "Silicon Valley"}, {"country", "USA"}}},
      {"employees", json::array()},
      {"departments",
       {{"engineering", {{"head", "John Doe"}, {"size", 50}}},
        {"marketing", {{"head", "Jane Smith"}, {"size", 20}}}}}};

  // 添加员工
  company["employees"].push_back(
      {{"name", "Alice Johnson"}, {"position", "Software Engineer"}, {"salary", 85000}});

  company["employees"].push_back(
      {{"name", "Bob Wilson"}, {"position", "Product Manager"}, {"salary", 95000}});

  std::cout << "  公司信息:\n" << company.dump(2) << "\n\n";

  // 访问嵌套数据
  std::cout << "  公司名称: " << company["name"] << "\n";
  std::cout << "  地址: " << company["address"]["city"] << ", " << company["address"]["country"]
            << "\n";
  std::cout << "  工程部门负责人: " << company["departments"]["engineering"]["head"] << "\n";

  // 遍历员工
  std::cout << "\n  员工列表:\n";
  for (const auto& employee : company["employees"]) {
    std::cout << "    " << employee["name"] << " - " << employee["position"] << " ($"
              << employee["salary"] << ")\n";
  }
}

void demo_json_parsing() {
  std::cout << "\n=== JSON解析 ===\n";

  // 从字符串解析
  std::string json_string = R"({
        "product": "Laptop",
        "brand": "TechBrand",
        "price": 999.99,
        "specifications": {
            "cpu": "Intel i7",
            "ram": "16GB",
            "storage": "512GB SSD"
        },
        "tags": ["electronics", "computers", "portable"]
    })";

  try {
    json product = json::parse(json_string);

    std::cout << "  解析成功!\n";
    std::cout << "  产品: " << product["product"] << "\n";
    std::cout << "  品牌: " << product["brand"] << "\n";
    std::cout << "  价格: $" << product["price"] << "\n";

    std::cout << "\n  规格:\n";
    for (const auto& [key, value] : product["specifications"].items()) {
      std::cout << "    " << key << ": " << value << "\n";
    }

    std::cout << "\n  标签: ";
    for (const auto& tag : product["tags"]) {
      std::cout << tag << " ";
    }
    std::cout << "\n";

  } catch (const json::parse_error& e) {
    std::cout << "  ❌ 解析错误: " << e.what() << "\n";
  }

  // 错误处理示例
  std::cout << "\n  错误处理示例:\n";
  std::string invalid_json = R"({"invalid": json})";

  try {
    auto _ = json::parse(invalid_json);
  } catch (const json::parse_error& e) {
    std::cout << "    捕获到解析错误: " << e.what() << "\n";
    std::cout << "    错误位置: 字节 " << e.byte << "\n";
  }
}

void demo_custom_serialization() {
  std::cout << "\n=== 自定义序列化 ===\n";

  // 创建Person对象
  Person person1("Charlie Brown", 30);
  person1.hobbies = {"reading", "coding", "traveling"};
  person1.email = "charlie@example.com";

  Person person2("Diana Prince", 28);
  person2.hobbies = {"martial arts", "archaeology"};
  // person2没有email

  // 序列化为JSON
  json j1 = person1;
  json j2 = person2;

  std::cout << "  Person1 JSON:\n" << j1.dump(2) << "\n\n";
  std::cout << "  Person2 JSON:\n" << j2.dump(2) << "\n\n";

  // 从JSON反序列化
  std::string person_json = R"({
        "name": "Eve Adams",
        "age": 35,
        "hobbies": ["photography", "hiking", "cooking"],
        "email": "eve@example.com"
    })";

  try {
    json j = json::parse(person_json);
    Person person3 = j.get<Person>();

    std::cout << "  反序列化的Person:\n";
    std::cout << "    姓名: " << person3.name << "\n";
    std::cout << "    年龄: " << person3.age << "\n";
    std::cout << "    爱好: ";
    for (const auto& hobby : person3.hobbies) {
      std::cout << hobby << " ";
    }
    std::cout << "\n";
    if (person3.email) {
      std::cout << "    邮箱: " << *person3.email << "\n";
    }

  } catch (const std::exception& e) {
    std::cout << "  ❌ 反序列化错误: " << e.what() << "\n";
  }
}

void demo_json_manipulation() {
  std::cout << "\n=== JSON操作和修改 ===\n";

  json config = {{"version", "1.0.0"},
                 {"debug", true},
                 {"database", {{"host", "localhost"}, {"port", 5432}, {"name", "myapp"}}},
                 {"features", {{"logging", true}, {"caching", false}, {"analytics", true}}}};

  std::cout << "  原始配置:\n" << config.dump(2) << "\n\n";

  // 修改值
  config["version"] = "1.1.0";
  config["debug"] = false;
  config["database"]["port"] = 3306;

  // 添加新字段
  config["database"]["username"] = "admin";
  config["features"]["notifications"] = true;

  // 删除字段
  config["features"].erase("caching");

  std::cout << "  修改后的配置:\n" << config.dump(2) << "\n\n";

  // 检查字段存在性
  std::cout << "  字段检查:\n";
  std::cout << "    有database.host? " << config["database"].contains("host") << "\n";
  std::cout << "    有database.password? " << config["database"].contains("password") << "\n";

  // 安全访问
  std::cout << "\n  安全访问:\n";
  auto port = config["database"].value("port", 5432);
  auto timeout = config["database"].value("timeout", 30);

  std::cout << "    数据库端口: " << port << "\n";
  std::cout << "    连接超时 (默认): " << timeout << "\n";
}

void demo_json_file_io() {
  std::cout << "\n=== JSON文件读写 ===\n";

  // 创建测试数据
  json test_data = {
      {"application", "JSON Demo"},
      {"version", "1.0.0"},
      {"settings", {{"theme", "dark"}, {"language", "en"}, {"auto_save", true}}},
      {"recent_files", {"/path/to/file1.txt", "/path/to/file2.txt", "/path/to/file3.txt"}}};

  // 写入文件
  try {
    std::ofstream file("test_config.json");
    file << test_data.dump(2);
    file.close();

    std::cout << "  ✅ JSON已写入 test_config.json\n";

    // 从文件读取
    std::ifstream input_file("test_config.json");
    json loaded_data;
    input_file >> loaded_data;
    input_file.close();

    std::cout << "  ✅ JSON已从文件读取\n";
    std::cout << "  应用程序: " << loaded_data["application"] << "\n";
    std::cout << "  主题: " << loaded_data["settings"]["theme"] << "\n";

    // 验证数据完整性
    if (test_data == loaded_data) {
      std::cout << "  ✅ 数据完整性验证通过\n";
    } else {
      std::cout << "  ❌ 数据完整性验证失败\n";
    }

  } catch (const std::exception& e) {
    std::cout << "  ❌ 文件操作错误: " << e.what() << "\n";
  }
}

void demo_advanced_features() {
  std::cout << "\n=== 高级特性 ===\n";

  json data = {{"numbers", {1, 2, 3, 4, 5}}, {"person", {{"name", "John"}, {"age", 30}}}};

  // JSON Patch (修补)
  std::cout << "  原始数据: " << data.dump() << "\n";

  // 使用JSON Pointer访问嵌套数据
  try {
    auto name = data["/person/name"_json_pointer];
    auto age = data["/person/age"_json_pointer];

    std::cout << "  使用JSON Pointer:\n";
    std::cout << "    姓名: " << name << "\n";
    std::cout << "    年龄: " << age << "\n";

    // 修改嵌套值
    data["/person/age"_json_pointer] = 31;
    std::cout << "  修改后年龄: " << data["/person/age"_json_pointer] << "\n";

  } catch (const std::exception& e) {
    std::cout << "  JSON Pointer 错误: " << e.what() << "\n";
  }

  // JSON合并
  json patch = {{"person", {{"city", "New York"}, {"age", 32}}}};

  data.merge_patch(patch);
  std::cout << "\n  合并后的数据:\n" << data.dump(2) << "\n";
}

int main() {
  std::cout << "🚀 nlohmann/json 现代C++ JSON库演示\n";
  std::cout << "====================================\n";

  try {
    demo_basic_json_operations();
    demo_array_operations();
    demo_nested_json();
    demo_json_parsing();
    demo_custom_serialization();
    demo_json_manipulation();
    demo_json_file_io();
    demo_advanced_features();

    std::cout << "\n✅ nlohmann/json 演示完成!\n";
    std::cout << "\n📚 主要特性:\n";
    std::cout << "  • 直观的现代C++语法\n";
    std::cout << "  • 完整的JSON标准支持\n";
    std::cout << "  • 自动类型转换和序列化\n";
    std::cout << "  • 异常安全和错误处理\n";
    std::cout << "  • JSON Pointer和JSON Patch支持\n";
    std::cout << "  • 头文件库，无需编译\n";
    std::cout << "  • STL容器兼容\n";

  } catch (const std::exception& e) {
    std::cerr << "❌ 错误: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
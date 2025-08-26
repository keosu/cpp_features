#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <set>
#include <string>
#include <vector>

#include <fmt/color.h>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

using json = nlohmann::json;

// 数据模型类
class Student {
 public:
  std::string name;
  int age;
  double gpa;
  std::vector<std::string> courses;

  Student() : name(""), age(0), gpa(0.0) {}
  Student(const std::string& n, int a, double g) : name(n), age(a), gpa(g) {}

  void add_course(const std::string& course) { courses.push_back(course); }
};

// JSON序列化支持
void to_json(json& j, const Student& s) {
  j = json{{"name", s.name}, {"age", s.age}, {"gpa", s.gpa}, {"courses", s.courses}};
}

void from_json(const json& j, Student& s) {
  j.at("name").get_to(s.name);
  j.at("age").get_to(s.age);
  j.at("gpa").get_to(s.gpa);
  j.at("courses").get_to(s.courses);
}

// 学生管理系统类
class StudentManager {
 private:
  std::vector<Student> students;
  std::shared_ptr<spdlog::logger> logger;

 public:
  StudentManager() {
    // 初始化日志系统
    try {
      auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
      auto file_sink =
          std::make_shared<spdlog::sinks::basic_file_sink_mt>("student_system.log", true);

      std::vector<spdlog::sink_ptr> sinks{console_sink, file_sink};
      logger = std::make_shared<spdlog::logger>("StudentManager", sinks.begin(), sinks.end());

      logger->set_level(spdlog::level::info);
      logger->set_pattern("[%Y-%m-%d %H:%M:%S] [%n] [%^%l%$] %v");

      spdlog::register_logger(logger);

    } catch (const spdlog::spdlog_ex& ex) {
      std::cout << "日志初始化失败: " << ex.what() << std::endl;
    }
  }

  void add_student(const Student& student) {
    students.push_back(student);

    logger->info("添加新学生: {}, 年龄: {}, GPA: {:.2f}", student.name, student.age, student.gpa);

    // 使用fmt库进行彩色输出
    fmt::print(fg(fmt::color::green), "✅ 成功添加学生: {}\n", student.name);
  }

  std::vector<Student> find_students_by_gpa(double min_gpa) const {
    std::vector<Student> result;

    for (const auto& student : students) {
      if (student.gpa >= min_gpa) {
        result.push_back(student);
      }
    }

    logger->info("查找GPA >= {:.2f}的学生，找到 {} 名", min_gpa, result.size());

    return result;
  }

  void print_statistics() const {
    if (students.empty()) {
      fmt::print(fg(fmt::color::yellow), "⚠️  没有学生数据\n");
      return;
    }

    // 计算统计信息
    double total_gpa = 0.0;
    int total_age = 0;
    double max_gpa = 0.0;
    double min_gpa = 4.0;

    for (const auto& student : students) {
      total_gpa += student.gpa;
      total_age += student.age;
      max_gpa = std::max(max_gpa, student.gpa);
      min_gpa = std::min(min_gpa, student.gpa);
    }

    double avg_gpa = total_gpa / students.size();
    double avg_age = static_cast<double>(total_age) / students.size();

    // 使用fmt格式化输出统计信息
    fmt::print("\n📊 学生统计信息\n");
    fmt::print("{}\n", std::string(40, '='));
    fmt::print("总学生数: {}\n", students.size());
    fmt::print("平均GPA: {:.2f}\n", avg_gpa);
    fmt::print("最高GPA: {:.2f}\n", max_gpa);
    fmt::print("最低GPA: {:.2f}\n", min_gpa);
    fmt::print("平均年龄: {:.1f}\n", avg_age);

    logger->info("统计信息 - 学生数: {}, 平均GPA: {:.2f}, 平均年龄: {:.1f}", students.size(),
                 avg_gpa, avg_age);
  }

  bool save_to_file(const std::string& filename) const {
    try {
      json students_json = students;

      std::ofstream file(filename);
      file << students_json.dump(2);
      file.close();

      logger->info("学生数据已保存到文件: {}", filename);
      fmt::print(fg(fmt::color::green), "✅ 数据已保存到: {}\n", filename);

      return true;

    } catch (const std::exception& e) {
      logger->error("保存文件失败: {}", e.what());
      fmt::print(fg(fmt::color::red), "❌ 保存失败: {}\n", e.what());

      return false;
    }
  }

  bool load_from_file(const std::string& filename) {
    try {
      std::ifstream file(filename);
      if (!file.is_open()) {
        logger->warn("文件不存在: {}", filename);
        fmt::print(fg(fmt::color::yellow), "⚠️  文件不存在: {}\n", filename);
        return false;
      }

      json students_json;
      file >> students_json;
      file.close();

      students.clear();
      for (const auto& json_student : students_json) {
        Student student;
        from_json(json_student, student);
        students.push_back(student);
      }

      logger->info("从文件加载了 {} 名学生: {}", students.size(), filename);
      fmt::print(fg(fmt::color::green), "✅ 从 {} 加载了 {} 名学生\n", filename, students.size());

      return true;

    } catch (const std::exception& e) {
      logger->error("加载文件失败: {}", e.what());
      fmt::print(fg(fmt::color::red), "❌ 加载失败: {}\n", e.what());

      return false;
    }
  }

  void print_student_list() const {
    if (students.empty()) {
      fmt::print(fg(fmt::color::yellow), "📋 学生列表为空\n");
      return;
    }

    fmt::print("\n📋 学生列表\n");
    fmt::print("{}\n", std::string(60, '='));

    fmt::print("{:<15} {:<5} {:<6} {:<30}\n", "姓名", "年龄", "GPA", "课程");
    fmt::print("{}\n", std::string(60, '-'));

    for (const auto& student : students) {
      // 手动创建课程字符串
      std::string courses_str;
      for (size_t i = 0; i < student.courses.size(); ++i) {
        if (i > 0) courses_str += ", ";
        courses_str += student.courses[i];
      }
      if (courses_str.length() > 28) {
        courses_str = courses_str.substr(0, 25) + "...";
      }

      // 根据GPA使用不同颜色
      auto gpa_color = fmt::color::white;
      if (student.gpa >= 3.5) {
        gpa_color = fmt::color::green;
      } else if (student.gpa >= 3.0) {
        gpa_color = fmt::color::yellow;
      } else {
        gpa_color = fmt::color::red;
      }

      fmt::print("{:<15} {:<5} ", student.name, student.age);
      fmt::print(fg(gpa_color), "{:<6.2f} ", student.gpa);
      fmt::print("{:<30}\n", courses_str);
    }
  }

  size_t get_student_count() const { return students.size(); }
};

// 数据生成器
class DataGenerator {
 private:
  std::vector<std::string> first_names = {"Alice", "Bob",   "Charlie", "Diana", "Eve",  "Frank",
                                          "Grace", "Henry", "Ivy",     "Jack",  "Kate", "Leo",
                                          "Mary",  "Nick",  "Olivia",  "Paul"};

  std::vector<std::string> last_names = {
      "Smith", "Johnson",   "Williams", "Brown",     "Jones", "Garcia",  "Miller",
      "Davis", "Rodriguez", "Martinez", "Hernandez", "Lopez", "Gonzalez"};

  std::vector<std::string> course_list = {"Mathematics",      "Physics", "Chemistry", "Biology",
                                          "Computer Science", "English", "History",   "Economics",
                                          "Psychology",       "Art",     "Music"};

  std::mt19937 gen;

 public:
  DataGenerator() : gen(std::chrono::steady_clock::now().time_since_epoch().count()) {}

  std::vector<Student> generate_students(size_t count) {
    std::vector<Student> students;

    std::uniform_int_distribution<size_t> first_name_dist(0, first_names.size() - 1);
    std::uniform_int_distribution<size_t> last_name_dist(0, last_names.size() - 1);
    std::uniform_int_distribution<> age_dist(18, 25);
    std::uniform_real_distribution<> gpa_dist(2.0, 4.0);
    std::uniform_int_distribution<> course_count_dist(3, 7);
    std::uniform_int_distribution<size_t> course_dist(0, course_list.size() - 1);

    for (size_t i = 0; i < count; ++i) {
      std::string name = first_names[first_name_dist(gen)] + " " + last_names[last_name_dist(gen)];
      int age = age_dist(gen);
      double gpa = gpa_dist(gen);

      Student student(name, age, gpa);

      // 随机添加课程
      int num_courses = course_count_dist(gen);
      std::set<int> selected_courses;

      while (selected_courses.size() < num_courses) {
        selected_courses.insert(course_dist(gen));
      }

      for (int course_idx : selected_courses) {
        student.add_course(course_list[course_idx]);
      }

      students.push_back(student);
    }

    return students;
  }
};

void demo_basic_operations() {
  fmt::print(fg(fmt::color::cyan), "\n🎓 基础操作演示\n");
  fmt::print("{}\n", std::string(50, '='));

  StudentManager manager;

  // 手动添加一些学生
  Student alice("Alice Johnson", 20, 3.8);
  alice.add_course("Computer Science");
  alice.add_course("Mathematics");
  alice.add_course("Physics");

  Student bob("Bob Smith", 19, 3.2);
  bob.add_course("Biology");
  bob.add_course("Chemistry");

  Student charlie("Charlie Brown", 21, 3.9);
  charlie.add_course("Economics");
  charlie.add_course("Psychology");
  charlie.add_course("History");

  manager.add_student(alice);
  manager.add_student(bob);
  manager.add_student(charlie);

  manager.print_student_list();
  manager.print_statistics();
}

void demo_file_operations() {
  fmt::print(fg(fmt::color::cyan), "\n💾 文件操作演示\n");
  fmt::print("{}\n", std::string(50, '='));

  StudentManager manager;
  DataGenerator generator;

  // 生成随机学生数据
  auto students = generator.generate_students(10);

  fmt::print("生成了 {} 名随机学生\n", students.size());

  for (const auto& student : students) {
    manager.add_student(student);
  }

  // 保存到文件
  manager.save_to_file("students.json");

  // 创建新的管理器并加载数据
  StudentManager new_manager;
  new_manager.load_from_file("students.json");

  fmt::print("\n从文件加载后的数据:\n");
  new_manager.print_statistics();
}

void demo_search_and_filter() {
  fmt::print(fg(fmt::color::cyan), "\n🔍 搜索和筛选演示\n");
  fmt::print("{}\n", std::string(50, '='));

  StudentManager manager;
  DataGenerator generator;

  // 生成大量学生数据
  auto students = generator.generate_students(50);

  for (const auto& student : students) {
    manager.add_student(student);
  }

  fmt::print("生成了 {} 名学生进行搜索演示\n\n", students.size());

  // 搜索高GPA学生
  std::vector<double> gpa_thresholds = {3.0, 3.5, 3.8};

  for (double threshold : gpa_thresholds) {
    auto high_gpa_students = manager.find_students_by_gpa(threshold);

    fmt::print("GPA >= {:.1f} 的学生数量: ", threshold);

    auto color = fmt::color::white;
    if (high_gpa_students.size() > 15)
      color = fmt::color::green;
    else if (high_gpa_students.size() > 5)
      color = fmt::color::yellow;
    else
      color = fmt::color::red;

    fmt::print(fg(color), "{}\n", high_gpa_students.size());
  }
}

void demo_performance_benchmark() {
  fmt::print(fg(fmt::color::cyan), "\n⚡ 性能基准测试\n");
  fmt::print("{}\n", std::string(50, '='));

  std::vector<size_t> test_sizes = {1000, 5000, 10000, 50000};

  for (size_t size : test_sizes) {
    fmt::print("\n测试大小: {} 名学生\n", size);

    // 数据生成性能
    auto start = std::chrono::high_resolution_clock::now();

    DataGenerator generator;
    auto students = generator.generate_students(size);

    auto end = std::chrono::high_resolution_clock::now();
    auto generation_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // 数据处理性能
    start = std::chrono::high_resolution_clock::now();

    StudentManager manager;
    for (const auto& student : students) {
      manager.add_student(student);
    }

    end = std::chrono::high_resolution_clock::now();
    auto processing_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // JSON序列化性能
    start = std::chrono::high_resolution_clock::now();

    json students_json = students;
    std::string json_string = students_json.dump();

    end = std::chrono::high_resolution_clock::now();
    auto serialization_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // 搜索性能
    start = std::chrono::high_resolution_clock::now();

    auto high_gpa_students = manager.find_students_by_gpa(3.5);

    end = std::chrono::high_resolution_clock::now();
    auto search_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    fmt::print("  数据生成: {} ms\n", generation_time.count());
    fmt::print("  数据处理: {} ms\n", processing_time.count());
    fmt::print("  JSON序列化: {} ms ({:.1f} MB)\n", serialization_time.count(),
               json_string.length() / (1024.0 * 1024.0));
    fmt::print("  搜索操作: {} ms (找到{}名)\n", search_time.count(), high_gpa_students.size());
  }
}

void demo_error_handling() {
  fmt::print(fg(fmt::color::cyan), "\n⚠️  错误处理演示\n");
  fmt::print("{}\n", std::string(50, '='));

  StudentManager manager;

  // 尝试加载不存在的文件
  manager.load_from_file("nonexistent.json");

  // 尝试加载格式错误的JSON文件
  {
    std::ofstream bad_file("bad_students.json");
    bad_file << "{ invalid json content }";
    bad_file.close();
  }

  manager.load_from_file("bad_students.json");

  // 正常操作以显示系统仍然工作
  Student test_student("Test Student", 20, 3.5);
  test_student.add_course("Test Course");
  manager.add_student(test_student);

  fmt::print("\n系统在错误后仍正常工作:\n");
  manager.print_statistics();
}

int main() {
  fmt::print(fg(fmt::color::magenta), "🚀 多库集成演示 - 学生管理系统\n");
  fmt::print(fg(fmt::color::magenta), "=====================================\n");

  fmt::print("使用的库:\n");
  fmt::print("  • {} - 字符串格式化和彩色输出\n", fmt::format(fg(fmt::color::green), "fmt"));
  fmt::print("  • {} - 高性能日志记录\n", fmt::format(fg(fmt::color::blue), "spdlog"));
  fmt::print("  • {} - JSON解析和序列化\n", fmt::format(fg(fmt::color::yellow), "nlohmann/json"));

  try {
    demo_basic_operations();
    demo_file_operations();
    demo_search_and_filter();
    demo_performance_benchmark();
    demo_error_handling();

    fmt::print(fg(fmt::color::green), "\n✅ 多库集成演示完成!\n");

    fmt::print("\n📚 集成优势:\n");
    fmt::print("  • fmt + spdlog: 美观的日志输出\n");
    fmt::print("  • nlohmann/json + spdlog: 结构化数据持久化和日志记录\n");
    fmt::print("  • 所有库协同工作，提供完整的应用程序功能\n");
    fmt::print("  • 现代C++风格，类型安全，性能优异\n");

  } catch (const std::exception& e) {
    fmt::print(fg(fmt::color::red), "❌ 错误: {}\n", e.what());
    return 1;
  }

  return 0;
}
# 现代C++ 第三方库示例集合

这个目录包含了流行的现代C++第三方库的使用示例，展示了如何在实际项目中集成和使用这些库。

## 📚 包含的库

### 📝 字符串格式化和输出
- **[fmt](https://fmt.dev/)** - 现代C++字符串格式化库
  - 类型安全的字符串格式化
  - 高性能，比printf更快
  - 支持彩色输出
  - 容器和自定义类型的格式化支持

### 🚀 高性能日志
- **[spdlog](https://github.com/gabime/spdlog)** - 极速C++日志库
  - 异步日志支持
  - 多种输出目标（控制台、文件、轮转文件等）
  - 可配置的日志级别和格式
  - 线程安全

### 📄 JSON处理
- **[nlohmann/json](https://github.com/nlohmann/json)** - 现代C++ JSON库
  - 直观的现代C++语法
  - 自动类型转换和序列化
  - JSON Pointer和JSON Patch支持
  - 头文件库，无需编译

### 🧪 单元测试
- **[Catch2](https://github.com/catchorg/Catch2)** - 现代C++测试框架
  - BDD风格的测试语法
  - 内置断言和匹配器
  - 丰富的输出格式
  - 头文件库

### 🔢 线性代数
- **[Eigen](https://eigen.tuxfamily.org/)** - 高性能线性代数库
  - 表达式模板技术，零开销抽象
  - 稠密和稀疏矩阵支持
  - 丰富的矩阵分解算法
  - SIMD向量化优化

### 🎮 游戏开发
- **[raylib](https://www.raylib.com/)** - 简单易用的游戏开发库
  - 跨平台支持 (Windows, Linux, macOS)
  - 2D/3D图形渲染
  - 音频和输入处理
  - 学习友好的API

## 🏗️ 构建和运行

### 构建所有示例
```bash
# 构建所有第三方库示例
xmake build -g formatting    # fmt示例
xmake build -g logging       # spdlog示例
xmake build -g serialization # json示例
xmake build -g testing       # catch2示例
xmake build -g math          # eigen示例
xmake build -g graphics      # raylib示例
xmake build -g integration   # 多库集成示例

# 或者构建特定示例
xmake build fmt_example
xmake build json_example
# ... 等等
```

### 运行示例
```bash
# 查看所有可用示例
xmake run show_examples

# 运行特定示例
xmake run fmt_example      # 字符串格式化演示
xmake run spdlog_example   # 日志系统演示
xmake run json_example     # JSON处理演示
xmake run catch2_example   # 单元测试演示
xmake run eigen_example    # 线性代数演示
xmake run raylib_example   # 游戏开发演示（需要图形环境）
xmake run combined_example # 多库集成学生管理系统
```

## 💡 示例特色

### fmt_example - 字符串格式化演示
- 基础格式化语法
- 数字和时间格式化
- 彩色输出
- 容器和自定义类型格式化
- 性能对比测试

### spdlog_example - 日志系统演示
- 不同日志级别的使用
- 多种输出目标配置
- 自定义日志格式
- 高性能异步日志
- 结构化日志记录

### json_example - JSON处理演示
- 基础JSON操作
- 嵌套结构处理
- 自定义类型序列化/反序列化
- 文件读写操作
- 错误处理和验证
- JSON Pointer高级特性

### catch2_example - 单元测试演示
- BDD风格测试用例
- 参数化测试
- 浮点数比较
- 异常测试
- 自定义匹配器

### eigen_example - 线性代数演示
- 基础矩阵和向量操作
- 矩阵分解（LU, QR, Cholesky, SVD）
- 特征值和特征向量计算
- 线性方程组求解
- 稀疏矩阵操作
- 几何变换
- 性能优化示例

### raylib_example - 游戏开发演示
- 完整的Pong游戏实现
- 现代C++类设计（RAII, 智能指针）
- 粒子系统视觉效果
- 碰撞检测和物理模拟
- AI对手实现
- 状态机管理

### combined_example - 多库集成演示
- 学生管理系统
- fmt + spdlog 美观日志输出
- nlohmann/json 数据持久化
- 现代C++设计模式
- 错误处理和异常安全
- 性能测试和基准测试

## 🔧 技术特色

### 现代C++特性
- C++17标准（统一使用）
- RAII和智能指针
- 异常安全编程
- 类型安全和编译时检查
- STL容器集成

### 构建系统
- xmake跨平台构建
- 自动依赖管理
- 分组构建支持
- 并行编译优化

### 代码质量
- 完整的错误处理
- 详细的中文注释
- 实用的示例场景
- 性能优化技巧

## 📖 学习路径建议

1. **基础工具链**
   - 首先学习 `fmt_example` - 掌握现代字符串格式化
   - 然后学习 `spdlog_example` - 理解日志系统设计

2. **数据处理**
   - 学习 `json_example` - 掌握数据序列化技术
   - 实践 `catch2_example` - 养成单元测试习惯

3. **高级应用**
   - 学习 `eigen_example` - 掌握数值计算技术
   - 尝试 `raylib_example` - 体验游戏开发流程

4. **综合应用**
   - 最后学习 `combined_example` - 理解多库集成设计

## 🚀 扩展建议

- 添加更多第三方库示例（如 Boost、OpenCV、gRPC等）
- 集成CI/CD构建流水线
- 添加Docker容器化部署
- 创建性能基准测试套件
- 添加更多实际应用场景

## 📋 依赖要求

- C++17兼容编译器
- xmake构建系统
- 图形环境（仅raylib示例需要）

所有第三方依赖会由xmake自动下载和管理，无需手动安装。
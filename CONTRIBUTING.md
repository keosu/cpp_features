# 贡献指南 🤝

感谢您对现代C++特性展示项目的兴趣！我们欢迎各种形式的贡献。

## 🚀 如何贡献

### 1. 报告问题
- 使用GitHub Issues报告bug
- 提供详细的复现步骤
- 包含编译器版本和操作系统信息

### 2. 建议功能
- 新的C++特性演示
- 改进现有示例
- 文档优化建议

### 3. 代码贡献
- Fork项目
- 创建feature分支
- 遵循代码规范
- 添加测试（如适用）
- 提交Pull Request

## 📝 代码规范

### C++ 代码风格
- 使用现代C++特性
- 清晰的注释和文档
- 一致的命名约定
- 适当的错误处理

### 文件结构
```
src/cpp{version}/
├── main.cpp           # 主演示程序
└── specific_feature.cpp  # 特定特性演示（可选）
```

### 示例格式
```cpp
void demo_feature_name() {
    cpp_features::Demo::print_section("特性名称");
    
    // 简单示例
    auto example = modern_cpp_feature();
    
    // 解释和输出
    cpp_features::Demo::print_value("结果", example);
}
```

## 🧪 测试

- 确保所有代码能够编译
- 运行完整的测试套件：`xmake && xmake run`
- 在多个编译器上测试（如可能）

## 📚 文档

- 更新README.md（如适用）
- 添加代码注释
- 包含使用示例

## 🌟 示例贡献

1. **添加新的C++特性**
2. **改进现有演示的清晰度**
3. **添加性能对比**
4. **完善跨平台支持**
5. **改进构建配置**

谢谢您的贡献！🎉
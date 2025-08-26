# GitHub Actions CI/CD 指南

## 🎯 概述

本项目使用GitHub Actions实现完整的CI/CD流水线，提供自动化构建、测试、安全扫描和发布功能。

## 📋 工作流概览

### 1. 主CI/CD流水线 (`ci.yml`)

**触发条件：**
- 推送到 `main` 或 `develop` 分支
- 创建Pull Request到 `main` 分支

**功能：**
- ✅ 代码格式检查 (clang-format)
- 🏗️ 多平台构建 (Windows, Linux, macOS)
- 🧪 自动化测试
- 📦 构建产物上传
- 📊 代码质量分析

**支持的平台和编译器：**
- **Ubuntu**: GCC 12, Clang 15
- **Windows**: MSVC 2022
- **macOS**: Clang (最新版本)

### 2. 文档部署 (`deploy.yml`)

**触发条件：**
- 推送到 `main` 分支且修改了文档
- 手动触发

**功能：**
- 📚 自动生成项目文档
- 🌐 部署到GitHub Pages
- 📊 生成项目结构和API文档

### 3. 发布流水线 (`release.yml`)

**触发条件：**
- 推送版本标签 (如 `v1.0.0`)
- 手动触发

**功能：**
- 🏗️ 构建所有平台的发布版本
- 📦 自动打包和压缩
- 🚀 创建GitHub Release
- 📝 自动生成发布说明

### 4. 安全和依赖扫描 (`security.yml`)

**触发条件：**
- 每周日定时运行
- 修改依赖配置文件
- 手动触发

**功能：**
- 🔍 依赖漏洞扫描
- 🛡️ 静态代码分析
- 📄 许可证合规检查
- 📊 现代C++特性使用统计

## 🚀 使用指南

### 开发工作流

1. **提交代码**
   ```bash
   git add .
   git commit -m "feat: add new C++20 feature example"
   git push origin feature-branch
   ```

2. **创建Pull Request**
   - 自动触发CI/CD检查
   - 代码格式验证
   - 多平台构建测试
   - 代码质量分析

3. **合并到主分支**
   - 触发完整的CI流水线
   - 自动部署文档更新

### 发布新版本

1. **创建版本标签**
   ```bash
   git tag v1.2.0
   git push origin v1.2.0
   ```

2. **自动发布流程**
   - 构建所有平台版本
   - 创建GitHub Release
   - 上传发布包

### 手动触发工作流

在GitHub仓库页面：
1. 进入 "Actions" 标签页
2. 选择要运行的工作流
3. 点击 "Run workflow"

## 📊 状态徽章

将以下徽章添加到README.md：

```markdown
![CI/CD Pipeline](https://github.com/YOUR_USERNAME/cpp_features/workflows/CI/CD%20Pipeline/badge.svg)
![Security & Dependencies](https://github.com/YOUR_USERNAME/cpp_features/workflows/Security%20&%20Dependencies/badge.svg)
![Release](https://github.com/YOUR_USERNAME/cpp_features/workflows/Release/badge.svg)
```

## 🔧 配置说明

### 环境变量

工作流使用以下全局环境变量：
- `BUILD_TYPE`: 构建类型 (Release)
- `XMAKE_VERSION`: xmake版本 (v2.8.7)

### 构建矩阵

CI流水线使用构建矩阵来测试多个平台组合：
- 操作系统: Ubuntu, Windows, macOS
- 编译器: GCC, Clang, MSVC
- C++标准: 11, 14, 17, 20, 23, 26

### 依赖管理

- **主项目**: 无外部依赖
- **第三方示例**: 
  - fmt, spdlog, nlohmann_json
  - catch2, eigen, raylib
  - 由xmake自动管理

## 🛠️ 故障排除

### 常见问题

1. **构建失败**
   - 检查编译器版本兼容性
   - 验证C++标准支持
   - 查看构建日志详细信息

2. **依赖安装失败**
   - 网络连接问题
   - 包管理器版本不兼容
   - 平台特定依赖缺失

3. **测试超时**
   - 图形界面程序在无头系统运行
   - 使用 `continue-on-error` 标记

### 调试步骤

1. **查看构建日志**
   - 在Actions页面查看详细日志
   - 检查特定步骤的错误信息

2. **本地复现**
   ```bash
   # 使用与CI相同的命令
   xmake config --mode=release
   xmake build cpp20_features
   ```

3. **平台特定问题**
   - Windows: 检查MSVC环境
   - Linux: 验证依赖包安装
   - macOS: 确认Xcode版本

## 📈 监控和维护

### 定期任务

- **每周**: 安全扫描自动运行
- **每月**: 检查依赖更新
- **每季度**: 更新CI配置和工具版本

### 性能优化

1. **缓存策略**
   - xmake包缓存
   - 编译器工具链缓存
   - 依赖项缓存

2. **并行化**
   - 多平台并行构建
   - 独立测试并行运行

3. **资源使用**
   - 构建超时设置
   - 产物保留时间
   - 工作流并发限制

## 🔒 安全考虑

### 权限管理

- 工作流使用最小权限原则
- 敏感操作需要特定令牌
- 第三方Action版本固定

### 依赖安全

- 定期漏洞扫描
- 依赖版本锁定
- 许可证合规检查

### 代码安全

- 静态分析工具集成
- 内存安全检查
- 现代C++最佳实践验证

## 📚 扩展功能

### 可添加的特性

1. **性能基准测试**
   - 代码性能回归检测
   - 编译时间监控

2. **文档生成**
   - Doxygen API文档
   - 代码覆盖率报告

3. **部署扩展**
   - 容器化构建
   - 包管理器发布

### 自定义工作流

可以基于现有模板创建自定义工作流：
```yaml
name: Custom Workflow
on:
  push:
    paths: ['custom/**']
jobs:
  custom-job:
    runs-on: ubuntu-latest
    steps:
    - uses: actions/checkout@v4
    - name: Custom Action
      run: echo "Custom logic here"
```

## 🎓 最佳实践

1. **提交规范**
   - 使用语义化提交信息
   - 保持提交原子性
   - 及时修复CI失败

2. **分支策略**
   - 功能分支开发
   - PR代码审查
   - 主分支保护

3. **测试策略**
   - 单元测试覆盖
   - 集成测试验证
   - 平台兼容性测试

4. **文档维护**
   - 同步更新文档
   - 示例代码验证
   - API变更记录

---

通过这套完整的CI/CD流水线，项目实现了：
- ✅ 自动化质量保证
- 🚀 高效的开发流程  
- 📦 可靠的发布管理
- 🔒 全面的安全保障

持续改进和优化CI/CD流程，确保项目的高质量和可维护性。
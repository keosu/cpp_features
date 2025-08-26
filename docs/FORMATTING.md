# 代码格式化指南

本项目使用 **clang-format** 工具和 **Google C++ 代码风格** 来保证代码格式的一致性。

## 📋 配置文件

项目根目录下的 `.clang-format` 文件包含了完整的格式化配置，基于Google C++代码风格指南：

- **缩进**: 2空格
- **行长度**: 80字符
- **大括号**: Attach风格
- **指针对齐**: 左对齐 (`int* ptr`)
- **头文件排序**: 自动排序和分组

## 🛠️ 安装 clang-format

### Windows (推荐使用 winget)
```powershell
winget install --id LLVM.LLVM
```

### 其他安装方式
- **Visual Studio**: 内置clang-format
- **chocolatey**: `choco install llvm`
- **手动安装**: 从 [LLVM官网](https://llvm.org/builds/) 下载

## 🚀 使用方法

### 格式化单个文件
```bash
clang-format -i --style=file <filename>
```

### 格式化所有源文件
```powershell
# PowerShell (推荐)
Get-ChildItem -Path "." -Recurse -Include "*.cpp","*.h","*.hpp" | Where-Object { $_.FullName -notmatch "\\\.xmake\\" } | ForEach-Object { clang-format -i --style=file $_.FullName }
```

```bash
# Linux/macOS
find . -name "*.cpp" -o -name "*.h" -o -name "*.hpp" | grep -v ".xmake" | xargs clang-format -i --style=file
```

### 使用提供的脚本
```powershell
# Windows PowerShell
.\scripts\format_all.ps1
```

## 📝 IDE 集成

### Visual Studio Code
1. 安装 "C/C++" 扩展
2. 安装 "Clang-Format" 扩展  
3. 设置自动格式化:
   ```json
   {
     "C_Cpp.clang_format_style": "file",
     "editor.formatOnSave": true
   }
   ```

### Visual Studio
1. 工具 → 选项 → 文本编辑器 → C/C++ → 格式设置
2. 选择 "使用clang-format"
3. 设置样式为 "file"

### CLion
1. 设置 → 编辑器 → 代码样式 → C/C++
2. 选择 "ClangFormat"
3. 设置配置为 "Project"

## ✅ 验证格式化

格式化后，验证代码是否仍能正确编译：

```bash
# 构建主程序
xmake build modern_cpp_showcase

# 构建测试示例
cd tests
xmake build fmt_example
xmake build combined_example
```

## 📚 代码风格规范

本项目遵循 [Google C++ 代码风格指南](https://google.github.io/styleguide/cppguide.html) 的主要规范：

### 命名约定
- **变量**: `snake_case`
- **函数**: `snake_case` 
- **类/结构体**: `PascalCase`
- **常量**: `kConstantName`
- **宏**: `MACRO_NAME`

### 格式规范
- **缩进**: 2空格，不使用Tab
- **行长度**: 最大80字符
- **大括号**: 开括号不换行
- **指针**: 左对齐 `int* ptr`，不是 `int *ptr`
- **引用**: 左对齐 `int& ref`

### 头文件顺序
1. C系统头文件 (`<stdio.h>`)
2. C++标准库头文件 (`<iostream>`)  
3. 第三方库头文件 (`<fmt/core.h>`)
4. 项目头文件 (`"utils.h"`)

## ⚠️ 注意事项

1. **格式化前备份**: 首次运行前建议提交代码到Git
2. **构建验证**: 格式化后务必重新构建项目验证
3. **团队协作**: 确保团队成员都使用相同的配置文件
4. **持续集成**: 可在CI/CD中添加格式检查步骤

## 🔧 故障排除

### 常见问题

**Q: 提示 "clang-format 不是可识别的命令"**
A: 确保LLVM已正确安装并添加到PATH环境变量

**Q: 格式化后代码编译失败**  
A: 检查是否有语法错误，clang-format不会修复语法问题

**Q: 某些文件格式化效果不理想**
A: 检查文件是否有语法错误，修复后重新格式化

**Q: IDE中格式化样式不一致**
A: 确保IDE配置使用项目根目录的`.clang-format`文件

### 获取帮助
```bash
clang-format --help
clang-format --dump-config
```

---

通过遵循这些格式化规范，我们可以确保项目代码的一致性和可读性，提升代码质量和团队协作效率。
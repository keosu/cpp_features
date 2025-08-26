# Format all C++ source files using clang-format
# Script: format_all.ps1

Write-Host "🎯 开始格式化所有C++源文件..." -ForegroundColor Green
Write-Host "使用Google代码风格规范" -ForegroundColor Cyan

# 设置clang-format路径
$clangFormat = "C:\Program Files\LLVM\bin\clang-format.exe"

# 检查clang-format是否存在
if (-not (Test-Path $clangFormat)) {
    Write-Host "❌ 错误: 找不到clang-format工具" -ForegroundColor Red
    Write-Host "请确保LLVM已正确安装" -ForegroundColor Yellow
    exit 1
}

# 获取项目根目录
$projectRoot = Split-Path -Parent $PSScriptRoot
if (-not $projectRoot) {
    $projectRoot = Get-Location
}

Write-Host "📂 项目根目录: $projectRoot" -ForegroundColor Yellow

# 查找所有C++源文件
$sourceFiles = @()
$sourceFiles += Get-ChildItem -Path $projectRoot -Recurse -Include "*.cpp", "*.h", "*.hpp" | Where-Object { 
    # 排除构建目录和第三方库目录
    $_.FullName -notmatch "\\build\\" -and 
    $_.FullName -notmatch "\\.xmake\\" -and
    $_.FullName -notmatch "\\third_party\\" 
}

Write-Host "📋 找到 $($sourceFiles.Count) 个源文件需要格式化" -ForegroundColor Cyan

$formatted = 0
$skipped = 0
$errors = 0

foreach ($file in $sourceFiles) {
    $relativePath = $file.FullName.Substring($projectRoot.Length + 1)
    
    try {
        Write-Host "  📝 格式化: $relativePath" -ForegroundColor Gray
        
        # 使用clang-format格式化文件
        $result = & $clangFormat -i --style=file "$($file.FullName)" 2>&1
        
        if ($LASTEXITCODE -eq 0) {
            $formatted++
        } else {
            Write-Host "    ⚠️  警告: $relativePath - $result" -ForegroundColor Yellow
            $skipped++
        }
    }
    catch {
        Write-Host "    ❌ 错误: $relativePath - $($_.Exception.Message)" -ForegroundColor Red
        $errors++
    }
}

Write-Host "`n📊 格式化完成统计:" -ForegroundColor Green
Write-Host "  ✅ 成功格式化: $formatted 个文件" -ForegroundColor Green
Write-Host "  ⚠️  跳过文件: $skipped 个文件" -ForegroundColor Yellow
Write-Host "  ❌ 错误文件: $errors 个文件" -ForegroundColor Red

if ($errors -eq 0) {
    Write-Host "`n🎉 所有文件格式化完成！" -ForegroundColor Green
    Write-Host "代码现在符合Google C++代码风格规范" -ForegroundColor Cyan
} else {
    Write-Host "`n⚠️  格式化过程中遇到一些问题，请检查上述错误信息" -ForegroundColor Yellow
}

Write-Host "`n📚 提示:" -ForegroundColor Cyan
Write-Host "  • 可以使用 'git diff' 查看格式化前后的差异" -ForegroundColor Gray
Write-Host "  • 建议在提交前运行此脚本确保代码风格一致性" -ForegroundColor Gray
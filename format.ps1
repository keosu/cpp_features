#!/usr/bin/env pwsh
# format.ps1 - 简化的代码格式化脚本

param(
    [string]$Path = ".",
    [switch]$Check,
    [switch]$Verbose
)

Write-Host "🎯 C++ 代码格式化工具" -ForegroundColor Green
Write-Host "使用 Google 代码风格" -ForegroundColor Cyan

# 查找 clang-format
$clangFormat = $null

# 首先尝试从PATH中找到
$clangFormat = Get-Command clang-format -ErrorAction SilentlyContinue
if ($clangFormat) {
    $clangFormat = $clangFormat.Source
    Write-Host "✅ 找到 clang-format: $clangFormat" -ForegroundColor Green
} else {
    # 尝试标准安装路径
    $standardPath = "C:\Program Files\LLVM\bin\clang-format.exe"
    if (Test-Path $standardPath) {
        $clangFormat = $standardPath
        Write-Host "✅ 找到 clang-format: $clangFormat" -ForegroundColor Green
    } else {
        Write-Host "❌ 错误: 找不到 clang-format" -ForegroundColor Red
        Write-Host "请安装 LLVM: winget install --id LLVM.LLVM" -ForegroundColor Yellow
        Write-Host "或者重新启动PowerShell以刷新环境变量" -ForegroundColor Yellow
        exit 1
    }
}

# 查找源文件
$files = Get-ChildItem -Path $Path -Recurse -Include "*.cpp", "*.h", "*.hpp" | 
    Where-Object { $_.FullName -notmatch "\\\.xmake\\" -and $_.FullName -notmatch "\\build\\" }

Write-Host "📁 在 $Path 中找到 $($files.Count) 个源文件" -ForegroundColor Yellow

if ($Check) {
    Write-Host "🔍 检查模式 - 只显示需要格式化的文件" -ForegroundColor Cyan
    $needsFormatting = @()
    
    foreach ($file in $files) {
        $original = Get-Content $file.FullName -Raw
        $formatted = & $clangFormat --style=file $file.FullName
        
        if ($original -ne $formatted) {
            $needsFormatting += $file
            if ($Verbose) {
                Write-Host "  📝 需要格式化: $($file.Name)" -ForegroundColor Yellow
            }
        }
    }
    
    if ($needsFormatting.Count -eq 0) {
        Write-Host "✅ 所有文件格式已正确" -ForegroundColor Green
    } else {
        Write-Host "⚠️  有 $($needsFormatting.Count) 个文件需要格式化" -ForegroundColor Yellow
        $needsFormatting | ForEach-Object { Write-Host "  • $($_.Name)" }
    }
} else {
    Write-Host "🔧 格式化模式 - 修改文件" -ForegroundColor Cyan
    
    foreach ($file in $files) {
        if ($Verbose) {
            Write-Host "  📝 格式化: $($file.Name)" -ForegroundColor Gray
        }
        & $clangFormat -i --style=file $file.FullName
    }
    
    Write-Host "✅ 格式化完成!" -ForegroundColor Green
    Write-Host "💡 建议运行构建测试: xmake build" -ForegroundColor Cyan
}

Write-Host "`n📚 使用提示:" -ForegroundColor Cyan
Write-Host "  .\format.ps1           # 格式化所有文件" -ForegroundColor Gray
Write-Host "  .\format.ps1 -Check    # 检查哪些文件需要格式化" -ForegroundColor Gray
Write-Host "  .\format.ps1 -Verbose  # 显示详细信息" -ForegroundColor Gray
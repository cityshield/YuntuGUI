# Qt Shadcn/UI 项目 Windows 环境检查和设置脚本
# PowerShell 脚本，需要以管理员身份运行

param(
    [switch]$CheckOnly,
    [switch]$InstallChocolatey,
    [switch]$InstallQt
)

Write-Host "🎨 Qt Shadcn/UI 项目 Windows 环境设置" -ForegroundColor Cyan
Write-Host "================================================" -ForegroundColor Cyan

# 检查管理员权限
function Test-Administrator {
    $currentUser = [Security.Principal.WindowsIdentity]::GetCurrent()
    $principal = New-Object Security.Principal.WindowsPrincipal($currentUser)
    return $principal.IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)
}

if (-not (Test-Administrator)) {
    Write-Host "❌ 需要管理员权限运行此脚本" -ForegroundColor Red
    Write-Host "请右键点击 PowerShell 并选择 '以管理员身份运行'" -ForegroundColor Yellow
    exit 1
}

# 环境检查函数
function Test-Command($command) {
    try {
        Get-Command $command -ErrorAction Stop | Out-Null
        return $true
    }
    catch {
        return $false
    }
}

function Test-VisualStudio {
    $vsWhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
    if (Test-Path $vsWhere) {
        $vs = & $vsWhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64
        return $vs.Length -gt 0
    }
    return $false
}

function Test-QtInstallation {
    $qtPaths = @(
        "C:\Qt",
        "C:\Qt\6.5.3",
        "C:\Qt\6.5.2",
        "C:\Qt\6.5.1",
        "C:\Qt\6.5.0",
        "C:\Qt\5.15.2"
    )
    
    foreach ($path in $qtPaths) {
        if (Test-Path $path) {
            return $path
        }
    }
    return $null
}

# 开始环境检查
Write-Host "`n🔍 检查开发环境..." -ForegroundColor Yellow

$checks = @()

# 检查 Windows 版本
$winVersion = [System.Environment]::OSVersion.Version
if ($winVersion.Major -ge 10) {
    $checks += @{Name="Windows 10/11"; Status="✅"; Details="版本 $($winVersion.Major).$($winVersion.Minor)"}
} else {
    $checks += @{Name="Windows 10/11"; Status="❌"; Details="需要 Windows 10 或更高版本"}
}

# 检查 Visual Studio
if (Test-VisualStudio) {
    $checks += @{Name="Visual Studio"; Status="✅"; Details="已安装 C++ 构建工具"}
} else {
    $checks += @{Name="Visual Studio"; Status="❌"; Details="需要安装 Visual Studio 2019/2022"}
}

# 检查 CMake
if (Test-Command "cmake") {
    $cmakeVersion = (cmake --version | Select-String "cmake version" | ForEach-Object { $_.ToString().Split(" ")[2] })
    $checks += @{Name="CMake"; Status="✅"; Details="版本 $cmakeVersion"}
} else {
    $checks += @{Name="CMake"; Status="❌"; Details="需要安装 CMake 3.16+"}
}

# 检查 Qt
$qtPath = Test-QtInstallation
if ($qtPath) {
    $checks += @{Name="Qt Framework"; Status="✅"; Details="安装路径: $qtPath"}
} else {
    $checks += @{Name="Qt Framework"; Status="❌"; Details="需要安装 Qt 5.15+ 或 6.x"}
}

# 检查 qmake
if (Test-Command "qmake") {
    $qmakeVersion = (qmake --version | Select-String "Qt version" | ForEach-Object { $_.ToString().Split(" ")[2] })
    $checks += @{Name="qmake"; Status="✅"; Details="Qt 版本 $qmakeVersion"}
} else {
    $checks += @{Name="qmake"; Status="❌"; Details="Qt bin 目录未添加到 PATH"}
}

# 检查 Git (可选)
if (Test-Command "git") {
    $gitVersion = (git --version | ForEach-Object { $_.ToString().Split(" ")[2] })
    $checks += @{Name="Git"; Status="✅"; Details="版本 $gitVersion"}
} else {
    $checks += @{Name="Git"; Status="⚠️"; Details="建议安装 Git (可选)"}
}

# 显示检查结果
Write-Host "`n📋 环境检查结果:" -ForegroundColor Cyan
foreach ($check in $checks) {
    Write-Host "  $($check.Status) $($check.Name): $($check.Details)"
}

# 统计结果
$passed = ($checks | Where-Object { $_.Status -eq "✅" }).Count
$failed = ($checks | Where-Object { $_.Status -eq "❌" }).Count
$warnings = ($checks | Where-Object { $_.Status -eq "⚠️" }).Count

Write-Host "`n📊 检查统计: $passed 通过, $failed 失败, $warnings 警告" -ForegroundColor Cyan

if ($CheckOnly) {
    exit 0
}

# 如果有失败项，提供安装建议
if ($failed -gt 0) {
    Write-Host "`n🔧 安装建议:" -ForegroundColor Yellow
    
    # Visual Studio 安装建议
    if (-not (Test-VisualStudio)) {
        Write-Host "  📥 Visual Studio 2022 Community (免费):"
        Write-Host "     https://visualstudio.microsoft.com/downloads/"
        Write-Host "     选择 'C++ 桌面开发' 工作负载"
    }
    
    # Qt 安装建议
    if (-not $qtPath) {
        Write-Host "  📥 Qt 开发框架:"
        Write-Host "     https://www.qt.io/download-qt-installer"
        Write-Host "     选择 Qt 6.5.x LTS + Qt Creator + CMake"
    }
    
    # CMake 安装建议
    if (-not (Test-Command "cmake")) {
        Write-Host "  📥 CMake 构建工具:"
        Write-Host "     https://cmake.org/download/"
        Write-Host "     或使用 Qt 安装器中的 CMake"
    }
    
    # PATH 配置建议
    if ($qtPath -and -not (Test-Command "qmake")) {
        Write-Host "  ⚙️ 环境变量配置:"
        Write-Host "     将以下路径添加到系统 PATH:"
        Write-Host "     $qtPath\msvc2019_64\bin"
        Write-Host "     $qtPath\Tools\CMake_64\bin"
    }
}

# Chocolatey 安装选项
if ($InstallChocolatey -and -not (Test-Command "choco")) {
    Write-Host "`n📦 安装 Chocolatey 包管理器..." -ForegroundColor Yellow
    Set-ExecutionPolicy Bypass -Scope Process -Force
    [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072
    iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
    
    if (Test-Command "choco") {
        Write-Host "✅ Chocolatey 安装成功" -ForegroundColor Green
        
        # 使用 Chocolatey 安装工具
        Write-Host "📦 使用 Chocolatey 安装开发工具..." -ForegroundColor Yellow
        
        if (-not (Test-Command "git")) {
            choco install git -y
        }
        
        if (-not (Test-Command "cmake")) {
            choco install cmake -y
        }
        
        # 刷新环境变量
        $env:Path = [System.Environment]::GetEnvironmentVariable("Path","Machine") + ";" + [System.Environment]::GetEnvironmentVariable("Path","User")
    }
}

# 项目构建测试
if ($failed -eq 0) {
    Write-Host "`n🚀 环境检查通过！可以开始构建项目" -ForegroundColor Green
    
    $buildChoice = Read-Host "`n是否现在构建项目？(y/N)"
    if ($buildChoice -eq "y" -or $buildChoice -eq "Y") {
        Write-Host "`n🔨 开始构建项目..." -ForegroundColor Yellow
        
        if (Test-Path "build") {
            Remove-Item -Recurse -Force "build"
        }
        
        New-Item -ItemType Directory -Name "build" | Out-Null
        Set-Location "build"
        
        try {
            Write-Host "⚙️ 配置 CMake..." -ForegroundColor Cyan
            cmake .. -G "Visual Studio 17 2022" -A x64
            
            if ($LASTEXITCODE -eq 0) {
                Write-Host "🔨 编译项目..." -ForegroundColor Cyan
                cmake --build . --config Release
                
                if ($LASTEXITCODE -eq 0) {
                    Write-Host "✅ 构建成功！" -ForegroundColor Green
                    Write-Host "📁 可执行文件: build\Release\MyApp.exe" -ForegroundColor Green
                    
                    $runChoice = Read-Host "`n是否立即运行程序？(y/N)"
                    if ($runChoice -eq "y" -or $runChoice -eq "Y") {
                        Start-Process "Release\MyApp.exe"
                    }
                } else {
                    Write-Host "❌ 编译失败" -ForegroundColor Red
                }
            } else {
                Write-Host "❌ CMake 配置失败" -ForegroundColor Red
            }
        }
        catch {
            Write-Host "❌ 构建过程出错: $($_.Exception.Message)" -ForegroundColor Red
        }
        finally {
            Set-Location ".."
        }
    }
} else {
    Write-Host "`n⚠️ 请先安装缺失的组件，然后重新运行此脚本" -ForegroundColor Yellow
}

Write-Host "`n📖 更多帮助信息请查看 Windows构建指南.md" -ForegroundColor Cyan
Write-Host "🎯 完成！按任意键退出..." -ForegroundColor Green
$null = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")


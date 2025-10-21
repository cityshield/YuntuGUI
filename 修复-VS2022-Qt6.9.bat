@echo off
chcp 65001 >nul
echo 🔧 VS 2022 + Qt 6.9 兼容性修复和构建脚本
echo ================================================

REM 设置颜色
for /f %%A in ('"prompt $H &echo on &for %%B in (1) do rem"') do set BS=%%A

REM 检查当前目录
if not exist "CMakeLists.txt" (
    echo ❌ 错误：请在项目根目录运行此脚本
    echo 📁 当前目录：%CD%
    echo 📁 应该包含：CMakeLists.txt
    pause
    exit /b 1
)

echo ✅ 项目目录确认：%CD%

REM 检查 Qt 6.9 环境
echo.
echo 🔍 检查 Qt 6.9 环境...
where qmake >nul 2>nul
if %ERRORLEVEL% neq 0 (
    echo ❌ 找不到 qmake
    echo 💡 请确保 Qt 6.9 的 bin 目录已添加到 PATH
    echo    例如：C:\Qt\6.9.0\msvc2022_64\bin
    goto :set_qt_path
) else (
    echo ✅ 找到 qmake
    qmake --version | findstr "Qt version"
)

REM 检查 CMake
echo.
echo 🔍 检查 CMake...
where cmake >nul 2>nul
if %ERRORLEVEL% neq 0 (
    echo ❌ 找不到 cmake
    echo 💡 请确保 CMake 已安装并添加到 PATH
    pause
    exit /b 1
) else (
    echo ✅ 找到 CMake
    cmake --version | findstr "cmake version"
)

REM 检查 Visual Studio 2022
echo.
echo 🔍 检查 Visual Studio 2022...
if not defined VCINSTALLDIR (
    echo ⚠️ 未检测到 VS 2022 环境
    echo 🔧 尝试设置 VS 2022 环境...
    
    REM 尝试常见的 VS 2022 路径
    set "VS2022_PATH=C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
    if exist "%VS2022_PATH%" (
        echo ✅ 找到 VS 2022 Community
        call "%VS2022_PATH%"
    ) else (
        set "VS2022_PATH=C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvars64.bat"
        if exist "%VS2022_PATH%" (
            echo ✅ 找到 VS 2022 Professional
            call "%VS2022_PATH%"
        ) else (
            echo ❌ 找不到 Visual Studio 2022
            echo 💡 请手动运行 VS 2022 开发者命令提示符
            pause
            exit /b 1
        )
    )
) else (
    echo ✅ VS 2022 环境已设置
)

REM 显示编译器信息
echo.
echo 📋 编译器信息：
cl 2>nul | findstr "Microsoft"

goto :build_project

:set_qt_path
echo.
echo 🔧 设置 Qt 6.9 路径...
echo 请输入你的 Qt 6.9 安装路径 (例如: C:\Qt\6.9.0\msvc2022_64)
set /p QT_PATH="Qt 路径: "

if not exist "%QT_PATH%\bin\qmake.exe" (
    echo ❌ 路径无效：找不到 qmake.exe
    pause
    exit /b 1
)

echo ✅ 设置 Qt 环境变量...
set "PATH=%QT_PATH%\bin;%PATH%"
set "CMAKE_PREFIX_PATH=%QT_PATH%"
set "QTDIR=%QT_PATH%"

echo ✅ Qt 环境设置完成
qmake --version

:build_project
echo.
echo 🚀 开始构建项目...

REM 清理旧的构建文件
if exist "build" (
    echo 🗑️ 清理旧的构建文件...
    rmdir /s /q "build" 2>nul
)

REM 创建构建目录
mkdir build
if %ERRORLEVEL% neq 0 (
    echo ❌ 无法创建 build 目录
    pause
    exit /b 1
)

cd build

REM 配置 CMake
echo.
echo ⚙️ 配置 CMake (VS 2022 + Qt 6.9)...
cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Release

if %ERRORLEVEL% neq 0 (
    echo.
    echo ❌ CMake 配置失败
    echo.
    echo 🔍 可能的原因：
    echo   1. Qt 6.9 路径不正确
    echo   2. CMake 版本过低 (需要 3.21+)
    echo   3. Visual Studio 2022 C++ 工具未安装
    echo.
    echo 💡 解决方案：
    echo   1. 检查 Qt 安装：%CMAKE_PREFIX_PATH%
    echo   2. 更新 CMake 到 3.21+
    echo   3. 安装 VS 2022 C++ 桌面开发工作负载
    echo.
    cd ..
    pause
    exit /b 1
)

echo ✅ CMake 配置成功

REM 构建项目
echo.
echo 🔨 编译项目 (Release 模式)...
cmake --build . --config Release --parallel

if %ERRORLEVEL% neq 0 (
    echo.
    echo ❌ 编译失败
    echo.
    echo 🔍 检查编译错误信息：
    echo   - 头文件包含错误
    echo   - 链接库问题
    echo   - Qt 模块缺失
    echo.
    cd ..
    pause
    exit /b 1
)

echo ✅ 编译成功！

REM 部署 Qt 库
echo.
echo 📦 部署 Qt 运行库...
cd Release

if exist "MyApp.exe" (
    echo ✅ 找到可执行文件：MyApp.exe
    
    REM 使用 windeployqt 部署
    where windeployqt >nul 2>nul
    if %ERRORLEVEL% equ 0 (
        echo 🚀 使用 windeployqt 部署 Qt 库...
        windeployqt MyApp.exe --qmldir ..\..\ --no-translations --no-system-d3d-compiler --no-opengl-sw
        
        if %ERRORLEVEL% equ 0 (
            echo ✅ Qt 库部署完成
        ) else (
            echo ⚠️ Qt 库部署可能不完整
        )
    ) else (
        echo ⚠️ 找不到 windeployqt，跳过自动部署
        echo 💡 如果程序无法运行，请手动复制 Qt DLL 文件
    )
    
    REM 检查文件大小
    for %%F in (MyApp.exe) do (
        echo 📊 可执行文件大小：%%~zF 字节
    )
    
) else (
    echo ❌ 找不到 MyApp.exe
    cd ..\..
    pause
    exit /b 1
)

cd ..\..

echo.
echo 🎉 构建完成！
echo 📁 可执行文件位置：build\Release\MyApp.exe
echo.

REM 询问是否运行
set /p run_choice="🚀 是否立即运行程序？(y/N): "
if /i "%run_choice%"=="y" (
    echo 🎯 启动程序...
    start "" "build\Release\MyApp.exe"
    
    REM 等待程序启动
    timeout /t 2 /nobreak >nul
    
    REM 检查程序是否正在运行
    tasklist /fi "imagename eq MyApp.exe" 2>nul | find /i "MyApp.exe" >nul
    if %ERRORLEVEL% equ 0 (
        echo ✅ 程序启动成功！
    ) else (
        echo ⚠️ 程序可能启动失败，请检查错误信息
    )
) else (
    echo 💡 你可以手动运行：build\Release\MyApp.exe
)

echo.
echo 📖 如果遇到问题，请查看：
echo    - Qt6.9兼容性修复.md
echo    - Windows构建指南.md
echo.
echo ✨ 构建脚本执行完成！
pause


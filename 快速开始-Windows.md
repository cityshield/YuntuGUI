# 🚀 Windows 10 快速开始指南

## ⚡ 5分钟快速设置

### 📋 准备工作清单
- [ ] Windows 10 版本 1903+ (检查: `winver`)
- [ ] 至少 8GB 可用磁盘空间
- [ ] 管理员权限
- [ ] 稳定网络连接

### 🎯 一键环境检查
```powershell
# 1. 以管理员身份打开 PowerShell
# 2. 运行环境检查脚本
.\setup-windows.ps1 -CheckOnly
```

## 📦 必需软件下载

### 🥇 推荐方案：Qt Creator + MSVC

#### 1️⃣ Visual Studio 2022 Community (免费)
```
📥 下载链接: https://visualstudio.microsoft.com/zh-hans/downloads/
💾 文件大小: ~3GB
⏱️ 安装时间: 15-30分钟

安装选项:
✅ 使用 C++ 的桌面开发
✅ MSVC v143 编译器工具集
✅ Windows 10/11 SDK
✅ CMake 工具
```

#### 2️⃣ Qt 6.5.x LTS + Qt Creator
```
📥 下载链接: https://www.qt.io/download-qt-installer
💾 文件大小: ~2GB
⏱️ 安装时间: 10-20分钟

必选组件:
✅ Qt 6.5.3 → MSVC 2019 64-bit
✅ Qt Creator (最新版)
✅ CMake 工具
✅ Qt 5 Compatibility Module
```

### 🥈 备选方案：MinGW (轻量级)

#### 1️⃣ MSYS2 + MinGW
```
📥 下载链接: https://www.msys2.org/
💾 文件大小: ~1GB
⏱️ 安装时间: 10分钟

安装后运行:
pacman -S mingw-w64-x86_64-gcc
pacman -S mingw-w64-x86_64-cmake
pacman -S mingw-w64-x86_64-qt6
```

## 🔧 环境配置

### 自动配置 (推荐)
```powershell
# 运行自动配置脚本
.\setup-windows.ps1
```

### 手动配置
```
1. 添加到系统 PATH:
   C:\Qt\6.5.3\msvc2019_64\bin
   C:\Qt\Tools\CMake_64\bin

2. 设置环境变量:
   QTDIR=C:\Qt\6.5.3\msvc2019_64
   CMAKE_PREFIX_PATH=C:\Qt\6.5.3\msvc2019_64
```

## 🚀 构建项目

### 方法 1: 一键构建 (最简单)
```cmd
# 双击运行
build.bat
```

### 方法 2: Qt Creator (推荐)
```
1. 启动 Qt Creator
2. File → Open File or Project
3. 选择 CMakeLists.txt
4. 选择 Kit: Desktop Qt 6.5.3 MSVC2019 64bit
5. 点击 Build (Ctrl+B)
6. 点击 Run (Ctrl+R)
```

### 方法 3: 命令行
```cmd
# 打开 "Developer Command Prompt for VS 2022"
mkdir build && cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
Release\MyApp.exe
```

## ✅ 验证安装

### 快速测试命令
```cmd
# 检查编译器
cl

# 检查 CMake
cmake --version

# 检查 Qt
qmake --version

# 检查 Qt Creator
qtcreator --version
```

### 预期输出
```
C:\>cmake --version
cmake version 3.27.1

C:\>qmake --version
QMake version 3.1
Using Qt version 6.5.3 in C:/Qt/6.5.3/msvc2019_64/lib
```

## 🐛 常见问题速查

### ❌ "找不到 Qt"
```cmd
# 解决方案
set CMAKE_PREFIX_PATH=C:\Qt\6.5.3\msvc2019_64
```

### ❌ "找不到编译器"
```cmd
# 解决方案：使用 VS 开发者命令提示符
开始菜单 → Visual Studio 2022 → Developer Command Prompt
```

### ❌ "DLL 缺失"
```cmd
# 解决方案：部署 Qt 库
cd build\Release
C:\Qt\6.5.3\msvc2019_64\bin\windeployqt.exe MyApp.exe
```

### ❌ "中文乱码"
```cpp
// 在 main.cpp 中添加
#include <QTextCodec>
QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
```

## 📞 获取帮助

### 🔍 自助排查
1. 运行环境检查: `.\setup-windows.ps1 -CheckOnly`
2. 查看详细指南: `Windows构建指南.md`
3. 检查系统日志: 事件查看器

### 💬 在线帮助
- Qt 官方文档: https://doc.qt.io/
- Qt 论坛: https://forum.qt.io/
- Stack Overflow: 搜索 "Qt Windows CMake"

## 🎯 成功标志

当你看到以下界面时，说明构建成功：

```
┌─────────────────────────────────────────────────────────────┐
│                        MyApp                                │
├─────────────────────────────────────────────────────────────┤
│  ┌─────────────────┐    ┌─────────────────────────────┐    │
│  │   欢迎回来       │    │          登录               │    │
│  │                 │    │                             │    │
│  │ 请使用手机号登录  │    │  手机号: [___________]       │    │
│  │ 您的账户         │    │                             │    │
│  │                 │    │  验证码: [_______] [获取]    │    │
│  │ 或使用微信扫码    │    │                             │    │
│  │ 快速登录         │    │  [      登录      ]         │    │
│  │                 │    │                             │    │
│  │ [装饰图形区域]    │    │         ── 或 ──            │    │
│  │                 │    │                             │    │
│  │                 │    │  [   微信扫码登录   ]        │    │
│  │                 │    │                             │    │
│  │                 │    │    还没有账户？立即注册       │    │
│  └─────────────────┘    └─────────────────────────────┘    │
└─────────────────────────────────────────────────────────────┘
```

## ⏱️ 时间预估

| 步骤 | 新手 | 有经验 |
|------|------|--------|
| 下载软件 | 30分钟 | 15分钟 |
| 安装配置 | 45分钟 | 20分钟 |
| 构建项目 | 10分钟 | 5分钟 |
| **总计** | **85分钟** | **40分钟** |

---

**🎉 祝你构建成功！享受现代化的 Qt Shadcn/UI 界面！**


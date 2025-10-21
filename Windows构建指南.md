# 🪟 Windows 10 构建指南

## 📋 环境准备清单

### 🔧 必需软件

#### 1. Qt 开发环境
**选项 A: Qt 官方安装器 (推荐)**
- 📥 下载地址: https://www.qt.io/download-qt-installer
- 💾 文件名: `qt-unified-windows-x64-online.exe`
- 📦 推荐版本: Qt 6.5.x LTS 或 Qt 5.15.x LTS
- 🎯 必需组件:
  - Qt → Qt 6.5.x → Desktop gcc 64-bit (或 MSVC 2019 64-bit)
  - Qt → Developer and Designer Tools → CMake
  - Qt → Developer and Designer Tools → Qt Creator

**选项 B: 在线安装器**
```powershell
# 使用 Chocolatey (需要先安装 Chocolatey)
choco install qt-creator

# 或使用 winget (Windows 10 1809+)
winget install --id=QtProject.QtCreator -e
```

#### 2. C++ 编译器
**选项 A: Visual Studio 2019/2022 (推荐)**
- 📥 下载: https://visualstudio.microsoft.com/downloads/
- 🎯 必需组件:
  - C++ 桌面开发工作负载
  - MSVC v143 编译器工具集
  - Windows 10/11 SDK (最新版本)
  - CMake 工具

**选项 B: MinGW-w64**
```powershell
# 使用 MSYS2 安装 MinGW
# 1. 下载 MSYS2: https://www.msys2.org/
# 2. 安装后运行以下命令:
pacman -S mingw-w64-x86_64-gcc
pacman -S mingw-w64-x86_64-cmake
pacman -S mingw-w64-x86_64-make
```

#### 3. CMake (如果 Qt 安装器没有包含)
- 📥 下载: https://cmake.org/download/
- 💾 文件名: `cmake-3.27.x-windows-x86_64.msi`
- ✅ 安装时勾选 "Add CMake to system PATH"

#### 4. Git (可选，用于版本控制)
- 📥 下载: https://git-scm.com/download/win
- 💾 文件名: `Git-2.x.x-64-bit.exe`

### 🎯 推荐配置组合

#### 🥇 配置 1: Qt Creator + MSVC (最佳体验)
```
✅ Qt 6.5.x LTS + Qt Creator
✅ Visual Studio 2022 Community
✅ CMake 3.27+
✅ Windows 10 SDK
```

#### 🥈 配置 2: Visual Studio + Qt
```
✅ Visual Studio 2022 + Qt VS Tools
✅ Qt 6.5.x LTS
✅ CMake (内置)
```

#### 🥉 配置 3: MinGW (轻量级)
```
✅ Qt 6.5.x + MinGW
✅ Qt Creator
✅ MSYS2 + MinGW-w64
```

## 🚀 详细安装步骤

### 步骤 1: 安装 Visual Studio 2022

1. **下载安装器**
   ```
   https://visualstudio.microsoft.com/thank-you-downloading-visual-studio/?sku=Community
   ```

2. **选择工作负载**
   - ✅ 使用 C++ 的桌面开发
   - ✅ 使用 C++ 的游戏开发 (可选)

3. **单个组件** (确保已选中)
   - ✅ MSVC v143 - VS 2022 C++ x64/x86 生成工具
   - ✅ Windows 10/11 SDK (10.0.22621.0 或更新)
   - ✅ CMake 工具 (Visual Studio)
   - ✅ 适用于 Windows 的 Git

### 步骤 2: 安装 Qt

1. **下载 Qt 在线安装器**
   ```
   https://www.qt.io/download-qt-installer
   ```

2. **创建 Qt 账户** (免费)
   - 注册地址: https://login.qt.io/register

3. **选择安装组件**
   ```
   Qt/
   ├── 6.5.3 (或最新 LTS 版本)/
   │   ├── ✅ MSVC 2019 64-bit
   │   ├── ✅ MinGW 11.2.0 64-bit (可选)
   │   ├── ✅ Qt 5 Compatibility Module
   │   └── ✅ Additional Libraries (全选)
   │
   Developer and Designer Tools/
   ├── ✅ Qt Creator 11.x.x CDB Debugger Support
   ├── ✅ Debugging Tools for Windows
   ├── ✅ CMake 3.24.2
   └── ✅ Ninja 1.10.2
   ```

4. **安装路径建议**
   ```
   C:\Qt\          # 默认路径，推荐保持
   ```

### 步骤 3: 配置环境变量

1. **打开系统环境变量**
   ```
   Win + R → sysdm.cpl → 高级 → 环境变量
   ```

2. **添加 Qt 路径到 PATH**
   ```
   C:\Qt\6.5.3\msvc2019_64\bin
   C:\Qt\Tools\CMake_64\bin
   C:\Qt\Tools\Ninja
   ```

3. **设置 Qt 相关变量** (可选)
   ```
   变量名: QTDIR
   变量值: C:\Qt\6.5.3\msvc2019_64
   
   变量名: CMAKE_PREFIX_PATH
   变量值: C:\Qt\6.5.3\msvc2019_64
   ```

### 步骤 4: 验证安装

1. **打开命令提示符** (以管理员身份)
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

2. **预期输出示例**
   ```
   C:\>cmake --version
   cmake version 3.27.1
   
   C:\>qmake --version
   QMake version 3.1
   Using Qt version 6.5.3 in C:/Qt/6.5.3/msvc2019_64/lib
   ```

## 📦 构建项目

### 方法 1: 使用 Qt Creator (推荐新手)

1. **启动 Qt Creator**
   ```
   开始菜单 → Qt Creator
   ```

2. **打开项目**
   ```
   File → Open File or Project → 选择 CMakeLists.txt
   ```

3. **配置构建套件**
   ```
   Kit Selection:
   ✅ Desktop Qt 6.5.3 MSVC2019 64bit
   ```

4. **构建项目**
   ```
   Build → Build Project "QtShadcnAuth"
   或按 Ctrl+B
   ```

5. **运行项目**
   ```
   Build → Run
   或按 Ctrl+R
   ```

### 方法 2: 使用命令行

1. **打开开发者命令提示符**
   ```
   开始菜单 → Visual Studio 2022 → Developer Command Prompt for VS 2022
   ```

2. **导航到项目目录**
   ```cmd
   cd /d "C:\path\to\qt-shadcn-design"
   ```

3. **运行构建脚本**
   ```cmd
   build.bat
   ```

   或手动构建:
   ```cmd
   mkdir build
   cd build
   cmake .. -G "Visual Studio 17 2022" -A x64
   cmake --build . --config Release
   ```

4. **运行程序**
   ```cmd
   Release\MyApp.exe
   ```

### 方法 3: 使用 Visual Studio

1. **安装 Qt VS Tools**
   ```
   Extensions → Manage Extensions → 搜索 "Qt VS Tools"
   ```

2. **配置 Qt 版本**
   ```
   Extensions → Qt VS Tools → Qt Versions → Add
   Path: C:\Qt\6.5.3\msvc2019_64
   ```

3. **打开项目**
   ```
   File → Open → CMake → 选择 CMakeLists.txt
   ```

4. **构建运行**
   ```
   Build → Build All
   Debug → Start Without Debugging (Ctrl+F5)
   ```

## 🐛 常见问题解决

### ❌ 问题 1: "Qt 找不到"
```
CMake Error: Could not find Qt6
```

**解决方案:**
```cmd
# 设置 CMAKE_PREFIX_PATH
set CMAKE_PREFIX_PATH=C:\Qt\6.5.3\msvc2019_64
cmake .. -DCMAKE_PREFIX_PATH=C:\Qt\6.5.3\msvc2019_64
```

### ❌ 问题 2: "MSVC 编译器找不到"
```
CMake Error: CMAKE_CXX_COMPILER not set
```

**解决方案:**
```cmd
# 使用 Visual Studio 开发者命令提示符
# 或手动设置编译器
cmake .. -G "Visual Studio 17 2022" -A x64
```

### ❌ 问题 3: "moc.exe 找不到"
```
Error: moc.exe not found
```

**解决方案:**
```cmd
# 添加 Qt bin 目录到 PATH
set PATH=%PATH%;C:\Qt\6.5.3\msvc2019_64\bin
```

### ❌ 问题 4: "DLL 缺失"
```
应用程序无法启动，因为找不到 Qt6Core.dll
```

**解决方案:**
```cmd
# 使用 windeployqt 部署依赖
cd build\Release
C:\Qt\6.5.3\msvc2019_64\bin\windeployqt.exe MyApp.exe
```

### ❌ 问题 5: "中文乱码"
**解决方案:**
```cpp
// 在 main.cpp 中添加
QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
```

## 📋 构建检查清单

### ✅ 安装前检查
- [ ] Windows 10 版本 1903 或更高
- [ ] 至少 8GB 可用磁盘空间
- [ ] 管理员权限
- [ ] 稳定的网络连接

### ✅ 安装后检查
- [ ] Visual Studio 2022 正常启动
- [ ] Qt Creator 正常启动
- [ ] 命令行可以运行 `cmake --version`
- [ ] 命令行可以运行 `qmake --version`
- [ ] 环境变量 PATH 包含 Qt 路径

### ✅ 构建前检查
- [ ] 项目文件完整下载
- [ ] CMakeLists.txt 文件存在
- [ ] 所有 .h 和 .cpp 文件存在
- [ ] resources.qrc 文件存在

### ✅ 构建后检查
- [ ] build 目录生成
- [ ] MyApp.exe 文件生成
- [ ] 程序可以正常启动
- [ ] 界面显示正常

## 🎯 性能优化建议

### 💾 磁盘空间优化
```
Qt 完整安装: ~3GB
Visual Studio: ~2-4GB
项目构建: ~50MB
总计需求: ~6-8GB
```

### ⚡ 编译速度优化
```cmd
# 使用多核编译
cmake --build . --config Release --parallel 8

# 或在 CMakeLists.txt 中设置
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
```

### 🔧 调试优化
```
Debug 模式: 开发调试使用
Release 模式: 最终发布使用
RelWithDebInfo: 发布版本但保留调试信息
```

## 📞 获取帮助

如果遇到问题，可以通过以下方式获取帮助:

1. **Qt 官方文档**: https://doc.qt.io/
2. **Qt 论坛**: https://forum.qt.io/
3. **Stack Overflow**: 搜索 "Qt Windows build"
4. **GitHub Issues**: 项目相关问题

---

**祝你构建成功！** 🎉


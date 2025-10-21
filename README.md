# 🎨 Qt Shadcn/UI 认证界面

[![Build Windows](https://github.com/YOUR_USERNAME/qt-shadcn-design/actions/workflows/build-windows.yml/badge.svg)](https://github.com/YOUR_USERNAME/qt-shadcn-design/actions/workflows/build-windows.yml)
[![Build Qt 6.5](https://github.com/YOUR_USERNAME/qt-shadcn-design/actions/workflows/build-qt6.5.yml/badge.svg)](https://github.com/YOUR_USERNAME/qt-shadcn-design/actions/workflows/build-qt6.5.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

基于 **Shadcn/UI** 设计风格的现代化 Qt Windows 桌面应用认证界面，支持手机号登录、短信验证码和微信扫码登录。

## ✨ 特性

### 🎯 功能特性
- ✅ **手机号 + 验证码登录** - 支持中国大陆手机号验证
- ✅ **微信扫码登录** - 集成微信 OAuth 登录界面
- ✅ **用户注册** - 手机号注册，用户协议确认
- ✅ **表单验证** - 实时输入验证和错误提示
- ✅ **倒计时功能** - 60秒验证码获取倒计时
- ✅ **页面切换** - 登录/注册页面平滑切换

### 🎨 设计特性
- ✅ **Shadcn/UI 风格** - 现代化的设计语言
- ✅ **响应式布局** - 完美适配 900×600 窗口尺寸
- ✅ **无边框窗口** - 自定义标题栏设计
- ✅ **平滑动画** - 优雅的交互动画效果
- ✅ **高 DPI 支持** - 适配不同分辨率显示器

## 📸 界面预览

### 登录界面 (900×600)
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

## 🚀 快速开始

### 📦 下载预编译版本 (推荐)

1. 访问 [Releases](https://github.com/YOUR_USERNAME/qt-shadcn-design/releases) 页面
2. 下载最新的 `QtShadcnAuth-Windows-x64-*.zip`
3. 解压后双击 `MyApp.exe` 运行

### 🔧 自动构建下载

如果没有 Release 版本，可以从 GitHub Actions 下载自动构建的版本：

1. 访问 [Actions](https://github.com/YOUR_USERNAME/qt-shadcn-design/actions) 页面
2. 点击最新的成功构建
3. 在 "Artifacts" 部分下载构建产物

## 🛠️ 本地构建

### 环境要求

- **操作系统**: Windows 10/11
- **Qt 版本**: 6.5+ 或 6.9+ (推荐)
- **编译器**: Visual Studio 2019/2022 或 MinGW
- **CMake**: 3.21+

### 构建步骤

#### 方法 1: 一键构建脚本
```cmd
# 克隆项目
git clone https://github.com/YOUR_USERNAME/qt-shadcn-design.git
cd qt-shadcn-design

# 运行构建脚本 (VS 2022 + Qt 6.9)
修复-VS2022-Qt6.9.bat
```

#### 方法 2: Qt Creator
```
1. 启动 Qt Creator
2. File → Open File or Project → 选择 CMakeLists.txt
3. 选择构建套件 (Desktop Qt 6.x MSVC 64bit)
4. Build → Build Project
5. Run
```

#### 方法 3: 命令行
```cmd
mkdir build && cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
Release\MyApp.exe
```

## 📋 技术栈

- **框架**: Qt 6.5+ / 6.9+
- **语言**: C++17
- **构建**: CMake 3.21+
- **样式**: QSS (Qt Style Sheets)
- **平台**: Windows 10/11 x64
- **CI/CD**: GitHub Actions

## 📁 项目结构

```
qt-shadcn-design/
├── 📄 CMakeLists.txt           # CMake 构建配置
├── 🎨 login_styles.qss         # Shadcn/UI 样式表
├── 📱 login_window.h/cpp       # 登录窗口实现
├── 📝 register_window.h/cpp    # 注册窗口实现
├── 🚀 main.cpp                 # 应用程序入口
├── 📦 resources.qrc            # Qt 资源文件
├── 🔧 .github/workflows/       # GitHub Actions 配置
├── 📖 docs/                    # 详细文档
│   ├── Windows构建指南.md
│   ├── Qt6.9兼容性修复.md
│   └── 界面设计预览.md
└── 🛠️ 修复-VS2022-Qt6.9.bat   # 构建脚本
```

## 🎨 设计系统

### 颜色方案
```css
/* 主色调 */
--primary: #0f172a;           /* 深色主色 */
--background: #ffffff;        /* 白色背景 */
--border: #e2e8f0;           /* 边框色 */
--input: #e2e8f0;            /* 输入框边框 */
--muted: #64748b;            /* 静音文字 */

/* 状态色 */
--success: #10b981;          /* 成功绿 */
--error: #ef4444;            /* 错误红 */
--wechat: #07c160;           /* 微信绿 */
```

### 字体规范
- **主标题**: 24px, 粗体
- **副标题**: 18px, 中等
- **正文**: 14px, 常规
- **小字**: 12px, 常规

## 🔧 自定义配置

### 修改颜色主题
编辑 `login_styles.qss` 文件中的颜色变量。

### 调整窗口尺寸
在 `login_window.cpp` 和 `register_window.cpp` 中修改：
```cpp
setFixedSize(900, 600);  // 修改为你需要的尺寸
```

### 集成真实 API
替换 `onLoginClicked()` 和 `onGetCodeClicked()` 中的模拟逻辑。

## 🐛 故障排除

### 常见问题

1. **编译错误: 找不到 Qt**
   ```cmd
   set CMAKE_PREFIX_PATH=C:\Qt\6.9.0\msvc2022_64
   ```

2. **头文件错误: QtWidgets/QTimer**
   ```cpp
   // 错误
   #include <QtWidgets/QTimer>
   
   // 正确
   #include <QtCore/QTimer>
   ```

3. **DLL 缺失**
   ```cmd
   windeployqt MyApp.exe
   ```

4. **中文乱码**
   ```cpp
   QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
   ```

更多问题请查看 [故障排除指南](docs/Windows构建指南.md#故障排除)。

## 📚 文档

- [Windows 构建指南](docs/Windows构建指南.md) - 详细的构建说明
- [Qt 6.9 兼容性修复](docs/Qt6.9兼容性修复.md) - 版本兼容性问题
- [界面设计预览](docs/界面设计预览.md) - 详细的设计说明
- [快速开始指南](docs/快速开始-Windows.md) - 5分钟快速上手

## 🤝 贡献

欢迎提交 Issue 和 Pull Request！

### 开发流程
1. Fork 本仓库
2. 创建特性分支 (`git checkout -b feature/AmazingFeature`)
3. 提交更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 创建 Pull Request

## 📄 许可证

本项目采用 MIT 许可证。详见 [LICENSE](LICENSE) 文件。

## 🙏 致谢

- [Shadcn/UI](https://ui.shadcn.com/) - 设计灵感来源
- [Qt Framework](https://www.qt.io/) - 强大的跨平台框架
- [GitHub Actions](https://github.com/features/actions) - 自动化构建

## 📞 支持

- 🐛 [提交 Bug](https://github.com/YOUR_USERNAME/qt-shadcn-design/issues/new?template=bug_report.md)
- 💡 [功能建议](https://github.com/YOUR_USERNAME/qt-shadcn-design/issues/new?template=feature_request.md)
- 💬 [讨论交流](https://github.com/YOUR_USERNAME/qt-shadcn-design/discussions)

---

**🎉 享受使用现代化的 Qt Shadcn/UI 认证界面！**
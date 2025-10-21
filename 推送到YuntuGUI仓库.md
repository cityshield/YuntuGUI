# 🚀 推送到 YuntuGUI 仓库指南

## 📋 仓库信息

- **仓库地址**: https://github.com/cityshield/YuntuGUI.git
- **仓库状态**: 空仓库 (正好适合推送我们的项目)
- **项目名称**: Qt Shadcn/UI 认证界面

## 🔧 推送步骤

### 方法 1: 使用 GitHub CLI (推荐)

如果你有 GitHub CLI，这是最简单的方法：

```bash
# 1. 安装 GitHub CLI (如果还没有)
# macOS: brew install gh
# Windows: winget install --id GitHub.cli

# 2. 登录 GitHub
gh auth login

# 3. 推送代码
cd "/Users/fengdaniu/Documents/cursor try/WinUI/qt-shadcn-design"
git push -u origin main
```

### 方法 2: 使用 Personal Access Token

1. **创建 Personal Access Token**
   - 访问 https://github.com/settings/tokens
   - 点击 "Generate new token" → "Generate new token (classic)"
   - 选择权限: `repo` (完整仓库访问权限)
   - 复制生成的 token

2. **使用 Token 推送**
   ```bash
   cd "/Users/fengdaniu/Documents/cursor try/WinUI/qt-shadcn-design"
   
   # 使用 token 推送 (替换 YOUR_TOKEN)
   git remote set-url origin https://YOUR_TOKEN@github.com/cityshield/YuntuGUI.git
   git push -u origin main
   ```

### 方法 3: 使用 SSH (最安全)

1. **生成 SSH 密钥** (如果还没有)
   ```bash
   ssh-keygen -t ed25519 -C "your_email@example.com"
   ```

2. **添加 SSH 密钥到 GitHub**
   - 复制公钥: `cat ~/.ssh/id_ed25519.pub`
   - 访问 https://github.com/settings/keys
   - 点击 "New SSH key"，粘贴公钥

3. **使用 SSH 推送**
   ```bash
   cd "/Users/fengdaniu/Documents/cursor try/WinUI/qt-shadcn-design"
   
   # 更改为 SSH URL
   git remote set-url origin git@github.com:cityshield/YuntuGUI.git
   git push -u origin main
   ```

## 🎯 推送后的自动化

### GitHub Actions 自动编译

推送成功后，GitHub Actions 会自动开始编译：

1. **访问 Actions 页面**
   ```
   https://github.com/cityshield/YuntuGUI/actions
   ```

2. **两个构建工作流**
   - `🪟 Build Windows Qt Application` (Qt 6.9)
   - `🪟 Build Windows Qt 6.5 (Fallback)` (Qt 6.5)

3. **构建时间**: 约 10-15 分钟

4. **下载编译结果**
   - 构建完成后，在 Artifacts 中下载
   - 文件名: `QtShadcnAuth-Windows-x64-*.zip`

### 自动部署特性

- ✅ 自动检测 Qt 版本
- ✅ 自动部署 Qt 依赖库
- ✅ 自动打包为 ZIP 文件
- ✅ 支持 Release 自动发布

## 📦 项目重命名建议

由于仓库名是 `YuntuGUI`，建议更新项目中的一些引用：

### 1. 更新 README.md 中的链接
```markdown
# 将所有 YOUR_USERNAME/qt-shadcn-design 替换为
cityshield/YuntuGUI
```

### 2. 更新构建脚本中的项目名
```cpp
// 在 main.cpp 中可以更新应用名称
app.setApplicationName("YuntuGUI");
app.setApplicationDisplayName("云图 GUI - Shadcn/UI 认证界面");
```

### 3. 更新 CMakeLists.txt
```cmake
project(YuntuGUI VERSION 1.0.0 LANGUAGES CXX)
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "YuntuGUI"
)
```

## 🔍 验证推送成功

推送成功后，你应该能看到：

1. ✅ GitHub 仓库不再显示 "This repository is empty"
2. ✅ 所有项目文件都已上传
3. ✅ README.md 正确显示项目介绍
4. ✅ GitHub Actions 开始自动构建

## 🎉 推送完成后的操作

### 1. 创建第一个 Release
```bash
# 创建版本标签
git tag -a v1.0.0 -m "🎉 YuntuGUI v1.0.0 - Qt Shadcn/UI 认证界面首发版本"
git push origin v1.0.0
```

### 2. 更新仓库描述
在 GitHub 仓库页面添加描述：
```
基于 Shadcn/UI 设计风格的现代化 Qt Windows 桌面应用认证界面
```

### 3. 添加主题标签
```
qt, cpp, shadcn-ui, windows, desktop-app, authentication, login, gui
```

## 📞 如果遇到问题

### 认证失败
- 确保有仓库的写入权限
- 检查 Personal Access Token 权限
- 尝试使用 SSH 方式

### 推送被拒绝
- 确保仓库是空的或者你有权限覆盖
- 使用 `git push --force-with-lease origin main` (谨慎使用)

### 构建失败
- 检查 GitHub Actions 日志
- Qt 6.9 不可用时会自动回退到 Qt 6.5

---

**🚀 准备好推送你的 Qt Shadcn/UI 项目到 YuntuGUI 仓库了！**

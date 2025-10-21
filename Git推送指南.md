# 🚀 Git 推送和自动编译指南

## 📋 推送到 GitHub 的步骤

### 1️⃣ 创建 GitHub 仓库

1. **登录 GitHub**
   - 访问 https://github.com
   - 登录你的账户

2. **创建新仓库**
   - 点击右上角的 "+" → "New repository"
   - 仓库名称: `qt-shadcn-design`
   - 描述: `Qt Shadcn/UI 风格的现代化认证界面`
   - 设置为 Public (公开) 或 Private (私有)
   - **不要**勾选 "Add a README file"
   - **不要**勾选 "Add .gitignore"
   - **不要**勾选 "Choose a license"
   - 点击 "Create repository"

### 2️⃣ 推送本地代码

在项目目录中运行以下命令：

```bash
# 1. 设置远程仓库 (替换 YOUR_USERNAME 为你的 GitHub 用户名)
git remote add origin https://github.com/YOUR_USERNAME/qt-shadcn-design.git

# 2. 设置默认分支
git branch -M main

# 3. 推送代码到 GitHub
git push -u origin main
```

### 3️⃣ 验证推送成功

1. 刷新 GitHub 仓库页面
2. 确认所有文件都已上传
3. 检查 README.md 是否正确显示

## 🔧 自动编译配置

### GitHub Actions 自动触发

推送代码后，GitHub Actions 会自动开始编译：

1. **访问 Actions 页面**
   ```
   https://github.com/YOUR_USERNAME/qt-shadcn-design/actions
   ```

2. **查看构建状态**
   - ✅ 绿色勾号 = 构建成功
   - ❌ 红色叉号 = 构建失败
   - 🟡 黄色圆圈 = 正在构建

3. **下载构建产物**
   - 点击成功的构建
   - 在 "Artifacts" 部分下载编译好的程序

### 两个构建配置

#### 🥇 主构建 (Qt 6.9)
- **文件**: `.github/workflows/build-windows.yml`
- **触发**: 推送到 main 分支
- **Qt 版本**: 6.9.0
- **编译器**: MSVC 2022

#### 🥈 备用构建 (Qt 6.5)
- **文件**: `.github/workflows/build-qt6.5.yml`
- **触发**: 手动触发或推送到 main
- **Qt 版本**: 6.5.3
- **编译器**: MSVC 2022

## 📦 下载编译结果

### 方法 1: 从 Actions 下载

1. 访问 Actions 页面
2. 点击最新的成功构建
3. 滚动到底部的 "Artifacts" 部分
4. 下载 `QtShadcnAuth-Windows-x64-*.zip`

### 方法 2: 创建 Release (推荐)

1. **创建标签和发布**
   ```bash
   # 在本地创建标签
   git tag -a v1.0.0 -m "🎉 首个正式版本"
   
   # 推送标签
   git push origin v1.0.0
   ```

2. **GitHub 自动创建 Release**
   - GitHub Actions 会自动检测到标签
   - 自动编译并上传到 Releases 页面
   - 用户可以直接从 Releases 下载

## 🔍 故障排除

### 常见推送问题

#### ❌ 认证失败
```bash
# 如果使用 HTTPS 推送失败，尝试使用 Personal Access Token
# 1. GitHub → Settings → Developer settings → Personal access tokens
# 2. 生成新的 token
# 3. 使用 token 作为密码推送
```

#### ❌ 仓库已存在
```bash
# 如果远程仓库已存在，先删除再添加
git remote remove origin
git remote add origin https://github.com/YOUR_USERNAME/qt-shadcn-design.git
```

### 常见构建问题

#### ❌ Qt 6.9 不可用
- GitHub Actions 会自动回退到 Qt 6.5
- 或者手动触发 Qt 6.5 构建工作流

#### ❌ 编译失败
1. 检查 Actions 日志
2. 查看具体错误信息
3. 修复代码后重新推送

#### ❌ 依赖缺失
- GitHub Actions 已配置所有必需依赖
- 包括 Qt、CMake、MSVC 编译器

## 🎯 完整推送流程示例

```bash
# 1. 确保在项目目录
cd "/path/to/qt-shadcn-design"

# 2. 检查文件状态
git status

# 3. 添加远程仓库 (替换用户名)
git remote add origin https://github.com/YOUR_USERNAME/qt-shadcn-design.git

# 4. 推送到 GitHub
git push -u origin main

# 5. 创建第一个版本标签 (可选)
git tag -a v1.0.0 -m "🎉 Qt Shadcn/UI 认证界面 v1.0.0"
git push origin v1.0.0
```

## 📊 构建状态徽章

推送成功后，你可以在 README.md 中看到构建状态徽章：

```markdown
[![Build Windows](https://github.com/YOUR_USERNAME/qt-shadcn-design/actions/workflows/build-windows.yml/badge.svg)](https://github.com/YOUR_USERNAME/qt-shadcn-design/actions/workflows/build-windows.yml)
```

## 🎉 成功标志

当你看到以下内容时，说明一切设置成功：

1. ✅ GitHub 仓库包含所有文件
2. ✅ Actions 页面显示构建成功
3. ✅ Artifacts 中有可下载的 exe 文件
4. ✅ README 显示绿色的构建徽章

## 📞 获取帮助

如果遇到问题：

1. **检查 Actions 日志** - 查看详细错误信息
2. **查看 Issues** - 搜索类似问题
3. **创建 Issue** - 描述具体问题和错误信息

---

**🚀 现在你可以在任何地方访问和下载编译好的 Qt 应用程序了！**

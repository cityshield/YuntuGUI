# 🔧 GitHub Actions 故障排除指南

## 🎯 如果推送后仍然没有看到构建

### 1️⃣ **手动触发构建**
访问：https://github.com/cityshield/YuntuGUI/actions

1. 点击左侧的 "🪟 Build Windows Qt Application"
2. 点击右侧的 "Run workflow" 按钮
3. 选择 "main" 分支
4. 点击绿色的 "Run workflow" 按钮

### 2️⃣ **检查工作流文件**
确认以下文件存在于 GitHub 仓库中：
- `.github/workflows/build-windows.yml`
- `.github/workflows/build-qt6.5.yml`

访问：https://github.com/cityshield/YuntuGUI/tree/main/.github/workflows

### 3️⃣ **检查仓库权限**
确保：
- 你有仓库的 Actions 权限
- 仓库的 Actions 功能已启用
- 访问：https://github.com/cityshield/YuntuGUI/settings/actions

### 4️⃣ **强制触发构建**
创建一个小的更改来触发构建：

```bash
cd "/Users/fengdaniu/Documents/cursor try/WinUI/qt-shadcn-design"

# 创建一个小的更改
echo "# 触发构建测试" >> README.md
git add README.md
git commit -m "🔄 触发 GitHub Actions 构建测试"
git push origin main
```

### 5️⃣ **检查 Actions 日志**
如果构建开始但失败了：
1. 访问 Actions 页面
2. 点击失败的构建
3. 查看详细日志
4. 根据错误信息调试

## 🚀 **备用方案：手动触发 Qt 6.5 构建**

如果主构建有问题，可以手动触发备用构建：

1. 访问：https://github.com/cityshield/YuntuGUI/actions
2. 点击 "🪟 Build Windows Qt 6.5 (Fallback)"
3. 点击 "Run workflow"
4. 选择 "main" 分支并运行

## 📊 **预期的构建流程**

### 构建步骤 (约 10-15 分钟)：
1. **📥 Checkout Repository** (30秒)
2. **🔧 Setup MSVC** (1分钟)
3. **📦 Install Qt** (3-5分钟)
4. **🔍 Verify Environment** (30秒)
5. **⚙️ Configure CMake** (1分钟)
6. **🔨 Build Application** (2-3分钟)
7. **📦 Deploy Qt Libraries** (1分钟)
8. **📊 Package Application** (1分钟)

### 成功标志：
- ✅ 所有步骤显示绿色勾号
- ✅ 在 Artifacts 中有下载文件
- ✅ 文件名类似：`YuntuGUI-Windows-x64-*.zip`

## 🔍 **调试命令**

如果需要本地调试，可以运行：

```bash
cd "/Users/fengdaniu/Documents/cursor try/WinUI/qt-shadcn-design"

# 检查 Git 状态
git status
git log --oneline -5

# 检查远程仓库
git remote -v

# 检查工作流文件
ls -la .github/workflows/
cat .github/workflows/build-windows.yml | head -20
```

## 📞 **如果问题持续存在**

1. **检查 GitHub 状态**：https://www.githubstatus.com/
2. **查看 GitHub Actions 文档**：https://docs.github.com/en/actions
3. **检查仓库设置**：确保 Actions 功能已启用
4. **联系仓库管理员**：确认权限设置

---

**🎯 大多数情况下，推送工作流文件后 GitHub Actions 会立即开始工作！**

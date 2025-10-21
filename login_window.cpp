#include "login_window.h"
#include <QtWidgets/QApplication>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QRegularExpression>
#include <QtGui/QPixmap>
#include <QtGui/QPainter>
#include <QtGui/QBrush>
#include <QtCore/QDebug>

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_centralWidget(nullptr)
    , m_codeTimer(new QTimer(this))
    , m_codeCountdown(60)
    , m_isCodeSent(false)
    , m_isFormValid(false)
{
    // 设置窗口属性
    setFixedSize(900, 600);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
    setAttribute(Qt::WA_TranslucentBackground);
    
    setupUI();
    loadStyles();
    setupAnimations();
    
    // 连接信号槽
    connect(m_codeTimer, &QTimer::timeout, this, &LoginWindow::updateCodeButtonText);
    connect(m_phoneEdit, &QLineEdit::textChanged, this, &LoginWindow::onPhoneTextChanged);
    connect(m_codeEdit, &QLineEdit::textChanged, this, &LoginWindow::onCodeTextChanged);
    connect(m_getCodeButton, &QPushButton::clicked, this, &LoginWindow::onGetCodeClicked);
    connect(m_loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginClicked);
    connect(m_wechatButton, &QPushButton::clicked, this, &LoginWindow::onWeChatLoginClicked);
    connect(m_switchLink, &QLabel::mousePressEvent, this, &LoginWindow::onSwitchToRegister);
    connect(m_closeButton, &QPushButton::clicked, this, &QWidget::close);
    connect(m_minimizeButton, &QPushButton::clicked, this, &QWidget::showMinimized);
}

LoginWindow::~LoginWindow()
{
}

void LoginWindow::setupUI()
{
    // 创建中央部件
    m_centralWidget = new QWidget(this);
    m_centralWidget->setObjectName("MainWindow");
    setCentralWidget(m_centralWidget);
    
    // 创建主布局
    m_mainLayout = new QHBoxLayout(m_centralWidget);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);
    
    setupLeftPanel();
    setupRightPanel();
    
    // 添加到主布局
    m_mainLayout->addWidget(m_leftPanel);
    m_mainLayout->addWidget(m_rightPanel);
}

void LoginWindow::setupLeftPanel()
{
    // 左侧装饰面板
    m_leftPanel = new QWidget();
    m_leftPanel->setObjectName("LeftPanel");
    m_leftPanel->setFixedWidth(400);
    
    m_leftLayout = new QVBoxLayout(m_leftPanel);
    m_leftLayout->setContentsMargins(48, 80, 48, 80);
    m_leftLayout->setSpacing(16);
    
    // Logo
    m_logoLabel = new QLabel("MyApp");
    m_logoLabel->setObjectName("LogoLabel");
    m_logoLabel->setAlignment(Qt::AlignCenter);
    
    // 欢迎文字
    m_welcomeLabel = new QLabel("欢迎回来");
    m_welcomeLabel->setObjectName("WelcomeLabel");
    m_welcomeLabel->setAlignment(Qt::AlignCenter);
    
    // 描述文字
    m_descriptionLabel = new QLabel("请使用手机号登录您的账户\n或使用微信扫码快速登录");
    m_descriptionLabel->setObjectName("DescriptionLabel");
    m_descriptionLabel->setAlignment(Qt::AlignCenter);
    m_descriptionLabel->setWordWrap(true);
    
    // 装饰图形 (可以后续添加 SVG 图标)
    m_decorationLabel = new QLabel();
    m_decorationLabel->setMinimumHeight(200);
    m_decorationLabel->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #e0e7ff, stop:1 #c7d2fe); border-radius: 12px;");
    
    m_leftLayout->addWidget(m_logoLabel);
    m_leftLayout->addWidget(m_welcomeLabel);
    m_leftLayout->addWidget(m_descriptionLabel);
    m_leftLayout->addStretch();
    m_leftLayout->addWidget(m_decorationLabel);
    m_leftLayout->addStretch();
}

void LoginWindow::setupRightPanel()
{
    // 右侧表单面板
    m_rightPanel = new QWidget();
    m_rightPanel->setObjectName("RightPanel");
    m_rightPanel->setFixedWidth(500);
    
    m_rightLayout = new QVBoxLayout(m_rightPanel);
    m_rightLayout->setContentsMargins(48, 40, 48, 40);
    m_rightLayout->setSpacing(0);
    
    setupTitleBar();
    setupFormArea();
    setupWeChatArea();
    setupSwitchArea();
}

void LoginWindow::setupTitleBar()
{
    // 自定义标题栏 (可选)
    // 这里可以添加窗口控制按钮
}

void LoginWindow::setupFormArea()
{
    // 表单容器
    m_formContainer = new QWidget();
    m_formContainer->setObjectName("FormContainer");
    
    m_formLayout = new QVBoxLayout(m_formContainer);
    m_formLayout->setContentsMargins(0, 0, 0, 0);
    m_formLayout->setSpacing(16);
    
    // 标题
    m_titleFormLabel = new QLabel("登录");
    m_titleFormLabel->setObjectName("TitleLabel");
    
    m_subtitleLabel = new QLabel("输入手机号和验证码登录");
    m_subtitleLabel->setObjectName("SubtitleLabel");
    
    // 手机号输入组
    m_phoneInputGroup = new QWidget();
    m_phoneInputGroup->setObjectName("PhoneInputGroup");
    m_phoneLayout = new QVBoxLayout(m_phoneInputGroup);
    m_phoneLayout->setContentsMargins(0, 0, 0, 0);
    m_phoneLayout->setSpacing(6);
    
    m_phoneLabel = new QLabel("手机号");
    m_phoneLabel->setObjectName("InputLabel");
    
    m_phoneEdit = new QLineEdit();
    m_phoneEdit->setPlaceholderText("请输入手机号");
    m_phoneEdit->setMaxLength(11);
    
    m_phoneErrorLabel = new QLabel();
    m_phoneErrorLabel->setObjectName("ErrorLabel");
    m_phoneErrorLabel->hide();
    
    m_phoneLayout->addWidget(m_phoneLabel);
    m_phoneLayout->addWidget(m_phoneEdit);
    m_phoneLayout->addWidget(m_phoneErrorLabel);
    
    // 验证码输入组
    m_codeInputGroup = new QWidget();
    m_codeInputGroup->setObjectName("CodeInputGroup");
    m_codeLayout = new QVBoxLayout(m_codeInputGroup);
    m_codeLayout->setContentsMargins(0, 0, 0, 0);
    m_codeLayout->setSpacing(6);
    
    m_codeLabel = new QLabel("验证码");
    m_codeLabel->setObjectName("InputLabel");
    
    m_codeInputLayout = new QHBoxLayout();
    m_codeInputLayout->setSpacing(12);
    
    m_codeEdit = new QLineEdit();
    m_codeEdit->setPlaceholderText("请输入验证码");
    m_codeEdit->setMaxLength(6);
    
    m_getCodeButton = new QPushButton("获取验证码");
    m_getCodeButton->setObjectName("CodeButton");
    m_getCodeButton->setEnabled(false);
    
    m_codeInputLayout->addWidget(m_codeEdit, 1);
    m_codeInputLayout->addWidget(m_getCodeButton);
    
    m_codeErrorLabel = new QLabel();
    m_codeErrorLabel->setObjectName("ErrorLabel");
    m_codeErrorLabel->hide();
    
    m_codeLayout->addWidget(m_codeLabel);
    m_codeLayout->addLayout(m_codeInputLayout);
    m_codeLayout->addWidget(m_codeErrorLabel);
    
    // 登录按钮
    m_buttonGroup = new QWidget();
    m_buttonGroup->setObjectName("ButtonGroup");
    m_buttonLayout = new QVBoxLayout(m_buttonGroup);
    m_buttonLayout->setContentsMargins(0, 0, 0, 0);
    
    m_loginButton = new QPushButton("登录");
    m_loginButton->setObjectName("PrimaryButton");
    m_loginButton->setEnabled(false);
    
    m_buttonLayout->addWidget(m_loginButton);
    
    // 消息提示
    m_messageLabel = new QLabel();
    m_messageLabel->setObjectName("ErrorLabel");
    m_messageLabel->setAlignment(Qt::AlignCenter);
    m_messageLabel->hide();
    
    // 添加到表单布局
    m_formLayout->addWidget(m_titleFormLabel);
    m_formLayout->addWidget(m_subtitleLabel);
    m_formLayout->addWidget(m_phoneInputGroup);
    m_formLayout->addWidget(m_codeInputGroup);
    m_formLayout->addWidget(m_buttonGroup);
    m_formLayout->addWidget(m_messageLabel);
    
    m_rightLayout->addWidget(m_formContainer);
}

void LoginWindow::setupWeChatArea()
{
    // 分割线
    m_dividerWidget = new QWidget();
    m_dividerLayout = new QHBoxLayout(m_dividerWidget);
    m_dividerLayout->setContentsMargins(0, 24, 0, 24);
    
    m_dividerLine1 = new QFrame();
    m_dividerLine1->setObjectName("DividerLine");
    m_dividerLine1->setFrameShape(QFrame::HLine);
    
    m_dividerText = new QLabel("或");
    m_dividerText->setObjectName("DividerText");
    m_dividerText->setAlignment(Qt::AlignCenter);
    
    m_dividerLine2 = new QFrame();
    m_dividerLine2->setObjectName("DividerLine");
    m_dividerLine2->setFrameShape(QFrame::HLine);
    
    m_dividerLayout->addWidget(m_dividerLine1, 1);
    m_dividerLayout->addWidget(m_dividerText);
    m_dividerLayout->addWidget(m_dividerLine2, 1);
    
    // 微信登录区域
    m_wechatArea = new QWidget();
    m_wechatArea->setObjectName("WeChatArea");
    m_wechatLayout = new QVBoxLayout(m_wechatArea);
    m_wechatLayout->setContentsMargins(0, 0, 0, 0);
    m_wechatLayout->setSpacing(16);
    
    m_wechatButton = new QPushButton("🔄 微信扫码登录");
    m_wechatButton->setObjectName("WeChatButton");
    
    // 二维码区域 (初始隐藏)
    m_qrCodeFrame = new QFrame();
    m_qrCodeFrame->setObjectName("QRCodeFrame");
    m_qrCodeFrame->setFixedSize(200, 200);
    m_qrCodeFrame->hide();
    
    QVBoxLayout *qrLayout = new QVBoxLayout(m_qrCodeFrame);
    m_qrCodeLabel = new QLabel("二维码");
    m_qrCodeLabel->setAlignment(Qt::AlignCenter);
    m_qrCodeLabel->setStyleSheet("background-color: #f8fafc; border: 2px dashed #cbd5e1; min-height: 150px;");
    
    m_qrCodeText = new QLabel("请使用微信扫描二维码");
    m_qrCodeText->setObjectName("QRCodeLabel");
    
    qrLayout->addWidget(m_qrCodeLabel);
    qrLayout->addWidget(m_qrCodeText);
    
    m_wechatLayout->addWidget(m_wechatButton);
    m_wechatLayout->addWidget(m_qrCodeFrame, 0, Qt::AlignCenter);
    
    m_rightLayout->addWidget(m_dividerWidget);
    m_rightLayout->addWidget(m_wechatArea);
}

void LoginWindow::setupSwitchArea()
{
    // 页面切换区域
    m_switchArea = new QWidget();
    m_switchArea->setObjectName("SwitchArea");
    m_switchLayout = new QHBoxLayout(m_switchArea);
    m_switchLayout->setContentsMargins(0, 0, 0, 0);
    
    m_switchText = new QLabel("还没有账户？");
    m_switchText->setStyleSheet("color: #64748b; font-size: 14px;");
    
    m_switchLink = new QLabel("立即注册");
    m_switchLink->setObjectName("LinkLabel");
    m_switchLink->setCursor(Qt::PointingHandCursor);
    
    m_switchLayout->addStretch();
    m_switchLayout->addWidget(m_switchText);
    m_switchLayout->addWidget(m_switchLink);
    m_switchLayout->addStretch();
    
    m_rightLayout->addStretch();
    m_rightLayout->addWidget(m_switchArea);
}

void LoginWindow::loadStyles()
{
    QFile file(":/styles/login_styles.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString styleSheet = stream.readAll();
        setStyleSheet(styleSheet);
    }
}

void LoginWindow::setupAnimations()
{
    // 设置淡入淡出动画
    m_fadeAnimation = new QPropertyAnimation(m_messageLabel, "windowOpacity");
    m_fadeAnimation->setDuration(300);
    m_fadeAnimation->setEasingCurve(QEasingCurve::InOutQuad);
}

void LoginWindow::onPhoneTextChanged()
{
    QString phone = m_phoneEdit->text();
    bool isValid = isValidPhone(phone);
    
    if (phone.isEmpty()) {
        m_phoneErrorLabel->hide();
        m_getCodeButton->setEnabled(false);
    } else if (!isValid && phone.length() >= 11) {
        m_phoneErrorLabel->setText("请输入正确的手机号");
        m_phoneErrorLabel->show();
        m_getCodeButton->setEnabled(false);
    } else if (isValid) {
        m_phoneErrorLabel->hide();
        m_getCodeButton->setEnabled(!m_isCodeSent);
    } else {
        m_phoneErrorLabel->hide();
        m_getCodeButton->setEnabled(false);
    }
    
    validateForm();
}

void LoginWindow::onCodeTextChanged()
{
    validateForm();
}

void LoginWindow::onGetCodeClicked()
{
    if (!isValidPhone(m_phoneEdit->text())) {
        showMessage("请输入正确的手机号", true);
        return;
    }
    
    // 模拟发送验证码
    m_isCodeSent = true;
    m_codeCountdown = 60;
    m_getCodeButton->setEnabled(false);
    m_codeTimer->start(1000);
    
    showMessage("验证码已发送", false);
    m_codeEdit->setFocus();
}

void LoginWindow::onLoginClicked()
{
    QString phone = m_phoneEdit->text();
    QString code = m_codeEdit->text();
    
    if (!isValidPhone(phone)) {
        showMessage("请输入正确的手机号", true);
        return;
    }
    
    if (code.length() != 6) {
        showMessage("请输入6位验证码", true);
        return;
    }
    
    // 模拟登录过程
    m_loginButton->setText("登录中...");
    m_loginButton->setEnabled(false);
    
    // 这里应该调用实际的登录 API
    QTimer::singleShot(2000, [this]() {
        showMessage("登录成功！", false);
        // 跳转到主界面
        // emit loginSuccess();
    });
}

void LoginWindow::onWeChatLoginClicked()
{
    if (m_qrCodeFrame->isVisible()) {
        m_qrCodeFrame->hide();
        m_wechatButton->setText("🔄 微信扫码登录");
    } else {
        m_qrCodeFrame->show();
        m_wechatButton->setText("🔄 刷新二维码");
        // 这里应该生成实际的二维码
        showMessage("请使用微信扫描二维码", false);
    }
}

void LoginWindow::onSwitchToRegister()
{
    // 切换到注册页面
    // emit switchToRegister();
}

void LoginWindow::updateCodeButtonText()
{
    m_codeCountdown--;
    if (m_codeCountdown <= 0) {
        m_codeTimer->stop();
        m_getCodeButton->setText("获取验证码");
        m_getCodeButton->setEnabled(isValidPhone(m_phoneEdit->text()));
        m_isCodeSent = false;
    } else {
        m_getCodeButton->setText(QString("重新发送(%1s)").arg(m_codeCountdown));
    }
}

void LoginWindow::validateForm()
{
    bool phoneValid = isValidPhone(m_phoneEdit->text());
    bool codeValid = m_codeEdit->text().length() == 6;
    
    m_isFormValid = phoneValid && codeValid;
    m_loginButton->setEnabled(m_isFormValid);
}

bool LoginWindow::isValidPhone(const QString &phone)
{
    QRegularExpression regex("^1[3-9]\\d{9}$");
    return regex.match(phone).hasMatch();
}

void LoginWindow::showMessage(const QString &message, bool isError)
{
    m_messageLabel->setText(message);
    m_messageLabel->setObjectName(isError ? "ErrorLabel" : "SuccessLabel");
    m_messageLabel->style()->unpolish(m_messageLabel);
    m_messageLabel->style()->polish(m_messageLabel);
    m_messageLabel->show();
    
    // 3秒后自动隐藏
    QTimer::singleShot(3000, [this]() {
        m_messageLabel->hide();
    });
}


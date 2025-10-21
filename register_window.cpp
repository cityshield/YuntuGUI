#include "register_window.h"
#include <QtWidgets/QApplication>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QRegularExpression>
#include <QtCore/QDebug>

RegisterWindow::RegisterWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_centralWidget(nullptr)
    , m_codeTimer(new QTimer(this))
    , m_codeCountdown(60)
    , m_isCodeSent(false)
    , m_isFormValid(false)
    , m_isAgreementAccepted(false)
{
    // 设置窗口属性
    setFixedSize(900, 600);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
    setAttribute(Qt::WA_TranslucentBackground);
    
    setupUI();
    loadStyles();
    setupAnimations();
    
    // 连接信号槽
    connect(m_codeTimer, &QTimer::timeout, this, &RegisterWindow::updateCodeButtonText);
    connect(m_phoneEdit, &QLineEdit::textChanged, this, &RegisterWindow::onPhoneTextChanged);
    connect(m_codeEdit, &QLineEdit::textChanged, this, &RegisterWindow::onCodeTextChanged);
    connect(m_getCodeButton, &QPushButton::clicked, this, &RegisterWindow::onGetCodeClicked);
    connect(m_registerButton, &QPushButton::clicked, this, &RegisterWindow::onRegisterClicked);
    connect(m_agreementCheckBox, &QCheckBox::toggled, this, &RegisterWindow::onAgreementToggled);
    connect(m_switchLink, &QLabel::mousePressEvent, this, &RegisterWindow::onSwitchToLogin);
    connect(m_userAgreementLink, &QLabel::mousePressEvent, this, &RegisterWindow::onUserAgreementClicked);
    connect(m_privacyPolicyLink, &QLabel::mousePressEvent, this, &RegisterWindow::onPrivacyPolicyClicked);
}

RegisterWindow::~RegisterWindow()
{
}

void RegisterWindow::setupUI()
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

void RegisterWindow::setupLeftPanel()
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
    m_welcomeLabel = new QLabel("加入我们");
    m_welcomeLabel->setObjectName("WelcomeLabel");
    m_welcomeLabel->setAlignment(Qt::AlignCenter);
    
    // 描述文字
    m_descriptionLabel = new QLabel("创建您的账户\n开始您的精彩旅程");
    m_descriptionLabel->setObjectName("DescriptionLabel");
    m_descriptionLabel->setAlignment(Qt::AlignCenter);
    m_descriptionLabel->setWordWrap(true);
    
    // 装饰图形
    m_decorationLabel = new QLabel();
    m_decorationLabel->setMinimumHeight(200);
    m_decorationLabel->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #dcfce7, stop:1 #bbf7d0); border-radius: 12px;");
    
    m_leftLayout->addWidget(m_logoLabel);
    m_leftLayout->addWidget(m_welcomeLabel);
    m_leftLayout->addWidget(m_descriptionLabel);
    m_leftLayout->addStretch();
    m_leftLayout->addWidget(m_decorationLabel);
    m_leftLayout->addStretch();
}

void RegisterWindow::setupRightPanel()
{
    // 右侧表单面板
    m_rightPanel = new QWidget();
    m_rightPanel->setObjectName("RightPanel");
    m_rightPanel->setFixedWidth(500);
    
    m_rightLayout = new QVBoxLayout(m_rightPanel);
    m_rightLayout->setContentsMargins(0, 0, 0, 0);
    m_rightLayout->setSpacing(0);
    
    // 创建滚动区域
    m_scrollArea = new QScrollArea();
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_scrollArea->setFrameShape(QFrame::NoFrame);
    
    m_scrollContent = new QWidget();
    m_scrollLayout = new QVBoxLayout(m_scrollContent);
    m_scrollLayout->setContentsMargins(48, 40, 48, 40);
    m_scrollLayout->setSpacing(0);
    
    setupFormArea();
    setupAgreementArea();
    setupSwitchArea();
    
    m_scrollArea->setWidget(m_scrollContent);
    m_rightLayout->addWidget(m_scrollArea);
}

void RegisterWindow::setupFormArea()
{
    // 表单容器
    m_formContainer = new QWidget();
    m_formContainer->setObjectName("FormContainer");
    
    m_formLayout = new QVBoxLayout(m_formContainer);
    m_formLayout->setContentsMargins(0, 0, 0, 0);
    m_formLayout->setSpacing(16);
    
    // 标题
    m_titleFormLabel = new QLabel("注册");
    m_titleFormLabel->setObjectName("TitleLabel");
    
    m_subtitleLabel = new QLabel("输入手机号和验证码创建账户");
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
    
    // 添加到表单布局
    m_formLayout->addWidget(m_titleFormLabel);
    m_formLayout->addWidget(m_subtitleLabel);
    m_formLayout->addWidget(m_phoneInputGroup);
    m_formLayout->addWidget(m_codeInputGroup);
    
    m_scrollLayout->addWidget(m_formContainer);
}

void RegisterWindow::setupAgreementArea()
{
    // 用户协议区域
    m_agreementArea = new QWidget();
    m_agreementArea->setObjectName("AgreementArea");
    m_agreementLayout = new QHBoxLayout(m_agreementArea);
    m_agreementLayout->setContentsMargins(0, 16, 0, 16);
    m_agreementLayout->setSpacing(8);
    
    m_agreementCheckBox = new QCheckBox();
    m_agreementCheckBox->setObjectName("AgreementCheckBox");
    
    m_agreementText = new QLabel("我已阅读并同意");
    m_agreementText->setStyleSheet("color: #64748b; font-size: 14px;");
    
    m_userAgreementLink = new QLabel("《用户协议》");
    m_userAgreementLink->setObjectName("LinkLabel");
    m_userAgreementLink->setCursor(Qt::PointingHandCursor);
    
    m_andLabel = new QLabel("和");
    m_andLabel->setStyleSheet("color: #64748b; font-size: 14px;");
    
    m_privacyPolicyLink = new QLabel("《隐私政策》");
    m_privacyPolicyLink->setObjectName("LinkLabel");
    m_privacyPolicyLink->setCursor(Qt::PointingHandCursor);
    
    m_agreementLayout->addWidget(m_agreementCheckBox);
    m_agreementLayout->addWidget(m_agreementText);
    m_agreementLayout->addWidget(m_userAgreementLink);
    m_agreementLayout->addWidget(m_andLabel);
    m_agreementLayout->addWidget(m_privacyPolicyLink);
    m_agreementLayout->addStretch();
    
    // 注册按钮
    m_buttonGroup = new QWidget();
    m_buttonGroup->setObjectName("ButtonGroup");
    m_buttonLayout = new QVBoxLayout(m_buttonGroup);
    m_buttonLayout->setContentsMargins(0, 0, 0, 0);
    
    m_registerButton = new QPushButton("注册");
    m_registerButton->setObjectName("PrimaryButton");
    m_registerButton->setEnabled(false);
    
    m_buttonLayout->addWidget(m_registerButton);
    
    // 消息提示
    m_messageLabel = new QLabel();
    m_messageLabel->setObjectName("ErrorLabel");
    m_messageLabel->setAlignment(Qt::AlignCenter);
    m_messageLabel->hide();
    
    m_scrollLayout->addWidget(m_agreementArea);
    m_scrollLayout->addWidget(m_buttonGroup);
    m_scrollLayout->addWidget(m_messageLabel);
}

void RegisterWindow::setupSwitchArea()
{
    // 页面切换区域
    m_switchArea = new QWidget();
    m_switchArea->setObjectName("SwitchArea");
    m_switchLayout = new QHBoxLayout(m_switchArea);
    m_switchLayout->setContentsMargins(0, 24, 0, 0);
    
    m_switchText = new QLabel("已有账户？");
    m_switchText->setStyleSheet("color: #64748b; font-size: 14px;");
    
    m_switchLink = new QLabel("立即登录");
    m_switchLink->setObjectName("LinkLabel");
    m_switchLink->setCursor(Qt::PointingHandCursor);
    
    m_switchLayout->addStretch();
    m_switchLayout->addWidget(m_switchText);
    m_switchLayout->addWidget(m_switchLink);
    m_switchLayout->addStretch();
    
    m_scrollLayout->addWidget(m_switchArea);
    m_scrollLayout->addStretch();
}

void RegisterWindow::loadStyles()
{
    QFile file(":/styles/login_styles.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString styleSheet = stream.readAll();
        setStyleSheet(styleSheet);
    }
}

void RegisterWindow::setupAnimations()
{
    // 设置淡入淡出动画
    m_fadeAnimation = new QPropertyAnimation(m_messageLabel, "windowOpacity");
    m_fadeAnimation->setDuration(300);
    m_fadeAnimation->setEasingCurve(QEasingCurve::InOutQuad);
}

void RegisterWindow::onPhoneTextChanged()
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

void RegisterWindow::onCodeTextChanged()
{
    validateForm();
}

void RegisterWindow::onAgreementToggled()
{
    m_isAgreementAccepted = m_agreementCheckBox->isChecked();
    validateForm();
}

void RegisterWindow::onGetCodeClicked()
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

void RegisterWindow::onRegisterClicked()
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
    
    if (!m_isAgreementAccepted) {
        showMessage("请先同意用户协议和隐私政策", true);
        return;
    }
    
    // 模拟注册过程
    m_registerButton->setText("注册中...");
    m_registerButton->setEnabled(false);
    
    // 这里应该调用实际的注册 API
    QTimer::singleShot(2000, [this]() {
        showMessage("注册成功！", false);
        // 跳转到登录页面或主界面
        // emit registerSuccess();
    });
}

void RegisterWindow::onSwitchToLogin()
{
    // 切换到登录页面
    // emit switchToLogin();
}

void RegisterWindow::onUserAgreementClicked()
{
    // 打开用户协议页面
    showMessage("正在打开用户协议...", false);
}

void RegisterWindow::onPrivacyPolicyClicked()
{
    // 打开隐私政策页面
    showMessage("正在打开隐私政策...", false);
}

void RegisterWindow::updateCodeButtonText()
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

void RegisterWindow::validateForm()
{
    bool phoneValid = isValidPhone(m_phoneEdit->text());
    bool codeValid = m_codeEdit->text().length() == 6;
    
    m_isFormValid = phoneValid && codeValid && m_isAgreementAccepted;
    m_registerButton->setEnabled(m_isFormValid);
}

bool RegisterWindow::isValidPhone(const QString &phone)
{
    QRegularExpression regex("^1[3-9]\\d{9}$");
    return regex.match(phone).hasMatch();
}

void RegisterWindow::showMessage(const QString &message, bool isError)
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


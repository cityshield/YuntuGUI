#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QFrame>
#include <QtWidgets/QCheckBox>
#include <QtCore/QTimer>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QEasingCurve>
#include <QtGui/QPixmap>
#include <QtGui/QPainter>
#include <QtGui/QFont>

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void onLoginClicked();
    void onGetCodeClicked();
    void onWeChatLoginClicked();
    void onSwitchToRegister();
    void onPhoneTextChanged();
    void onCodeTextChanged();
    void updateCodeButtonText();

private:
    void setupUI();
    void setupLeftPanel();
    void setupRightPanel();
    void setupTitleBar();
    void setupFormArea();
    void setupWeChatArea();
    void setupSwitchArea();
    void loadStyles();
    void setupAnimations();
    void validateForm();
    bool isValidPhone(const QString &phone);
    void showMessage(const QString &message, bool isError = false);

    // UI 组件
    QWidget *m_centralWidget;
    QHBoxLayout *m_mainLayout;
    
    // 标题栏
    QWidget *m_titleBar;
    QHBoxLayout *m_titleLayout;
    QLabel *m_titleLabel;
    QPushButton *m_minimizeButton;
    QPushButton *m_closeButton;
    
    // 左侧面板
    QWidget *m_leftPanel;
    QVBoxLayout *m_leftLayout;
    QLabel *m_logoLabel;
    QLabel *m_welcomeLabel;
    QLabel *m_descriptionLabel;
    QLabel *m_decorationLabel;
    
    // 右侧面板
    QWidget *m_rightPanel;
    QVBoxLayout *m_rightLayout;
    
    // 表单区域
    QWidget *m_formContainer;
    QVBoxLayout *m_formLayout;
    QLabel *m_titleFormLabel;
    QLabel *m_subtitleLabel;
    
    // 手机号输入
    QWidget *m_phoneInputGroup;
    QVBoxLayout *m_phoneLayout;
    QLabel *m_phoneLabel;
    QLineEdit *m_phoneEdit;
    QLabel *m_phoneErrorLabel;
    
    // 验证码输入
    QWidget *m_codeInputGroup;
    QVBoxLayout *m_codeLayout;
    QHBoxLayout *m_codeInputLayout;
    QLabel *m_codeLabel;
    QLineEdit *m_codeEdit;
    QPushButton *m_getCodeButton;
    QLabel *m_codeErrorLabel;
    
    // 按钮组
    QWidget *m_buttonGroup;
    QVBoxLayout *m_buttonLayout;
    QPushButton *m_loginButton;
    
    // 分割线
    QWidget *m_dividerWidget;
    QHBoxLayout *m_dividerLayout;
    QFrame *m_dividerLine1;
    QLabel *m_dividerText;
    QFrame *m_dividerLine2;
    
    // 微信登录区域
    QWidget *m_wechatArea;
    QVBoxLayout *m_wechatLayout;
    QPushButton *m_wechatButton;
    QFrame *m_qrCodeFrame;
    QLabel *m_qrCodeLabel;
    QLabel *m_qrCodeText;
    
    // 页面切换区域
    QWidget *m_switchArea;
    QHBoxLayout *m_switchLayout;
    QLabel *m_switchText;
    QLabel *m_switchLink;
    
    // 消息提示
    QLabel *m_messageLabel;
    
    // 定时器和动画
    QTimer *m_codeTimer;
    int m_codeCountdown;
    QPropertyAnimation *m_fadeAnimation;
    
    // 状态标志
    bool m_isCodeSent;
    bool m_isFormValid;
};

#endif // LOGIN_WINDOW_H

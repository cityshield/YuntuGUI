#ifndef REGISTER_WINDOW_H
#define REGISTER_WINDOW_H

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
#include <QtWidgets/QScrollArea>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QEasingCurve>

class RegisterWindow : public QMainWindow
{
    Q_OBJECT

public:
    RegisterWindow(QWidget *parent = nullptr);
    ~RegisterWindow();

private slots:
    void onRegisterClicked();
    void onGetCodeClicked();
    void onSwitchToLogin();
    void onPhoneTextChanged();
    void onCodeTextChanged();
    void onAgreementToggled();
    void updateCodeButtonText();
    void onUserAgreementClicked();
    void onPrivacyPolicyClicked();

private:
    void setupUI();
    void setupLeftPanel();
    void setupRightPanel();
    void setupFormArea();
    void setupAgreementArea();
    void setupSwitchArea();
    void loadStyles();
    void setupAnimations();
    void validateForm();
    bool isValidPhone(const QString &phone);
    void showMessage(const QString &message, bool isError = false);

    // UI 组件
    QWidget *m_centralWidget;
    QHBoxLayout *m_mainLayout;
    
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
    QScrollArea *m_scrollArea;
    QWidget *m_scrollContent;
    QVBoxLayout *m_scrollLayout;
    
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
    
    // 用户协议区域
    QWidget *m_agreementArea;
    QHBoxLayout *m_agreementLayout;
    QCheckBox *m_agreementCheckBox;
    QLabel *m_agreementText;
    QLabel *m_userAgreementLink;
    QLabel *m_andLabel;
    QLabel *m_privacyPolicyLink;
    
    // 按钮组
    QWidget *m_buttonGroup;
    QVBoxLayout *m_buttonLayout;
    QPushButton *m_registerButton;
    
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
    bool m_isAgreementAccepted;
};

#endif // REGISTER_WINDOW_H

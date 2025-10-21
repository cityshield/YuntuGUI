#include <QtWidgets/QApplication>
#include <QtCore/QDir>
#include <QtCore/QStandardPaths>
#include <QtCore/QTextCodec>
#include <QtGui/QFont>
#include <QtGui/QFontDatabase>
#include "login_window.h"
#include "register_window.h"

class AuthManager : public QObject
{
    Q_OBJECT

public:
    AuthManager(QObject *parent = nullptr) : QObject(parent)
    {
        m_loginWindow = new LoginWindow();
        m_registerWindow = new RegisterWindow();
        
        // 连接页面切换信号
        connect(m_loginWindow, &LoginWindow::switchToRegister, this, &AuthManager::showRegister);
        connect(m_registerWindow, &RegisterWindow::switchToLogin, this, &AuthManager::showLogin);
        
        // 连接成功信号
        connect(m_loginWindow, &LoginWindow::loginSuccess, this, &AuthManager::onLoginSuccess);
        connect(m_registerWindow, &RegisterWindow::registerSuccess, this, &AuthManager::onRegisterSuccess);
    }
    
    ~AuthManager()
    {
        delete m_loginWindow;
        delete m_registerWindow;
    }
    
    void start()
    {
        showLogin();
    }

private slots:
    void showLogin()
    {
        m_registerWindow->hide();
        m_loginWindow->show();
        m_loginWindow->raise();
        m_loginWindow->activateWindow();
    }
    
    void showRegister()
    {
        m_loginWindow->hide();
        m_registerWindow->show();
        m_registerWindow->raise();
        m_registerWindow->activateWindow();
    }
    
    void onLoginSuccess()
    {
        // 登录成功，跳转到主界面
        m_loginWindow->hide();
        // 这里可以创建并显示主界面
        qDebug() << "登录成功，跳转到主界面";
    }
    
    void onRegisterSuccess()
    {
        // 注册成功，跳转到登录页面
        showLogin();
        qDebug() << "注册成功，请登录";
    }

private:
    LoginWindow *m_loginWindow;
    RegisterWindow *m_registerWindow;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Qt 6.9 中文编码支持
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    
    // 设置应用程序信息
    app.setApplicationName("MyApp");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("MyCompany");
    
    // Qt 6.9 高DPI支持
    QApplication::setHighDpiScaleFactorRoundingPolicy(
        Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    
    // 设置字体
    QFont font("Microsoft YaHei UI", 9);
    app.setFont(font);
    
    // 设置样式 (Qt 6.9 优化)
    app.setStyle("Fusion");
    
    // 创建认证管理器
    AuthManager authManager;
    authManager.start();
    
    return app.exec();
}

#include "main.moc"

#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H

#include <QWidget>
#include <QStackedWidget>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class Login_Window; }
QT_END_NAMESPACE

class Login_Window : public QWidget
{
    Q_OBJECT

public:
    explicit Login_Window(QWidget *parent = nullptr, QStackedWidget* stackedWidget = nullptr);
    ~Login_Window();

public slots:
    void onComenzarButtonClicked();

private:
    Ui::Login_Window *ui;
    QStackedWidget* stackedWidget;
};

#endif // LOGIN_WINDOW_H

#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H

#include <QWidget>
#include <QStackedWidget>
#include <QMainWindow>
#include <string>

#include "../../common/socket.h"
#include "../protocolo/protocoloCliente.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Login_Window; }
QT_END_NAMESPACE

class Login_Window : public QWidget
{
    Q_OBJECT

public:
    explicit Login_Window(QWidget *parent = nullptr, QStackedWidget* stackedWidget = nullptr, Socket* skt = nullptr);
    ~Login_Window();
    Socket* getSocket();
    Socket* skt;

public slots:
    void onComenzarButtonClicked();

private:
    Ui::Login_Window *ui;
    QStackedWidget* stackedWidget;
};

#endif // LOGIN_WINDOW_H

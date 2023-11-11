#include <QMessageBox>
#include <QString>

#include "login_window.h"
#include "ui/ui_login_window.h"
#include "mainwindow.h"

Login_Window::Login_Window(QWidget *parent, QStackedWidget* stackedWidget, Socket* skt) :
    QWidget(parent),
    ui(new Ui::Login_Window) {
    this->ui->setupUi(this);
    this->stackedWidget = stackedWidget;
    this->skt = skt;
    connect(ui->start, SIGNAL(clicked()), this, SLOT(onComenzarButtonClicked()));
}

Login_Window::~Login_Window() {
    delete this->ui;
}

void Login_Window::onComenzarButtonClicked() {

    QString serverText = ui->serverInput->text();
    QString portText = ui->portInput->text();

    if (serverText.isEmpty() || portText.isEmpty()) {
        QMessageBox::warning(this, "Error", "Por favor, complete ambos campos.");
        return;
    }

    std::string server = serverText.toStdString();
    std::string port = portText.toStdString();

    const char* serverChar = server.c_str();
    const char* portChar = port.c_str();

    this->skt = new Socket(serverChar, portChar);
    
    this->stackedWidget->setCurrentWidget(this->stackedWidget->widget(PANTALLA_LOBBY));
}

Socket* Login_Window::getSocket() {
    return this->skt;
}

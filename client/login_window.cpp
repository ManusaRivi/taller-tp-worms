#include <QMessageBox>
#include <QString>

#include "login_window.h"
#include "ui/ui_login_window.h"
#include "mainwindow.h"

Login_Window::Login_Window(QWidget *parent, QStackedWidget* stackedWidget) :
    QWidget(parent),
    ui(new Ui::Login_Window) {
    this->ui->setupUi(this);
    this->stackedWidget = stackedWidget;
    connect(ui->start, SIGNAL(clicked()), this, SLOT(onComenzarButtonClicked()));
}

Login_Window::~Login_Window() {
    delete this->ui;
}

void Login_Window::onComenzarButtonClicked() {

    //QString serverText = ui->serverInput->text();
    //QString portText = ui->portInput->text();

    //if (serverText.isEmpty() || portText.isEmpty()) {
    //    QMessageBox::warning(this, "Error", "Por favor, complete ambos campos.");
    //    return;
    //}

    //this->mainWindow->setServer(serverText.toStdString());
    //this->mainWindow->setPort(portText.toStdString());

    this->stackedWidget->setCurrentWidget(this->stackedWidget->widget(PANTALLA_LOBBY));
}

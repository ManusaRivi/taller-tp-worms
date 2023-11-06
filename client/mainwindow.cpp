#include "mainwindow.h"
#include "login_window.h"
#include "lobby_window.h"
#include "lista_espera.h"
#include "crear_partida.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    stackedWidget(new QStackedWidget(this)) {

    setCentralWidget(this->stackedWidget);

    this->ui1 = new Login_Window(parent, this->stackedWidget);
    this->ui2 = new Lobby_Window(parent, this->stackedWidget, this->ui1);
    this->ui3 = new Lista_Espera(parent, this->stackedWidget, this);
    this->ui4 = new Crear_Partida(parent, this->stackedWidget, this->ui1);

    this->stackedWidget->addWidget(this->ui1);
    this->stackedWidget->addWidget(this->ui2);
    this->stackedWidget->addWidget(this->ui3);
    this->stackedWidget->addWidget(this->ui4);
}

MainWindow::~MainWindow() {
    delete this->ui1;
    delete this->ui2;
    delete this->ui3;
    delete this->ui4;
}

const std::string MainWindow::getServer() {
    return this->serverInput;
}

const std::string MainWindow::getPort() {
    return this->portInput;
}

void MainWindow::setServer(const std::string& server) {
    this->serverInput = server;
}

void MainWindow::setPort(const std::string& port) {
    this->portInput = port;
}


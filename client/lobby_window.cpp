#include "lobby_window.h"
#include "ui/ui_lobby_window.h"
#include "mainwindow.h"

Lobby_Window::Lobby_Window(QWidget *parent, QStackedWidget* stackedWidget) :
    QWidget(parent),
    ui(new Ui::Lobby_Window) {
    this->ui->setupUi(this);
    this->stackedWidget = stackedWidget;
    connect(ui->crear, SIGNAL(clicked()), this, SLOT(onCrearButtonClicked()));
    connect(ui->listar, SIGNAL(clicked()), this, SLOT(onListarButtonClicked()));
    connect(ui->unir, SIGNAL(clicked()), this, SLOT(onUnirButtonClicked()));
}

Lobby_Window::~Lobby_Window() {
    delete this->ui;
}

void Lobby_Window::onCrearButtonClicked() {
    this->stackedWidget->setCurrentWidget(this->stackedWidget->widget(PANTALLA_CREAR));
}

void Lobby_Window::onListarButtonClicked() {
    this->stackedWidget->setCurrentWidget(this->stackedWidget->widget(PANTALLA_PINCIPAL));
}

void Lobby_Window::onUnirButtonClicked() {
    this->stackedWidget->setCurrentWidget(this->stackedWidget->widget(PANTALLA_ESPERA));
}

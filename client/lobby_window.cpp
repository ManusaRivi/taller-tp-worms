#include <QMessageBox>

#include "lobby_window.h"
#include "ui/ui_lobby_window.h"
#include "mainwindow.h"
#include "protocolo/protocoloCliente.h"
#include "../common/socket.h"

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
    if (!this->ui->listWidget->selectedItems().isEmpty()) {
        this->stackedWidget->setCurrentWidget(this->stackedWidget->widget(PANTALLA_CREAR));
    } else {
        QMessageBox::warning(this, "Advertencia", "Ningún elemento está seleccionado.", QMessageBox::Ok);
    }
}

void Lobby_Window::onListarButtonClicked() {
    //this->stackedWidget->setCurrentWidget(this->stackedWidget->widget(PANTALLA_PINCIPAL));
    const std::string server = "127.0.0.1";
    const std::string port = "8080";

    this->ui->listWidget->clear();

    Socket skt(server.data(), port.data());
    ClienteProtocolo protocol(skt);
    protocol.pedir_lista_partidas();
    std::map<uint32_t,std::string> maps = protocol.listar_partidas();
    //std::vector<std::string> maps = protocol.receiveMapsList();
    //std::vector<std::string> maps = {"mapa 1", "mapa 2", "mapa 3"};

    for (const auto& pair : maps) {
        QString mapQString = QString::fromStdString(pair.second); // Accede al valor (cadena)
        QListWidgetItem* item = new QListWidgetItem(mapQString);
        this->ui->listWidget->addItem(item);
    }
}

void Lobby_Window::onUnirButtonClicked() {
    if (!this->ui->listWidget->selectedItems().isEmpty()) {
        this->stackedWidget->setCurrentWidget(this->stackedWidget->widget(PANTALLA_ESPERA));
    } else {
        QMessageBox::warning(this, "Advertencia", "Ningún elemento está seleccionado.", QMessageBox::Ok);
    }
}

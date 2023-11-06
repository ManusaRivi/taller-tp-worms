#include <QMessageBox>

#include "crear_partida.h"
#include "ui/ui_crear_partida.h"
#include "mainwindow.h"
#include "protocolo/protocoloCliente.h"
#include "../common/socket.h"

Crear_Partida::Crear_Partida(QWidget *parent, QStackedWidget* stackedWidget) :
    QWidget(parent),
    ui(new Ui::Crear_Partida) {
    ui->setupUi(this);
    this->stackedWidget = stackedWidget;
    connect(ui->crear, SIGNAL(clicked()), this, SLOT(onCrearButtonClicked()));
}

Crear_Partida::~Crear_Partida() {
    delete ui;
}

void Crear_Partida::onCrearButtonClicked() {

    const std::string server = "127.0.0.1";
    const std::string port = "8080";

    if (!this->ui->lineEdit->text().trimmed().isEmpty()) {
        Socket skt(server.data(), port.data());
        ClienteProtocolo protocol(skt);

        protocol.crear_partida("mapa1.yml");

        this->stackedWidget->setCurrentWidget(this->stackedWidget->widget(PANTALLA_LOBBY));
    } else {
        QMessageBox::warning(this, "Advertencia", "Debe colocar un nombre.", QMessageBox::Ok);
    }
}

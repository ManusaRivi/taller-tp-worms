#include <QMessageBox>
#include <QString>
#include <string>

#include "crear_partida.h"
#include "ui/ui_crear_partida.h"
#include "mainwindow.h"
#include "protocolo/protocoloCliente.h"
#include "../common/socket.h"
#include "login_window.h"

Crear_Partida::Crear_Partida(QWidget *parent, QStackedWidget* stackedWidget, Login_Window* ui1) :
    QWidget(parent),
    ui(new Ui::Crear_Partida) {
    ui->setupUi(this);
    this->stackedWidget = stackedWidget;
    this->ui1 = ui1;
    connect(ui->crear, SIGNAL(clicked()), this, SLOT(onCrearButtonClicked()));
}

Crear_Partida::~Crear_Partida() {
    delete ui;
}

void Crear_Partida::onCrearButtonClicked() {

    if (!this->ui->lineEdit->text().trimmed().isEmpty()) {
        Socket skt(this->ui1->server.data(), this->ui1->port.data());
        ClienteProtocolo protocol(skt);

        QString nombreMapa = this->ui->lineEdit->text();

        // El segundo argumento no se usa
        protocol.crear_partida(nombreMapa.toStdString(),0);

        this->stackedWidget->setCurrentWidget(this->stackedWidget->widget(PANTALLA_LOBBY));
    } else {
        QMessageBox::warning(this, "Advertencia", "Debe colocar un nombre.", QMessageBox::Ok);
    }
}

#include <QMessageBox>
#include <QString>
#include <map>
#include <string>
#include <QAbstractButton>
#include <QAbstractItemView>

#include "crear_partida.h"
#include "ui/ui_crear_partida.h"
#include "mainwindow.h"

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

void Crear_Partida::listarMapas() {
    ClienteProtocolo protocol(*this->ui1->skt);
    //protocol.listar_partidas();
    std::map<uint32_t, std::string> maps = protocol.pedir_mapas();
    
    ui->comboBox->clear();

    for (const auto& pair : maps) {
        ui->comboBox->addItem(QString::fromStdString(pair.second));
    }
    ui->comboBox->showPopup();
}

void Crear_Partida::onCrearButtonClicked() {

    if (ui->comboBox->currentText().isEmpty() || ui->lineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Advertencia", "Por favor, selecciona un mapa y proporciona un nombre para la partida.", QMessageBox::Ok);
        return;
    }

    ClienteProtocolo protocol(*this->ui1->skt);
    QString nombreMapa = ui->comboBox->currentText();
    protocol.crear_partida(nombreMapa.toStdString(), 0);
    //std::map<uint32_t,std::string> partidas = protocol.pedir_lista_partidas();
    //protocol.unirse_partida("1");
    this->stackedWidget->setCurrentWidget(this->stackedWidget->widget(PANTALLA_ESPERA));
}

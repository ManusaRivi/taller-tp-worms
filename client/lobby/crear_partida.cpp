#include <QMessageBox>
#include <QString>
#include <map>
#include <string>
#include <QAbstractButton>
#include <QAbstractItemView>
#include <QtDebug>

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
        this->mapas.push_back(pair);
        ui->comboBox->addItem(QString::fromStdString(pair.second),QVariant(pair.first));
    }

    ui->comboBox->showPopup();
}

void Crear_Partida::onCrearButtonClicked() {

    if (ui->comboBox->currentText().isEmpty() || ui->lineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Advertencia", "Por favor, selecciona un mapa y proporciona un nombre para la partida.", QMessageBox::Ok);
        return;
    }
    uint8_t selectedIndex = ui->comboBox->currentIndex();

    if (selectedIndex >= 0 && selectedIndex < this->mapas.size()) {
        int selectedId = this->mapas[selectedIndex].first;
        QString selectedName = QString::fromStdString(this->mapas[selectedIndex].second);
        ClienteProtocolo protocol(*this->ui1->skt);
        // QString nombreMapa = ui->comboBox->currentText();
        protocol.crear_partida(ui->lineEdit->text().toStdString(), selectedId);

        // Now you can use selectedId and selectedName as needed
        qDebug() << "Selected ID: " << selectedId << ", Selected Name: " << ui->lineEdit->text();
    } else {
        qDebug() << "No item selected.";
    }


    //std::map<uint32_t,std::string> partidas = protocol.pedir_lista_partidas();
    //protocol.unirse_partida("1");
    this->stackedWidget->setCurrentWidget(this->stackedWidget->widget(PANTALLA_ESPERA));
}

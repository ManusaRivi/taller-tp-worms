#include "crear_partida.h"
#include "ui/ui_crear_partida.h"
#include "mainwindow.h"

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
    this->stackedWidget->setCurrentWidget(this->stackedWidget->widget(PANTALLA_LOBBY));
}

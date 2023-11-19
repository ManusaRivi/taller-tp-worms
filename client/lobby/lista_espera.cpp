#include "lista_espera.h"
#include "ui/ui_lista_espera.h"
#include "mainwindow.h"

Lista_Espera::Lista_Espera(QWidget *parent, QStackedWidget* stackedWidget, QMainWindow* mainWindow, Login_Window* ui1) :
    QWidget(parent),
    ui(new Ui::Lista_Espera) {
    ui->setupUi(this);
    this->stackedWidget = stackedWidget;
    this->mainWindow = mainWindow;
    this->ui1 = ui1;
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onComenzarButtonClicked()));
}

Lista_Espera::~Lista_Espera() {
    delete ui;
}

void Lista_Espera::onComenzarButtonClicked() {
    ClienteProtocolo protocol(*this->ui1->skt);
    protocol.empezar_partida();
    this->mainWindow->close();
}

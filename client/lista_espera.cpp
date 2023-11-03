#include "lista_espera.h"
#include "ui/ui_lista_espera.h"
#include "mainwindow.h"

Lista_Espera::Lista_Espera(QWidget *parent, QStackedWidget* stackedWidget, QMainWindow* mainWindow) :
    QWidget(parent),
    ui(new Ui::Lista_Espera) {
    ui->setupUi(this);
    this->stackedWidget = stackedWidget;
    this->mainWindow = mainWindow;
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onComenzarButtonClicked()));
}

Lista_Espera::~Lista_Espera() {
    delete ui;
}

void Lista_Espera::onComenzarButtonClicked() {
    //this->stackedWidget->setCurrentWidget(this->stackedWidget->widget(PANTALLA_LOBBY));
    this->mainWindow->close();
}

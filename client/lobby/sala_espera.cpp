#include "sala_espera.h"
#include "ui/ui_sala_espera.h"

Sala_Espera::Sala_Espera(QWidget *parent, QMainWindow* mainWindow, Login_Window* ui1) :
    QWidget(parent),
    ui(new Ui::Sala_Espera) {
    ui->setupUi(this);
    this->mainWindow = mainWindow;
    this->ui1 = ui1;
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onComenzarButtonClicked()));
}

Sala_Espera::~Sala_Espera() {
    delete ui;
}

void Sala_Espera::onComenzarButtonClicked() {

    //printf("Se unio a la partida, esperando comenzar");
    this->ui->label->setText("Esperando jugadores...");
    ClienteProtocolo protocol(*this->ui1->skt);
    // protocol.unirse_partida("1");
    while (protocol.recibir_comienzo_de_partida() == false) {
    }
    this->mainWindow->close();
}

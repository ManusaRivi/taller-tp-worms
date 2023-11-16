#include "sala_espera.h"
#include "ui/ui_sala_espera.h"

Sala_Espera::Sala_Espera(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sala_Espera)
{
    ui->setupUi(this);
}

Sala_Espera::~Sala_Espera()
{
    delete ui;
}

#ifndef SALA_ESPERA_H
#define SALA_ESPERA_H

#include <QWidget>

namespace Ui {
class Sala_Espera;
}

class Sala_Espera : public QWidget
{
    Q_OBJECT

public:
    explicit Sala_Espera(QWidget *parent = nullptr);
    ~Sala_Espera();

private:
    Ui::Sala_Espera *ui;
};

#endif // SALA_ESPERA_H

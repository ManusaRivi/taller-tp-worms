#ifndef SALA_ESPERA_H
#define SALA_ESPERA_H

#include <QWidget>
#include <QMainWindow>

#include "login_window.h"
#include "../protocolo/protocoloCliente.h"

namespace Ui {
class Sala_Espera;
}

class Sala_Espera : public QWidget
{
    Q_OBJECT

public:
    explicit Sala_Espera(QWidget *parent = nullptr, QMainWindow* mainWindow = nullptr, Login_Window* ui1 = nullptr);
    ~Sala_Espera();

public slots:
    void onComenzarButtonClicked();
    
private:
    Ui::Sala_Espera *ui;
    QMainWindow* mainWindow;
    Login_Window* ui1;
};

#endif // SALA_ESPERA_H

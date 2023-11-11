#ifndef LISTA_ESPERA_H
#define LISTA_ESPERA_H

#include <QWidget>
#include <QStackedWidget>
#include <QMainWindow>

#include "login_window.h"
#include "../protocolo/protocoloCliente.h"

namespace Ui {
class Lista_Espera;
}

class Lista_Espera : public QWidget
{
    Q_OBJECT

public:
    explicit Lista_Espera(QWidget *parent = nullptr, QStackedWidget* stackedWidget = nullptr, QMainWindow* mainWindow = nullptr, Login_Window* ui1 = nullptr);
    ~Lista_Espera();

public slots:
    void onComenzarButtonClicked();

private:
    Ui::Lista_Espera *ui;
    QStackedWidget* stackedWidget;
    QMainWindow* mainWindow;
    Login_Window* ui1;
};

#endif // LISTA_ESPERA_H
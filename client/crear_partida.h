#ifndef CREAR_PARTIDA_H
#define CREAR_PARTIDA_H

#include <QWidget>
#include <QStackedWidget>
#include <string>

#include "login_window.h"
#include "protocolo/protocoloCliente.h"

namespace Ui {
class Crear_Partida;
}

class Crear_Partida : public QWidget
{
    Q_OBJECT

public:
    explicit Crear_Partida(QWidget *parent = nullptr, QStackedWidget *stackedWidget = nullptr, Login_Window* ui1 = nullptr);
    ~Crear_Partida();
    void listarMapas();

public slots:
    void onCrearButtonClicked();

private:
    Ui::Crear_Partida *ui;
    QStackedWidget* stackedWidget;
    Login_Window* ui1;
};

#endif // CREAR_PARTIDA_H

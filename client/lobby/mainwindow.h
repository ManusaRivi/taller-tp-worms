#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <string>

#include "login_window.h"
#include "lobby_window.h"
#include "lista_espera.h"
#include "crear_partida.h"
#include "sala_espera.h"

#include "../../common/socket.h"

#define PANTALLA_PINCIPAL                       0
#define PANTALLA_LOBBY                          1
#define PANTALLA_ESPERA                         2
#define PANTALLA_CREAR                          3
#define PANTALLA_ESPERA_SIN_OPCION_A_COMENZAR   4

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, Socket* skt = nullptr);
    ~MainWindow();
    Socket* getSocket();

private:
    QStackedWidget* stackedWidget;

    Login_Window* ui1;
    Lobby_Window* ui2;
    Lista_Espera* ui3;
    Crear_Partida* ui4;
    Sala_Espera* ui5;
};
#endif // MAINWINDOW_H

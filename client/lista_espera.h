#ifndef LISTA_ESPERA_H
#define LISTA_ESPERA_H

#include <QWidget>
#include <QStackedWidget>
#include <QMainWindow>

namespace Ui {
class Lista_Espera;
}

class Lista_Espera : public QWidget
{
    Q_OBJECT

public:
    explicit Lista_Espera(QWidget *parent = nullptr, QStackedWidget* stackedWidget = nullptr, QMainWindow* mainWindow = nullptr);
    ~Lista_Espera();

public slots:
    void onComenzarButtonClicked();

private:
    Ui::Lista_Espera *ui;
    QStackedWidget* stackedWidget;
    QMainWindow* mainWindow;
};

#endif // LISTA_ESPERA_H

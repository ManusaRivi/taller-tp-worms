#ifndef CREAR_PARTIDA_H
#define CREAR_PARTIDA_H

#include <QWidget>
#include <QStackedWidget>

namespace Ui {
class Crear_Partida;
}

class Crear_Partida : public QWidget
{
    Q_OBJECT

public:
    explicit Crear_Partida(QWidget *parent = nullptr, QStackedWidget *stackedWidget = nullptr);
    ~Crear_Partida();

public slots:
    void onCrearButtonClicked();

private:
    Ui::Crear_Partida *ui;
    QStackedWidget* stackedWidget;
};

#endif // CREAR_PARTIDA_H

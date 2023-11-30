// mainwindow.h

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include <QString>
#include <QList>
#include <vector>
#include <QRectF>
#include <string>
#include <random>
#include <ctime>

#include "graphicsscene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void agregarGusano();
    void agregarViga();
    void agregarVigaLarga();
    void exportarMapa();
    void limpiarMapa();
    void cambiarFondo();
    void exitApplication();
    std::string generarNombreAleatorio();

private:
    Ui::MainWindow *ui;
    GraphicsScene* scene;
    QList<QString> backgrounds;
    int currentBackgroundIndex;
    std::vector<QGraphicsPixmapItem*> worms;
    std::vector<QGraphicsPixmapItem*> vigas;
    std::vector<float> angulos;
};

#endif // MAINWINDOW_H

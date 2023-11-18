#include "mainwindow.h"
#include "ui/ui_mainwindow.h"
#include "yaml-cpp/yaml.h"

#include <fstream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    this->backgrounds << ":/imagenes/Background.png" <<":/res/worm-removebg-preview.png" << ":/res/viga2-removebg-preview.png" << ":/res/viga_larga2-removebg-preview.png";
    this->currentBackgroundIndex = 0;

    this->scene = new GraphicsScene(this);
    this->scene->setBackgroundBrush(QBrush(QPixmap(this->backgrounds[this->currentBackgroundIndex])));
    this->ui->graphicsView->setScene(scene);

    QPixmap vigaCompleta(":/imagenes/Beam.png");
    QPixmap vigaMitad = vigaCompleta.copy(0, 0, vigaCompleta.width() / 2, vigaCompleta.height());
    vigaMitad = vigaMitad.scaled(64, 64, Qt::KeepAspectRatio);
    ui->viga->setIcon(QIcon(vigaMitad));

    connect(ui->worm, &QPushButton::clicked, this, &MainWindow::agregarGusano);
    connect(ui->viga, &QPushButton::clicked, this, &MainWindow::agregarViga);
    connect(ui->vigaLarga, &QPushButton::clicked, this, &MainWindow::agregarVigaLarga);
    connect(ui->exportar, &QPushButton::clicked, this, &MainWindow::exportarMapa);
    connect(ui->limpiar, &QPushButton::clicked, this, &MainWindow::limpiarMapa);
    connect(ui->cambiarFondo, &QPushButton::clicked, this, &MainWindow::cambiarFondo);
    connect(ui->exitApplication, &QPushButton::clicked, this, &MainWindow::exitApplication);
    connect(this, &MainWindow::destroyed, this, &MainWindow::exitApplication);
}

MainWindow::~MainWindow() {
    for (QGraphicsPixmapItem* worm : this->worms) {
        delete worm;
    }

    for (QGraphicsPixmapItem* viga : this->vigas) {
        delete viga;
    }

    this->worms.clear();
    this->vigas.clear();

    delete scene;
    delete ui;
}

void MainWindow::agregarGusano() {

    QGraphicsPixmapItem* worm = new QGraphicsPixmapItem(QPixmap(":/imagenes/worm-removebg-preview.png"));

    this->worms.push_back(worm);
    this->scene->addItem(worm);
    worm->setPos(0, 0);
}

void MainWindow::agregarViga() {

    QGraphicsPixmapItem* viga = new QGraphicsPixmapItem(QPixmap(":/imagenes/Beam.png"));

    QString rotacion = this->ui->lineEdit->text();

    viga->setRotation(rotacion.toFloat());
    viga->setPos(0, 0);

    qreal anchoOriginal = viga->boundingRect().width();
    qreal altoOriginal = viga->boundingRect().height();

    qreal anchoMitad = anchoOriginal / 2;

    QPixmap mitadVigaPixmap = QPixmap(":/imagenes/Beam.png").copy(0, 0, anchoMitad, altoOriginal);
    QGraphicsPixmapItem* mitadViga = new QGraphicsPixmapItem(mitadVigaPixmap);

    this->vigas.push_back(mitadViga);
    this->scene->addItem(mitadViga);

    delete viga;
}


void MainWindow::agregarVigaLarga() {

    QGraphicsPixmapItem* viga = new QGraphicsPixmapItem(QPixmap(":/imagenes/Beam.png"));

    QString rotacion = this->ui->lineEdit->text();

    this->vigas.push_back(viga);
    this->scene->addItem(viga);
    viga->setRotation(rotacion.toFloat());
    viga->setPos(0, 0);
}

void MainWindow::exportarMapa() {
    YAML::Emitter emitter;
    std::string nombre = "mapa";

    emitter << YAML::Key << "nombre" << YAML::Value << nombre;

    emitter << YAML::Key << "vigas" << YAML::Value << YAML::BeginSeq;
    for (QGraphicsPixmapItem* viga : this->vigas) {
        QPointF posicion = viga->scenePos();
        qreal angulo = obtenerAnguloInclinacion(viga);

        emitter << YAML::BeginMap;
        emitter << YAML::Key << "tipo" << YAML::Value << "larga";
        emitter << YAML::Key << "pos_x" << YAML::Value << posicion.x();
        emitter << YAML::Key << "pos_y" << YAML::Value << posicion.y();
        emitter << YAML::Key << "angulo" << YAML::Value << angulo;
        emitter << YAML::EndMap;
    }
    //emitter << YAML::EndSeq;

    emitter << YAML::Key << "gusanos" << YAML::Value << YAML::BeginSeq;
    for (QGraphicsPixmapItem* worm : this->worms) {
        QPointF posicion = worm->scenePos();

        emitter << YAML::BeginMap;
        emitter << YAML::Key << "pos_x" << YAML::Value << posicion.x();
        emitter << YAML::Key << "pos_y" << YAML::Value << posicion.y();
        emitter << YAML::Key << "direccion" << YAML::Value << 0;  // Dirección de ejemplo
        emitter << YAML::EndMap;
    }
    //emitter << YAML::EndSeq;

    std::ofstream file("server/mapas/mapa.yaml");
    file << emitter.c_str();
}


void MainWindow::limpiarMapa() {
    for (QGraphicsPixmapItem* worm : this->worms) {
        delete worm;
    }

    for (QGraphicsPixmapItem* viga : this->vigas) {
        delete viga;
    }

    this->worms.clear();
    this->vigas.clear();
}

void MainWindow::cambiarFondo() {
    this->currentBackgroundIndex = (this->currentBackgroundIndex + 1) % this->backgrounds.size();
    this->scene->setBackgroundBrush(QBrush(QPixmap(this->backgrounds[this->currentBackgroundIndex])));
}

qreal MainWindow::obtenerAnguloInclinacion(QGraphicsPixmapItem* item) {
    return item->rotation();
}

void MainWindow::exitApplication() {

    for (QGraphicsPixmapItem* worm : this->worms) {
        delete worm;
    }

    for (QGraphicsPixmapItem* viga : this->vigas) {
        delete viga;
    }

    this->worms.clear();
    this->vigas.clear();

    this->close();
}

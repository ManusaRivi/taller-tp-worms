#include "mainwindow.h"
#include "ui/ui_mainwindow.h"
#include "yaml-cpp/yaml.h"

#include <fstream>

#define OFFSET_CAMARA 500

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    this->backgrounds << ":/imagenes/Background.png" <<":/imagenes/Background2.png" << ":/imagenes/Background3.png" << ":/imagenes/Background4.png";
    this->currentBackgroundIndex = 0;

    this->scene = new GraphicsScene(this);
    this->scene->setBackgroundBrush(QBrush(QPixmap(this->backgrounds[this->currentBackgroundIndex])));
    
    this->ui->graphicsView->setScene(this->scene);

    QPixmap vigaCompleta(":/imagenes/Beam.png");
    QPixmap vigaMitad = vigaCompleta.copy(0, 0, vigaCompleta.width() / 2, vigaCompleta.height());
    vigaMitad = vigaMitad.scaled(64, 64, Qt::KeepAspectRatio);
    this->ui->viga->setIcon(QIcon(vigaMitad));

    connect(this->ui->worm, &QPushButton::clicked, this, &MainWindow::agregarGusano);
    connect(this->ui->viga, &QPushButton::clicked, this, &MainWindow::agregarViga);
    connect(this->ui->vigaLarga, &QPushButton::clicked, this, &MainWindow::agregarVigaLarga);
    connect(this->ui->exportar, &QPushButton::clicked, this, &MainWindow::exportarMapa);
    connect(this->ui->limpiar, &QPushButton::clicked, this, &MainWindow::limpiarMapa);
    connect(this->ui->cambiarFondo, &QPushButton::clicked, this, &MainWindow::cambiarFondo);
    connect(this->ui->exitApplication, &QPushButton::clicked, this, &MainWindow::exitApplication);
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

    delete this->scene;
    delete this->ui;
}

void MainWindow::agregarGusano() {

    QGraphicsPixmapItem* worm = new QGraphicsPixmapItem(QPixmap(":/imagenes/worm-removebg-preview.png"));

    this->worms.push_back(worm);
    this->scene->addItem(worm);
    worm->setPos(OFFSET_CAMARA, OFFSET_CAMARA);
}

void MainWindow::agregarViga() {
    QPixmap vigaPixmap(":/imagenes/Beam.png");

    QString rotacion = this->ui->lineEdit->text();
    qreal angulo = rotacion.toFloat();

    this->angulos.push_back(angulo);

    qreal anchoOriginal = vigaPixmap.width();
    qreal altoOriginal = vigaPixmap.height();

    qreal anchoMitad = anchoOriginal / 2;

    vigaPixmap = vigaPixmap.copy(0, 0, anchoMitad, altoOriginal);
    vigaPixmap = vigaPixmap.transformed(QTransform().rotate(angulo));

    QGraphicsPixmapItem* mitadViga = new QGraphicsPixmapItem(vigaPixmap);
    mitadViga->setPos(OFFSET_CAMARA, OFFSET_CAMARA);

    this->vigas.push_back(mitadViga);
    this->scene->addItem(mitadViga);
}


void MainWindow::agregarVigaLarga() {
    QPixmap vigaPixmap(":/imagenes/Beam.png");

    QString rotacion = this->ui->lineEdit->text();
    qreal angulo = rotacion.toFloat();

    this->angulos.push_back(angulo);

    vigaPixmap = vigaPixmap.transformed(QTransform().rotate(angulo));

    QGraphicsPixmapItem* viga = new QGraphicsPixmapItem(vigaPixmap);
    viga->setPos(OFFSET_CAMARA, OFFSET_CAMARA);

    this->vigas.push_back(viga);
    this->scene->addItem(viga);
}


std::string MainWindow::generarNombreAleatorio() {
    const std::string letras = "abcdefghijklmnopqrstuvwxyz";
    const int longitudNombre = 5;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, letras.size() - 1);

    std::string nombreAleatorio;

    for (int i = 0; i < longitudNombre; ++i) {
        nombreAleatorio += letras[dis(gen)];
    }

    return nombreAleatorio;
}

void MainWindow::exportarMapa() {
    QString nombre = this->ui->nombreMapa->text();
    std::string nombre_mapa = nombre.toStdString();

    if(nombre_mapa.empty()) {
        nombre_mapa = this->generarNombreAleatorio();
    }

    YAML::Emitter emitter;
    std::string tipo;
    float largo;
    float scale;
    float offset;

    emitter << YAML::BeginMap;
    emitter << YAML::Key << "nombre";
    emitter << YAML::Value << nombre_mapa;

    emitter << YAML::Key << "vigas";
    emitter << YAML::Value;
    emitter << YAML::BeginSeq;

    size_t i = 0;
    for (QGraphicsPixmapItem* viga : this->vigas) {

        QPointF posicion = viga->scenePos();
        QRectF boundingRect = viga->boundingRect();

        if(boundingRect.width() > 100 || boundingRect.height() > 100) {
            tipo = "larga";
            largo = 138;
            scale = 6;
            offset = 0;
        } else {
            tipo = "corta";
            largo = 69;
            scale = 3;
            offset = 0.375;
        }

        emitter << YAML::BeginMap;
        emitter << YAML::Key << "tipo" << YAML::Value << tipo;
        emitter << YAML::Key << "pos_x" << YAML::Value << (posicion.x() + largo/2) / largo * scale - offset;
        emitter << YAML::Key << "pos_y" << YAML::Value << abs(2 * OFFSET_CAMARA - posicion.y() + 138/2) / 20;
        emitter << YAML::Key << "angulo" << YAML::Value << this->angulos[i];
        emitter << YAML::EndMap;
        i++;
    }

    emitter << YAML::EndSeq;

    emitter << YAML::Key << "gusanos";
    emitter << YAML::Value;
    emitter << YAML::BeginSeq;

    for (QGraphicsPixmapItem* worm : this->worms) {
        QPointF posicion = worm->scenePos();
        QRectF boundingRect = worm->boundingRect();

        emitter << YAML::BeginMap;
        emitter << YAML::Key << "pos_x" << YAML::Value << abs((posicion.x() + boundingRect.width()/2)/138*6);
        emitter << YAML::Key << "pos_y" << YAML::Value << abs(2 * OFFSET_CAMARA - posicion.y() + boundingRect.height())/20;
        emitter << YAML::Key << "direccion" << YAML::Value << 0;
        emitter << YAML::EndMap;
    }

    emitter << YAML::EndSeq;
    emitter << YAML::EndMap;

    std::ofstream file(PROJECT_SOURCE_DIR "/server/mapas/" + nombre_mapa + ".yaml");
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

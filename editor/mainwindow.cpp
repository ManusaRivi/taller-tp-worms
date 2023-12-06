#include "mainwindow.h"
#include "ui/ui_mainwindow.h"
#include "yaml-cpp/yaml.h"

#include <fstream>
#include <QDir>

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

    QDir directory(PROJECT_SOURCE_DIR "/server/mapas/");
    QStringList fileList = directory.entryList(QDir::Files);
    this->ui->comboBox->addItems(fileList);

    connect(this->ui->worm, &QPushButton::clicked, this, &MainWindow::agregarGusano);
    connect(this->ui->viga, &QPushButton::clicked, this, &MainWindow::agregarViga);
    connect(this->ui->vigaLarga, &QPushButton::clicked, this, &MainWindow::agregarVigaLarga);
    connect(this->ui->exportar, &QPushButton::clicked, this, &MainWindow::exportarMapa);
    connect(this->ui->limpiar, &QPushButton::clicked, this, &MainWindow::limpiarMapa);
    connect(this->ui->cambiarFondo, &QPushButton::clicked, this, &MainWindow::cambiarFondo);
    connect(this->ui->importar, &QPushButton::clicked, this, &MainWindow::importarMapa);
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
    
    QRectF boundingRect = mitadViga->boundingRect();
    mitadViga->setPos(OFFSET_CAMARA - boundingRect.width()/2, OFFSET_CAMARA - boundingRect.height()/2);

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

    QRectF boundingRect = viga->boundingRect();
    viga->setPos(OFFSET_CAMARA - boundingRect.width()/2, OFFSET_CAMARA - boundingRect.height()/2);

    this->vigas.push_back(viga);
    this->scene->addItem(viga);
}


std::string MainWindow::generarNombreAleatorio() {

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int numeroAleatorio = std::rand() % 1000;

    std::string nombreMapa = "mapa" + std::to_string(numeroAleatorio);

    std::ostringstream ss;
    ss << std::setw(4) << std::setfill('0') << numeroAleatorio;

    return "mapa" + ss.str();
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

    std::string bg = (this->backgrounds[this->currentBackgroundIndex]).toStdString();
    int numero = 0;
    size_t inicioNumero = bg.find_first_of("0123456789");

    if (inicioNumero != std::string::npos) {

        size_t finNumero = bg.find_first_not_of("0123456789", inicioNumero);

        std::string numeroString = bg.substr(inicioNumero, finNumero - inicioNumero);

        numero = std::stoi(numeroString);
    }

    emitter << YAML::Key << "background";
    emitter << YAML::Value << numero;

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
        emitter << YAML::Key << "pos_x" << YAML::Value << (posicion.x() + boundingRect.width()/2) / largo * scale - offset;
        emitter << YAML::Key << "pos_y" << YAML::Value << abs(2 * OFFSET_CAMARA - posicion.y() - boundingRect.height()/2) / 23;
        
        float ang;

        if(180 - this->angulos[i] < 0) {
            ang = 360 - this->angulos[i];
        } else {
            ang = 180 - this->angulos[i];
        }

        emitter << YAML::Key << "angulo" << YAML::Value << ang;
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
        emitter << YAML::Key << "pos_y" << YAML::Value << abs(2 * OFFSET_CAMARA - posicion.y() - boundingRect.height()/2)/23;
        emitter << YAML::Key << "direccion" << YAML::Value << 0;
        emitter << YAML::EndMap;
    }

    emitter << YAML::EndSeq;
    emitter << YAML::EndMap;

    std::ofstream file(PROJECT_SOURCE_DIR "/server/mapas/" + nombre_mapa + ".yaml");
    file << emitter.c_str();
}

void MainWindow::importarMapa() {

    QString nombreArchivo = this->ui->comboBox->currentText();
    YAML::Node nodo = YAML::LoadFile(PROJECT_SOURCE_DIR "/server/mapas/" + nombreArchivo.toStdString());
    this->limpiarMapa();

    std::string nombreMapa = nodo["nombre"].as<std::string>();

    const YAML::Node& vigasNode = nodo["vigas"];
    for (const auto& vigaNode : vigasNode) {
        std::string tipo = vigaNode["tipo"].as<std::string>();
        float pos_x = vigaNode["pos_x"].as<float>();
        float pos_y = vigaNode["pos_y"].as<float>();
        float angulo = vigaNode["angulo"].as<float>();

        if (tipo == "larga") {
            this->agregarVigaLargaImportada(pos_x, pos_y, angulo);
        } else {
            this->agregarVigaImportada(pos_x, pos_y, angulo);
        }
    }
    const YAML::Node& gusanosNode = nodo["gusanos"];
    for (const auto& gusanoNode : gusanosNode) {
        float pos_x = gusanoNode["pos_x"].as<float>();
        float pos_y = gusanoNode["pos_y"].as<float>();
        float direccion = gusanoNode["direccion"].as<float>();
        this->agregarGusanoImportada(pos_x, pos_y, direccion);
    }
    this->ui->nombreMapa->setText(QString::fromStdString(nombreMapa));
}

void MainWindow::agregarVigaImportada(float pos_x, float pos_y, float angulo) {
    QPixmap vigaPixmap(":/imagenes/Beam.png");

    qreal anchoMitad = vigaPixmap.width() / 2;

    vigaPixmap = vigaPixmap.copy(0, 0, anchoMitad, vigaPixmap.height());
    vigaPixmap = vigaPixmap.transformed(QTransform().rotate(-angulo + 180));

    QGraphicsPixmapItem* mitadViga = new QGraphicsPixmapItem(vigaPixmap);

    QRectF boundingRect = mitadViga->boundingRect();

    mitadViga->setPos((pos_x + 0.375) * 69 / 3 - boundingRect.width()/2, -(23 * pos_y - 2 * OFFSET_CAMARA + boundingRect.height()/2));

    this->angulos.push_back(180 - angulo);
    this->vigas.push_back(mitadViga);
    this->scene->addItem(mitadViga);
}

void MainWindow::agregarVigaLargaImportada(float pos_x, float pos_y, float angulo) {
    QPixmap vigaPixmap(":/imagenes/Beam.png");
    vigaPixmap = vigaPixmap.transformed(QTransform().rotate(-angulo + 180));

    QGraphicsPixmapItem* viga = new QGraphicsPixmapItem(vigaPixmap);

    QRectF boundingRect = viga->boundingRect();

    viga->setPos(pos_x * 69 / 3 - boundingRect.width()/2, -(23 * pos_y - 2 * OFFSET_CAMARA + boundingRect.height()/2));

    this->angulos.push_back(180 - angulo);
    this->vigas.push_back(viga);
    this->scene->addItem(viga);
}

void MainWindow::agregarGusanoImportada(float pos_x, float pos_y, float direccion) {
    QGraphicsPixmapItem* worm = new QGraphicsPixmapItem(QPixmap(":/imagenes/worm-removebg-preview.png"));
    this->worms.push_back(worm);
    this->scene->addItem(worm);
    QRectF boundingRect = worm->boundingRect();
    worm->setPos(pos_x * 138 / 6 - boundingRect.width()/2, -(23 * pos_y - 2 * OFFSET_CAMARA + boundingRect.height()/2));
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

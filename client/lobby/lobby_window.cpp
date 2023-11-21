#include <QMessageBox>
#include <string>

#include "lobby_window.h"
#include "ui/ui_lobby_window.h"
#include "mainwindow.h"
#include <QtDebug>

Lobby_Window::Lobby_Window(QWidget *parent, QStackedWidget* stackedWidget, Login_Window* ui1, Crear_Partida* ui4) :
    QWidget(parent),
    ui(new Ui::Lobby_Window) {
    this->ui->setupUi(this);
    this->stackedWidget = stackedWidget;
    this->ui1 = ui1;
    this->ui4 = ui4;
    connect(ui->crear, SIGNAL(clicked()), this, SLOT(onCrearButtonClicked()));
    connect(ui->listar, SIGNAL(clicked()), this, SLOT(onListarButtonClicked()));
    connect(ui->unir, SIGNAL(clicked()), this, SLOT(onUnirButtonClicked()));
}

Lobby_Window::~Lobby_Window() {
    delete this->ui;
}

void Lobby_Window::onCrearButtonClicked() {
    this->ui4->listarMapas();
    this->stackedWidget->setCurrentWidget(this->stackedWidget->widget(PANTALLA_CREAR));
}

void Lobby_Window::onListarButtonClicked() {

    this->ui->listWidget->clear();

    ClienteProtocolo protocol(*this->ui1->skt);
    //protocol.pedir_lista_partidas();
    std::map<uint32_t,std::string> maps = protocol.pedir_lista_partidas();

    for (const auto& pair : maps) {
        QString mapQString = QString::fromStdString(pair.second);
        QListWidgetItem* item = new QListWidgetItem(mapQString);

            // Associate the ID with the item using QVariant
        QVariant idVariant(pair.first);
        item->setData(Qt::UserRole, idVariant);

        this->ui->listWidget->addItem(item);
    }
}

void Lobby_Window::onUnirButtonClicked() {
    if (!this->ui->listWidget->selectedItems().isEmpty()) {
        QListWidgetItem* selectedItem = this->ui->listWidget->currentItem();

        if (selectedItem) {
        // Retrieve the associated ID from the item's user role
            QVariant idVariant = selectedItem->data(Qt::UserRole);
            uint32_t selectedId = idVariant.toUInt();

            qDebug() << "Selected ID: " << selectedId;
            ClienteProtocolo protocol(*this->ui1->skt);
            protocol.unirse_partida(selectedId);
            this->stackedWidget->setCurrentWidget(this->stackedWidget->widget(PANTALLA_ESPERA_SIN_OPCION_A_COMENZAR));
        } else {
            QMessageBox::warning(this, "Advertencia", "Ningún elemento está seleccionado.", QMessageBox::Ok);
        }
    }
}
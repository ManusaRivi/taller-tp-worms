#include <QMessageBox>

#include "mainwindow.h"
#include "ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->start, SIGNAL(clicked()), this, SLOT(onComenzarButtonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onComenzarButtonClicked() {
    QString serverText = ui->serverInput->text();
    QString portText = ui->portInput->text();

    // Validar los datos como lo desees, por ejemplo, verificar que no estén vacíos.
    if (serverText.isEmpty() || portText.isEmpty()) {
        QMessageBox::warning(this, "Error", "Por favor, complete ambos campos.");
        return;
    }

    this->serverInput = serverText.toStdString();
    this->portInput = portText.toStdString();

    MainWindow::close();
}

std::string MainWindow::getServer() const {
    return this->serverInput;
}

std::string MainWindow::getPort() const {
    return this->portInput;
}

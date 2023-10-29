#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    std::string getServer() const;
    std::string getPort() const;

public slots:
    void onComenzarButtonClicked();

private:
    Ui::MainWindow *ui;
    std::string serverInput;
    std::string portInput;
};
#endif // MAINWINDOW_H

#ifndef LOBBY_WINDOW_H
#define LOBBY_WINDOW_H

#include <QWidget>
#include <QStackedWidget>

namespace Ui {
class Lobby_Window;
}

class Lobby_Window : public QWidget
{
    Q_OBJECT

public:
    explicit Lobby_Window(QWidget *parent = nullptr, QStackedWidget* stackedWidget = nullptr);
    ~Lobby_Window();

public slots:
    void onCrearButtonClicked();
    void onListarButtonClicked();
    void onUnirButtonClicked();

private:
    Ui::Lobby_Window *ui;
    QStackedWidget* stackedWidget;
};

#endif // LOBBY_WINDOW_H

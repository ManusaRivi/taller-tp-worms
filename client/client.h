#ifndef CLIENT_H
#define CLIENT_H

#include "menu.h"
#include "game.h"

class Client {
    private:
    Menu menu;

    public:
    Client();

    int iniciar();
};

#endif
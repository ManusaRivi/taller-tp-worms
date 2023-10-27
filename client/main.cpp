//#include <QApplication>
//#include "pocsdl.h"
#include "client.h"

int main(int argc, char* argv[]) {
    //SDLPoc poc;
    //return poc.run();
    Client client(argc, argv);
    client.iniciar();
}
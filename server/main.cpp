#include "poc.h"
#include "threads/threadAceptador.h"

int main(int argc, char* argv[]) {

    const char* name = "8080";
    Aceptador skt(name);
    skt.start();
    Box2dPoC poc;
    poc.run();
    skt.join();
    return 0;
}
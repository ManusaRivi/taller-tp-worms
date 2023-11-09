#include "client.h"
#include "game.h"
#include "login.h"
#include "pocsdl.h"


Client::Client(int argc, char** argv) : skt(nullptr), login(argc, argv, this->skt) {}

Client::~Client() {
    delete this->skt;
}

int Client::iniciar() {

    try {
        this->login.start();

        //const std::string server = "127.0.0.1";
        //const std::string port = "8080";

        Queue<Mensaje> queue_comandos; //TODO: Cambiar a Unique ptr
        Queue<Mensaje> queue_snapshots;

        //Socket skt(server.data(),port.data());

        crear_partida();
        containerThreads container(*this->skt, queue_snapshots, queue_comandos);

        //Protocolo prot(server, port);
        container.start();
        Game game(queue_snapshots,queue_comandos);
        game.run();
        container.join();
        return 0;
        // SDLPoc poc(queue_snapshots,queue_comandos);
        // return poc.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
	    return 1;
    }

}


void Client::crear_partida(){
    ClienteProtocolo ptcl(*this->skt);
    bool se_empieza_partida = false;
    
    while (!se_empieza_partida){
        std::string argumento, comando;
        std::cin >> comando;
        if (comando == "Exit") {
            break;
        }

        if(comando == "crear"){
            std::getline(std::cin, argumento);
            ptcl.crear_partida(argumento);
        }

        if(comando == "empezar"){
            ptcl.empezar_partida();
            Mensaje msg = ptcl.recibir_snapshot();
            if (msg.tipo_comando == PARTIDA_COMENZO){
                return;
            }
        }
        
        if(comando == "listar"){
            ptcl.pedir_lista_partidas();
            Mensaje partidas = ptcl.recibir_snapshot();
            if(partidas.tipo_comando == COMANDO::CMD_LISTAR_PARTIDAS){
                imprimir_partidas_disponibles(partidas.lista_partidas);
            }
        }

        if (comando == "unirse"){
            std::getline(std::cin, argumento);
            ptcl.unirse_partida(argumento);
            Mensaje msg = ptcl.recibir_snapshot();
            if(msg.tipo_comando == PARTIDA_COMENZO){
                return;
            }
        }




    }
}

void Client::imprimir_partidas_disponibles(std::map<uint32_t,std::string> partidas){
     for (auto i = partidas.begin(); i != partidas.end(); i++){
        uint32_t id = i->first;
        
        std::string nombre = i->second;

        std::cout <<" La partida " << unsigned(id) << " Con nombre " << nombre << std::endl;
        
    }
}
#include "client.h"


Client::Client(int argc, char** argv) : login(argc, argv) {}

int Client::iniciar() {

    try {
        //this->login.start();

        //const std::string server = this->login.getServer();
        //const std::string port = this->login.getPort();

        const std::string server = "127.0.0.1";
        const std::string port = "1560";

        Queue<std::shared_ptr<MensajeCliente>> queue_comandos; //TODO: Cambiar a Unique ptr
        Queue<std::shared_ptr<MensajeCliente>> queue_snapshots;

        Socket skt(server.data(),port.data());

        crear_partida(skt);
        printf("asdadasd");
        containerThreads container(skt,queue_snapshots,queue_comandos);

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


void Client::crear_partida(Socket &skt){
    ClienteProtocolo ptcl(skt);
    bool se_empieza_partida = false;
    
    while (!se_empieza_partida){
        std::string argumento, comando;
        std::cin >> comando;
        if (comando == "Exit") {
            break;
        }

        if(comando == "crear"){
            std::getline(std::cin, argumento);
            ptcl.crear_partida(argumento,0);
        }

        if(comando == "empezar"){

            ptcl.empezar_partida();
            std::shared_ptr<MensajeCliente> msg = ptcl.recibir_snapshot();
            if (msg->tipo_comando == PARTIDA_COMENZO){
                printf("Se recibe comando de que la partida empezo\n");
                return;
            }
        }
        
        if(comando == "listar"){
            imprimir_partidas_disponibles(ptcl.pedir_lista_partidas());
        }

        if (comando == "unirse"){
            std::getline(std::cin, argumento);
            ptcl.unirse_partida(argumento);
            std::shared_ptr<MensajeCliente> msg = ptcl.recibir_snapshot();
            if(msg->tipo_comando == PARTIDA_COMENZO){
                return;
            }
        }

        if(comando == "mapas"){
            std::map<uint32_t,std::string> mapas = ptcl.pedir_mapas();
            imprimir_partidas_disponibles(mapas);
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
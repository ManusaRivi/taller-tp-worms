#include "protocolo.h"


Protocolo::Protocolo(Socket& skt_):skt(skt_){

}

void Protocolo::enviar_1_byte(uint8_t num){
    bool was_closed = false;
    skt.sendall(&num,SIZE_UNO,&was_closed);
    if(was_closed) throw ClosedSocket();
}

void Protocolo::enviar_2_byte(uint16_t num){
    bool was_closed = false;
    // uint16_t transf = htons(num);
    std::vector<uint8_t> buf(2,0);
    memcpy(buf.data(),&num,2);
    skt.sendall(buf.data(),2,&was_closed);
    if(was_closed) throw ClosedSocket();
}

std::string Protocolo::recibir_string(){
    bool was_closed = false;
    uint16_t len_string;
    skt.recvall(&len_string,SIZE_DOS,&was_closed);
    if(was_closed) throw ClosedSocket();
    uint16_t len = ntohs(len_string);
    std::vector<uint8_t> str(len,0);
    skt.recvall(str.data(),len,&was_closed);
    std::string mensaje(str.begin(), str.end());
    return mensaje;
}

void Protocolo::enviar_string(std::string nombre){
    bool was_closed = false;
    uint16_t len_name = nombre.length();
    uint16_t transform = htons(len_name);
    enviar_2_byte(transform);
    skt.sendall(nombre.data(),len_name,&was_closed);
    if(was_closed) throw ClosedSocket();
}

void Protocolo::enviar_4_bytes(uint32_t id){
    bool was_closed = false;
    uint32_t len_tf = htonl(id);
    std::vector<uint32_t> buf(4,0);
    memcpy(buf.data(),&len_tf,4);
    skt.sendall(buf.data(),4,&was_closed);
    if(was_closed) throw ClosedSocket();
}

uint32_t Protocolo::recibir_4_bytes(){
    bool was_closed = false;
    std::vector<uint8_t> buf(4,0);
    skt.recvall(buf.data(),4, &was_closed);
    if(was_closed) throw ClosedSocket();
    uint32_t num;
    memcpy(&num,buf.data(),4);
    num = ntohl(num);
    return num;
}

uint16_t Protocolo::recibir_2_bytes(){
    bool was_closed = false;
    std::vector<uint8_t> buf(2,0);
    skt.recvall(buf.data(),2, &was_closed);
    if(was_closed) throw ClosedSocket();
    uint16_t num;
    memcpy(&num,buf.data(),2);
    //num = ntohs(num);
    return num;
}

uint8_t Protocolo::recibir_1_byte(){
    bool was_closed = false;
    std::vector<uint8_t> buf(1,0);
    skt.recvall(buf.data(),1, &was_closed);
    if(was_closed) throw ClosedSocket();
    uint16_t num;
    memcpy(&num,buf.data(),1);
    //num = ntohs(num);
    return num;
}

void Protocolo::enviar_4_bytes_float(float num){
    std::vector<uint8_t> buf(4,0);
    uint32_t numero = num*100;
    //std::cout << "Se manda por socket un float de " << numero << std::endl;
    enviar_4_bytes(numero);
}

float Protocolo::recibir_4_bytes_float(){
    uint32_t num = recibir_4_bytes();
    float mero = num;
    mero = mero/100;
    return mero;

}
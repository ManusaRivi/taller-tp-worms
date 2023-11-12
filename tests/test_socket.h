#ifndef TESTCLASS
#define TESTCLASS
#include <arpa/inet.h>
#include <vector>
#include <string.h>
#include <sstream>
#include <stdio.h>

class Socket{

    public:
    std::vector<char> vector;

    public:
    Socket();

    int sendall(const void *data,
        unsigned int sz,
        bool *was_closed);

    int recvall(void *data,
        unsigned int sz,
        bool *was_closed);

};

#endif
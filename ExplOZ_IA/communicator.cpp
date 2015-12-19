#include "communicator.h"

Communicator::Communicator(quint16 port)
{
    this->ip = "127.0.0.1";
    this->port = port;
}
Communicator::Communicator(QString ip, quint16 port){
    this->ip = ip;
    this->port = port;
}

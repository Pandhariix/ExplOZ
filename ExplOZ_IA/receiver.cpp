#include "receiver.h"

Receiver::Receiver(QString ip, quint16 port) : Communicator(ip, port)
{

}

void Receiver::start(){
    socket.connectToHost(ip, port);

    connect(&socket, SIGNAL(readyRead()), this, SLOT(extract()));
}

void Receiver::extract(){
    //TODO
}

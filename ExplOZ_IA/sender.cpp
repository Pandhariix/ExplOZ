#include "sender.h"

Sender::Sender(quint16 port) : Communicator(port)
{

}
Sender::Sender(QString ip, quint16 port) : Communicator(ip, port)
{

}

void Sender::send()
{
    this->socket.write(this->data);
}

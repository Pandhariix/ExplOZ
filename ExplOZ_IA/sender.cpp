#include "sender.h"
#include <iostream>

Sender::Sender(quint16 port) : Communicator(port)
{
    this->timer = new QTimer();
}
Sender::Sender(QString ip, quint16 port) : Communicator(ip, port)
{
    this->timer = new QTimer();
}

void Sender::start()
{
    connect(this->timer, SIGNAL(timeout()), this, SLOT(send()));

    this->socket.connectToHost(this->ip, this->port);
    this->timer->start(50);
}

void Sender::send()
{
    this->socket.write(this->data);
}

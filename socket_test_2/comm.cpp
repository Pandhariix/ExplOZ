#include "comm.h"
#include <iostream>
#include <QThread>
#include <QTimer>

Comm::Comm(QObject *parent) : QObject(parent)
{
    socket_moteur = new QTcpSocket();
    socket_capteur = new QTcpSocket();

    socket_capteur->connectToHost("127.0.0.1", 3332);

    connect(socket_capteur, SIGNAL(readyRead()), this, SLOT(detection()));

    socket_moteur->connectToHost("127.0.0.1", 3331);

    data = new QByteArray();

    data->append("NAIO01");
    data->append(1);
    data->append((char)0);
    data->append((char)0);
    data->append((char)0);
    data->append((char)2);
    data->append((char)127);
    data->append((char)127);
    data->append((char)0);
    data->append((char)0);
    data->append((char)0);
    data->append((char)0);

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(50);

    connect()
}

void Comm::detection(){
    std::cout << (std::string)((socket_capteur->readLine()).toHex()) << std::endl;
}

void Comm::update(){
    socket_moteur->write(*data);
    std::cout << "Done" << std::endl;
}

Comm::onQuit(){
    if(socket_moteur->isOpen())
        socket_moteur->disconnectFromHost();
    if(socket_capteur->isOpen())
        socket_capteur->disconnectFromHost();

    socket_capteur->deleteLater();
    socket_moteur->deleteLater();

    delete data;

    delete timer;
}

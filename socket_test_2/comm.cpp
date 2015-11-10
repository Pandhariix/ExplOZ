#include "comm.h"
#include <iostream>
#include <QTimer>

Comm::Comm(QObject *parent) : QObject(parent)
{
    socket_moteur = new QTcpSocket();
    socket_capteur = new QTcpSocket();

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
}

void Comm::run(){
    socket_capteur->connectToHost("127.0.0.1", 3339);

    connect(socket_capteur, SIGNAL(readyRead()), this, SLOT(detection()));
    connect(socket_capteur, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleSocketError()));

    socket_moteur->connectToHost("127.0.0.1", 3331);

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(50);
}

void Comm::detection(){
    qDebug() << (socket_capteur->readLine()).toHex();
}

void Comm::update(){
    if(socket_moteur->state() == QAbstractSocket::ConnectedState){
        socket_moteur->write(*data);

        qDebug() << "Data sent : " << data;
    }
}

void Comm::handleSocketError(){
    qDebug() << socket_capteur->errorString();
}

Comm::~Comm(){
    socket_capteur->close();
    socket_capteur->waitForDisconnected(1000);
    delete socket_capteur;

    socket_moteur->close();
    socket_moteur->waitForDisconnected(1000);
    delete socket_moteur;

    delete data;
}

#include "com.h"
#include<QTcpSocket>
#include<iostream>
#include<QString>
#include <windows.h>

Com::Com(QObject *parent) :
    QObject(parent)
{
    socket=new QTcpSocket();

    //this->trame_lidar = new QByteArray();

    connect(socket,SIGNAL(readyRead()),this,SLOT(lireDonnees()));
    socket->connectToHost("127.0.0.1",3337);

}

void Com::lireDonnees(void)
{
    Sleep(5000);
    qDebug(socket->readAll().toHex());
    qDebug("lol");
}

#include "receiver.h"

#include <iostream>
#include <string>

Receiver::Receiver(QString ip, quint16 port, QElapsedTimer* appTime) : Communicator(ip, port){
    unusedPostdataSize = 0;
    unusedPredataSize = 0;

    this->appTime = appTime;
}

void Receiver::extract(){    
    if(eMode == START){
        if(socket.bytesAvailable() < 1)
            return;

        data = socket.read(1);
        //qDebug() << (QString)data;

        if(data == "N")
            eMode = CONFIRMATION;
    }

    if(eMode == CONFIRMATION){
        if(socket.bytesAvailable() < 5)
            return;

        data = socket.read(5);
        //qDebug() << (QString)data;

        if(data == "AIO01")
            eMode = ID;
        else{
            eMode = START;
            //qDebug() << "Nope.";
        }
    }

    if(eMode == ID){
        if(socket.bytesAvailable() < 1)
            return;

        QDataStream ds(socket.read(1));
        quint8 id;

        ds >> id;

        //qDebug() << "Target ID : " << id;

        eMode = SIZE;
    }

    if(eMode == SIZE){
        if(socket.bytesAvailable() < 4)
            return;

        QDataStream ds(socket.read(4));

        ds >> dataSize;

        //qDebug() << "Data block size : " << dataSize;

        eMode = UNUSED_PREDATA;
    }

    if(eMode == UNUSED_PREDATA){
        if(socket.bytesAvailable() < unusedPredataSize)
            return;

        socket.read(unusedPredataSize);

        eMode = DATA;
    }

    if(eMode == DATA){
        if(socket.bytesAvailable() < dataSize - unusedPostdataSize - unusedPredataSize)
            return;

        extractData();

        eMode = UNUSED_POSTDATA;
    }

    if(eMode == UNUSED_POSTDATA){
        if(socket.bytesAvailable() < unusedPredataSize)
            return;

        socket.read(unusedPostdataSize);

        eMode = CRC;
    }

    if(eMode == CRC){
        if(socket.bytesAvailable() < 4)
            return;

        //socket.read(4);
        socket.readAll();

        eMode = START;

        lastRecTime = appTime->elapsed();

        //qDebug() << "Received at : " << lastRecTime;
    }
}

void Receiver::start(){
    socket.connectToHost(ip, port);

    eMode = START;

    connect(&socket, SIGNAL(readyRead()), this, SLOT(extract()));
}

quint64 Receiver::getLastRecTime(){
    return lastRecTime;
}


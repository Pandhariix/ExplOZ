#include "receiver.h"

Receiver::Receiver(QString ip, quint16 port) : Communicator(ip, port)
{
    unusedPostdataSize = 0;
    unusedPredataSize = 0;
}

void Receiver::start(){
    socket.connectToHost(ip, port);

    eMode = START;

    connect(&socket, SIGNAL(readyRead()), this, SLOT(extract()));
}

void Receiver::extract(){
    if(eMode == START){
        if(socket.bytesAvailable() < 1)
            return;
        if((socket.read(1) == "N"))
            eMode = CONFIRMATION;
    }

    if(eMode == CONFIRMATION){
        if(socket.bytesAvailable() < 5)
            return;

        if(socket.read(5) == "AIO01")
            eMode = ID;
        else
            eMode = START;
    }

    if(eMode == ID){
        if(socket.bytesAvailable() < 1)
            return;

        qDebug() << "Target ID : " + socket.read(1);

        eMode = SIZE;
    }

    if(eMode == SIZE){
        if(socket.bytesAvailable() < 4)
            return;

        dataSize = (socket.read(4)).toLong();

        qDebug() << "Data block size : " + dataSize;

        eMode = UNUSED_PREDATA;
    }

    if(eMode == UNUSED_PREDATA){
        if(socket.bytesAvailable() < unusedPredataSize)
            return;

        socket.read(unusedPredataSize);

        eMode = DATA;
    }

    if(eMode == DATA){
        extractData();
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

        socket.read(4);

        eMode = START;
    }
}

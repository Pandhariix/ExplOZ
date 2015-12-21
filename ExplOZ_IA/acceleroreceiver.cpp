#include "acceleroreceiver.h"

AcceleroReceiver::AcceleroReceiver(QString ip, quint16 port) : Receiver(ip, port)
{
    unusedPostdataSize = 0;
    unusedPredataSize = 0;
}

void AcceleroReceiver::extractData(){
    QDataStream ds(socket.read(dataSize));

    ds >> accX;
    ds >> accY;
    ds >> accZ;

    qDebug() << "AccX : " << accX << " ; AccY : " << accY << " ; AccZ : " << accZ;
}

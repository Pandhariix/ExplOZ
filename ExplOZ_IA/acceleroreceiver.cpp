#include "acceleroreceiver.h"

AcceleroReceiver::AcceleroReceiver(QString ip, quint16 port, QElapsedTimer* appTime) : Receiver(ip, port, appTime)
{
    unusedPostdataSize = 0;
    unusedPredataSize = 0;
}

void AcceleroReceiver::extractData(){
    QDataStream ds(socket.read(dataSize));

    ds >> accX;
    ds >> accY;
    ds >> accZ;

    //qDebug() << "AccX : " << accX << " ; AccY : " << accY << " ; AccZ : " << accZ;
}

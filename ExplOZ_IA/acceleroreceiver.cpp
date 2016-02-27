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
    angleZ=angleZ+accZ*(appTime->elapsed()-dernierAcquisitionTemps)/1000;

    //qDebug() << " dern acq " <<dernierAcquisitionTemps;
    dernierAcquisitionTemps=appTime->elapsed();

    //qDebug() << " AccZ : " << accZ << " AngleZ : " << angleZ;
    //socket.readAll();
}


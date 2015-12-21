#include "lidarreceiver.h"

LidarReceiver::LidarReceiver(QString ip, quint16 port) : Receiver(ip, port)
{
    unusedPredataSize = 46 * 2;
    unusedPostdataSize = 45 * 2 + 271;
}

void LidarReceiver::extractData(){
    data = socket.read(dataSize - unusedPostdataSize - unusedPredataSize);

    QDataStream ds(data);

    for (uint i = 0 ; i < (dataSize - unusedPostdataSize - unusedPredataSize)/2 ; i++){
        ds >> distance[i];

        qDebug() << "distance[" << i << "] = " << distance[i];
    }
}

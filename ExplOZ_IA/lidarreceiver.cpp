#include "lidarreceiver.h"

LidarReceiver::LidarReceiver(QString ip, quint16 port, QElapsedTimer* appTime) : Receiver(ip, port, appTime)
{
    unusedPredataSize = 46 * 2;
    unusedPostdataSize = 45 * 2 + 271;
}

void LidarReceiver::extractData(){
    data = socket.read(dataSize - unusedPostdataSize - unusedPredataSize);

    QDataStream ds(data);

    for (uint i = 0 ; i < (dataSize - unusedPostdataSize - unusedPredataSize)/2 ; i++){
        ds >> distance[i];

        //qDebug() << "distance[" << i << "] = " << distance[i];
    }
}

void LidarReceiver::getDistance(quint16* dist){
    for (int i = 0 ; i < 180 ; i++)
        dist[i] = distance[i];
}

void LidarReceiver::getCartesianLidarMap(QVector<QPair<double,double> > &cartesianLidarMap)
{
    cartesianLidarMap.clear();

    for(int i=0;i<181;i++)
    {
        if(distance[i]!=4000)
        {
            cartesianLidarMap.append(qMakePair(distance[i]*cos(i*PI/180.0),distance[i]*sin(i*PI/180.0)));
        }
    }
}

#ifndef LIDARRECEIVER_H
#define LIDARRECEIVER_H

#define PI 3.14159265

#include "receiver.h"
#include <math.h>

class LidarReceiver : public Receiver
{
public:
    LidarReceiver(QString ip, quint16 port, QElapsedTimer *appTime);

    void getDistance(quint16* dist);
    void getCartesianLidarMap(QVector<QPair<double,double> > &cartesianLidarMap);

private:
    void extractData();

    quint16 distance[181];
};

#endif // LIDARRECEIVER_H

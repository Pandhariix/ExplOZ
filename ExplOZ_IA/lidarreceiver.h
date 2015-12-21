#ifndef LIDARRECEIVER_H
#define LIDARRECEIVER_H

#include "receiver.h"

class LidarReceiver : public Receiver
{
public:
    LidarReceiver(QString ip, quint16 port, QElapsedTimer *appTime);

    void getDistance(quint16* dist);

private:
    void extractData();

    quint16 distance[181];
};

#endif // LIDARRECEIVER_H

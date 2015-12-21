#ifndef ACCELERORECEIVER_H
#define ACCELERORECEIVER_H

#include "receiver.h"

class AcceleroReceiver : public Receiver
{
public:
    AcceleroReceiver(QString ip, quint16 port, QElapsedTimer *appTime);
private:
    qint16 accX;
    qint16 accY;
    qint16 accZ;

    void extractData();
};

#endif // ACCELERORECEIVER_H

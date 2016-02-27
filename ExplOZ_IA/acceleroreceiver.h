#ifndef ACCELERORECEIVER_H
#define ACCELERORECEIVER_H

#include "receiver.h"

class AcceleroReceiver : public Receiver
{
public:
    AcceleroReceiver(QString ip, quint16 port, QElapsedTimer *appTime);
      qint16 accZ;
      qint16 angleZ;
    qint64 dernierAcquisitionTemps;
private:
    qint16 accX;
    qint16 accY;


    void extractData();
};

#endif // ACCELERORECEIVER_H

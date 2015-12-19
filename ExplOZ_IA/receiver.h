#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include "communicator.h"

#define ID_SIZE_IN_BYTES 1
#define SIZE_SIZE_IN_BYTES 4
#define START_SIZE_IN_BYTES 1
#define CONFIRMATION_SIZE_IN_BYTES 5

enum extractMode{START,
                 CONFIRMATION,
                 ID,
                 SIZE,
                 UNUSED_PREDATA,
                 DATA,
                 UNUSED_POSTDATA,
                 CRC};

class Receiver : public Communicator
{
public:
    Receiver(QString ip, quint16 port);
private:
    quint32 dataSize;
    extractMode eMode;
signals:
    void newValue();
public slots:
    virtual void extract(void* returnPointer = 0) = 0;
};

#endif // RECEIVER_H

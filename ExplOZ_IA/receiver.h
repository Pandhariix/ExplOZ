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
    Q_OBJECT

public:
    Receiver(QString ip, quint16 port);
    void start();

protected:
    virtual void extractData() = 0;

    quint32 dataSize;
    extractMode eMode;
    quint32 unusedPredataSize;
    quint32 unusedPostdataSize;

signals:
    void newValue();

public slots:
    void extract();
};

#endif // RECEIVER_H

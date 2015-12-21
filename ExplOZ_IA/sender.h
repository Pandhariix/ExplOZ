#ifndef SENDER_H
#define SENDER_H

#include <QObject>
#include <qtimer.h>
#include "communicator.h"

class Sender : public Communicator
{
public:
    Sender(quint16 port);
    Sender(QString ip, quint16 port);

    void start();

protected:
    QTimer *timer;

signals:

public slots:
    void send();
    virtual void translate() = 0;
};

#endif // SENDER_H

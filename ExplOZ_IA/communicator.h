#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QObject>
#include <QTcpSocket>

class Communicator
{
public:
    Communicator(QString* ip, quint16 port);
    virtual void start() = 0;
private:
    QString ip;
    QTcpSocket socket;
    QByteArray data;
    quint16 port;
};

#endif // COMMUNICATOR_H

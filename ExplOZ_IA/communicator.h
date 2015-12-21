#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QObject>
#include <QTcpSocket>

#define PORT_GPS 3334
#define PORT_MOTOR 3331
#define PORT_TOOL 3345
#define PORT_ACCELERO 3339
#define PORT_GYRO 3340
#define PORT_LIDAR 3337

class Communicator : public QObject
{

public:
    Communicator(quint16 port);
    Communicator(QString ip, quint16 port);
    virtual void start() = 0;

protected:
    QString ip;
    QTcpSocket socket;
    QByteArray data;
    quint16 port;
};

#endif // COMMUNICATOR_H

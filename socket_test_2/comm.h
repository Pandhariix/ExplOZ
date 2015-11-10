#ifndef COMM_H
#define COMM_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>

class Comm : public QObject
{
    Q_OBJECT
public:
    Comm(QObject *parent = 0);
    ~Comm();
    void run();

signals:

public slots:
    void detection();
    void update();
    void handleSocketError();

private:
    QTcpSocket* socket_moteur;
    QTcpSocket* socket_capteur;
    QByteArray* data;
    QTimer* timer;
};

#endif // COMM_H

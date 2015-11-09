#ifndef COMM_H
#define COMM_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>

class Comm : public QObject
{
    Q_OBJECT
public:
    explicit Comm(QObject *parent = 0);

signals:

public slots:
    void detection();
    void update();

private:
    QTcpSocket* socket_moteur;
    QTcpSocket* socket_capteur;
    QByteArray* data;
    QTimer* timer;
};

#endif // COMM_H

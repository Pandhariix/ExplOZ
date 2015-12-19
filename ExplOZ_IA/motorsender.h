#ifndef MOTORSENDER_H
#define MOTORSENDER_H

#include <QObject>
#include "sender.h"

class MotorSender : public Sender
{
public:
    MotorSender(quint16 port);
    MotorSender(QString ip, quint16 port);

    void setSpeed(quint8 leftSpeed, quint8 rightSpeed);

private:
    quint8 leftSpeedToTranslate;
    quint8 rightSpeedToTranslate;

signals:

public slots:
    void translate() = 0;
};

#endif // MOTORSENDER_H

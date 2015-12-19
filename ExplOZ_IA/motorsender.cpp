#include "motorsender.h"

MotorSender::MotorSender(quint16 port) : Sender(port)
{

}
MotorSender::MotorSender(QString ip, quint16 port) : Sender(ip, port)
{

}

void MotorSender::setSpeed(quint8 leftSpeed, quint8 rightSpeed)
{
    this->leftSpeedToTranslate = leftSpeed;
    this->rightSpeedToTranslate = rightSpeed;
}

void translate()
{

}

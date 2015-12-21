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

void MotorSender::translate()
{
    this->data.clear();

    this->data.append("NAIO01");
    this->data.append(1);
    this->data.append((char)0);
    this->data.append((char)0);
    this->data.append((char)0);
    this->data.append((char)2);
    this->data.append((char)this->leftSpeedToTranslate);
    this->data.append((char)this->rightSpeedToTranslate);
    this->data.append((char)0);
    this->data.append((char)0);
    this->data.append((char)0);
    this->data.append((char)0);
}

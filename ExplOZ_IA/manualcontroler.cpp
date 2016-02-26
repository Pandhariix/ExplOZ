#include "manualcontroler.h"

ManualControler::ManualControler(MotorSender *motSender)
{
    this->timer = new QTimer();
    this->motorSender = motSender;
}

void ManualControler::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Up)
        this->motorSender->setSpeed(100,100);

    else if(event->key() == Qt::Key_Right)
        this->motorSender->setSpeed(100,50);

    else if(event->key() == Qt::Key_Left)
        this->motorSender->setSpeed(50,100);

    else if(event->key() == Qt::Key_Down)
        this->motorSender->setSpeed(-100,-100);
}

void ManualControler::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Up || event->key() == Qt::Key_Right || event->key() == Qt::Key_Left || event->key() == Qt::Key_Down)
        this->motorSender->setSpeed(0,0);
}




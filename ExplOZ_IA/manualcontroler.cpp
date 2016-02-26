#include "manualcontroler.h"

ManualControler::ManualControler(MotorSender *motSender, ToolSender *toolSender)
{
    this->timer = new QTimer();
    this->motorSender = motSender;
    this->toolSender = toolSender;
}

void ManualControler::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Up)
        this->motorSender->setSpeed(100,100);

    else if(event->key() == Qt::Key_Right)
        this->motorSender->setSpeed(100,40);

    else if(event->key() == Qt::Key_Left)
        this->motorSender->setSpeed(40,100);

    else if(event->key() == Qt::Key_Down)
        this->motorSender->setSpeed(-100,-100);

    else if(event->key() == Qt::Key_S)
            this->toolSender->setToolAction(LOWER);

    else if(event->key() == Qt::Key_Z)
            this->toolSender->setToolAction(RAISE);
}

void ManualControler::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Up || event->key() == Qt::Key_Right || event->key() == Qt::Key_Left || event->key() == Qt::Key_Down)
        this->motorSender->setSpeed(0,0);

    else if(event->key() == Qt::Key_S || event->key() == Qt::Key_Z)
        this->toolSender->setToolAction(FREEZE);
}




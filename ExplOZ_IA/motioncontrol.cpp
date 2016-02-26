#include "motioncontrol.h"

MotionControl::MotionControl(QElapsedTimer *elapsedTimer, LidarReceiver *lidar, MotorSender *motSender)
{
    this->timer = new QTimer();
    this->elapsedTimer = elapsedTimer;
    this->lidar = lidar;
    this->motSender = motSender;
}

void MotionControl::commandLoop()
{
    if(this->elapsedTimer->msecsSinceReference() < 2000)
        return;

    //Hough operations

    this->lidar->getDistance(this->distance);
    this->detector.buildCartesianMap(this->distance, this->factor);
    this->detector.transform();

    //

    this->deltaTheta= deltaD*KD - this->theta;
    this->deltaVitesse= KTHETA*this->deltaTheta;

    if(this->deltaVitesse <= 0)
    {
        this->vDroite=VMAX;
        this->vGauche=this->vDroite+this->deltaVitesse;
    }

    else{
        this->vGauche=VMAX;
        this->vDroite=this->vGauche-this->deltaVitesse;
    }
}

void MotionControl::start()
{
    connect(this->timer, SIGNAL(timeout()), this, SLOT(commandLoop()));
    this->timer->start(1000);
}


#include "motioncontrol.h"

MotionControl::MotionControl(QElapsedTimer *elapsedTimer, LidarReceiver *lidar, MotorSender *motSender, AcceleroReceiver *gyro)
{
    this->timer = new QTimer();
    this->elapsedTimer = elapsedTimer;
    this->lidar = lidar;
    this->motSender = motSender;
    this->sommeDistance=0;
    this->sommeTheta=0;
    this->compteurVirage=0;
    this->modeVirage=false;
    this->gyro=gyro;
}

void MotionControl::commandLoop()
{
    if(modeVirage==false){
        //qDebug()<<"COucou";
        if(this->elapsedTimer->msecsSinceReference() < 2000)
            return;


        //Hough operations

        this->lidar->getDistance(this->distance);
        this->detector.buildCartesianMap(this->distance, this->factor);
        this->detector.transform();
        this->detector.getDetectedLines(this->lines, wall);

        //qDebug() << "size : " << lines.size();
        int deltaDG;
        int deltaDD;
        switch(wall) {
        case RIGHT:
            compteurVirage=0;
            //qDebug()<<"rho"<<lines[0].first;
            if(lines[0].second>3.1415/2){
                theta=-3.1415+lines[0].second;
            }
            else{
                theta=lines[0].second;
            }
            deltaD=lines[0].first/cos(lines[0].second)-400-OFFSETWALL;
            /*
        qDebug()<<"angle"<<theta;
        qDebug()<<"deltad"<<deltaD;
        qDebug()<<"cos"<<cos(theta);
        qDebug() << "Right";
        */
            break;
        case LEFT:
            compteurVirage=0;
            //qDebug()<<"rho"<<lines[0].first;
            if(lines[0].second>3.1415/2){
                theta=3.1415-lines[0].second;
            }
            else{
                theta=-lines[0].second;
            }
            deltaD=lines[0].first/cos(lines[0].second)-400+OFFSETWALL;
            /*
        qDebug()<<"angle"<<theta;
        qDebug()<<"deltad"<<deltaD;
        qDebug()<<"cos"<<cos(theta);


        */
            //qDebug() << "Left";
            break;
        case BOTH:
            compteurVirage=0;
            deltaDG=lines[0].first/cos(lines[0].second)-400;
            deltaDD=lines[1].first/cos(lines[1].second)-400;

            if(abs(deltaDG)<abs(deltaDD)){
                deltaD=deltaDG+OFFSETWALL;
                if(lines[0].second>3.1415/2){
                    theta=3.1415-lines[0].second;
                }
                else{
                    theta=-lines[0].second;
                }
            }
            else{
                deltaD=deltaDD-OFFSETWALL;
                if(lines[1].second>3.1415/2){
                    theta=-3.1415+lines[1].second;
                }
                else{
                    theta=lines[1].second;
                }
            }

            break;

        case NONE:
            compteurVirage++;
            theta=0;
            deltaD=0;
            //qDebug() <<"None";

            if(compteurVirage>10){
                modeVirage = true;
                stateMachine=0;
                tempsDebutDemiTour=elapsedTimer->elapsed();
            }
            break;
        }



        //qDebug() << this->lines[0].first << this->lines[0].second;

        //

        this->deltaTheta= deltaD*KD + sommeTheta - this->theta;
        this->deltaVitesse= KTHETA*this->deltaTheta+sommeDistance;
        /*
    this->sommeTheta=sommeTheta+deltaTheta;
    this->sommeDistance=sommeDistance+deltaVitesse;
*/
        if(deltaVitesse>(VMAX-10)){
            deltaVitesse=VMAX-10;
        }
        if(deltaVitesse<(-VMAX+10)){
            deltaVitesse=-VMAX+10;
        }
        if(this->deltaVitesse <= 0)
        {
            this->vDroite=VMAX;
            this->vGauche=this->vDroite+this->deltaVitesse;
        }

        else{
            this->vGauche=VMAX;
            this->vDroite=this->vGauche-this->deltaVitesse;
        }
        motSender->setSpeed((quint8)vGauche,(quint8)vDroite);
    }
    else{
        switch(stateMachine)
        {
        case 0:
            if(elapsedTimer->elapsed()-tempsDebutDemiTour>TEMPSDEMITOURAVANT){

                angleDebutVirage=gyro->angleZ;
                stateMachine=1;
            }
            break;
        case 1:
            //qDebug() << "Ontourne";
            motSender->setSpeed(VMAX/4,VMAX);
            if(gyro->angleZ-angleDebutVirage>PARAMETREANGLE){
                tempsDebutDemiTour=elapsedTimer->elapsed();
                stateMachine=2;
            }
            break;
        case 2:
            //qDebug() << "Onrecule";
            motSender->setSpeed(-VMAX,-VMAX);
            if(elapsedTimer->elapsed()-tempsDebutDemiTour>TEMPSMARCHEARRIERE){
                angleDebutVirage=gyro->angleZ;
                stateMachine=3;
            }
            break;
        case 3:
            motSender->setSpeed(VMAX/4,VMAX);
            //qDebug() << "angledebut : " << angleDebutVirage << "angleZ : " << gyro->angleZ;

            if((gyro->angleZ-angleDebutVirage)>PARAMETREANGLE){
                tempsDebutDemiTour=elapsedTimer->elapsed();
                modeVirage=false;
                break;
            }




        }
    }
}

    void MotionControl::start()
    {
        connect(this->timer, SIGNAL(timeout()), this, SLOT(commandLoop()));
        this->timer->start(0);
    }


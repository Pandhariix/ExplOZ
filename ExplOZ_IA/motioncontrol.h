#ifndef MOTIONCONTROL_H
#define MOTIONCONTROL_H

#define KD 1.2
#define KTHETA 1.1

#define VMAX 100
#define OFFSETWALL 40

#define TEMPSDEMITOURAVANT 6000
#define PARAMETREANGLE 2900
#define TEMPSMARCHEARRIERE 100

#include <qtimer.h>
#include <qelapsedtimer.h>
#include "houghdetector.h"
#include "lidarreceiver.h"
#include "motorsender.h"
#include "acceleroreceiver.h"

class MotionControl : public QObject
{
    Q_OBJECT

public:
    MotionControl(QElapsedTimer *elapsedTimer, LidarReceiver *lidar, MotorSender *motSender, AcceleroReceiver *gyro);
    void start();

private:
    int deltaD;
    int deltaTheta;
    int vGauche;
    int vDroite;
    int deltaVitesse;
    double theta;
    long sommeTheta;
    long sommeDistance;
    int compteurVirage;
    bool modeVirage;
    qint16 angleDebutVirage;

    int stateMachine;
    quint64 tempsDebutDemiTour;

    QTimer *timer;
    QElapsedTimer *elapsedTimer;
    LidarReceiver *lidar;
    MotorSender *motSender;
    std::vector<std::pair<float, float> > lines;
    directionWall wall;
    AcceleroReceiver *gyro;


    int factor = 10;
    std::vector<quint16> distance;
    HoughDetector detector;

signals:

public slots:
    void commandLoop();

};

#endif // MOTIONCONTROL_H

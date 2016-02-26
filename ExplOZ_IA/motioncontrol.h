#ifndef MOTIONCONTROL_H
#define MOTIONCONTROL_H

#define KD 1
#define KTHETA 1
#define VMAX 127

#include <qtimer.h>
#include <qelapsedtimer.h>
#include "houghdetector.h"
#include "lidarreceiver.h"
#include "motorsender.h"

class MotionControl : public QObject
{
    Q_OBJECT

public:
    MotionControl(QElapsedTimer *elapsedTimer, LidarReceiver *lidar, MotorSender *motSender);
    void start();

private:
    int a1;
    int a2;
    int b1;
    int b2;
    int aRef;
    int bRef;
    int deltaD;
    int deltaTheta;
    int vGauche;
    int vDroite;
    int deltaVitesse;
    int theta;

    QTimer *timer;
    QElapsedTimer *elapsedTimer;
    LidarReceiver *lidar;
    MotorSender *motSender;

    int factor = 8;
    std::vector<quint16> distance;
    HoughDetector detector;

signals:

public slots:
    void commandLoop();

};

#endif // MOTIONCONTROL_H

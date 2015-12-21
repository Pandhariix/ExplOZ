#include <QCoreApplication>
#include "lidarreceiver.h"
#include "acceleroreceiver.h"
#include "motorsender.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /*
    LidarReceiver lRec("127.0.0.1", PORT_LIDAR);
    lRec.start();
    */

    /*
    AcceleroReceiver accRec("127.0.0.1", PORT_ACCELERO);
    accRec.start();
    */

    MotorSender motSender("127.0.0.1",PORT_MOTOR);
    motSender.setSpeed(127,127);
    motSender.start();

    return a.exec();
}

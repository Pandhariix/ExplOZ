#include <QCoreApplication>
#include "lidarreceiver.h"
#include "acceleroreceiver.h"
#include "motorsender.h"
#include "toolsender.h"

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
    motSender.setSpeed(50,50);
    motSender.start();

    ToolSender tSender("127.0.0.1",PORT_TOOL);
    tSender.setToolAction(LOWER);
    tSender.start();

    return a.exec();
}

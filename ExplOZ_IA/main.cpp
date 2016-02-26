#include <QCoreApplication>
#include <QElapsedTimer>

#include "lidarreceiver.h"
#include "acceleroreceiver.h"
#include "motorsender.h"
#include "toolsender.h"

#include "motioncontrol.h"
#include "manualcontroler.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    QApplication a(argc, argv);

    QElapsedTimer appTime;
    appTime.start();

    //QString ip = "192.168.5.11";
    QString ip = "127.0.0.1";

    MotorSender motSender(ip,PORT_MOTOR);
    //motSender.setSpeed(50,50);
    motSender.start();

    /*
    ToolSender tSender(ip,PORT_TOOL);
    //tSender.setToolAction(LOWER);
    tSender.start();
*/

    LidarReceiver lRec(ip, PORT_LIDAR, &appTime);
    lRec.start();
/*
    AcceleroReceiver accRec(ip, PORT_ACCELERO, &appTime);
    accRec.start();

    AcceleroReceiver gyroRec(ip, PORT_GYRO, &appTime);
    accRec.start();
*/
    MotionControl motion(&appTime, &lRec, &motSender);
    motion.start();

    ManualControler manual(&motSender, NULL);
    manual.setMaximumWidth(20);
    manual.setMaximumHeight(20);
    manual.show();

    /*
    AcceleroReceiver accRec("127.0.0.1", PORT_ACCELERO, &appTime);
    accRec.start();

    ToolSender tSender("127.0.0.1",PORT_TOOL);
    tSender.setToolAction(LOWER);
    tSender.start();
    */

    return a.exec();
}

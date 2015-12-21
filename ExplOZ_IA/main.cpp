#include <QCoreApplication>
#include <QElapsedTimer>

#include "lidarreceiver.h"
#include "acceleroreceiver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QElapsedTimer appTime;
    appTime.start();

    LidarReceiver lRec("127.0.0.1", PORT_LIDAR, &appTime);
    lRec.start();

    AcceleroReceiver accRec("127.0.0.1", PORT_ACCELERO, &appTime);
    accRec.start();

    return a.exec();
}

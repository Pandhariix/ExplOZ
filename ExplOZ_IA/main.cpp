#include <QCoreApplication>
#include "lidarreceiver.h"
#include "acceleroreceiver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /*LidarReceiver lRec("127.0.0.1", PORT_LIDAR);
    lRec.start();*/

    AcceleroReceiver accRec("127.0.0.1", PORT_ACCELERO);
    accRec.start();

    return a.exec();
}

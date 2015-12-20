#include <QCoreApplication>
#include "lidarreceiver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LidarReceiver lRec("127.0.0.1", PORT_LIDAR);
    lRec.start();

    return a.exec();
}

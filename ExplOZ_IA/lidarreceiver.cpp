#include "lidarreceiver.h"

#include <QFile>
#include <cmath>

LidarReceiver::LidarReceiver(QString ip, quint16 port, QElapsedTimer* appTime) : Receiver(ip, port, appTime)
{
    unusedPredataSize = 46 * 2;
    unusedPostdataSize = 45 * 2 + 271;
}

void LidarReceiver::extractData(){
    data = socket.read(dataSize - unusedPostdataSize - unusedPredataSize);

    QDataStream ds(data);

    for (uint i = 0 ; i < (dataSize - unusedPostdataSize - unusedPredataSize)/2 ; i++){
        ds >> distance[i];

        //qDebug() << "distance[" << i << "] = " << distance[i];
    }

    quint16 cart[40][20];

    for (int i = 0 ; i < 40 ; i++){
        for (int j = 0 ; j < 20 ; j++){
            cart[i][j] = 0;
        }
    }


    for (int i = 0 ; i < 180 ; i++){
        if(distance[i] < 4000){
            quint16 x = distance[i]*cos(3.14/180*i)/200 + 20;
            quint16 y = distance[i]*sin(3.14/180*i)/200;

            qDebug() << "dist : " << distance[i] << "i : " << i << "x : " << x << " y : " << y << " cos : " << cos(3.14/180*i) << " sin : " << sin(3.14/180*i);

            //Expansion
            cart[x][y] += 12;
            cart[x+1][y] += 3;
            cart[x-1][y] += 3;
            cart[x][y+1] += 3;
            cart[x][y-1] += 3;
            cart[x+1][y+1] += 1;
            cart[x+1][y-1] += 1;
            cart[x-1][y+1] += 1;
            cart[x-1][y-1] += 1;
        }
    }

    //Seuillage
    for (int i = 0 ; i < 40 ; i++){
        for (int j = 0 ; j < 20 ; j++){
            if(cart[i][j] > 40)
                cart[i][j] -= 40;
            else
                cart[i][j] = 0;
        }
    }

    /*quint16 disc[20][20];

    for (int i = 0 ; i < 20 ; i++){
        for (int j = 0 ; j < 20 ; j++){
            disc[i][j] = 0;
        }
    }

    for (int i = 0 ; i < 180 ; i++){
        if(distance[i] < 4000){
            quint16 rho = distance[i]/200;
            quint16 thet = i/9;

            //qDebug() << "dist : " << distance[i] << "i : " << i << "x : " << x << " y : " << y << " cos : " << cos(3.14/180*i) << " sin : " << sin(3.14/180*i);

            //Expansion
            disc[rho][thet] += 12;
            disc[rho+1][thet] += 3;
            disc[rho-1][thet] += 3;
            disc[rho][thet+1] += 3;
            disc[rho][thet-1] += 3;
        }
    }

    quint16 cart[40][20];

    for (int i = 0 ; i < 40 ; i++){
        for (int j = 0 ; j < 20 ; j++){
            cart[i][j] = 0;
        }
    }*/




    QFile* file = new QFile("trait.csv");

    if(file->exists())
        return;

    file->open(QIODevice::ReadWrite);

    for(int i = 0 ; i < 20 ; i++){
        for(int j = 0 ; j < 40 ; j++){
            file->write(QString().number(cart[j][i]).toStdString().c_str());

            if(j < 39)
                file->write(" ; ");
            else
                file->write("\n");
        }
    }

    file->close();

}

void LidarReceiver::getDistance(quint16* dist){
    for (int i = 0 ; i < 180 ; i++)
        dist[i] = distance[i];
}

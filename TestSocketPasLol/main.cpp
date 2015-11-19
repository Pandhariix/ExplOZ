#include <QCoreApplication>
#include <QTcpSocket> // classe qui permet de facilement se connecter en tcp easy peasy
#include "com.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Com comTest;

    return a.exec();
}

#include <QCoreApplication>
#include <comm.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Comm comm();

    return a.exec();
}

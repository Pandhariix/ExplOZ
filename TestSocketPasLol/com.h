#ifndef COM_H
#define COM_H


#include <QObject>
#include <QTcpSocket>

class Com : public QObject
{
    Q_OBJECT
public:
    explicit Com(QObject *parent = 0);

private:

    QTcpSocket* socket;
    QByteArray *trame_lidar;

signals:

public slots:
    void lireDonnees(void);

};

#endif // COM_H

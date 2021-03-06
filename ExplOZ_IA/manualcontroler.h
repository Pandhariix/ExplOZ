#ifndef MANUALCONTROLER_H
#define MANUALCONTROLER_H

#include <QWidget>
#include <QKeyEvent>
#include <qtimer.h>
#include "motorsender.h"
#include "toolsender.h"

class ManualControler : public QWidget
{
    Q_OBJECT
public:
    ManualControler(MotorSender *motSender, ToolSender *toolSender);
    void start();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    QTimer *timer;
    MotorSender *motorSender;
    ToolSender *toolSender;

    quint8 rightSpeed;
    quint8 leftSpeed;

signals:

public slots:
};

#endif // MANUALCONTROLER_H

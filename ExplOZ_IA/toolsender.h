#ifndef TOOLSENDER_H
#define TOOLSENDER_H

#include <QObject>
#include "sender.h"

enum toolAction{LOWER,
                RISE,
                FREEZE};

class ToolSender : public Sender
{
public:
    ToolSender(quint16 port);
    ToolSender(QString ip, quint16 port);

    void setToolAction(toolAction tAction);

private:
    toolAction tActionToTranslate;

signals:

public slots:
    void translate() = 0;
};

#endif // TOOLSENDER_H

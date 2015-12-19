#include "toolsender.h"

ToolSender::ToolSender(quint16 port) : Sender(port)
{

}
ToolSender::ToolSender(QString ip, quint16 port) : Sender(ip, port)
{

}

void ToolSender::setToolAction(toolAction tAction)
{
    this->tActionToTranslate = tAction;
}

void ToolSender::translate()
{
    //TODO
}

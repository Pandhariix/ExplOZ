#include "toolsender.h"

ToolSender::ToolSender(quint16 port) : Sender(port)
{
    this->tActionToTranslate = FREEZE;
}
ToolSender::ToolSender(QString ip, quint16 port) : Sender(ip, port)
{
    this->tActionToTranslate = FREEZE;
}

void ToolSender::setToolAction(toolAction tAction)
{
    this->tActionToTranslate = tAction;
}

void ToolSender::translate()
{
    switch(this->tActionToTranslate)
    {
        case LOWER:
            //TODO
            break;

        case RISE:
            //TODO
            break;

        case FREEZE:
            //TODO
            break;
    }
}

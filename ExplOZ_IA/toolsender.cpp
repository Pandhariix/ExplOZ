#include "toolsender.h"

ToolSender::ToolSender(quint16 port) : Sender(port)
{
    this->tActionToTranslate = FREEZE;
    this->translate();
}
ToolSender::ToolSender(QString ip, quint16 port) : Sender(ip, port)
{
    this->tActionToTranslate = FREEZE;
    this->translate();
}

void ToolSender::setToolAction(toolAction tAction)
{
    this->tActionToTranslate = tAction;
}

void ToolSender::translate()
{
    data.clear();

    this->data.append("NAIO01");
    this->data.append('F');
    this->data.append((char)0);
    this->data.append((char)0);
    this->data.append((char)0);
    this->data.append((char)1);

    switch(this->tActionToTranslate){
    case LOWER:
        this->data.append((char)2);
        break;

    case RAISE:
        this->data.append((char)1);
        break;

    case FREEZE:
        this->data.append((char)3);
        break;
     }

    this->data.append((char)0);
    this->data.append((char)0);
    this->data.append((char)0);
    this->data.append((char)0);
}

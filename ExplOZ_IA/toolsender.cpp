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
            this->data.append("NAIO01");
            this->data.append('F');
            this->data.append((char)0);
            this->data.append((char)0);
            this->data.append((char)0);
            this->data.append((char)1);
            this->data.append((char)2);
            this->data.append((char)0);
            this->data.append((char)0);
            this->data.append((char)0);
            this->data.append((char)0);
            break;

        case RAISE:
            this->data.append("NAIO01");
            this->data.append('F');
            this->data.append((char)0);
            this->data.append((char)0);
            this->data.append((char)0);
            this->data.append((char)1);
            this->data.append((char)1);
            this->data.append((char)0);
            this->data.append((char)0);
            this->data.append((char)0);
            this->data.append((char)0);
            break;

        case FREEZE:
            this->data.append("NAIO01");
            this->data.append('F');
            this->data.append((char)0);
            this->data.append((char)0);
            this->data.append((char)0);
            this->data.append((char)1);
            this->data.append((char)3);
            this->data.append((char)0);
            this->data.append((char)0);
            this->data.append((char)0);
            this->data.append((char)0);
            break;
    }
}

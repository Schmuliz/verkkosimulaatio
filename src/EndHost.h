#ifndef ENDHOST_H
#define ENDHOST_H

#include "Node.h"
#include "Application.h"

class EndHost : public Node
{
public:
    EndHost(int address, int applicationId);
    ~EndHost(){}
    void processPacket(Packet *packet) override;
    void paint(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget) override;
    QRectF boundingRect() const override;

private:
    Application* application_;
};


#endif // ENDHOST_H

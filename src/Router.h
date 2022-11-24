#ifndef ROUTER_H
#define ROUTER_H

#include "Packet.h"
#include "Node.h"


class Router : public Node
{
public:
    Router(int address) : Node(address) {};

    QRectF boundingRect() const override;
    void paint(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget) override;

    void processPacket(Packet *packet) override;

private:
    void nexthop(Packet* packet);
};

#endif // ROUTER_H

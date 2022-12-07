#ifndef ROUTER_H
#define ROUTER_H

#include "Packet.h"
#include "Node.h"


class Router : virtual public Node
{
public:
    Router(int address);
    ~Router(){}
    void processPacket(Packet *packet) override;
    void paint(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget) override;

private:
    void nexthop(Packet* packet);
};

#endif // ROUTER_H

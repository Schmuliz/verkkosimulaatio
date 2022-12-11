#ifndef ROUTER_H
#define ROUTER_H

#include "Packet.h"
#include "Node.h"

/**
 * @brief The Router class. A type of netowork node that is capable of routing packages forward.
 */
class Router : virtual public Node
{
public:
    Router(int address, std::vector<int> queue);
    ~Router(){}
    void processPacket(Packet *packet) override;
    void paint(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget) override;

private:
    void nexthop(Packet* packet);
};

#endif // ROUTER_H

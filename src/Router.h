#ifndef ROUTER_H
#define ROUTER_H

#include "Packet.h"
#include "Node.h"


class Router : public Node
{
public:
    Router(int address);
    ~Router(){}
    void processPacket(Packet *packet) override;

private:
    void nexthop(Packet* packet);
};

#endif // ROUTER_H

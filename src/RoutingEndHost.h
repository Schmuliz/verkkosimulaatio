#ifndef ROUTINGENDHOST_H
#define ROUTINGENDHOST_H

#include "Router.h"
#include "EndHost.h"


class RoutingEndHost : public EndHost, public Router
{
public:
    RoutingEndHost(int address, std::vector<int> application);
    ~RoutingEndHost(){}
    void processPacket(Packet *packet) override;
    void paint(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget) override;
};


#endif // ROUTINGENDHOST_H

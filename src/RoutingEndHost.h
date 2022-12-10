#ifndef ROUTINGENDHOST_H
#define ROUTINGENDHOST_H

#include "Router.h"
#include "EndHost.h"

/**
 * @brief The RoutingEndHost class. Represents a type of network node that is capable of running applications like a endhost and forwarding packages like a router.
 */
class RoutingEndHost : public EndHost, public Router
{
public:
    RoutingEndHost(int address, std::vector<int> application);
    ~RoutingEndHost(){}
    void processPacket(Packet *packet) override;
    void paint(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget) override;
};


#endif // ROUTINGENDHOST_H

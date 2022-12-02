#ifndef ROUTINGENDHOST_H
#define ROUTINGENDHOST_H

#include "Application.h"
#include "Router.h"


class RoutingEndHost : public Router
{
public:
    RoutingEndHost(int address, std::vector<int> application);
    ~RoutingEndHost(){}
    void processPacket(Packet *packet) override;
    void paint(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget) override;
    QRectF boundingRect() const override;

private:
    Application application_;
};


#endif // ROUTINGENDHOST_H

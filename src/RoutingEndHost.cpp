#include "RoutingEndHost.h"
#include <QDebug>


RoutingEndHost::RoutingEndHost(int address, Application* application)
    : Router(address), application_(application) {}

void RoutingEndHost::processPacket(Packet *packet) {}


void RoutingEndHost::paint(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget) {
    qInfo() << "trying to draw a routing endhost";
    QPixmap routerimg("../assets/routingendhost.png");
    painter->drawPixmap(-sizeconst, -sizeconst, routerimg.scaled(2*sizeconst, 2*sizeconst));
}


QRectF RoutingEndHost::boundingRect() const {
    return QRectF(-sizeconst, -sizeconst, sizeconst, sizeconst);
}

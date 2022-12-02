#include "RoutingEndHost.h"
#include "qpainter.h"
#include <QDebug>


RoutingEndHost::RoutingEndHost(int address, std::vector<int> application)
    : Router(address) {
    // Avoid this being a duplicate implementation of std::vector application parsing
}

void RoutingEndHost::processPacket(Packet *packet) {}


void RoutingEndHost::paint(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget) {
    qInfo() << "trying to draw a routing endhost";
    QPixmap routerimg(":/resources/routingendhost.png");
    painter->drawPixmap(-sizeconst, -sizeconst, routerimg.scaled(2*sizeconst, 2*sizeconst));
}


QRectF RoutingEndHost::boundingRect() const {
    return QRectF(-sizeconst, -sizeconst, sizeconst, sizeconst);
}

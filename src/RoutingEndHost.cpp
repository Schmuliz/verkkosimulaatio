#include "RoutingEndHost.h"
#include "qpainter.h"
#include <QDebug>


RoutingEndHost::RoutingEndHost(int address, int applicationId)
    : Router(address), application_(new SimpleApplication(std::vector<int>{0, 1, 2}, 5)) {}

void RoutingEndHost::processPacket(Packet *packet) {}


void RoutingEndHost::paint(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget) {
    qInfo() << "trying to draw a routing endhost";
    QPixmap routerimg(":/resources/routingendhost.png");
    painter->drawPixmap(-sizeconst, -sizeconst, routerimg.scaled(2*sizeconst, 2*sizeconst));
}


QRectF RoutingEndHost::boundingRect() const {
    return QRectF(-sizeconst, -sizeconst, sizeconst, sizeconst);
}

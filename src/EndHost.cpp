#include "EndHost.h"
#include <QDebug>


EndHost::EndHost(int address, int applicationid)
    : Node(address), application_(applicationid) {}

void EndHost::processPacket(Packet *packet) {}


void EndHost::paint(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget) {
    qInfo() << "trying to draw a endhost";
    QPixmap routerimg("../assets/endhost.png");
    painter->drawPixmap(0, 0, routerimg.scaled(2*sizeconst, 2*sizeconst));
}

QRectF EndHost::boundingRect() const {
    return QRectF(-25, -25, 25, 25);
}

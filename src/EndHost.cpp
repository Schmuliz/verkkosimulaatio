#include "EndHost.h"
#include "qpainter.h"
#include <QDebug>


EndHost::EndHost(int address, int applicationid)
    : Node(address), application_(new SimpleApplication(std::vector<int>{0, 1, 2}, 5)) {}

void EndHost::processPacket(Packet *packet) {}


void EndHost::paint(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget) {
    qInfo() << "trying to draw a endhost";
    QPixmap routerimg(":/resources/endhost.png");
    painter->drawPixmap(-sizeconst, -sizeconst, routerimg.scaled(2*sizeconst, 2*sizeconst));
}

QRectF EndHost::boundingRect() const {
    return QRectF(-25, -25, 25, 25);
}

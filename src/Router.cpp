#include "Router.h"
#include "qpainter.h"

QRectF Router::boundingRect() const {
    return QRectF(50,50,50,50);
}

void Router::processPacket(Packet *packet) {
}

void Router::paint(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget) {
    painter->drawRoundedRect(-10, -10, 20, 20, 5, 5);
}

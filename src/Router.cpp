#include "Router.h"
#include <QPixmap>
#include <QDebug>


Router::Router(int address)
    : Node(address) {}

void Router::processPacket(Packet *packet) {

}

void Router::paint(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget) {
    qInfo() << "trying to draw a router";
    QPixmap routerimg("../assets/router.png");
    painter->drawPixmap(-sizeconst, -sizeconst, routerimg.scaled(2*sizeconst, 2*sizeconst));
}

QRectF Router::boundingRect() const {
    return QRectF(-sizeconst, -sizeconst, sizeconst, sizeconst);
}

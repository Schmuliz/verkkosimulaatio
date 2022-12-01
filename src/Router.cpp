#include "Router.h"
#include "qpainter.h"
#include <QPixmap>
#include <QDebug>


Router::Router(int address)
    : Node(address) {}

void Router::processPacket(Packet *packet) {

}

void Router::paint(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget) {
    qInfo() << "trying to draw a router";
    QPixmap routerimg(":/resources/router.png");
    painter->drawPixmap(-sizeconst, -sizeconst, routerimg.scaled(2*sizeconst, 2*sizeconst));
    painter->drawText(QPointF(0,0), QString::number(dummyStat()));
}

QRectF Router::boundingRect() const {
    return QRectF(-sizeconst, -sizeconst, sizeconst, sizeconst);
}

#include "Router.h"
#include "qpainter.h"
#include <QPixmap>
#include <QDebug>


Router::Router(int address)
    : Node(address) {}

void Router::processPacket(Packet *packet) {
    if (packet != nullptr && packet->destinationAddress == address_){
        delete packet;
    }
}

/**
 * @brief Router::paint paints router specifically
 * @param painter painter to use
 * @param option unused qt stuff
 * @param widget unused qt stuff
 */
void Router::paint(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget) {
    qInfo() << "trying to draw a router";
    QPixmap routerimg(":/resources/router.png");
    painter->drawPixmap(-sizeconst, -sizeconst, routerimg.scaled(2*sizeconst, 2*sizeconst)); // draw the raster

    drawBottomText(painter, QString::number(getBufferSize()));

}

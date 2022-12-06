#include "Router.h"
#include "qpainter.h"
#include <QPixmap>
#include <QDebug>


Router::Router(int address)
    : Node(address) {}

void Router::runOneTick() {
    if (!packets_.empty()) {
        int dst = packets_.front()->destinationAddress;

        if (dst == address_) {
            this->processPacket(packets_.front());
            packets_.erase(packets_.begin());
            return;
        }

        Link* destinationLink = lookupTable_[dst];
        if (destinationLink->receive(packets_.front())) {
            packets_.erase(packets_.begin());
        }
    }
}

void Router::processPacket(Packet *packet) {
    delete packet;
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

    drawTopText(painter, "moi");
    drawBottomText(painter, "hei");

}

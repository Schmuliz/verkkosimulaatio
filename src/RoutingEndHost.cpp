#include "RoutingEndHost.h"
#include "qpainter.h"
#include <QDebug>


RoutingEndHost::RoutingEndHost(int address, std::vector<int> application)
    : Router(address) {
    // Avoid this being a duplicate implementation of std::vector application parsing
}


void RoutingEndHost::processPacket(Packet *packet) {
    auto newlyReceived = std::vector<Packet*>{packet};
    std::vector<Packet*> toBeSent = application_->packetGenerator(address_, newlyReceived);
    for (auto newPacket : toBeSent) {
        packets_.push_back(newPacket);
    }
    delete packet;
}

/**
 * @brief RoutingEndHost::paint paints routingendhost specific
 * @param painter qt painter
 * @param option unused qt stuff
 * @param widget unused qt stuff
 */
void RoutingEndHost::paint(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget) {
    qInfo() << "trying to draw a routing endhost";
    QPixmap routerimg(":/resources/routingendhost.png");
    painter->drawPixmap(-sizeconst, -sizeconst, routerimg.scaled(2*sizeconst, 2*sizeconst));
    drawTopText(painter, "1234");
}

#include "RoutingEndHost.h"
#include "qpainter.h"
#include <QDebug>


RoutingEndHost::RoutingEndHost(int address, std::vector<int> application, std::vector<int> queue)
    : Node(address, queue), Router(address, queue), EndHost(address, application, queue) {
    // Avoid this being a duplicate implementation of std::vector application parsing
}

/**
 * @brief RoutingEndHost::processPacket forwards packet to application
 * @param packet to be processed, default value nullptr (no packets available)
 */
void RoutingEndHost::processPacket(Packet *packet = nullptr) {
    EndHost::processPacket(packet);
}

/**
 * @brief RoutingEndHost::paint paints routingendhost specific
 * @param painter qt painter
 * @param option unused qt stuff
 * @param widget unused qt stuff
 */
void RoutingEndHost::paint(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget) {
    QPixmap routerimg(":/resources/routingendhost.png");
    painter->drawPixmap(-sizeconst, -sizeconst, routerimg.scaled(2*sizeconst, 2*sizeconst));
    drawTopText(painter, QString::number(getLastPacketAge()));
    drawBottomText(painter, QString::number(getBufferSize()));
}

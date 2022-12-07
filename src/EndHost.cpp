#include "EndHost.h"
#include "qpainter.h"
#include <QDebug>


/**
 * @brief EndHost constructor
 *
 * @param address network address
 * @param application vector of variable length that defines a application. First item defines application type, rest are application specific parameters
 */
EndHost::EndHost(int address, std::vector<int> application)
    : Node(address) {
    int appid = application.at(0); // always safe to read
    if(appid == 1) {
        application_ = new SimpleApplication(std::vector<int>{1,2,3}, 5); //TODO parse parameters from vector
    } else {
        throw "unkown appid";
    }
}


void EndHost::processPacket(Packet *packet) {
    Packet* newPacket = application_->packetGenerator(address_, packet);
    if (newPacket != nullptr) {
        qInfo() << "Got a packet to send";
        packets_.push_back(newPacket);
    }
    if (packet != nullptr && packet->destinationAddress == address_) {
        delete packet;
    }

}

/**
 * @brief EndHost::paint paints endhost specific
 * @param painter qt painter
 * @param option unused qt stuff
 * @param widget unused qt stuff
 */
void EndHost::paint(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget) {
    qInfo() << "trying to draw a endhost";
    QPixmap routerimg(":/resources/endhost.png");
    painter->drawPixmap(-sizeconst, -sizeconst, routerimg.scaled(2*sizeconst, 2*sizeconst));
    drawTopText(painter, QString::number(getBufferSize()));
    drawBottomText(painter, QString::number(getLastPacketAge()));
}

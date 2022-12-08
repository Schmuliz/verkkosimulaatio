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
        std::vector<int> destPart(application.begin()+3, application.end());
        application_ = new SimpleApplication(destPart,
                                             application.at(1) );
    } else {
        throw "unkown appid";
    }
}

/**
 * @brief EndHost::processPacket forwards current packet to application, if no packets lets application know that, too
 * @param packet current packet this EndHost is handling, default value is nullptr (no packets)
 */
void EndHost::processPacket(Packet *packet = nullptr) {
    Packet* newPacket = application_->packetGenerator(address_, packet);
    if (newPacket != nullptr) {
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
    QPixmap routerimg(":/resources/endhost.png");
    painter->drawPixmap(-sizeconst, -sizeconst, routerimg.scaled(2*sizeconst, 2*sizeconst));
    drawTopText(painter, QString::number(getLastPacketAge()));
    drawBottomText(painter, QString::number(getBufferSize()));
}

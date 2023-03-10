#include "EndHost.h"
#include "qpainter.h"
#include <QDebug>


/**
 * @brief EndHost constructor
 *
 * @param address network address
 * @param application vector of variable length that defines a application. First item defines application type, rest are application specific parameters
 */
EndHost::EndHost(int address, std::vector<int> application, std::vector<int> queue)
    : Node(address, queue) {
    int appid = application.at(0); // always safe to read
    std::vector<int> destPart(application.begin()+3, application.end());
    switch (appid) {
        case 1:
            application_ = new SimpleApplication(destPart, application.at(1), application.at(2));
            break;
        case 2:
            application_ = new BurstApplication(destPart, application.at(1), application.at(2));
            break;
        case 3:
            application_ = new RespondingApplication(destPart, application.at(1), application.at(2));
            break;
        case 4:
            application_ = new ReceivingApplication();
            break;
        default:
            throw "unkown appid";
    }
}

/**
 * @brief EndHost::~EndHost destructor to delete application;
 * virtual destructor of parent Node will delete packets
 */
EndHost::~EndHost() {
    delete application_;
}

/**
 * @brief EndHost::processPacket forwards current packet to application, if no packets lets application know that, too
 * @param packet current packet this EndHost is handling, default value is nullptr (no packets)
 */
void EndHost::processPacket(Packet *packet = nullptr) {
    Packet* newPacket = application_->packetGenerator(address_, packet);
    if (newPacket != nullptr) {
        packets_->maybe_push_back(newPacket);
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

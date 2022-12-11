#ifndef NODE_H
#define NODE_H

#include "Link.h"
#include "Packet.h"
#include "Network.h"
#include "Application.h"
#include "Queue.h"
#include <QGraphicsItem>
#include <vector>
#include <queue>
#include <QPainter>

constexpr double sizeconst = 25;

/**
 * @brief The Node class Abstract class that represents a node in a network
 */
class Node : public QGraphicsItem
{
public:
    Node(int address, std::vector<int> queue);
    ~Node();

    void runOneTick();
    void receive(Packet* packet);
    void receivePackets();
    void initializeRoutingTable();
    virtual void processPacket(Packet *packet = nullptr) = 0;

    int getAddress() const;
    int dummyStat() const;
    void addLink(Link* link);

    /**
     * @brief getLastPacketAge
     * @return age of last received packet in ticks
     */
    int getLastPacketAge() const;

    /**
     * @brief getBufferSize
     * @return number of packets waiting their turn in the node's buffer
     */
    int getBufferSize() const;

    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    QRectF boundingRect() const override { return QRectF(-sizeconst, -sizeconst, sizeconst*2, sizeconst*2); }

protected:
    void drawTopText(QPainter*, QString);
    void drawBottomText(QPainter*, QString);

    std::vector<Link*> links_;
    Queue* packets_;
    int address_;
    std::vector<Packet*> received_;
    std::map<int, Link*> lookupTable_;
    Network* network_;
    int lastPacketAge_ = 0;
    Application* application_;
    bool lastPacketStatus_ = true;
};

#endif // NODE_H

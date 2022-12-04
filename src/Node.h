#ifndef NODE_H
#define NODE_H

#include "Link.h"
#include "Packet.h"
#include "Network.h"
#include "Application.h"
#include <QGraphicsItem>
#include <vector>
#include <queue>
#include <QPainter>

#define sizeconst 25


class Node : public QGraphicsItem
{
public:
    Node(int address);
    ~Node(){}

    virtual void runOneTick() = 0;
    void receive(Packet* packet);
    void receivePackets();
    void initializeRoutingTable();
    virtual void processPacket(Packet *packet) = 0;

    int getAddress() const;
    int dummyStat() const;

    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
protected:
    std::vector<Link*> links_;
    std::vector<Packet*> packets_;
    int address_;
    std::vector<Packet*> received_;
    std::map<int, Link*> lookupTable_;
    Network* network_;
    Application* application_;
};

#endif // NODE_H

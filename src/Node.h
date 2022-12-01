#ifndef NODE_H
#define NODE_H

#include "Link.h"
#include "Packet.h"
#include "Network.h"
#include <QGraphicsItem>
#include <vector>
#include <queue>
#include "qpainter.h"

#define sizeconst 25


class Node : public QGraphicsItem
{
public:
    Node(int address);
    ~Node(){}

    void runOneTick();
    void receive(Packet* packet);
    void receivePackets();
    void initializeRoutingTable();
    virtual void processPacket(Packet *packet) = 0;

    int getAddress() const;
private:
    std::vector<Link*> links_;
    std::vector<Packet*> packets_;
    int address_;
    std::vector<Packet*> received_;
    std::map<int, Link*> lookupTable_;
    Network* network_;
};

#endif // NODE_H

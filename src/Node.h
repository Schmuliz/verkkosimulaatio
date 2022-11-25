#ifndef NODE_H
#define NODE_H

#include "Link.h"
#include "Packet.h"
#include <QGraphicsItem>
#include <vector>

class Node : public QGraphicsItem
{
public:
    Node(int address);

    void runOneTick();
    void receive(Packet* packet);
    void receivePackets();
    virtual void processPacket(Packet *packet) = 0;
private:
    std::vector<Link*> links;
    std::vector<Packet*> packets;
    int address;
    std::vector<Packet*> received;
    std::map<int, Link*> lookupTable;
};

#endif // NODE_H

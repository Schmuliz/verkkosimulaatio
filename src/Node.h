#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <vector>

class Node : public QGraphicsItem
{
public:
    Node(int address);
    ~Node();
    void runOneTick();
    void receive(Packet packet);
    void receivePackets();
    void processPacket(Packet packet) = 0;
private:
    std::vector<Link*> links;
    std::vector<Packet*> packets;
    int address;
    std:vector<Packet*> received;
};

#endif // NODE_H

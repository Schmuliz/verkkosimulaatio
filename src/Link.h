#ifndef LINK_H
#define LINK_H

#include <QGraphicsItem>
#include <vector>

class Link : public QGraphicsItem
{
public:
    Link(Node* node1, Node* node2, double transmissionSpeed, double propagationDelay);
    ~Link();
    void runOneTick();
    int receive(Packet);
    void receivePackets();
private:
    double transmissionSpeed;
    double propagationDelay;
    Node* node1;
    Node* node2;
    std::vector<Packet*> packets;
    Packet* inTransmission;
};

#endif // LINK_H

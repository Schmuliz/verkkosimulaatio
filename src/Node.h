#ifndef NODE_H
#define NODE_H

#include "Link.h"
#include "Packet.h"
#include <QGraphicsItem>
#include <vector>
#include "qpainter.h"

class Node : public QGraphicsItem
{
public:
    Node(int address);
    ~Node(){}

    void runOneTick();
    void receive(Packet* packet);
    void receivePackets();
    virtual void processPacket(Packet *packet) = 0;

    //QT inherited functions, might be overridden by different types of nodes
    QRectF boundingRect() const override;
    void paint(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget) override;

private:
    std::vector<Link*> links_;
    std::vector<Packet*> packets_;
    int address_;
    std::vector<Packet*> received_;
    std::map<int, Link*> lookupTable_;
};

#endif // NODE_H

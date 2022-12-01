#ifndef LINK_H
#define LINK_H

//#include "Node.h"
#include "Packet.h"
#include <QGraphicsItem>
#include <QQueue>
#include <cmath>
#include <QDebug>

class Node; // forward definition, can not include normally

/**
 * @brief The Link class is a one-directional edge between nodes.
 * Goes from node1 to node 2
 */
class Link : public QGraphicsItem
{
public:
    Link(Node* node1, Node* node2, double transmissionSpeed, double propagationDelay);
    ~Link();

    /**
     * @brief runOneTick advances pakcets in packets_ according to
     * propagation delay. If the firs packet in the queue is transmitted,
     * move it to the next node
     */
    void runOneTick();

    /**
     * @brief receive sets the value of inTransmission to packet if there is no packet in transmission
     * @param packet
     * @return 1 if packet was received, 0 if packet couldn't be received
     */
    int receive(Packet* packet);

    /**
     * @brief receivePackets advances the packet in inTransmission and moves it to packets_
     * when it is completely transmitted from the sender node to this link.
     */
    void receivePackets();

    const Node* getDestination() const;
    const double getTransmissionSpeed() const;
    const double getPropagationDelay() const;

    // virtual mehtods inherited from Qt that must be implemented
    QRectF boundingRect() const override;
    void paint(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget) override;

    int dummyStat() const;
private:
    double transmissionSpeed_;
    double propagationDelay_;
    Node* node1_;
    Node* node2_;
    QQueue<Packet*> packets_;
    Packet* inTransmission_ = nullptr;
};

#endif // LINK_H

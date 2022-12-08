#ifndef LINK_H
#define LINK_H

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

    /**
     * @brief getCumulativeThroughput
     * @return amount of bits that have gone through this link
     */
    int getCumulativeThroughput() const;
    /**
     * @brief getUtilization
     * @return percentage of the link throughput that is currently used (1.0 = 100%)
     */
    double getUtilization() const;

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

    /**
     * @brief maxThroughput_, theoretical maximum amount of bits in the link
     */
    double maxThroughput_;

    /**
     * @brief cumulative throughput (in bits) of packets going through the link.
     * Packets size's are counted when when they leave the link
     */
    int cumulativeThroughput_ = 0;
    /**
     * @brief current throughput (in bits) of packets in the link.
     * The packet in inTransmission_ is also counted
     */
    int currentThroughput_ = 0;

};

#endif // LINK_H

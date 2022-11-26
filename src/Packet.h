#ifndef PACKET_H
#define PACKET_H

#include <QGraphicsItem>

class Packet /*: public QGraphicsItem */
{
public:
    Packet(int id, int source, int destination, int size, int age);
    void runOneTick() {} // not used for anything right now
    const int ID;
    const int sourceAddress;
    const int destinationAddress;
    const int size;
    const int age;
    double transmitted;
    double received;
};

#endif // PACKET_H

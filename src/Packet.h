#ifndef PACKET_H
#define PACKET_H

#include <QGraphicsItem>

class Packet
{
public:
    Packet(int source, int destination, int size);
    void runOneTick();
    const int sourceAddress;
    const int destinationAddress;
    const int size;
    int getAge() const;
    double transmitted = 0.0;
    double received = 0.0;
private:
    int age_ = 0;
};

#endif // PACKET_H

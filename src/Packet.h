#ifndef PACKET_H
#define PACKET_H

#include <QGraphicsItem>

class Packet /*: public QGraphicsItem */
{
public:
    Packet(int id, int source, int destination, int size, int age);
    ~Packet();
    void runOneTick();
private:
    int ID;
    int sourceAddress;
    int destinationAddress;
    int size;
    int age;
    double transmitted;
    double received;
};

#endif // PACKET_H

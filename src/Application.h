#ifndef APPLICATION_H
#define APPLICATION_H

#include "Packet.h"


class Application
{
public:
    Packet* packet_generator();
private:
    double transmission_interval;
};

#endif // APPLICATION_H

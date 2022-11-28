#ifndef APPLICATION_H
#define APPLICATION_H

#include "Packet.h"


class Application
{
public:
    Application(int id);
    Packet* packet_generator();
private:
    double transmission_interval;
};

#endif // APPLICATION_H

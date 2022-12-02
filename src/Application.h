#ifndef APPLICATION_H
#define APPLICATION_H

#include "Packet.h"


class Application
{
public:
    Application() {}; // delete me during AppType1 implementation
    Application(int id); // also me, this is supposed to be abstract class
    Packet* packet_generator();
private:
    double transmission_interval;
};

#endif // APPLICATION_H

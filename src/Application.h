#ifndef APPLICATION_H
#define APPLICATION_H

#include "Packet.h"

class Application
{
public:
    Application(){}
    ~Application(){}
    virtual Packet* packetGenerator(int, int, int) = 0;
private:
    double transmissionInterval;
};

class TestApplication : public Application
{
public:
    TestApplication();
    ~TestApplication(){}
    Packet* packetGenerator(int, int, int);
private:
    int counter_ = 0;
};

/*
class RespondingApplication : public Application
{
public:
    RespondingApplication(int id);
    ~RespondingApplication(){}
    Packet* packet_generator();
};

class SendingApplication : public Application
{
    SendingApplication(int id);
    ~SendingApplication(){}
    Packet* packet_generator();
};

class ReceivingApplication : public Application
{
    ReceivingApplication(int id);
    ~ReceivingApplication(){}
    Packet* packet_generator();
};
*/

#endif // APPLICATION_H

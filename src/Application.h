#ifndef APPLICATION_H
#define APPLICATION_H

#include "Packet.h"
#include <vector>
#include <cstdlib>

class Application
{
public:
    Application(std::vector<int> destinationAddresses, int transmissionInterval);
    ~Application(){}

    /**
     * @brief Virtual function that is called on every tick and
     * returns a pointer to a Packet if one is generated
     * or nullptr if no packet is generated.
     */
    virtual Packet* packetGenerator(int) = 0;
protected:
    std::vector<int> destinationAddresses_;
    int transmissionInterval_;

};

class SimpleApplication : public Application
{
public:
    SimpleApplication(std::vector<int> destinationAddresses, int transmissionInterval);
    ~SimpleApplication(){}
    Packet* packetGenerator(int source);
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

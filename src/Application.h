#ifndef APPLICATION_H
#define APPLICATION_H

#include "Packet.h"
#include <vector>
#include <cstdlib>

/**
 * @brief The Application class is an abstract class that is inherited by different types of applications
 */

class Application
{
public:
    Application(std::vector<int> destinationAddresses, int transmissionInterval, int packetSize);
    ~Application(){}

    /**
     * @brief The packetGenerator function is called on every tick and
     * returns a vector of Packet pointers created
     * or an empty vector if none were created
     * @param source: address of the node that is creating the packet
     */
    virtual Packet* packetGenerator(int source, Packet* currentPacket = nullptr) = 0;
protected:
    std::vector<int> destinationAddresses_;
    int transmissionInterval_;
    int packetSize_;
};

/**
 * @brief The SimpleApplication class sends a single packet every tranmissionInterval_ ticks
 */
class SimpleApplication : public Application
{
public:
    SimpleApplication(std::vector<int> destinationAddresses, int transmissionInterval, int packetSize);
    ~SimpleApplication(){}
    Packet* packetGenerator(int source, Packet* currentPacket);
private:
    int counter_;
};


/**
 * @brief The BurstApplication class sends packets in bursts where packets are
 * first sent for multiple ticks in a row and then packet sending goes on a break
 */
class BurstApplication : public Application
{
public:
    BurstApplication(std::vector<int> destinationAddresses, int transmissionInterval, int packetSize);
    ~BurstApplication(){}
    Packet* packetGenerator(int source, Packet* currentPacket);
private:
    /**
      *@brief currentDestination_ is the address of the node
      * that is currently being sent a burst if packetsLeftThisBurst_ > 0,
      */
    int currentDestination_;
    int packetsLeftThisBurst_ = 0;
    int counter_;
};


/**
 * @brief The RespondingApplication class sends packets when it is sent packets
 */
class RespondingApplication : public Application
{
public:
    RespondingApplication(std::vector<int> destinationAddresses, int transmissionInterval, int packetSize);
    ~RespondingApplication(){}
    Packet* packetGenerator(int source, Packet* currentPacket);
};

/**
 * @brief The ReceivingApplication class only receives packets
 */

class ReceivingApplication : public Application
{
public:
    ReceivingApplication(std::vector<int> destinationAddresses = {}, int transmissionInterval = 0, int packetSize = 0);
    ~ReceivingApplication(){}
    Packet* packetGenerator(int source, Packet* currentPacket);
};


#endif // APPLICATION_H

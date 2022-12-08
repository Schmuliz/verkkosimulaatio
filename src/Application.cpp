#include "Application.h"

// Application

Application::Application(std::vector<int> destinationAddresses, int transmissionInterval, int packetSize)
    : destinationAddresses_(destinationAddresses), transmissionInterval_(transmissionInterval), packetSize_(packetSize) {}

// SimpleApplication

SimpleApplication::SimpleApplication(std::vector<int> destinationAddresses, int transmissionInterval, int packetSize)
    : Application(destinationAddresses, transmissionInterval, packetSize), counter_(rand() % transmissionInterval) {}

/**
 * @brief SimpleApplication::packetGenerator will generate packets depending on a predetermined
 * interval; ignores the incoming packet
 * @return new packet to be sent or nullptr if nothing is sent
 */
Packet* SimpleApplication::packetGenerator(int source, Packet* currentPacket) {
    if (counter_ == transmissionInterval_) {
        counter_ = 0;

        int packetDestination = destinationAddresses_[rand() % destinationAddresses_.size()];
        Packet* p = new Packet(source, packetDestination, packetSize_);
        return p;
    }
    counter_++;
    return nullptr;
}

// BurstApplication

BurstApplication::BurstApplication(std::vector<int> destinationAddresses, int transmissionInterval, int packetSize)
    : Application(destinationAddresses, transmissionInterval, packetSize) {
    counter_ = rand() % transmissionInterval;
}

/**
 * @brief BurstApplication::packetGenerator sends a burst of packets every transmissionInterval_, otherwise
 * sends a nullptr. Updates how many packets are left in this burst or how long until next burst, depending
 * on whether a burst is ongoing when called.
 */
Packet* BurstApplication::packetGenerator(int source, Packet* currentPacket) {
    if (packetsLeftThisBurst_ != 0) {
        packetsLeftThisBurst_--;
        Packet* p = new Packet(source, currentDestination_, packetSize_);
        return p;
    } else {
        if (counter_ == transmissionInterval_) {
            currentDestination_ = destinationAddresses_[rand() % destinationAddresses_.size()];
            counter_ = 0;
            packetsLeftThisBurst_ = rand() % 3 + 3;
        }
        counter_++;
        return nullptr;
    }
}

// RespondingApplication

RespondingApplication::RespondingApplication(std::vector<int> destinationAddresses, int transmissionInterval, int packetSize)
    : Application(destinationAddresses, transmissionInterval, packetSize) {}

/**
 * @brief RespondingApplication::packetGenerator will generate a new packet only when
 * it receives a packet for itself; it responds to packets
 * @return new packet to be sent or nullptr, if it itself received a nullptr
 */
Packet* RespondingApplication::packetGenerator(int source, Packet* currentPacket) {
    if (currentPacket == nullptr) {
        return nullptr;
    }
    if (currentPacket->destinationAddress == source) {
        Packet* p = new Packet(source, currentPacket->sourceAddress, packetSize_);
        return p;
    }
    return nullptr;
}

// ReceivingApplication

ReceivingApplication::ReceivingApplication(std::vector<int> destinationAddresses, int transmissionInterval, int packetSize)
    : Application(destinationAddresses, transmissionInterval, packetSize) {}

/**
 * @brief ReceivingApplication::packetGenerator will always return nullptr; this application does not send anything
 * @return always a nullptr
 */
Packet* ReceivingApplication::packetGenerator(int source, Packet* currentPacket) {
    return nullptr;
}

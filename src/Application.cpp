#include "Application.h"

// Application

Application::Application(std::vector<int> destinationAddresses, int transmissionInterval)
    : destinationAddresses_(destinationAddresses), transmissionInterval_(transmissionInterval) {}

// TestApplication

SimpleApplication::SimpleApplication(std::vector<int> destinationAddresses, int transmissionInterval)
    : Application(destinationAddresses, transmissionInterval), counter_(rand() % transmissionInterval) {}

Packet* SimpleApplication::packetGenerator(int source, Packet* currentPacket) {
    if (counter_ == transmissionInterval_) {
        counter_ = 0;

        int packetDestination = destinationAddresses_[rand() % destinationAddresses_.size()];
        Packet* p = new Packet(source, packetDestination, 10);
        return p;
    }
    counter_++;
    return nullptr;
}

// BurstApplication

BurstApplication::BurstApplication(std::vector<int> destinationAddresses, int transmissionInterval)
    : Application(destinationAddresses, transmissionInterval) {
    counter_ = rand() % transmissionInterval;
}

Packet* BurstApplication::packetGenerator(int source, Packet* currentPacket) {
    if (packetsLeftThisBurst_ != 0) {
        packetsLeftThisBurst_--;
        Packet* p = new Packet(source, currentDestination_, 10);
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

RespondingApplication::RespondingApplication(std::vector<int> destinationAddresses, int transmissionInterval)
    : Application(destinationAddresses, transmissionInterval) {}

Packet* RespondingApplication::packetGenerator(int source, Packet* currentPacket) {
    if (currentPacket == nullptr) {
        return nullptr;
    }
    if (currentPacket->destinationAddress == source) {
        Packet* p = new Packet(source, currentPacket->sourceAddress, 10);
        return p;
    }
    return nullptr;
}

// ReceivingApplication

ReceivingApplication::ReceivingApplication(std::vector<int> destinationAddresses, int transmissionInterval)
    : Application(destinationAddresses, transmissionInterval) {}

Packet* ReceivingApplication::packetGenerator(int source, Packet* currentPacket) {
    return nullptr;
}

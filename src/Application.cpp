#include "Application.h"

// Application

Application::Application(std::vector<int> destinationAddresses, int transmissionInterval)
    : destinationAddresses_(destinationAddresses), transmissionInterval_(transmissionInterval) {}

// TestApplication

SimpleApplication::SimpleApplication(std::vector<int> destinationAddresses, int transmissionInterval)
    : Application(destinationAddresses, transmissionInterval), counter_(rand() % transmissionInterval) {}

std::vector<Packet*> SimpleApplication::packetGenerator(int source, std::vector<Packet*> receivedPackets) {
    if (counter_ == transmissionInterval_) {
        counter_ = 0;

        int packetDestination = rand() % destinationAddresses_.size();
        Packet* p = new Packet(source, packetDestination, 10, 0);
        return std::vector<Packet*>{p};
    }
    counter_++;
    return std::vector<Packet*>{};
}

// BurstApplication

BurstApplication::BurstApplication(std::vector<int> destinationAddresses, int transmissionInterval)
    : Application(destinationAddresses, transmissionInterval) {
    counter_ = rand() % transmissionInterval;
}

std::vector<Packet*> BurstApplication::packetGenerator(int source, std::vector<Packet*> receivedPackets) {
    if (packetsLeftThisBurst_ != 0) {
        packetsLeftThisBurst_--;
        Packet* p = new Packet(source, currentDestination_, 10, 0);
        return std::vector<Packet*>{p};
    } else {
        if (counter_ == transmissionInterval_) {
            currentDestination_ = rand() % destinationAddresses_.size();
            counter_ = 0;
            packetsLeftThisBurst_ = rand() % 3 + 3;
        }
        counter_++;
        return std::vector<Packet*>{};
    }
}

// RespondingApplication

RespondingApplication::RespondingApplication(std::vector<int> destinationAddresses, int transmissionInterval)
    : Application(destinationAddresses, transmissionInterval) {}

std::vector<Packet*> RespondingApplication::packetGenerator(int source, std::vector<Packet*> receivedPackets) {
    if (receivedPackets.size() > 0) {
        std::vector<Packet*> responsePacketList;
        for (auto packet : receivedPackets) {
            if (packet->destinationAddress == source) {
                Packet* p = new Packet(source, packet->sourceAddress, 10, 0);
                responsePacketList.push_back(p);
            }
        }
        if (receivedPackets.size() > 0) {
            return responsePacketList;
        }
    }
    return std::vector<Packet*>{};
}

// ReceivingApplication

ReceivingApplication::ReceivingApplication(std::vector<int> destinationAddresses, int transmissionInterval)
    : Application(destinationAddresses, transmissionInterval) {}

std::vector<Packet*> ReceivingApplication::packetGenerator(int source, std::vector<Packet*> receivedPackets) {
    return std::vector<Packet*>{};
}

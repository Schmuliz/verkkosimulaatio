#include "Application.h"

//Application

Application::Application(std::vector<int> destinationAddresses, int transmissionInterval)
    : destinationAddresses_(destinationAddresses), transmissionInterval_(transmissionInterval) {}

//TestApplication

SimpleApplication::SimpleApplication(std::vector<int> destinationAddresses, int transmissionInterval)
    : Application(destinationAddresses, transmissionInterval) {}

Packet* SimpleApplication::packetGenerator(int source) {
    if (counter_ == transmissionInterval_) {
        counter_ = 0;

        int packetDestination = rand() % destinationAddresses_.size();
        Packet* p = new Packet(source, packetDestination, 10);
        return p;
    }
    counter_++;
    return nullptr;
}

/*

//RespondingApplication


//SendingApplication


//ReceivingApplication


*/

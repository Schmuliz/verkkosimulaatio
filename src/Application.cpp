#include "Application.h"
#include <iostream>

//Application

//TestApplication

TestApplication::TestApplication(){}

Packet* TestApplication::packetGenerator(int packetId, int source, int destination) {
    if (counter_ == 100) {
        counter_ = 0;
    }
    counter_++;

    std::cout << "Hello" << std::endl;
    Packet* p = new Packet(packetId, source, destination, 10, 0);
    return p;
}

/*

//RespondingApplication


//SendingApplication


//ReceivingApplication


*/

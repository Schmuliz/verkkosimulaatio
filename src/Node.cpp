#include "Node.h"

Node::Node(int address) :
    address(address) {};

void Node::runOneTick() {
    if (!packets.empty()) {
        int dst = packets.front()->destinationAddress;

        if (dst == address) {
            this->processPacket(packets.front());
            packets.erase(packets.begin());
            return;
        }

        Link* destinationLink = lookupTable[dst];
        if (destinationLink->receive(packets.front())) {
            packets.erase(packets.begin());
        }
    }
}

void Node::receive(Packet* packet) {
    packets.push_back(packet);
}

void Node::receivePackets() {
    while (!received.empty()) {
        packets.push_back(received.front());
        received.erase(received.begin());
    }
}

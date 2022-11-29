#include "Node.h"

Node::Node(int address) :
    address_(address) {}

void Node::runOneTick() {
    if (!packets_.empty()) {
        int dst = packets_.front()->destinationAddress;

        if (dst == address_) {
            this->processPacket(packets_.front());
            packets_.erase(packets_.begin());
            return;
        }

        Link* destinationLink = lookupTable_[dst];
        if (destinationLink->receive(packets_.front())) {
            packets_.erase(packets_.begin());
        }
    }
}

void Node::receive(Packet* packet) {
    packets_.push_back(packet);
}

void Node::receivePackets() {
    while (!received_.empty()) {
        packets_.push_back(received_.front());
        received_.erase(received_.begin());
    }
}

int Node::getAddress() const {
    return address_;
}

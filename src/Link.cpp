#include "Link.h"
#include "Node.h"

Link::Link(Node* node1,
           Node* node2,
           double transmissionSpeed,
           double propagationDelay)
    : node1_(node1), node2_(node2), transmissionSpeed_(transmissionSpeed),
      propagationDelay_(propagationDelay) {}

Link::~Link() {
    for (auto packet : packets_) {
        delete packet;
    }
    delete inTransmission_;
}
/**
 * @brief Link::runOneTick advances pakcets in Link::packets_
 * according to propagation delay. If the firs packet in the queue
 * is transmitted, move it to the next node
 */
void Link::runOneTick() {
    if (std::size(packets_) > 0) {
        // advance packets
        for (auto packet : packets_) {
            packet->transmitted += 1 / propagationDelay_;
        }
        // if the first packet in the queue is transmitted, move it to the next node
        if (packets_.head()->transmitted >= 1) {
            packets_.head()->transmitted = 0;
            node2_->receive(packets_.dequeue());
        }
    }
}

int Link::receive(Packet* packet) {
    if (inTransmission_ == nullptr) {
        inTransmission_ = packet;
        return 1;
    }
    else return 0;
}

void Link::receivePackets() {
    if (inTransmission_ != nullptr) {
        if (inTransmission_->received >= 1) {
            inTransmission_->received = 0;
            packets_.enqueue(inTransmission_);
            inTransmission_ = nullptr;
        }
        else {
            inTransmission_->received += transmissionSpeed_ / inTransmission_->size;
        }
    }
}

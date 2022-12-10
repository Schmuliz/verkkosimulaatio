#include "Queue.h"

/**
 * @brief Queue::~Queue deconstructor will destoy all packets in the queue
 */
Queue::~Queue() {
    for (auto packet : *this) {
        delete packet;
    }
}


NoDropQueue::NoDropQueue()
    : Queue() {}

/**
 * @brief NoDropQueue::maybe_push_back will always add packet; nothing is dropped
 * @param packet to be added to the queue
 */
void NoDropQueue::maybe_push_back(Packet* packet) {
    push_back(packet);
}


RandomDropQueue::RandomDropQueue(int chanceOfDrop)
    : Queue(), chanceOfDrop_(chanceOfDrop) {}

/**
 * @brief RandomDropQueue::RandomDropQueue drops packet with 0-100 % probability (given when
 * initializing a RandomDropQueue)
 * @param packet to be added or dropped
 */
void RandomDropQueue::maybe_push_back(Packet* packet) {
    if (1 + rand() % 100 < chanceOfDrop_) {
        delete packet;
    } else {
        push_back(packet);
    }
}


SizeConstraintQueue::SizeConstraintQueue(int maxSize)
    : Queue(), maxSize_(maxSize) {}

/**
 * @brief SizeConstraintQueue::maybe_push_back pushes packet to queue if queue size
 * is not at maxSize, which is given during initialization; otherwise drops packet
 * @param packet to be added or dropped
 */
void SizeConstraintQueue::maybe_push_back(Packet* packet) {
    if (size() >= maxSize_) {
        delete packet;
    } else {
        push_back(packet);
    }
}

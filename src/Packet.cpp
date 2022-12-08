#include "Packet.h"

Packet::Packet(int source, int destination, int size)
    : sourceAddress(source), destinationAddress(destination),
      size(size) {}


/**
 * @brief Packet::runOneTick increments age of the packet by one, called by Packet's owner
 * (a Link or a Node)
 */
void Packet::runOneTick() { age_++; }

/**
 * @brief Packet::getAge
 * @return interger packet's age in ticks
 */
int Packet::getAge() const { return age_; }

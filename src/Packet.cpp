#include "Packet.h"

Packet::Packet(int source, int destination, int size)
    : sourceAddress(source), destinationAddress(destination),
      size(size) {}

void Packet::runOneTick() { age_++; }

int Packet::getAge() const { return age_; }

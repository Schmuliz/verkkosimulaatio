#include "Packet.h"

Packet::Packet(int source, int destination, int size, int age)
    : sourceAddress(source), destinationAddress(destination),
      size(size), age(age), transmitted(0.0), received(0.0) {}

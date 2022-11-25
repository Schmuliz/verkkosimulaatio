#include "Packet.h"

Packet::Packet(int id, int source, int destination, int size, int age)
    : ID(id), sourceAddress(source), destinationAddress(destination),
      size(size), age(age), transmitted(0.0), received(0.0) {}

#include "EndHost.h"

RoutingEndHost::RoutingEndHost(int address, Application applicationType)
    : Router(address), application_(applicationType) {}

void RoutingEndHost::processPacket(Packet *packet) {}

EndHost::EndHost(int address, Application applicationType)
    : Node(address), application_(applicationType) {}

void EndHost::processPacket(Packet *packet) {}

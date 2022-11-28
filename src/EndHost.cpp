#include "EndHost.h"

RoutingEndHost::RoutingEndHost(int address, int applicationid)
    : Router(address), application_(applicationid) {}

void RoutingEndHost::processPacket(Packet *packet) {}

EndHost::EndHost(int address, int applicationid)
    : Node(address), application_(applicationid) {}

void EndHost::processPacket(Packet *packet) {}

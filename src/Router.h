#ifndef ROUTER_H
#define ROUTER_H

class Router : public Node
{
private:
    void nexthop(Packet* packet);
};

#endif // ROUTER_H

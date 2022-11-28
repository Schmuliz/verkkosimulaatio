#ifndef ENDHOST_H
#define ENDHOST_H

#include "Node.h"
#include "Application.h"
#include "Router.h"

class EndHost : public Node
{
public:
    EndHost(int address, int applicationid);
    ~EndHost(){}
    void processPacket(Packet *packet) override;
private:
    Application application_;
};

class RoutingEndHost : public Router
{
public:
    RoutingEndHost(int address, int applicationid);
    ~RoutingEndHost(){}
    void processPacket(Packet *packet) override;
private:
    Application application_;
};


#endif // ENDHOST_H

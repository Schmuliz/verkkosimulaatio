#ifndef NETWORK_H
#define NETWORK_H

#include "Link.h"
#include "Application.h"
#include "EndHost.h"
#include "Router.h"
#include <QGraphicsItem>
#include <vector>


class Network
{
public:
    Network();
    ~Network();
    void runOneTick();
    void createRouter(int address);
    void createEndHost(int address, Application application);
    void createRoutingEndHost(int address, Application application);
    void createLink(Node* n1, Node* n2, double transmissionSpeed, double propagationDelay);
private:
    std::vector<Node*> nodes_;
    std::vector<Link*> links_;
};

#endif // NETWORK_H

#ifndef ENDHOST_H
#define ENDHOST_H

#include "Node.h"
#include "Application.h"
#include "Router.h"

class EndHost : public Node
{
private:
    Application application;
};

class RoutingEndHost : public Router
{
private:
    Application application;
};


#endif // ENDHOST_H

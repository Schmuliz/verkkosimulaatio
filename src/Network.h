#ifndef NETWORK_H
#define NETWORK_H

#include <QGraphicsItem>
#include <vector>

class Network : public QGraphicsItem
{
public:
    Network();
    ~Network();
    void runOneTick();
private:
    std::vector<Node*> nodes;
    std::vector<Link*> links;
};

#endif // NETWORK_H

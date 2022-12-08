#ifndef NETWORK_H
#define NETWORK_H

#include "Link.h"
#include <QGraphicsItem>
#include <vector>
#include <iostream>
#include <QString>
#include <QMap>

class Network
{
public:
    Network() {};
    Network(QString filename);
    ~Network();
    void runOneTick();
    void addNode(Node* n);
    void addLink(int a, int b, double bandwidth, double delay);
    void initializeRoutingTables() const;
    void populateScene(QGraphicsScene* scene);

private:
    QMap<int, Node*> nodes_; // address-node
    std::vector<Link*> links_;
};

#endif // NETWORK_H

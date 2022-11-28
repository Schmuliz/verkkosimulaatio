#include "Network.h"
#include <QJsonDocument>
#include <QFile>


Network::Network(QString filename) {
    qInfo() << "Loading network from file";
    QFile networkFile(filename);
    qInfo() << "network file size: " << networkFile.size();
}

Network::~Network() {
    for(auto n : nodes_) {
        delete n;
    }
    for(auto l : links_) {
        delete l;
    }
}

void Network::runOneTick() {
    for (auto const& node : nodes_) {
        node->runOneTick();
    }
    for (auto const& link : links_) {
        link->runOneTick();
    }
    for (auto const& node : nodes_) {
         node->receivePackets();
    }
    for (auto const& link : links_) {
        link->receivePackets();
    }
}

void Network::createRouter(int address) {
    Router* router = new Router(address);
    nodes_.push_back(router);
}

void Network::createEndHost(int address, Application application) {
    EndHost* endHost = new EndHost(address, application);
    nodes_.push_back(endHost);
}

void Network::createLink(Node* n1, Node* n2, double transmissionSpeed, double propagationDelay) {
    Link* link = new Link(n1, n2, transmissionSpeed, propagationDelay);
    links_.push_back(link);
}

void Network::createRoutingEndHost(int address, Application application) {
    RoutingEndHost* routingEndHost = new RoutingEndHost(address, application);
    nodes_.push_back(routingEndHost);
}


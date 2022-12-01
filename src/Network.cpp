#include "Network.h"
#include "EndHost.h"
#include "RoutingEndHost.h"
#include <QJsonDocument>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>

Node* createNodeFromJsonObject(QJsonObject obj) {
    Node* node;

    int address = obj["address"].toInt();
    int posx = obj["posx"].toInt();
    int posy = obj["posy"].toInt();
    int applicationid = obj["application"].toInt();
    int routing = obj["routing"].toInt();

    if(applicationid && routing) {
        node = new RoutingEndHost(address, applicationid);
    }
    else if (applicationid) {
        node = new EndHost(address, applicationid);
    }
    else if (routing) {
        node = new Router(address);
    }
    else {
        throw "unknown node type";
    }

    node->setPos(posx, posy);
    return node;
}

void addJsonLinkToNetwork(Network *net, QJsonObject obj) {
    int hosta = obj["hosta"].toInt();
    int hostb = obj["hostb"].toInt();
    double bandwidth = obj["bandwidth"].toDouble();
    double delay = obj["delay"].toDouble();

    net->addLink(hosta, hostb, bandwidth, delay);
}

Network::Network(QString filename) {
    qInfo() << "Loading network from file";

    // open the file, read it
    QFile networkFile(filename);
    if(!networkFile.open(QIODevice::ReadOnly | QIODevice::Text))
        throw "Opening config file failed";
    qInfo() << "network file size: " << networkFile.size();
    QByteArray barr = networkFile.readAll();

    // load json
    QJsonDocument doc = QJsonDocument::fromJson(barr);
    qInfo() << "the loaded json doc: " << doc.toJson();

    // parse json, create elements for each node and link, and initialize routing tables for nodes
    try {
        QJsonArray nodeArr = doc["nodes"].toArray();
        for(auto n : nodeArr) {
            QJsonObject jn = n.toObject();
            qInfo() << jn;
            Node* node = createNodeFromJsonObject(jn);
            addNode(node);
        }

        QJsonArray linkArr = doc["links"].toArray();
        for(auto l : linkArr) {
            QJsonObject jl = l.toObject();
            qInfo() << jl;
            addJsonLinkToNetwork(this, jl);
        }

        this->initializeRoutingTables();
    }
    catch (std::exception) {
        throw "failed to parse network configuration";
    }
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

void Network::addNode(Node *node) {
    nodes_.insert(node->getAddress(), node);
}

void Network::addLink(int a, int b, double bandwidth, double delay) {
    // lookup nodes based on address
    Node* hosta = nodes_[a];
    Node* hostb = nodes_[b];
    Link* link = new Link(hosta, hostb, bandwidth, delay);
    links_.push_back(link);
}

void Network::initializeRoutingTables() const {
    for (auto node : nodes_) {
        node->initializeRoutingTable();
    }
}

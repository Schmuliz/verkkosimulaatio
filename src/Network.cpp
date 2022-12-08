#include "Network.h"
#include "EndHost.h"
#include "RoutingEndHost.h"
#include <QJsonDocument>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QGraphicsScene>

/**
 * @brief createNodeFromJsonObject Parses QJsonObject for a node
 * @param obj The QJsonObject
 * @return returns pointer to the created node
 */
Node* createNodeFromJsonObject(QJsonObject obj) {
    Node* node;

    int address = obj["address"].toInt();
    int posx = obj["posx"].toInt();
    int posy = obj["posy"].toInt();
    QJsonArray application = obj["application"].toArray();
    std::vector<int> applicationparams;
    for(QJsonValue param : application) {
        applicationparams.push_back(param.toInt());
    }
    int routing = obj["routing"].toInt();

    if(applicationparams[0] && routing) {
        node = new RoutingEndHost(address, applicationparams);
    }
    else if (applicationparams[0]) {
        node = new EndHost(address, applicationparams);
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

/**
 * @brief addJsonLinkToNetwork takes Link parameters as a QJsonObject and uses them to create a Link which is added to the network
 * @param net pointer to the network we are constructing
 * @param obj JSON object which contains the Link's parameters
 */
void addJsonLinkToNetwork(Network *net, QJsonObject obj) {
    int hosta = obj["hosta"].toInt();
    int hostb = obj["hostb"].toInt();
    double bandwidth = obj["bandwidth"].toDouble();
    double delay = obj["delay"].toDouble();

    net->addLink(hosta, hostb, bandwidth, delay);
}

/**
 * @brief Network::Network constructs the network based on a JSON file in resources.qrc
 * @param filename name of the JSON file from which the network blueprint is read
 */
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

    // parse json, create elements for each node and link, and initialize routing tables for nodes
    try {
        QJsonArray nodeArr = doc["nodes"].toArray();
        for(auto n : nodeArr) {
            QJsonObject jn = n.toObject();
            Node* node = createNodeFromJsonObject(jn);
            addNode(node);
        }

        QJsonArray linkArr = doc["links"].toArray();
        for(auto l : linkArr) {
            QJsonObject jl = l.toObject();
            addJsonLinkToNetwork(this, jl);
        }

        this->initializeRoutingTables();
    }
    catch (std::exception) {
        throw "failed to parse network configuration";
    }
}

/**
 * @brief Network::~Network deconstructor deletes all Nodes and Links, and their
 * respective deconstructors destroy packets
 */
Network::~Network() {
    for(auto n : nodes_) {
        delete n;
    }
    for(auto l : links_) {
        delete l;
    }
}

/**
 * @brief Network::runOneTick For all Nodes and Links, first calls
 * runOneTick() and then, when all are done, calls receivePackets() and
 * this is done to make sure Nodes don't receive and pass forward a packet
 * within the same tick
 */
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

/**
 * @brief Network::addLink adds link to the netowrk based on addresses, populates node's links_ information
 * @param a node a address
 * @param b node b address
 * @param bandwidth link bandwidth
 * @param delay link delay
 */
void Network::addLink(int a, int b, double bandwidth, double delay) {
    // lookup nodes based on address
    Node* hosta = nodes_[a];
    Node* hostb = nodes_[b];
    Link* linka = new Link(hosta, hostb, bandwidth, delay);
    Link* linkb = new Link(hostb, hosta, bandwidth, delay);
    links_.push_back(linka);
    links_.push_back(linkb);
    hosta->addLink(linka);
    hostb->addLink(linkb);
}

/**
 * @brief Network::initializeRoutingTables Initialize all nodes' routing tables.
 */
void Network::initializeRoutingTables() const {
    for (auto node : nodes_) {
        node->initializeRoutingTable();
    }
}

/**
 * @brief Network::populateScene populates scene with this network
 * @param scene QGraphicsScene to populate
 */
void Network::populateScene(QGraphicsScene *scene) {
    for(auto link : links_) {
        scene->addItem(link);
    }
    for(auto node : nodes_) {
        scene->addItem(node);
    }
}

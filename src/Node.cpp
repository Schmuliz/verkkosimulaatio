#include "Node.h"
#include "Router.h"
#include <cstdlib>

Node::Node(int address) :
    address_(address) {
    setAcceptHoverEvents(true);
}

void Node::runOneTick() {
    if (!packets_.empty()) {
        int dst = packets_.front()->destinationAddress;

        if (dst == address_) {
            this->processPacket(packets_.front());
            packets_.erase(packets_.begin());
            return;
        }

        Link* destinationLink = lookupTable_[dst];
        if (destinationLink->receive(packets_.front())) {
            packets_.erase(packets_.begin());
        }
    }
}

void Node::receive(Packet* packet) {
    packets_.push_back(packet);
}

void Node::receivePackets() {
    while (!received_.empty()) {
        packets_.push_back(received_.front());
        received_.erase(received_.begin());
    }
}

int Node::getAddress() const {
    return address_;
}

// calculate the next link from this node for all destinations in the network using modified Dijkstra's algorithm, will only route packets through routers
void Node::initializeRoutingTable() {
    std::map<int, double> distances;
    std::map<int, bool> visited;
    std::map<int, Link*> lookupTable;

    // (currenty random) constant that is added to every edge weight
    // used to incentivize routes with less hops
    const double c = 100;

    // custom comparator for comparing pairs
    auto cmp = [](std::pair<const Node*, double> a, std::pair<const Node*, double> b) {
        return a.second <= b.second;
    };

    // min priority queue for (node, distance) pairs
    std::priority_queue<std::pair<const Node*, double>, std::vector<std::pair<const Node*, double>>, decltype(cmp)> queue(cmp);

    for (auto link : links_) { // add links to neighboring nodes
        lookupTable[link->getDestination()->getAddress()] = link;
        queue.push(std::pair(link->getDestination(), link->getPropagationDelay() + c));
    }

    while (!queue.empty()) {
        const Node* node = queue.top().first;
        double dist = queue.top().second;
        queue.pop();

        const Router* r = dynamic_cast<const Router*>(node); // used for checking if the node is a router
        if (r == nullptr) { // if node is not a router, don't consider its out-going links
            visited[node->getAddress()] = true;
        }
        else if (visited.count(node->getAddress()) == 0) { // the node has not been visited yet
            visited[node->getAddress()] = true;
            for (auto link : node->links_) {
                lookupTable[link->getDestination()->getAddress()] = lookupTable[node->getAddress()];
                double weight = link->getPropagationDelay() + c;
                queue.push(std::pair(link->getDestination(), dist + weight));
            }
        }
    }
    lookupTable_ = lookupTable;
}

int Node::dummyStat() const {
    return rand();
}

void Node::hoverMoveEvent(QGraphicsSceneHoverEvent *event) {
    setToolTip(QString::number(address_));
}

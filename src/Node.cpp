#include "Node.h"
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

// calculate the next link from this node for all destinations in the network using modified Dijkstra's algorithm
void Node::initializeRoutingTable() {
    std::map<int, double> distances;
    std::map<int, bool> visited;
    std::map<int, Link*> lookupTable;

    // (currenty random) constant used for calculating edge weights
    // in reality this should be correlated with the average amount of data that is going across the link
    double c = 100;

    // custom comparator for comparing pairs
    auto cmp = [](std::pair<const Node*, double> a, std::pair<const Node*, double> b) {
        return a.second <= b.second;
    };

    // min priority queue for (node, distance) pairs
    std::priority_queue<std::pair<const Node*, double>, std::vector<std::pair<const Node*, double>>, decltype(cmp)> queue(cmp);
    queue.push(std::pair(this, 0));

    while (!queue.empty()) {
        const Node* node = queue.top().first;
        double dist = queue.top().second;
        queue.pop();

        if (visited.count(node->getAddress()) == 0) { // the node has not been visited yet
            visited[node->getAddress()] = true;
            for (auto link : node->links_) {
                if (lookupTable.count(node->getAddress()) == 0) { // the current node does not have route to this node i.e. the node is this node
                    lookupTable[link->getDestination()->getAddress()] = link;
                }
                else {
                    lookupTable[link->getDestination()->getAddress()] = lookupTable[node->getAddress()];
                }
                double distance = link->getPropagationDelay() + c / link->getTransmissionSpeed();
                queue.push(std::pair(link->getDestination(), dist + distance));
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

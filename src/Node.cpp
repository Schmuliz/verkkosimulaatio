#include "Node.h"
#include "Router.h"
#include <cstdlib>


Node::Node(int address) :
    address_(address) {
    setAcceptHoverEvents(true);
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

/**
 * @brief Node::getAddress returns node's address
 * @return  the integer address
 */
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

/**
 * @brief Node::dummyStat returns random integer from node's scope
 * @return the random integer
 */
int Node::dummyStat() const {
    return rand();
}

int Node::getLastPacketAge() const { return lastPacketAge_; }
int Node::getBufferSize() const { return packets_.size(); }

void Node::hoverMoveEvent(QGraphicsSceneHoverEvent *event) {
    setToolTip(QString::number(address_));
}

/**
 * @brief Node::drawTopText draw text in a box above the node
 * @param painter qpainter to use
 * @param text qstring of the text
 */
void Node::drawTopText(QPainter* painter, QString text) {
    QRectF bottomrect(-sizeconst, sizeconst, sizeconst*2, sizeconst*2/3);
    bottomrect.translate(QPointF(0, 2));
    painter->fillRect(bottomrect, Qt::white);
    painter->setPen(QPen(Qt::black));
    painter->drawRect(bottomrect);
    painter->drawText(bottomrect, Qt::AlignCenter, text);
}

/**
 * @brief Node::drawBottomText draw text in a box below the node
 * @param painter qpainter to use
 * @param text qstring of the text
 */
void Node::drawBottomText(QPainter* painter, QString text) {

    // top text box
    QRectF toprect(-sizeconst, -sizeconst*5/3, sizeconst*2, sizeconst*2/3);
    toprect.translate(QPointF(0, -2));
    painter->fillRect(toprect, Qt::white);
    painter->setPen(QPen(Qt::black));
    painter->drawRect(toprect);
    painter->drawText(toprect, Qt::AlignCenter, text);
}

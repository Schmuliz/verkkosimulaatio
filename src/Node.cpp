#include "Node.h"
#include "Router.h"
#include <cstdlib>
#include <QDebug>

/**
 * @brief Node::Node constructor will parse queue type and initialize Queue* packets_
 * @param address integer address of this node
 * @param queue vector which contains id (type) and parameter(s) or queue
 */
Node::Node(int address, std::vector<int> queue) :
    address_(address) {
    setAcceptHoverEvents(true);

    int queueid = queue.at(0); // always safe to read
    switch (queueid) {
        case 1:
            packets_ = new NoDropQueue();
            break;
        case 2:
            packets_ = new RandomDropQueue(queue.at(1));
            break;
        case 3:
            packets_ = new SizeConstraintQueue(queue.at(1));
            break;
        default:
            throw "unkown queueid";
    }
}

/**
 * @brief Node::~Node deconstructor will delete all packets in received and delete packets_,
 * which is a Queue* and Queue's own deconstructor will in turn destroy its own packets
 */
Node::~Node() {
    delete packets_;
    for (auto packet : received_) {
        delete packet;
    }
}

/**
 * @brief Node::runOneTick processes the next packet in line and sends it to processPacket;
 * will route packets not meant for this Node to links according to lookupTable_
 */
void Node::runOneTick() {
    if (!packets_->empty()) {
        for (auto packet : *packets_) { // increase age of every packet in the node
            packet->runOneTick();
        }

        int dst = packets_->front()->destinationAddress;

        // Packets meant for this node are processed and removed from queue
        if (dst == address_) {
            lastPacketAge_ = packets_->front()->getAge();
            processPacket(packets_->front());
            packets_->erase(packets_->begin());
            return;
        }

        // Packets meant for other nodes are routed and passed along to link
        processPacket(packets_->front());
        auto destinationLinkIterator = lookupTable_.find(dst);

        if ( destinationLinkIterator == lookupTable_.end() ) { // log warning about unreachable destinations and drop package
            qWarning() << "Packet had unreachable destination " << dst;
            packets_->erase(packets_->begin());
            return;
        }
        if ( destinationLinkIterator->second->receive(packets_->front()) ) { // only pass to link if it has capacity
            packets_->erase(packets_->begin());
        }

    } else {
        // let application know there is no
        processPacket();
    }
}

/**
 * @brief Node::receive adds received packet to received_, from where it will be processed
 * @param packet packet from received
 */
void Node::receive(Packet* packet) {
    received_.push_back(packet);
}


void Node::addLink(Link* link) {
    links_.push_back(link);
}

/**
 * @brief Node::receivePackets transfers received packets to the packets_ queue,
 * from where they will be processed one by one. The queue does not necessarily
 * accept all of them, it may drop packets depending on its chosen behavior.
 * The purpose of this is so that Nodes cannot process packets received this "tick".
 */
void Node::receivePackets() {
    while (!received_.empty()) {
        bool succeeded = packets_->maybe_push_back(received_.front());
        received_.erase(received_.begin());
        lastPacketStatus_ = succeeded;
    }
}

/**
 * @brief Node::getAddress returns node's address
 * @return  the integer address
 */
int Node::getAddress() const {
    return address_;
}


/**
 * @brief Node::initializeRoutingTable calculates the next link from this node for all destinations in
 * the network using modified Dijkstra's algorithm, will only route packets through routers
 */
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
                const Node* destination = link->getDestination();
                if (lookupTable.count(destination->getAddress()) == 0) { // the outgoing link hasn't been traversed
                    lookupTable[destination->getAddress()] = lookupTable[node->getAddress()];
                    double weight = link->getPropagationDelay() + c;
                    queue.push(std::pair(destination, dist + weight));
                }
            }
        }
    }
    lookupTable_ = lookupTable;
    qInfo() << "LookupTable of node " << address_;
    for (auto item : lookupTable) {
        qInfo() << "Final dest: " << item.first << " Next: " << item.second->getDestination()->getAddress();
    }
}

/**
 * @brief Node::dummyStat returns random integer from node's scope
 * @return the random integer
 */
int Node::dummyStat() const {
    return rand();
}

int Node::getLastPacketAge() const { return lastPacketAge_; }
int Node::getBufferSize() const { return packets_->size(); }


void Node::hoverMoveEvent(QGraphicsSceneHoverEvent *event) {
    setToolTip(QString::number(address_));
}

/**
 * @brief Node::drawTopText draw text in a box above the node
 * @param painter qpainter to use
 * @param text qstring of the text
 */
void Node::drawTopText(QPainter* painter, QString text) {

    // top text box
    QRectF toprect(-sizeconst, -sizeconst*5/3, sizeconst*2, sizeconst*2/3);
    toprect.translate(QPointF(0, -2));
    painter->fillRect(toprect, Qt::white);
    painter->setPen(QPen(Qt::black));
    painter->drawRect(toprect);
    painter->drawText(toprect, Qt::AlignCenter, text);
}

/**
 * @brief Node::drawBelowText draw text in a box below the node - black if latest addition to queue
 * was a success, red if packet was dropped
 * @param painter qpainter to use
 * @param text qstring of the text
 */
void Node::drawBottomText(QPainter* painter, QString text) {
    QRectF bottomrect(-sizeconst, sizeconst, sizeconst*2, sizeconst*2/3);
    bottomrect.translate(QPointF(0, 2));
    painter->fillRect(bottomrect, Qt::white);

    // Check if latest arrived packet was dropped and set color accordingly
    if (lastPacketStatus_) {
        painter->setPen(QPen(Qt::black));
    } else {
        painter->setPen(QPen(Qt::red));
    }

    painter->drawRect(bottomrect);
    painter->drawText(bottomrect, Qt::AlignCenter, text);
}

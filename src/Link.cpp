#include "Link.h"
#include "Node.h"
#include "qpainter.h"
#include <QPen>

Link::Link(Node* node1,
           Node* node2,
           double transmissionSpeed,
           double propagationDelay) :
    node1_(node1), node2_(node2), transmissionSpeed_(transmissionSpeed),
    propagationDelay_(propagationDelay), maxThroughput_(transmissionSpeed * propagationDelay) {}

Link::~Link() {
    for (auto packet : packets_) {
        delete packet;
    }
    delete inTransmission_;
}

void Link::runOneTick() {
    if (std::size(packets_) > 0) {
        // advance packets
        for (auto packet : packets_) {
            packet->runOneTick();
            packet->transmitted += 1 / propagationDelay_;
        }
        // if the first packet in the queue is transmitted, move it to the next node
        if (packets_.head()->transmitted >= 1) {
            packets_.head()->transmitted = 0;
            cumulativeThroughput_ += packets_.head()->size; // increase cumulative throughput
            currentThroughput_ -= packets_.head()->size; // decrease current throughput
            node2_->receive(packets_.dequeue());
        }
    }
}

int Link::receive(Packet* packet) {
    if (inTransmission_ == nullptr) {
        inTransmission_ = packet;
        currentThroughput_ += packet->size; // increase current throughput
        return 1;
    }
    else return 0;
}

void Link::receivePackets() {
    if (inTransmission_ != nullptr) {
        if (inTransmission_->received >= 1) {
            inTransmission_->received = 0;
            packets_.enqueue(inTransmission_);
            inTransmission_ = nullptr;
        }
        else {
            inTransmission_->runOneTick();
            inTransmission_->received += transmissionSpeed_ / inTransmission_->size;
        }
    }
}

const Node* Link::getDestination() const { return node2_; }
const double Link::getTransmissionSpeed() const { return transmissionSpeed_; }
const double Link::getPropagationDelay() const { return propagationDelay_; }

/**
 * @brief Link::paint paints a link
 * @param painter the painter to use
 * @param option unused qt stuff
 * @param widget unused qt stuff
 */
void Link::paint(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget) {
    painter->setPen(QPen(Qt::black, 3));    // make the link line thicker
    painter->translate(node1_->pos()); // set origin to node1
    QPointF diff = node2_->pos() - node1_->pos();
    qreal tmpx = diff.x();
    qreal tmpy = diff.y();
    qreal euclidian = std::sqrt(tmpx*tmpx + tmpy*tmpy);
    qreal angle = std::atan2(tmpy, tmpx)*180/M_PI;

    painter->rotate(angle);
    painter->drawLine(sizeconst, 0, euclidian-sizeconst,0); //draw straight line in the translated coordinates

    painter->drawText(QRectF(euclidian*1/4, -20, euclidian*2/4, 17),
                      Qt::AlignCenter,
                      QString::number(dummyStat()).left(5) + "⟶"); // draw direction 2 statistic
    painter->rotate(180);
    painter->drawText(QRectF(-euclidian*3/4, -20, euclidian*2/4, 17),
                      Qt::AlignCenter,
                      QString::number(dummyStat()).left(5) + "⟶"); // draw direction 2 statistic
}

QRectF Link::boundingRect() const {
    // figure out top left && bottom right
    int x0 = std::min(node1_->x(), node2_->x());
    int y0 = std::min(node1_->y(), node2_->y());
    int x1 = std::max(node1_->x(), node2_->x());
    int y1 = std::max(node1_->y(), node2_->y());

    return QRectF(x0, y0, x1, y1);
}

/**
 * @brief Link::dummyStat Generates dummy statistic
 * @return returns random integer
 */
int Link::dummyStat() const {
    return rand();
}

int Link::getCumulativeThroughput() const { return cumulativeThroughput_; }
double Link::getUtilization() const { return currentThroughput_ / maxThroughput_; }

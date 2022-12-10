#ifndef QUEUE_H
#define QUEUE_H
#include <vector>
#include <Packet.h>

/**
 * @brief The Queue class is abstract. It inherits std::vector and is otherwise similar,
 * but includes (pure) virtual maybe_push_back which will only call push_back if certain
 * conditions are met
 */
class Queue : public std::vector<Packet*>
{
public:
    Queue(){};
    virtual ~Queue();
    virtual void maybe_push_back(Packet*) = 0;
};

/**
 * @brief The NoDropQueue class acts like a regular vector; no packets are dropped
 */
class NoDropQueue : public Queue
{
public:
    NoDropQueue();
    ~NoDropQueue(){};
    void maybe_push_back(Packet*) override;
};

/**
 * @brief The RandomDropQueue class will drop packets with int chanceOfDrop probability,
 * for example a value of 50 means half of the packets are dropped on average
 */
class RandomDropQueue : public Queue
{
public:
    RandomDropQueue(int chanceOfDrop);
    ~RandomDropQueue(){};
    void maybe_push_back(Packet*) override;
private:
    int chanceOfDrop_;
};

/**
 * @brief The SizeConstraintQueue class will drop new packets if queue size is at maxSize
 */
class SizeConstraintQueue : public Queue
{
public:
    SizeConstraintQueue(int maxSize);
    ~SizeConstraintQueue(){};
    void maybe_push_back(Packet*) override;
private:
    double maxSize_;
};



#endif // QUEUE_H

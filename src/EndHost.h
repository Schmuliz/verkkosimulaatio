#ifndef ENDHOST_H
#define ENDHOST_H

#include "Node.h"
#include "Application.h"

/**
 * @brief The EndHost class inherits Node. It does not route packets, only sends them
 * based on its application's behavior
 */
class EndHost : virtual public Node
{
public:
    EndHost(int address, std::vector<int> application, std::vector<int> queue);
    ~EndHost();
    void processPacket(Packet *packet) override;
    void paint(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget) override;

private:
    Application* application_;
};


#endif // ENDHOST_H

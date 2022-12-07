#ifndef ENDHOST_H
#define ENDHOST_H

#include "Node.h"
#include "Application.h"

class EndHost : virtual public Node
{
public:
    EndHost(int address, std::vector<int> application);
    ~EndHost(){}
    void processPacket(Packet *packet) override;
    void paint(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget) override;

private:
    Application* application_;
};


#endif // ENDHOST_H

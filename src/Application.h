#ifndef APPLICATION_H
#define APPLICATION_H

class Application
{
public:
    Packet* packet_generator();
private:
    double transmission_interval;
};

#endif // APPLICATION_H

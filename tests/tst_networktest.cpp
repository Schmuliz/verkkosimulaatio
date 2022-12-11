#include <QtTest>
#include <vector>
#include "EndHost.h"
#include "Network.h"

class NetworkTest: public QObject
{
    Q_OBJECT

private:
    Network *network;
    bool myCondition()
    {
        return true;
    }

private slots:
    void initTestCase()
    {
        network = new Network();
        EndHost *a = new EndHost(1, {1,10,256,2}, {1, 0});
        EndHost *b = new EndHost(2, {1,10,256,2}, {1, 0});
        network->addNode(a);
        network->addNode(b);
        network->addLink(1,2,500,50);
        network->initializeRoutingTables();
        qDebug("Called before everything else.");
    }

    void firstTest()
    {
        QVERIFY(myCondition());
        //QCOMPARE(1, 1); // compare two values
    }

    void packetTimingTest()
    {
        Network* network2 = new Network();
        EndHost* a = new EndHost(1, {3,0,256,2}, {1});
        EndHost* b = new EndHost(2, {3,0,256,1}, {1});
        network2->addNode(a);
        network2->addNode(b);
        network2->addLink(1,2,500,50);
        network2->initializeRoutingTables();
        Packet* p = new Packet(1, 2, 256);
        b->processPacket(p); // manually send packet to b
        int ticker = 0;
        while (a->getLastPacketAge() == 0) {
            network2->runOneTick();
            ticker++;
        }
        int packetAge = a->getLastPacketAge();
        qDebug() << "Current tick:" << ticker;
        qDebug() << "Packet age:" << packetAge;
        delete network2;
        QVERIFY(ticker == packetAge);
    }


    void cleanupTestCase()
    {
        delete network;
        qDebug("Called after myFirstTest and mySecondTest.");
    }
};

QTEST_MAIN(NetworkTest)
#include "tst_networktest.moc"

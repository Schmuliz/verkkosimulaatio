#include <QtTest>
#include <vector>
#include "EndHost.h"
#include "Network.h"

class NetworkTest: public QObject
{
    Q_OBJECT

private:
    bool myCondition()
    {
        Network bla;
        std::vector<int> aapp{1,10,256,2};
        EndHost a = EndHost(1, aapp);
        std::vector<int> bapp{1,10,256,2};
        EndHost b = EndHost(2, bapp);
        bla.addNode(&a);
        bla.addNode(&b);
        bla.addLink(1,2,500,50);
        bla.initializeRoutingTables();
        return true;
    }

private slots:
    void initTestCase()
    {
        qDebug("Called before everything else.");
    }

    void firstTest()
    {
        QVERIFY(myCondition());
        //QCOMPARE(1, 1); // compare two values
    }


    void cleanupTestCase()
    {
        qDebug("Called after myFirstTest and mySecondTest.");
    }
};

QTEST_MAIN(NetworkTest)
#include "tst_networktest.moc"

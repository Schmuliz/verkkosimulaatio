#ifndef SIMULATIONTHREAD_H
#define SIMULATIONTHREAD_H

#include "Network.h"
#include <QThread>
#include <QGraphicsScene>


class SimulationThread : public QThread
{
public:
    SimulationThread(QObject *parent, Network *network, QGraphicsScene *scene)
        : QThread(parent), network_(network), scene_(scene) {};

private:
    Q_OBJECT // Qt macro

    void run() override {
        while(true) {
            scene_->update(); // will update the dummyStats currently
            sleep(1);
        }
        //emit exitSim();
    }
    Network *network_;
    QGraphicsScene *scene_;
signals:
    //void exitSim();
};

// definitions for qt generated signal implementations etc.
//#include "SimulationThread.moc" // Must be after simulationThread declaration


#endif // SIMULATIONTHREAD_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qgraphicsscene.h"
#include "Network.h"
#include "SimulationThread.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void on_actionLoad_Simulation_triggered();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *Scene;
    Network *network_;
    SimulationThread *simthread_;
};


#endif // MAINWINDOW_H

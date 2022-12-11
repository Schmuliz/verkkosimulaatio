#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Network.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QLCDNumber>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief The MainWindow class. Represents the only window of the application.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void invSimSignal(bool state);
    void updateTickLcd(int tick);

protected:
    void timerEvent(QTimerEvent *event) override;

private slots:
    void on_actionExit_triggered();

    void on_actionLoad_Simulation_triggered();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked(bool checked);

    void invSimState(bool state) {
        emit invSimSignal(!state);
    };



private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene_;
    QLCDNumber *ticklcd_;
    Network *network_;
    qint64 simulationtimerid_;
    void replaceNetwork(Network* network);
    void runOneTick();
};


#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qgraphicsscene.h"
#include "Network.h"
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
signals:
    void invSimSignal(bool state);

protected:
    void timerEvent(QTimerEvent *event) override;

private slots:
    void on_actionExit_triggered();

    void on_actionLoad_Simulation_triggered();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked(bool checked);

    void invSimState(bool state) {
        qInfo() << "hey from inv slot";
        emit invSimSignal(!state);
    };

private:
    Ui::MainWindow *ui;
    QGraphicsScene *Scene;
    Network *network_;
    qint64 simulationtimerid_;
};


#endif // MAINWINDOW_H

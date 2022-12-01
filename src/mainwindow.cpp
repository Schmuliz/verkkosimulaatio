#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "EndHost.h"
#include "Router.h"
#include "RoutingEndHost.h"
#include "Node.h"
#include "SimulationThread.h"
#include <QFileDialog>
#include <QDebug> // qDebug() is cursed, use qInfo() or higher



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Scene = new QGraphicsScene(this);
    ui->networkView->setScene(Scene);

    network_ = new Network();

    // example render
    Node *g1 = new Router(123);            g1->setPos(100, 200);
    Node *g2 = new EndHost(124, 1);        g2->setPos(-100,100);
    Node *g3 = new RoutingEndHost(125, 1); g3->setPos(200,000);

    network_->addNode(g1);
    network_->addNode(g2);
    network_->addNode(g3);

    network_->addLink(123, 124, 1, 1);
    network_->addLink(123, 125, 1, 1);

    network_->populateScene(Scene);

    Scene->addEllipse(-5, -5, 10, 10); // center of the universe indicator

    simthread_ = new SimulationThread(this, network_, Scene);


}

MainWindow::~MainWindow()
{
    delete ui;
    delete network_;
    delete simthread_;
}


void MainWindow::on_actionExit_triggered()
{
    MainWindow::close();
}


void MainWindow::on_actionLoad_Simulation_triggered()
{

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter("json (*.json)");
    dialog.setViewMode(QFileDialog::Detail);
    QString filename;
    if(dialog.exec()) {
        filename = dialog.selectedFiles().at(0); // only single file can be selected
    }
    qInfo() << "File dialog selected file: " << filename;

    delete network_;
    network_ = new Network(filename);
}


/***
 * \brief Updates scene
 */
void MainWindow::on_pushButton_2_clicked()
{
    Scene->update();
}


void MainWindow::on_pushButton_clicked(bool checked)
{
    qInfo() << "play-pause checked  " << checked;

    if(checked) {
        simthread_->start();
    } else {

    }
}



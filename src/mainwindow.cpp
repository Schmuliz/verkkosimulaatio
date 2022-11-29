#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "EndHost.h"
#include "Router.h"
#include "RoutingEndHost.h"
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
    QGraphicsItem *g1 = new Router(123);
    QGraphicsItem *g2 = new EndHost(124, 1);        g2->setPos(100,100);
    QGraphicsItem *g3 = new RoutingEndHost(124, 1); g3->setPos(200,000);

    Scene->addItem(g1);
    Scene->addItem(g2);
    Scene->addItem(g3);

}

MainWindow::~MainWindow()
{
    delete ui;
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

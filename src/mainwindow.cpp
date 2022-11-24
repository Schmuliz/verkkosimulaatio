#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Router.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Scene = new QGraphicsScene(this);
    ui->networkView->setScene(Scene);

    // example render
    Scene->addText("Hello, world!");
    QGraphicsItem *g1 = new Router(123);
    Scene->addItem(g1);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionExit_triggered()
{
    MainWindow::close();
}

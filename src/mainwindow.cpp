#include "mainwindow.h"
#include "./ui_mainwindow.h"
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

    network_ = new Network(":/resources/network.json");
    network_->populateScene(Scene);

    Scene->addEllipse(-5, -5, 10, 10); // center of the universe indicator

    network_->initializeRoutingTables();
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



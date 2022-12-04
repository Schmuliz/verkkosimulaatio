#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QSlider>
#include <QLCDNumber>
#include <QFileDialog>
#include <QDebug> // qDebug() is cursed, use qInfo() or higher
#include <QPushButton>
#include <QDoubleSpinBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton,
            &QPushButton::clicked,
            this,
            &MainWindow::invSimState);
    connect(this,
            static_cast<void (MainWindow::*)(bool)>(&MainWindow::invSimSignal),
            ui->doubleSpinBox,
            static_cast<void (QDoubleSpinBox::*)(bool)>(&QDoubleSpinBox::setEnabled) );


    Scene = new QGraphicsScene(this);
    ui->networkView->setScene(Scene);

    network_ = new Network(":/resources/network.json");
    network_->populateScene(Scene);

    Scene->addEllipse(-5, -5, 10, 10); // center of the universe indicator

    network_->initializeRoutingTables();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete network_;
    //simthread_->quit(); // how to kill the thread, need to modify simulation loop to accpet immidiate on demand signals. It can't wait simulation delay to handle the signals!
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

void MainWindow::timerEvent(QTimerEvent *event) {
    qInfo() << "timer event triggered";
    ui->networkView->scene()->update();
}

void MainWindow::on_pushButton_clicked(bool checked)
{
    if(checked) {
        simulationtimerid_ = startTimer(ui->doubleSpinBox->value()*1000);
    } else {
        killTimer(simulationtimerid_);
    }
}



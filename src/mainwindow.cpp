#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QSlider>
#include <QLCDNumber>
#include <QFileDialog>
#include <QDebug> // qDebug() is cursed, use qInfo() or higher
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QMessageBox>


/**
 * @brief MainWindow::MainWindow constructs Qt MainWindow
 * @param parent parent relation to other widgets
 */
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


    network_ = new Network(":/resources/network.json");
    scene_ = new QGraphicsScene(this);
    ui->networkView->setScene(scene_);
    network_->initializeRoutingTables();
    network_->populateScene(scene_);

    scene_->setBackgroundBrush(Qt::white);
   // ui->networkView->ensureVisible(scene_->sceneRect());

    ticklcd_ = new QLCDNumber(ui->networkView);
    ticklcd_->setDigitCount(10);
    ticklcd_->show();
    connect(this,
            &MainWindow::updateTickLcd,
            ticklcd_,
            static_cast<void (QLCDNumber::*)(int)>(&QLCDNumber::display) );
}

MainWindow::~MainWindow()
{
    delete ui;
    delete network_;
}

void MainWindow::replaceNetwork(Network *network) {
    delete network_;
    scene_->clear();
    network_ = network;
    network_->populateScene(scene_);
    scene_->update();
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
        filename = dialog.selectedFiles().at(0); // only a single file can be selected
    }
    qInfo() << "File dialog selected file: " << filename;

    Network *newnetwork = nullptr;
    try {
        newnetwork = new Network(filename);
        replaceNetwork(newnetwork);
        ticklcd_->display(0);
    }
    catch (const char* msg) {
        qCritical() << msg;
        delete newnetwork;
        auto mbox = QMessageBox(QMessageBox::Critical, "Error", msg);
        mbox.exec();
    }
    catch (...) {
        auto mbox = QMessageBox(QMessageBox::Critical, "Error", "unknown file loading error");
        mbox.exec();
        delete newnetwork;
    }
}

void MainWindow::runOneTick() {
    network_->runOneTick();
    emit updateTickLcd(network_->getCurrentTick());
    scene_->update();
}

void MainWindow::on_pushButton_2_clicked()
{
    runOneTick();
}

void MainWindow::timerEvent(QTimerEvent *event) {
    runOneTick();
}

void MainWindow::on_pushButton_clicked(bool checked)
{
    if(checked) {
        qreal inversemsec = 1L/ui->doubleSpinBox->value()*1000;
        simulationtimerid_ = startTimer(inversemsec);
    } else {
        killTimer(simulationtimerid_);
    }
}

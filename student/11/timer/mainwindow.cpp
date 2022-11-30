#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // connect sklots and receivers

    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::onStartButtonClicked);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::onStopButtonClicked);
    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::onCloseButtonClicked);
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::onResetButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onStartButtonClicked()
{
    // check if timer is on
    if ( !timer ) {
        timer = new QTimer();
        connect(timer, &QTimer::timeout, this, &MainWindow::onTimerTimeout);
        // start timer
        timer->setInterval(1000);
        timer->start();
    }
}

void MainWindow::onStopButtonClicked()
{
    if ( timer ) {
        timer->stop();
    }
}

void MainWindow::onResetButtonClicked()
{
    if ( timer ) {
        delete timer;
        timer = nullptr;
        seconds_ = 0;
        updateView();
    }
}

void MainWindow::onCloseButtonClicked()
{
    if ( timer ) {delete timer;}
    close();

}

void MainWindow::onTimerTimeout()
{
    seconds_++;
    updateView();
}

void MainWindow::updateView()
{
    // calc seconds an minutes
    int minutes = seconds_/60;
    int remainingsSeconds = seconds_%60;

    ui->lcdNumberMin->display(minutes);
    ui->lcdNumberSec->display(remainingsSeconds);
}

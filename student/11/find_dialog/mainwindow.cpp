#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSpinBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_fileLineEdit_cursorPositionChanged(int arg1, int arg2)
{

}


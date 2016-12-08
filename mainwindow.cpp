#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(640, 480);
    this->move(25,25);


}

MainWindow::~MainWindow()
{
    delete ui;
}

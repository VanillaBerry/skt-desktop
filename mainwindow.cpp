#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "image_editor.h"
<<<<<<< HEAD
#include "app_database.h"
=======
>>>>>>> a1b85349746472ad9f4c5f6a96184b6531fc5e8d
#include <QFileDialog>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_Exit, SIGNAL (clicked()), this, SLOT (handlebutton_Exit()));
    connect(ui->pushButton_newimg, SIGNAL(released()), this, SLOT (handlebutton_New()));
<<<<<<< HEAD

=======
>>>>>>> a1b85349746472ad9f4c5f6a96184b6531fc5e8d
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handlebutton_New(){

    QImage img_orig;
    QString str;

    str=QFileDialog::getOpenFileName(0, "Select Image", "..//", "*.jpg *.png *.bmp");

    img_orig.load(str);
    img_orig.convertToFormat(QImage::Format_RGB32);

    image_editor *img_edit = new image_editor();


    img_edit->setImage(img_orig);
    img_edit->show();
    img_edit->setLocation(str);

<<<<<<< HEAD
    this->lower();

=======
>>>>>>> a1b85349746472ad9f4c5f6a96184b6531fc5e8d
};

void MainWindow::handlebutton_Exit(){
    emit MainWindow::closing();
};


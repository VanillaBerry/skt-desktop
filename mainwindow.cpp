#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "image_editor.h"
#include "app_database.h"
#include <QFileDialog>
#include <QApplication>
#include <QCloseEvent>
#include <QTreeView>
#include <QStandardItemModel>
#include <QStringList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

// CONNECT TO BUTTONS
    connect(ui->pushButton_Exit, SIGNAL (clicked()), this, SLOT (handlebutton_Exit()));
    connect(ui->pushButton_newimg, SIGNAL(released()), this, SLOT (handlebutton_New()));
    connect(ui->actionA_database, SIGNAL (triggered()), this, SLOT (handleA_database()));

// IMAGE EDITOR
    img_edit = new image_editor();
    img_edit->hide();

// CONNECT TO CLOSING OF EDITOR SIGNAL
    connect(img_edit, SIGNAL(EditorIsClosed()), this, SLOT (handleEditor_Closing()));

// DATABASE INIT
    app_db = new app_database;
    app_db->databaseInit();

// TREE VIEW

    treeView = new QTreeView();
    ui->scrollArea_tree->setWidget(treeView);
 //   InitAppDatabase();


    EditorIsOpen=false;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handlebutton_New(){

    if(!EditorIsOpen)
    {
    QImage img_orig;
    QString str;

    str=QFileDialog::getOpenFileName(0, "Select Image", "..//", "*.jpg *.png *.bmp");

    img_orig.load(str);
    img_orig.convertToFormat(QImage::Format_RGB32);

    img_edit->setImage(img_orig);
    img_edit->setLocation(str);
    img_edit->show();
    this->lower();

    EditorIsOpen=true;

    }
    else
    {
        //do nothing;
    };


};

void MainWindow::handlebutton_Exit(){
    if (!EditorIsOpen) emit MainWindow::closing();
};


void MainWindow::handleEditor_Closing(){
    EditorIsOpen=false;
};


void MainWindow::closeEvent(QCloseEvent *event) {
    if (EditorIsOpen)
        event->ignore();
    else
        event->accept();
};

void MainWindow::handleA_database(){
    InitAppDatabase();

};

void MainWindow::InitAppDatabase(){

        QStandardItemModel* standardModel = new QStandardItemModel();
        QStandardItem *rootNode = standardModel->invisibleRootItem();

        QStringList list;
        list<<"SEMESTER"; //<<"DISCIPLINE";

        standardModel->setHorizontalHeaderLabels(list);

  /*      QStandardItem *rootNode = standardModel->invisibleRootItem();*/

        QStandardItem *rightItem = new QStandardItem("RIGHT");
        QStandardItem *leftItem = new QStandardItem("LEFT");

        QStandardItem *Item1 = new QStandardItem("1");
        QStandardItem *Item2 = new QStandardItem("2");
        QStandardItem *Item3 = new QStandardItem("3");
        QStandardItem *Item4 = new QStandardItem("4");

        rootNode->appendRow(rightItem);
        rootNode->appendRow(leftItem);

        rightItem->appendRow(Item1);
        rightItem->appendRow(Item2);

        leftItem->appendRow(Item3);
        leftItem->appendRow(Item4);

        treeView->setModel(standardModel);

// без этого две полосы прокрутки появляется
        treeView->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    //  treeView->expandAll();

};



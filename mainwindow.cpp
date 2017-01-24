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
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

// CONNECT TO BUTTONS
    connect(ui->pushButton_Exit, SIGNAL (clicked()), this, SLOT (handlebutton_Exit()));
    connect(ui->pushButton_newimg, SIGNAL(released()), this, SLOT (handlebutton_New()));

// CONNECT TO MENU BUTTONS
    connect(ui->actionA_database, SIGNAL (triggered()), this, SLOT (handleA_database()));
    connect(ui->actionSemester, SIGNAL (triggered()), this, SLOT (handle_addSemester()));
    connect(ui->actionSubject, SIGNAL (triggered()), this, SLOT (handle_addSubject()));
    connect(ui->actionLecture, SIGNAL (triggered()), this, SLOT (handle_addLecture()));
    connect(ui->actionPage, SIGNAL (triggered()), this, SLOT (handle_addPage()));

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

    standardModel = app_db->app_db_model();
    treeView->setModel(standardModel);

    // без этого две полосы прокрутки появляется
    treeView->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

};



void MainWindow::handle_addSemester(){
    bool ok;
    QString str;

    str = QInputDialog::getText(this, tr("ADD NEW SEMESTER"),
                                tr("Semester name:"), QLineEdit::Normal,
                                "New Semester", &ok);

    if (ok && !str.isEmpty())
    app_db->add_Semester(str);
};


void MainWindow::handle_addSubject(){};
void MainWindow::handle_addLecture(){};
void MainWindow::handle_addPage(){};

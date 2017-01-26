#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "image_editor.h"
#include "app_database.h"
#include "subjectdialog.h"
#include "imageslistviewer.h"

#include <QAbstractItemView>
#include <QApplication>
#include <QCloseEvent>
#include <QComboBox>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QLineEdit>
#include <QTreeView>
#include <QStandardItemModel>
#include <QStringList>
#include <QPushButton>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

// CONNECT TO BUTTONS
    connect(ui->pushButton_newimg, SIGNAL(released()), this, SLOT (handlebutton_New()));

// CONNECT TO MENU BUTTONS FILE
    connect(ui->actionExit, SIGNAL (triggered()), this, SLOT (handlebutton_Exit()));
    connect(ui->actionView_selected, SIGNAL(triggered(bool)), this, SLOT (handleView_Selected()));

// CONNECT TO MENU BUTTONS ADD
    connect(ui->actionA_database, SIGNAL (triggered()), this, SLOT (handleA_database()));
    connect(ui->actionSemester, SIGNAL (triggered()), this, SLOT (handle_addSemester()));
    connect(ui->actionSubject, SIGNAL (triggered()), this, SLOT (handle_addSubject()));
    connect(ui->actionLecture, SIGNAL (triggered()), this, SLOT (handle_addLecture()));

// CONNECT TO -> BUTTON
    connect(ui->pushButton_addPagesToList, SIGNAL (pressed()), this, SLOT (handle_AddPagesToList()));

// IMAGE VIEWER
    image_viewer = new imageslistviewer();
    image_viewer->hide();

// IMAGE EDITOR
    img_edit = new image_editor();
    img_edit->hide();
    ui->label_imageLocation->setText("image location is not selected");
    connect(ui->pushButton_selectImgLoc, SIGNAL(pressed()), this, SLOT (handlebutton_ImgLocation()));
    connect(img_edit, SIGNAL (LocationChanged()), this, SLOT (handleImageLocationChanged()));

//  CONNECT TO CLOSING OF EDITOR SIGNAL
    connect(img_edit, SIGNAL(EditorIsClosed()), this, SLOT (handleEditor_Closing()));

//  SUBJECT DIALOG
    subj_diag = new subjectdialog();
    subj_diag->hide();
//  CONNECT TO SUBJ_DIAG BUTTON PRESSED
    connect(subj_diag, SIGNAL(subjectDialog_ok()), this, SLOT (handle_subjDialogOK()));

//  LECTURE DIALOG
    lect_diag = new lecturedialog();
    lect_diag->hide();
    connect(lect_diag, SIGNAL(signalSemesterPressed()), this, SLOT (handle_lectureDialogSemesterPressed()));
    connect(lect_diag, SIGNAL(lectureDialog_ok()), this, SLOT (handle_lectureDialogOK()));

//  CONNECT TO DOWNLINE COMBOBOXES
    connect(ui->comboBox_Semester, SIGNAL(currentIndexChanged(int)), this, SLOT(downline_SemesterPressed()));
    connect(ui->comboBox_Subject, SIGNAL(currentIndexChanged(int)), this, SLOT(downline_SubjectPressed()));
    connect(ui->pushButton_AddPage, SIGNAL(pressed()), this, SLOT(handle_addPage()));

//  DATABASE INIT
    app_db = new app_database;
    app_db->databaseInit();

// TREE VIEW

    treeView = new QTreeView();
    ui->scrollArea_tree->setWidget(treeView);
    treeView->setSelectionMode(QAbstractItemView::SingleSelection);
    treeView->setSelectionBehavior(QAbstractItemView::SelectRows);

 //   InitAppDatabase();

// LIST VIEW
    listView = new QListView();
    ui->scrollArea_list->setWidget(listView);
    createA_List();

// COMBO BOXES
    ui->comboBox_Semester->setInsertPolicy(QComboBox::NoInsert);
    ui->comboBox_Subject->setInsertPolicy(QComboBox::NoInsert);
    ui->comboBox_Lecture->setInsertPolicy(QComboBox::NoInsert);

    ui->comboBox_Semester->addItems(app_db->db_SemesterList());

    EditorIsOpen=false;

    this->handleA_database();

    images_selected = new QList<QImage>;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handlebutton_New(){

    if((!EditorIsOpen) and (!imgLocation.isEmpty()))
    {
        QImage img_orig;
        img_orig.load(imgLocation);
        img_orig.convertToFormat(QImage::Format_RGB32);

        img_edit->setImage(img_orig);
        img_edit->setLocation(imgLocation);
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
    this->raise();
};

void MainWindow::closeEvent(QCloseEvent *event) {
    if (EditorIsOpen)
        event->ignore();
    else
        event->accept();
};

// FOR IMAGE EDITOR
void MainWindow::handlebutton_ImgLocation(){
    QString str;
    str=QFileDialog::getOpenFileName(0, "Select Image", "..//", "*.jpg *.png *.bmp");
    if (!str.isEmpty())
    {
        imgLocation=str;
        ui->label_imageLocation->setText(imgLocation);
    };
    //else do nothing
};

// FOR IMAGE EDITOR
void MainWindow::handleImageLocationChanged(){
    img_edit->getLocation(imgLocation);
    ui->label_imageLocation->setText(imgLocation);
};

void MainWindow::handleA_database(){
    standardModel_tree = app_db->app_db_model();
    treeView->setModel(standardModel_tree);

    // без этого две полосы прокрутки появляется
    treeView->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
};

void MainWindow::createA_List(){
    standardModel_list = new QStandardItemModel();
    list_rootNode = standardModel_list->invisibleRootItem();

    QStringList list;
    list<<"NAME"<<"TAGS";

    standardModel_list->setHorizontalHeaderLabels(list);

    listView->setModel(standardModel_list);
    listView->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
};

void MainWindow::refresh_tree(){
    standardModel_tree = app_db->app_db_model();
    treeView->setModel(standardModel_tree);
};

void MainWindow::handle_addSemester(){
    bool ok;
    QString str;

    str = QInputDialog::getText(this, tr("ADD NEW SEMESTER"),
                                tr("Enter semester name here:"), QLineEdit::Normal,
                                "New Semester", &ok);
    if (ok && !str.isEmpty())
    app_db->add_Semester(str);

    refresh_tree();
};


void MainWindow::handle_addSubject(){
    subj_diag->setSemesterList(app_db->db_SemesterList());
    subj_diag->show();
};

void MainWindow::handle_addLecture(){
    QStringList _semesterList=app_db->db_SemesterList();

    lect_diag->SetSemesterList(_semesterList);
//    lect_diag->SetDatabase(app_db);

    lect_diag->SetSubjectList(app_db->db_SubjectsList(_semesterList.first()));
    lect_diag->show();
};

void MainWindow::handle_addPage(){
    semester = ui->comboBox_Semester->currentText();
    subject = ui->comboBox_Subject->currentText();
    lecture = ui->comboBox_Lecture->currentText();
    page = ui->lineEdit_PageName->text();

    bool _res = app_db->add_Page(semester, subject, lecture, page, "", imgLocation);
    if (_res)
    ui->label_imageLocation->setText("УСПЕШНО ДОБАВЛЕНО!");

    refresh_tree();
};

void MainWindow::handle_subjDialogOK(){
    bool ok=subj_diag->result(semester, subject);
    if (ok)
    {
        app_db->add_Subject(semester, subject, "");
        subj_diag->hide();
        refresh_tree();
    };
};

// FOR LECTURE DIALOG
void MainWindow::handle_lectureDialogOK(){
    bool ok=lect_diag->result(semester, subject, lecture);
    if (ok)
    {
        app_db->add_Lecture(semester, subject, lecture, "");
        lect_diag->hide();
        refresh_tree();
    };
};

void MainWindow::handle_lectureDialogSemesterPressed(){
     bool ok=lect_diag->result(semester, subject, lecture);
     lect_diag->SetSubjectList(app_db->db_SubjectsList(semester));
};

// SLOTS FOR PAGE SELECTING
void MainWindow::downline_SemesterPressed(){
    semester = ui->comboBox_Semester->currentText();

    QStringList _strList = app_db->db_SubjectsList(semester);
    ui->comboBox_Subject->clear();
    ui->comboBox_Subject->addItems(_strList);

    if (!_strList.isEmpty())
    {
        subject = _strList.first();
        _strList = app_db->db_LecturesList(semester, subject);
        ui->comboBox_Lecture->clear();
        ui->comboBox_Lecture->addItems(_strList);
    }
    else
    {
        ui->comboBox_Lecture->clear();
    };
};

void MainWindow::downline_SubjectPressed(){
    semester = ui->comboBox_Semester->currentText();
    subject = ui->comboBox_Subject->currentText();

    QStringList _strList = app_db->db_LecturesList(semester, subject);
    ui->comboBox_Lecture->clear();
    ui->comboBox_Lecture->addItems(_strList);
};

void MainWindow::handle_AddPagesToList(){

    QModelIndexList _index = treeView->selectionModel()->selectedIndexes();

    if (!_index.isEmpty())
    {

    QString name = _index.constFirst().data(0).toString();
    QString ID = _index.constLast().data(0).toString();

    int _level = app_db->getLevel(ID);

       if (_level==4)
       {
        QList<QStandardItem *> _newpage;
        _newpage << new QStandardItem(name) << new QStandardItem(ID);
        _newpage[0]->setEditable(false);
        _newpage[1]->setEditable(false);

        list_rootNode->appendRow(_newpage);
        ui->label_imageLocation->setText(name+ID);

        QImage _img;
        QString _imgloc;
        bool ok = app_db->getImage(ID, _imgloc);

        ui->label_imageLocation->setText(_imgloc);
        if (ok)
         {
            _img.load(_imgloc);
            images_selected->insert(0,_img);
            ui->label_imageLocation->setText(_imgloc);
         };
       };
    };
    // ELSE DO NOTHING
};

void MainWindow::handleView_Selected(){
    if (!images_selected->isEmpty())
    {
    image_viewer->set_listofIMAGES(images_selected);
    image_viewer->show();
    };
};

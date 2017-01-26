#include "subjectdialog.h"
#include "ui_subjectdialog.h"

subjectdialog::subjectdialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::subjectdialog)
{
    ui->setupUi(this);
    ok=false;
    ui->comboBox_Semester->hide();
    connect(ui->pushButton_SubjectAccept, SIGNAL(pressed()), this, SLOT (handleButtonPressed()));
}

subjectdialog::~subjectdialog()
{
    delete ui;
}

void subjectdialog::setSemesterList(QStringList _list){
    _SemesterList=_list;
    ui->comboBox_Semester->clear();
    ui->comboBox_Semester->addItems(_SemesterList);
    ui->comboBox_Semester->show();
};

void subjectdialog::handleButtonPressed(){
    subject=ui->lineEdit_SubjectName->text();
    semester=ui->comboBox_Semester->currentText();

    ok=((!subject.isEmpty()) and (!semester.isEmpty()));

    if (ok) emit subjectDialog_ok();
};

bool subjectdialog::result(QString &_semester, QString &_subject){
      _semester=semester;
      _subject=subject;

      return ok;
};

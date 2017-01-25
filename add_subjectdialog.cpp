#include "add_subjectdialog.h"

#include <QHBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>

add_SubjectDialog::add_SubjectDialog(){};

add_SubjectDialog::add_SubjectDialog(QStringList _list)
{
    _dialog = new QWidget;

    _layout = new QHBoxLayout(_dialog);

    _semester = new QComboBox();
    _semester->setInsertPolicy(QComboBox::NoInsert);
    _semester->addItems(_list);

    _line = new QLineEdit();
    _addSubject = new QPushButton();
    _addSubject->setText("ADD SUBJECT");

    _layout->addWidget(_semester);
    _layout->addWidget(_line);
    _layout->addWidget(_addSubject);

    _dialog->setWindowTitle("TO ADD SUBJECT SELECT SEMESTER");
    _dialog->show();

    ok=false;

    /*connect(ui->pushButton_newimg, SIGNAL(released()), this, SLOT (handlebutton_New()));*/
    connect(_addSubject, SIGNAL(pressed()), this, SLOT (handleButtonPressed()));

};

add_SubjectDialog::~add_SubjectDialog(){

};

void add_SubjectDialog::show(){
    _dialog->show();
};


bool add_SubjectDialog::result(QString &_semester, QString &_subject){
      _semester=semester;
      _subject=subject;

      return ok;
};

void add_SubjectDialog::handleButtonPressed(){
    subject=_line->text();
    semester=_semester->currentText();

    ok=((!subject.isEmpty()) and (!semester.isEmpty()));

//    if (ok) emit subjectDialog_ok();
};

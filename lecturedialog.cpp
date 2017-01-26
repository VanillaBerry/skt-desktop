#include "lecturedialog.h"
#include "ui_lecturedialog.h"

#include <QComboBox>

lecturedialog::lecturedialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::lecturedialog)
{
    ui->setupUi(this);
    this->setWindowTitle("SELECT SEMESTER AND SUBJECT");
    ok=false;
//    ui->comboBox_diagSemester->hide();
//    ui->comboBox_diagSubject->hide();

    connect(ui->pushButton_diagAddLecture, SIGNAL(pressed()), this, SLOT (handleButtonPressed()));
    connect(this, SIGNAL(signalsubjectsListIsREADY()), this, SLOT (handlesubjectsListIsREADY()));
    connect(ui->comboBox_diagSemester, SIGNAL(currentIndexChanged(int)), this, SLOT (slotSemesterPressed()));
}

lecturedialog::~lecturedialog()
{
    delete ui;
}

//  SLOTS
void lecturedialog::handleButtonPressed(){
    semester=ui->comboBox_diagSemester->currentText();
    subject=ui->comboBox_diagSubject->currentText();
    lecture=ui->lineEdit_diagLectureName->text();

    ok = ((!subject.isEmpty()) and (!semester.isEmpty()) and (!lecture.isEmpty()));

    if (ok) emit lectureDialog_ok();
};

void lecturedialog::slotSemesterPressed(){
    semester=ui->comboBox_diagSemester->currentText();
    emit signalSemesterPressed();
};

void lecturedialog::handlesubjectsListIsREADY(){
    ui->comboBox_diagSubject->clear();
    ui->comboBox_diagSubject->addItems(_SubjectList);
    ui->comboBox_diagSubject->show();
};

//  PUBLIC FUNCTIONS
void lecturedialog::SetSemesterList(QStringList _list){
    _SemesterList=_list;
    ui->comboBox_diagSemester->clear();
    ui->comboBox_diagSemester->addItems(_SemesterList);
    ui->comboBox_diagSemester->show();
};

void lecturedialog::SetSubjectList(QStringList _list){
    _SubjectList=_list;
    emit signalsubjectsListIsREADY();
};

bool lecturedialog::result(QString &_semester, QString &_subject, QString &_lecture){
    _semester=semester;
    _subject=subject;
    _lecture=lecture;

    return ok;
};

// SIGNALS
//void lectureDialog_ok(){};
// REFRESH SUBJECTS LIST WHEN NEW SEMESTER SELECTED
//void signalSemesterPressed(){};
//void signalsubjectsListIsREADY(){};

#ifndef LECTUREDIALOG_H
#define LECTUREDIALOG_H

#include <QWidget>
#include <QString>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>

#include "app_database.h"

namespace Ui {
class lecturedialog;
}

class lecturedialog : public QWidget
{
    Q_OBJECT

public:
    explicit lecturedialog(QWidget *parent = 0);
    ~lecturedialog();

private:
    Ui::lecturedialog *ui;

public:
    void SetSemesterList(QStringList _list);
    void SetSubjectList(QStringList _list);
    bool result(QString &_semester, QString &_subject, QString &_lecture);
//    void SetDatabase(app_database *_db);

private:
    bool ok;
    QString semester;
    QString subject;
    QString lecture;
    QStringList _SemesterList;
    QStringList _SubjectList;
//    app_database *db_lectureDiag;

private slots:
    void handleButtonPressed();
    void slotSemesterPressed();
    void handlesubjectsListIsREADY();

signals:
    void lectureDialog_ok();
// REFRESH SUBJECTS LIST WHEN NEW SEMESTER SELECTED
    void signalSemesterPressed();
    void signalsubjectsListIsREADY();
};

#endif // LECTUREDIALOG_H

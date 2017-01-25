#ifndef SUBJECTDIALOG_H
#define SUBJECTDIALOG_H

#include <QWidget>
#include <QString>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class subjectdialog;
}

class subjectdialog : public QWidget
{
    Q_OBJECT

public:
    explicit subjectdialog(QWidget *parent = 0);
    ~subjectdialog();

void setSemesterList(QStringList _list);
bool result(QString &_semester, QString &_subject);

private:
    bool ok;
    QString semester;
    QString subject;
    QStringList _SemesterList;

    Ui::subjectdialog *ui;

private slots:
    void handleButtonPressed();

signals:
    void subjectDialog_ok();

};

#endif // SUBJECTDIALOG_H

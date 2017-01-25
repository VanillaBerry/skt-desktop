#ifndef ADD_SUBJECTDIALOG_H
#define ADD_SUBJECTDIALOG_H

#include <QString>
#include <QWidget>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
    class add_SubjectDialog;
}

class add_SubjectDialog: public QWidget
{
    Q_OBJECT

public:
    add_SubjectDialog();
    add_SubjectDialog(QStringList _list);
    ~add_SubjectDialog();

bool result(QString &_semester, QString &_subject);
void show();

protected:
    QWidget *_dialog;
    QHBoxLayout *_layout;
    QComboBox *_semester;
    QLineEdit *_line;
    QPushButton *_addSubject;

private:
    bool ok;
    QString semester;
    QString subject;

private slots:
void handleButtonPressed();

signals:

void subjectDialog_ok();

};

#endif // ADD_SUBJECTDIALOG_H

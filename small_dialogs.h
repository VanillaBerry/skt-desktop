#ifndef SMALL_DIALOGS_H
#define SMALL_DIALOGS_H

#include <QWidget>
#include <QLabel>

namespace Ui {
    class add_subject;
}

class add_subject : public QWidget
{
    Q_OBJECT

public:
    explicit add_subject(QWidget *parent = 0);
    ~add_subject();

private:
    QString _semester;
    QString _subject;


};

#endif // SMALL_DIALOGS_H

/*namespace Ui {
class add_lecture;
class add_subject;
}

class add_lecture : public QWidget
{
    Q_OBJECT

public:
    explicit add_lecture(QWidget *parent = 0);
    ~add_lecture();

private:
    QString _semester;
    QString _subject;
    QString _lecture;

};*/

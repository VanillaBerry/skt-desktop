#ifndef APP_DATABASE_H
#define APP_DATABASE_H

#include <QtSql>
#include <QStandardItemModel>

class app_database
{
public:
    app_database();
    QSqlError databaseInit();

    QStandardItemModel* app_db_model();


// ADD PROCEDURES
    void add_Semester(QString _parent, QString _title, QString _tags="");
    void add_Semester(QString _title, QString _tags="");

    void add_Subject(QString _parent, QString _title, QString _tags="");
    void add_Lecture(QString _parent, QString _title, QString _tags="");
    void add_Page(QString _parent, QString _title, QString _tags="");

// GET LIST PROCEDURES
QStringList db_SemesterList();

QStringList db_SubjectsList();
QStringList db_SubjectsList(QString _semester);

QStringList db_LecturesList();
QStringList db_LecturesList(QString _subject);

QStringList db_PagesList();
QStringList db_PagesList(QString _lecture);


/*    app_db_create();
    app_db_use();*/

private:
    void addSubjects_toItem(QStandardItem *_item);
    void addLectures_toItem(QStandardItem *_item);
    void addPages_toItem(QStandardItem *_item);

    void add_Item(QString _parent, int _level, QString _title, QString _tags="");

    void setStorageFile(QString str);
    QString StorageFilename;

// MODEL ROOT
    QStandardItemModel* standardModel;
    QStandardItem *rootNode;

};



#endif // APP_DATABASE_H

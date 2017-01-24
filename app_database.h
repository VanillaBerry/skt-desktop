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




/*    app_db_create();
    app_db_use();*/

private:

    void add_Item(QString _parent, int _level, QString _title, QString _tags="");

    void setStorageFile(QString str);
    QString StorageFilename;

// MODEL ROOT
    QStandardItemModel* standardModel;
    QStandardItem *rootNode;

};



#endif // APP_DATABASE_H

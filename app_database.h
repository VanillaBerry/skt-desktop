#ifndef APP_DATABASE_H
#define APP_DATABASE_H

#include <QtSql>

class app_database
{
public:
    app_database();
    QSqlError databaseInit();


void add_Semester(QString _parent, QString _title, QString _tags="");
void add_Subject(QString _parent, QString _title, QString _tags="");
void add_Lecture(QString _parent, QString _title, QString _tags="");
void add_Page(QString _parent, QString _title, QString _tags="");



/*    app_db_create();
    app_db_use();*/

private:

    void add_Item();

    void setStorageFile(QString str);
    QString StorageFilename;

};



#endif // APP_DATABASE_H

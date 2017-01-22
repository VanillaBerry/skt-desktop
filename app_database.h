#ifndef APP_DATABASE_H
#define APP_DATABASE_H

#include <QtSql>

class app_database
{
public:
    app_database();
    QSqlError databaseInit();





/*    app_db_create();
    app_db_use();*/

private:
void setStorageFile(QString str);
QString StorageFilename;

};



#endif // APP_DATABASE_H

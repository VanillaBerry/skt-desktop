#include "app_database.h"

app_database::app_database()
{};

QSqlError app_database::databaseInit(){

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    if (StorageFilename.isEmpty()) StorageFilename="appDatabase.db";
    db.setDatabaseName(StorageFilename);

    /*---ERROR---*/
    if (!db.open())
            return db.lastError();
    /*---ERROR---*/

    return QSqlError();
};


void app_database::setStorageFile(QString str){
    StorageFilename=str;
};

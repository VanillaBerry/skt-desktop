#include "app_database.h"
#include <QCryptographicHash>
#include <QString>

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

    /*--list of tables in database--*/
    QSqlQuery _createTable;
    QStringList tables = db.tables();

    if (!tables.contains("pagebook", Qt::CaseInsensitive))
     {
        _createTable.prepare("CREATE TABLE pagebook(id varchar primary key, parent varchar, level integer, title varchar, tags varchar)");
        _createTable.exec();
     };

    if (!tables.contains("imagelist", Qt::CaseInsensitive))
     {
       //do something
     };



    return QSqlError();
};


void app_database::setStorageFile(QString str){
    StorageFilename=str;
};

void add_Item(QString _parent, int _level, QString _title, QString _tags){
// HASH WILL BE USED AS ID
    QString _id = _parent;
    QByteArray _ba =_id.toUtf8();
    QString id = QCryptographicHash::hash(_ba, QCryptographicHash::Md5).toHex();

// ADD ITEM TO DATABASE
    QSqlQuery query;

    query.prepare("INSERT INTO pagebook (id, parent, level, title, tags) VALUES (:id, :parent, :level, :title, :tags);");
    query.bindValue(":id", id);
    query.bindValue(":parent", _parent);
    query.bindValue(":level", _level);
    query.bindValue(":title", _title);
    query.bindValue(":tags", _tags);
    query.exec();
};


void add_Semester(QString _parent, QString _title, QString _tags=""){
    add_Item(_parent, 1, _title, _tags);
};

void add_Subject(QString _parent, QString _title, QString _tags=""){
    add_Item(_parent, 2, _title, _tags);
};

void add_Lecture(QString _parent, QString _title, QString _tags=""){
    add_Item(_parent, 3, _title, _tags);
};

void add_Page(QString _parent, QString _title, QString _tags=""){
    add_Item(_parent, 4, _title, _tags);
};

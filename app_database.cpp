#include "app_database.h"
#include <QCryptographicHash>
#include <QString>

app_database::app_database()
{};

QSqlError app_database::databaseInit(){

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    if (StorageFilename.isEmpty()) StorageFilename="crabDatabase.db";

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

void app_database::add_Item(QString _parent, int _level, QString _title, QString _tags){
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

/*--- ADD PROCEDURES ---*/

void app_database::add_Semester(QString _parent, QString _title, QString _tags){
    _parent="root";
    add_Item(_parent, 1, _title, _tags);
};

void app_database::add_Semester(QString _title, QString _tags){
    add_Item("root", 1, _title, _tags);
};

void app_database::add_Subject(QString _parent, QString _title, QString _tags){
    add_Item(_parent, 2, _title, _tags);
};

void app_database::add_Lecture(QString _parent, QString _title, QString _tags){
    add_Item(_parent, 3, _title, _tags);
};

void app_database::add_Page(QString _parent, QString _title, QString _tags){
    add_Item(_parent, 4, _title, _tags);
};

/*--- ADD PROCEDURES ---*/


QStandardItemModel* app_database::app_db_model(){

    standardModel = new QStandardItemModel();
    rootNode = standardModel->invisibleRootItem();

    QStringList list;
    list<<"SEMESTER"; //<<"DISCIPLINE";

    standardModel->setHorizontalHeaderLabels(list);

/*      QStandardItem *rootNode = standardModel->invisibleRootItem();*/

    QStandardItem *rightItem = new QStandardItem("RIGHT");
    QStandardItem *leftItem = new QStandardItem("LEFT");

    QStandardItem *Item1 = new QStandardItem("1");
    QStandardItem *Item2 = new QStandardItem("2");
    QStandardItem *Item3 = new QStandardItem("3");
    QStandardItem *Item4 = new QStandardItem("4");

    rootNode->appendRow(rightItem);
    rootNode->appendRow(leftItem);

    rightItem->appendRow(Item1);
    rightItem->appendRow(Item2);

    leftItem->appendRow(Item3);
    leftItem->appendRow(Item4);

    return standardModel;

};

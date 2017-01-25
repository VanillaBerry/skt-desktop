#include "app_database.h"
#include <QCryptographicHash>
#include <QString>
#include <QDateTime>

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
    QString _id = _parent+_title+_tags;
    QDateTime _datetime;
    _datetime.currentDateTimeUtc();
    _id += _datetime.toString("dd.MM.yyyy hh:mm:ss.zzz");

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

// CHECHK WHETHER SEMESTER IS ON DATABASE
    QSqlQuery query;
    query.prepare("SELECT * FROM pagebook WHERE title = ? AND level = 1");
    query.bindValue(0, _title);
    query.exec();

//  IF QUERY IS EMPTY, DO NOTHING
    if (!query.next())
    add_Item(_parent, 1, _title, _tags);
};

void app_database::add_Semester(QString _title, QString _tags){
    add_Semester("root", _title, _tags);
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
/* QStandardItem *rootNode = standardModel->invisibleRootItem(); */
    rootNode = standardModel->invisibleRootItem();

    QStringList list;
    list<<"NAME"<<"TAGS";

    standardModel->setHorizontalHeaderLabels(list);

/* SEMESTER LIST */
    QSqlQuery query;
    query.prepare("SELECT * FROM pagebook WHERE level = 1");
    query.exec();

//  QList<QStandardItem> semesterlist;
    QString semestername;
    QString tags;
    QList<QStandardItem *> semester_;
//    QStandardItem *record;

    while (query.next())
    {
        semestername = query.value("title").toString();
        tags = query.value("tags").toString();
        semester_.clear();
        semester_ << new QStandardItem(semestername)<< new QStandardItem(tags);
//        addSubjects_toItem(semester_);
// YOU CAN NOT EDIT
        semester_[0]->setEditable(false);
        semester_[1]->setEditable(false);

   //     record = new QStandardItem(semestername);
   //     rootNode->appendRow(record);

        rootNode->appendRow(semester_);
    };

    return standardModel;
};







// GET LIST PROCEDURES
QStringList app_database::db_SemesterList(){
    /* SEMESTER LIST */
        QSqlQuery query;
        query.prepare("SELECT * FROM pagebook WHERE level = 1");
        query.exec();

    QStringList SemesterList;

    while (query.next())
        SemesterList+=query.value("title").toString();

    return SemesterList;
};

void app_database::addSubjects_toItem(QStandardItem *_item){


};

/*
    void addLectures_toItem(QStandardItem *_item);
    void addPages_toItem(QStandardItem *_item);*/


/*
QStringList app_database::db_SubjectsList();
QStringList app_database::db_SubjectsList(QString _semester);

QStringList app_database::db_LecturesList();
QStringList app_database::db_LecturesList(QString _subject);

QStringList app_database::db_PagesList();
QStringList app_database::db_PagesList(QString _lecture);*/

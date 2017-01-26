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

void app_database::add_Item(QString _parentID, int _level, QString _title, QString _tags){
// HASH WILL BE USED AS ID
    QString _id = _parentID+_title+_tags;
    QDateTime _datetime;
    _datetime.currentDateTimeUtc();
    _id += _datetime.toString("dd.MM.yyyy hh:mm:ss.zzz");

    QByteArray _ba =_id.toUtf8();
    QString id = QCryptographicHash::hash(_ba, QCryptographicHash::Md5).toHex();
    id.truncate(8);

// ADD ITEM TO DATABASE
    QSqlQuery query;

    query.prepare("INSERT INTO pagebook (id, parent, level, title, tags) VALUES (:id, :parent, :level, :title, :tags);");
    query.bindValue(":id", id);
    query.bindValue(":parent", _parentID);
    query.bindValue(":level", _level);
    query.bindValue(":title", _title);
    query.bindValue(":tags", _tags);
    query.exec();
};

/*--- ADD PROCEDURES ---*/

void app_database::add_Semester(QString _parent, QString _title, QString _tags){
    _parent="root";

// CHECK WHETHER SEMESTER IS ON DATABASE
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
// CHECHK WHETHER PARENT SEMESTER IS ON DATABASE
    QSqlQuery query;
    query.prepare("SELECT * FROM pagebook WHERE title = ? AND level = 1");
    query.bindValue(0, _parent);
    query.exec();

    if (query.next())
    {
        QString _parentID=query.value("id").toString();
        add_Item(_parentID, 2, _title, _tags);
    }
//  IF QUERY IS EMPTY, DO NOTHING

};

void app_database::add_LectureFromID(QString _parentID, QString _title, QString _tags){
    add_Item(_parentID, 3, _title, _tags);
};

/*
void app_database::add_Page(QString _parent, QString _title, QString _tags){
    add_Item(_parent, 4, _title, _tags);
};
*/

/*--- ADD PROCEDURES ---*/


QStandardItemModel* app_database::app_db_model(){

    standardModel = new QStandardItemModel();
/* QStandardItem *rootNode = standardModel->invisibleRootItem(); */
    rootNode = standardModel->invisibleRootItem();

    QStringList list;
    list<<"NAME"<<"TAGS"<<"ID";

    standardModel->setHorizontalHeaderLabels(list);

/* SEMESTER LIST */
    QSqlQuery query;
    query.prepare("SELECT * FROM pagebook WHERE level = 1");
    query.exec();

//  QList<QStandardItem> semesterlist;
    QString semestername;
    QString tags;
    QString id;
    QList<QStandardItem *> semester_;

    while (query.next())
    {
        semestername = query.value("title").toString();
        tags = query.value("tags").toString();
        id = query.value("id").toString();

        semester_.clear();
        semester_ << new QStandardItem(semestername)<< new QStandardItem(tags)<< new QStandardItem(id);

        addSubjects_toItem(semester_);

// YOU CAN NOT EDIT
        semester_[0]->setEditable(false);
        semester_[1]->setEditable(false);
        semester_[2]->setEditable(false);

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

void app_database::addSubjects_toItem(QList<QStandardItem *> &_item){
        QString _parentid = _item[2]->text();
        QList<QStandardItem *> newsubject;

        QSqlQuery query;
        query.prepare("SELECT * FROM pagebook WHERE parent = ? AND level = 2");
        query.bindValue(0, _parentid);
        query.exec();

        QString subjectname;
        QString tags;
        QString id;

        while (query.next())
        {
            subjectname = query.value("title").toString();
            tags = query.value("tags").toString();
            id = query.value("id").toString();

            newsubject.clear();
            newsubject << new QStandardItem(subjectname)<< new QStandardItem(tags)<< new QStandardItem(id);

            addLectures_toItem(newsubject);
    // YOU CAN NOT EDIT
            newsubject[0]->setEditable(false);
            newsubject[1]->setEditable(false);
            newsubject[2]->setEditable(false);

            _item[0]->appendRow(newsubject);
        };
};


void app_database::addLectures_toItem(QList<QStandardItem *> &_item){
    QString _parentid = _item[2]->text();
    QList<QStandardItem *> newlecture;

    QSqlQuery query;
    query.prepare("SELECT * FROM pagebook WHERE parent = ? AND level = 3");
    query.bindValue(0, _parentid);
    query.exec();

    QString subjectname;
    QString tags;
    QString id;

    while (query.next())
    {
        subjectname = query.value("title").toString();
        tags = query.value("tags").toString();
        id = query.value("id").toString();

        newlecture.clear();
        newlecture << new QStandardItem(subjectname)<< new QStandardItem(tags)<< new QStandardItem(id);

        addPages_toItem(newlecture);
// YOU CAN NOT EDIT
        newlecture[0]->setEditable(false);
        newlecture[1]->setEditable(false);
        newlecture[2]->setEditable(false);

        _item[0]->appendRow(newlecture);
    };
};


void app_database::addPages_toItem(QList<QStandardItem *> &_item){
    QString _parentid = _item[2]->text();
    QList<QStandardItem *> newpage;

    QSqlQuery query;
    query.prepare("SELECT * FROM pagebook WHERE parent = ? AND level = 4");
    query.bindValue(0, _parentid);
    query.exec();

    QString subjectname;
    QString tags;
    QString id;

    while (query.next())
    {
        subjectname = query.value("title").toString();
        tags = query.value("tags").toString();
        id = query.value("id").toString();

        newpage.clear();
        newpage << new QStandardItem(subjectname)<< new QStandardItem(tags)<< new QStandardItem(id);

// YOU CAN NOT EDIT
        newpage[0]->setEditable(false);
        newpage[1]->setEditable(false);
        newpage[2]->setEditable(false);

        _item[0]->appendRow(newpage);
    };
};



QStringList app_database::db_SubjectsList(){
    QStringList result;

    return result;
};

QStringList app_database::db_SubjectsList(QString _semester){
    QStringList result;

    /* SUBJECTS LIST */
        QSqlQuery query;
        query.prepare("SELECT * FROM pagebook WHERE title = ? AND level = 1");
        query.bindValue(0, _semester);
        query.exec();

    if (!query.next()) return result;

    QString id = query.value("id").toString();

    query.prepare("SELECT * FROM pagebook WHERE parent = ? AND level = 2");
    query.bindValue(0, id);
    query.exec();

    while (query.next())
        result+=query.value("title").toString();

    return result;

};

void app_database::add_Lecture(QString _semester, QString _subject, QString _title, QString _tags){
    QSqlQuery query;
    query.prepare("SELECT * FROM pagebook WHERE title = ? AND level = 2");
    query.bindValue(0, _subject);
    query.exec();

    QString id, name;
    QSqlQuery secondQuery;
    bool finded=false;

    while (query.next() and (!finded))
    {
        id = query.value("parent").toString();

        secondQuery.prepare("SELECT * FROM pagebook WHERE id = ? AND level = 1");
        secondQuery.bindValue(0, id);
        secondQuery.exec();

        while (secondQuery.next()) {
            name = secondQuery.value("title").toString();
            if (name==_semester)
            {
               id = query.value("id").toString();
               finded=true;
            };
        };
    };

// CHECK IS THERE LECTION WITH SUCH TITLE
    if (finded)
    {
        query.prepare("SELECT * FROM pagebook WHERE title = ? AND level = 3 AND parent = ?");
        query.bindValue(0, _title);
        query.bindValue(1, id);
        query.exec();

        if (!query.next())
        add_Item(id, 3, _title, _tags);

    };
    // ELSE DO NOTHING
};

/*
QStringList app_database::db_LecturesList();
QStringList app_database::db_LecturesList(QString _subject);

QStringList app_database::db_PagesList();
QStringList app_database::db_PagesList(QString _lecture);*/

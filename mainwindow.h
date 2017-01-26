#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "image_editor.h"
#include "app_database.h"
#include "subjectdialog.h"
#include "lecturedialog.h"

#include <QTreeView>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QListView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;

// IMAGE EDITOR
    bool EditorIsOpen;
    image_editor *img_edit;
    QString imgLocation;

// TREE + DATABASE
    QTreeView * treeView;
    app_database *app_db;
    QStandardItemModel *standardModel_tree;

    subjectdialog *subj_diag;
    lecturedialog *lect_diag;

    void refresh_tree();

// LIST OF IMAGES
    QListView * listView;
    QStandardItemModel *standardModel_list;
    void createA_List();

// CURRENT ELEMENT
    QString semester;
    QString subject;
    QString lecture;
    QString page;

/*public:
    void setSemesterName(QString _semester);
    void setSubjectName(QString _semester);
    void setLectureName(QString _semester);
    void setPageName(QString _semester);*/


private slots:

// SLOTS FOR BUTTONS
    void handlebutton_New();
    void handlebutton_Exit();
    void handlebutton_ImgLocation();

// ONE SLOT TO SENSE IMAGE EDITOR
    void handleEditor_Closing();
    void handleImageLocationChanged();

// SLOTS FOR MENU BUTTONS
    void handleA_database();
    void handle_addSemester();
    void handle_addSubject();
    void handle_addLecture();

// SLOTS FOR PAGE SELECTING
    void downline_SemesterPressed();
    void downline_SubjectPressed();
//    void downline_LecturePressed();
    void handle_addPage();

// SLOT FOR SUBJDIAG
    void handle_subjDialogOK();

// SLOTS FOR LECTUREDIAG
    void handle_lectureDialogOK();
    void handle_lectureDialogSemesterPressed();

public: signals:
// JUST A CLOSING SIGNAL
    void closing();

};

#endif // MAINWINDOW_H

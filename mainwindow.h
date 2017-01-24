#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "image_editor.h"
#include "app_database.h"
#include <QTreeView>
#include <QStandardItem>
#include <QStandardItemModel>

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

// TREE + DATABASE
    QTreeView * treeView;
    app_database *app_db;
    QStandardItemModel* standardModel;


private slots:

// SLOTS FOR BUTTONS
    void handlebutton_New();
    void handlebutton_Exit();

// ONE SLOT TO SENSE WHETHER IMAGE EDITORIS CLOSED
    void handleEditor_Closing();

// SLOTS FOR MENU BUTTONS
    void handleA_database();
    void handle_addSemester();
    void handle_addSubject();
    void handle_addLecture();
    void handle_addPage();



public: signals:

// JUST A CLOSING SIGNAL
void closing();

};

#endif // MAINWINDOW_H

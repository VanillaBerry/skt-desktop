#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "image_editor.h"
#include "app_database.h"
#include <QTreeView>
#include <QStandardItem>

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
    bool EditorIsOpen;
    image_editor *img_edit;
    QTreeView * treeView;
    app_database *app_db;
 //   QStandardItem *rootNode;

void InitAppDatabase();

private slots:

    void handlebutton_New();
    void handlebutton_Exit();
    void handleEditor_Closing();
    void handleA_database();

public: signals:
void closing();
};

#endif // MAINWINDOW_H

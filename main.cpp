#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include "img_edit/img_effects.h"
#include "image_editor.h"
#include <QScrollArea>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    QImage img_orig;
    img_orig.load("../skt-desktop/bitmaps/gus.jpg");


    image_editor img_edit;

    img_edit.setImage(img_orig);
    img_edit.show();


    img_orig.save("../skt-desktop/bitmaps/gus_2.jpg",0,100);

    return a.exec();
}

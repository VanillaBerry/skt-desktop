#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include "img_edit/img_effects.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

     QLabel lbl;

     QImage img_orig;
     img_orig.load("../skt-desktop/bitmaps/hokusai.jpg");

     LiqudScale(img_orig,200);
     CounterClockwiseRotation(img_orig);
     LiqudScale(img_orig,300);
     ClockwiseRotation(img_orig);

    lbl.setPixmap(QPixmap::fromImage(img_orig, Qt::AutoColor));

    lbl.show();
    img_orig.save("../skt-desktop/bitmaps/hokusai_liq.jpg",0,100);

    return a.exec();
}

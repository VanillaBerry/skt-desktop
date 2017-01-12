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
//   lbl.setPixmap(QPixmap("./bitmaps/diana.bmp"));
//   lbl.show();

//   QImage * img=new QImage("E:/GitHub/Repositories/skt-desktop/bitmaps/geometriche.bmp");
//   QImage * img=new QImage("../skt-desktop/bitmaps/geometriche.bmp");

     QImage img_orig, img_rgb32, img_gray, img_trns;
     img_orig.load("../skt-desktop/bitmaps/diana.bmp");

     img_rgb32=img_orig.convertToFormat(QImage::Format_RGB32, Qt::AutoColor);
//     toGray(img_orig);

//     GrayBlur(img_orig);
     GrayDivision(img_orig, 5);


//    Contrast(img_orig);


//   QImage n_img = img->scaled(1200, 900, Qt::IgnoreAspectRatio, Qt::FastTransformation);


    lbl.setPixmap(QPixmap::fromImage(img_orig, Qt::AutoColor));

    lbl.show();
    img_orig.save("E:/GitHub/Repositories/skt-desktop/bitmaps/diana4.bmp",0,100);

    return a.exec();
}

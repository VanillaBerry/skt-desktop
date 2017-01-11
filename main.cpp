#include "mainwindow.h"
#include <QApplication>
#include <QLabel>

bool toGray(QImage &img_orig){
    int h_img = img_orig.height();
    int w_img = img_orig.width();
    int aver_value;
    QRgb one_point;


    for(int i=0; i<h_img; ++i)
    for(int j=0; j<w_img; ++j)
    {
        one_point=img_orig.pixel(j,i);
        aver_value=qGray(one_point);
        one_point=qRgb(aver_value,aver_value,aver_value);
        img_orig.setPixelColor(j,i,one_point);

    };

return true;
};

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
     img_orig.load("../skt-desktop/bitmaps/geometriche.bmp");

     int h_img = img_orig.height();
     int w_img = img_orig.width();

     toGray(img_orig);
     img_rgb32=img_orig.convertToFormat(QImage::Format_RGB32, Qt::AutoColor);

//koefficienty dlya razmitia po gaussu
    float gauss[5];
    gauss[0]=0.028087;
    gauss[1]=0.23431;
    gauss[2]=0.475207;
    gauss[3]=gauss[1];
    gauss[4]=gauss[0];
//koefficienty dlya razmitia po gaussu





//   QImage n_img = img->scaled(1200, 900, Qt::IgnoreAspectRatio, Qt::FastTransformation);






    lbl.setPixmap(QPixmap::fromImage(img_orig, Qt::AutoColor));

    lbl.show();

    return a.exec();
}

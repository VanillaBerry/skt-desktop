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

void Blur(QImage &img){
    int h_img = img.height();
    int w_img = img.width();

    int** img_matrix=new int* [w_img];
    float** img_matrix_av1=new float*[w_img];
    float** img_matrix_av2=new float*[w_img];
    float** img_matrix_new=new float*[w_img];


    for(int i=0; i<w_img; ++i){
        img_matrix[i]=new int[h_img];
        img_matrix_av1[i]=new float[h_img];
        img_matrix_av2[i]=new float[h_img];
        img_matrix_new[i]=new float[h_img];
    };


    QRgb one_point;

    for(int i=0; i<h_img; ++i)
    for(int j=0; j<w_img; ++j)
    {
        one_point=img.pixel(j,i);
        img_matrix[j][i]=qGray(one_point);
    };

    float gauss[5];
    gauss[0]=0.028087;
    gauss[1]=0.23431;
    gauss[2]=0.475207;
    gauss[3]=gauss[1];
    gauss[4]=gauss[0];


    for(int i=2; i<h_img-2; ++i)
    for(int j=0; j<w_img; ++j)
    {
        img_matrix_av1[j][i]=gauss[0]*img_matrix[j][i-2];
        img_matrix_av1[j][i]+=gauss[1]*img_matrix[j][i-1];
        img_matrix_av1[j][i]+=gauss[2]*img_matrix[j][i];
        img_matrix_av1[j][i]+=gauss[3]*img_matrix[j][i+1];
        img_matrix_av1[j][i]+=gauss[4]*img_matrix[j][i+2];

    };

    for(int j=0; j<w_img; ++j)
    {
        img_matrix_av1[j][0]=img_matrix[j][0];
        img_matrix_av1[j][1]=img_matrix[j][1];
        img_matrix_av1[j][h_img-2]=img_matrix[j][h_img-2];
        img_matrix_av1[j][h_img-1]=img_matrix[j][h_img-1];
    };



    for(int i=0; i<h_img; ++i)
    for(int j=2; j<w_img-2; ++j)
    {
        img_matrix_av2[j][i]=gauss[0]*img_matrix_av1[j-2][i];
        img_matrix_av2[j][i]+=gauss[1]*img_matrix_av1[j-1][i];
        img_matrix_av2[j][i]+=gauss[2]*img_matrix_av1[j][i];
        img_matrix_av2[j][i]+=gauss[3]*img_matrix_av1[j+1][i];
        img_matrix_av2[j][i]+=gauss[4]*img_matrix_av1[j+2][i];

    };

    for(int i=0; i<h_img; ++i)
    {
        img_matrix_av2[0][i]=img_matrix_av1[0][i];
        img_matrix_av2[1][i]=img_matrix_av1[1][i];
        img_matrix_av2[w_img-2][i]=img_matrix_av1[w_img-2][i];
        img_matrix_av2[w_img-1][i]=img_matrix_av1[w_img-1][i];

    };



    int new_value;

    for(int i=2; i<h_img-2; ++i)
    for(int j=2; j<w_img-2; ++j)
    {
       new_value=floor(455*img_matrix[j][i]/(img_matrix_av2[j][i]+1))-200;

        if (new_value>255) new_value=255;
        if (new_value<0) new_value=0;

        one_point=qRgb(new_value,new_value,new_value);
        img.setPixelColor(j,i,one_point);

    };





    for(int i=0; i<w_img; ++i){
        delete [] img_matrix[i];
        delete [] img_matrix_av1[i];
        delete [] img_matrix_av2[i];
        delete [] img_matrix_new[i];
    };


    delete [] img_matrix;
    delete [] img_matrix_av1;
    delete [] img_matrix_av2;
    delete [] img_matrix_new;

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

     img_rgb32=img_orig.convertToFormat(QImage::Format_RGB32, Qt::AutoColor);
     toGray(img_orig);

     Blur(img_orig);
//    Contrast(img_orig);


//   QImage n_img = img->scaled(1200, 900, Qt::IgnoreAspectRatio, Qt::FastTransformation);






    lbl.setPixmap(QPixmap::fromImage(img_orig, Qt::AutoColor));

    lbl.show();
    img_orig.save("E:/GitHub/Repositories/skt-desktop/bitmaps/geometriche3.bmp",0,100);

    return a.exec();
}

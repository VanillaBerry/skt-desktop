#include <QImage>
#include "img_edit/img_effects.h"

int Gray_from_RGB(QRgb color){
    int red, green, blue;
    int result;

    red=qRed(color);
    green=qGreen(color);
    blue=qBlue(color);

    result=floor((red+green+blue)/3);
    if (result<0) result=0;
    if (result>255) result=255;

    return  result;
};

bool toGray(QImage &img_orig){
    int h_img = img_orig.height();
    int w_img = img_orig.width();
    int aver_value;
    QRgb one_point;

    for(int i=0; i<h_img; ++i)
    for(int j=0; j<w_img; ++j)
    {
        one_point=img_orig.pixel(j,i);
        aver_value=Gray_from_RGB(one_point);
        one_point=qRgb(aver_value,aver_value,aver_value);
        img_orig.setPixelColor(j,i,one_point);

    };

return true;
};

void GrayGaussBlur(QImage &img){
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
        img_matrix[j][i]=Gray_from_RGB(one_point);
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
       new_value=floor(255*img_matrix[j][i]/(img_matrix_av2[j][i]+1));

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

void GrayBlur(QImage &img){
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
        img_matrix[j][i]=Gray_from_RGB(one_point);
    };

    for(int i=2; i<h_img-2; ++i)
    for(int j=0; j<w_img; ++j)
    {
        img_matrix_av1[j][i]=img_matrix[j][i-2]/5;
        img_matrix_av1[j][i]+=img_matrix[j][i-1]/5;
        img_matrix_av1[j][i]+=img_matrix[j][i]/5;
        img_matrix_av1[j][i]+=img_matrix[j][i+1]/5;
        img_matrix_av1[j][i]+=img_matrix[j][i+2]/5;

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
        img_matrix_av2[j][i]=img_matrix_av1[j-2][i]/5;
        img_matrix_av2[j][i]+=img_matrix_av1[j-1][i]/5;
        img_matrix_av2[j][i]+=img_matrix_av1[j][i]/5;
        img_matrix_av2[j][i]+=img_matrix_av1[j+1][i]/5;
        img_matrix_av2[j][i]+=img_matrix_av1[j+2][i]/5;

    };

    for(int i=0; i<h_img; ++i)
    {
        img_matrix_av2[0][i]=img_matrix_av1[0][i];
        img_matrix_av2[1][i]=img_matrix_av1[1][i];
        img_matrix_av2[w_img-2][i]=img_matrix_av1[w_img-2][i];
        img_matrix_av2[w_img-1][i]=img_matrix_av1[w_img-1][i];

    };

    int new_value;

    for(int i=0; i<h_img; ++i)
    for(int j=0; j<w_img; ++j)
    {
        new_value=floor(img_matrix_av2[j][i]);

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

void GrayDivision(QImage &img_to_proc, QImage img_divisor, int intensity){

    if (intensity<1) intensity=1;
    if (intensity>10) intensity=10;

    int h_img=qMin(img_to_proc.height(),img_divisor.height());
    int w_img=qMin(img_to_proc.width(),img_divisor.width());

    float relation, rel_;
    int proc_gray, divisor_gray;
    int new_value;
    QRgb one_point;

    for(int i=0; i<h_img; ++i)
    for(int j=0; j<w_img; ++j)
    {
        relation=1.0;
        proc_gray=Gray_from_RGB(img_to_proc.pixel(j,i));
        divisor_gray=Gray_from_RGB(img_divisor.pixel(j,i));
        rel_=((float)proc_gray/(divisor_gray+1));

        for(int k=0; k<intensity; ++k)
            relation=relation*rel_;


       new_value=floor(255*relation);

        if (new_value>255) new_value=255;
        if (new_value<0) new_value=0;

        one_point=qRgb(new_value,new_value,new_value);
        img_to_proc.setPixelColor(j,i,one_point);
    };

};

int * EnergyChain(QImage img){

    int w_img=img.width();
    int h_img=img.height();

    if (w_img<10) return NULL;
    if (h_img<10) return NULL;

    int **intensity_matrix = new int*[w_img];
    int **chain_matrix = new int*[w_img];

    for(int i=0; i<w_img; ++i)
    {
        chain_matrix[i]=new int[h_img];
        intensity_matrix[i]=new int[h_img];
    };

    int right,down,self,medium;

    for(int i=0; i<w_img-1; ++i)
    for(int j=0; j<h_img-1; ++j)
    {
        right=qRed(img.pixel(i+1,j));
        down=qRed(img.pixel(i,j+1));
        self=qRed(img.pixel(i,j));

        medium=(qAbs(right-self)+qAbs(down-self))/2;
        intensity_matrix[i][j]=medium;

        right=qGreen(img.pixel(i+1,j));
        down=qGreen(img.pixel(i,j+1));
        self=qGreen(img.pixel(i,j));

        medium=(qAbs(right-self)+qAbs(down-self))/2;
        intensity_matrix[i][j]+=medium;

        right=qBlue(img.pixel(i+1,j));
        down=qBlue(img.pixel(i,j+1));
        self=qBlue(img.pixel(i,j));

        medium=(qAbs(right-self)+qAbs(down-self))/2;
        intensity_matrix[i][j]+=medium;
    };

    for(int i=0; i<w_img-1; ++i)
    {
        right=Gray_from_RGB(img.pixel(i+1,h_img-1));
        self=Gray_from_RGB(img.pixel(i,h_img-1));
        medium=qAbs(right-self);
        intensity_matrix[i][h_img-1]=medium;
    };

    for(int j=0; j<h_img-1; ++j)
    {
        down=Gray_from_RGB(img.pixel(w_img-1,j+1));
        self=Gray_from_RGB(img.pixel(w_img-1,j));

        medium=qAbs(down-self);
        intensity_matrix[w_img-1][j]=medium;
    };

    intensity_matrix[w_img-1][h_img-1]=0;

    for(int i=0; i<w_img; ++i)
        chain_matrix[i][0]=intensity_matrix[i][0];

    int min_sum;

    for(int j=1; j<h_img; ++j)
    for(int i=0; i<w_img; ++i)
        {
        if (i==0) min_sum=qMin(chain_matrix[i][j-1], chain_matrix[i+1][j-1]);
        if (i==(w_img-1)) min_sum=qMin(chain_matrix[i][j-1], chain_matrix[i-1][j-1]);

        if ((i>0)and(i<(w_img-1)))
        {
            min_sum=qMin(chain_matrix[i-1][j-1],chain_matrix[i][j-1]);
            min_sum=qMin(chain_matrix[i+1][j-1], min_sum);
        };

        chain_matrix[i][j]=min_sum+intensity_matrix[i][j];
       };

    int * chain=new int[h_img];

    int min_elem=chain_matrix[0][h_img-1];
    int elem;
    chain[h_img-1]=0;

    for(int i=1; i<w_img; ++i)
    {
        elem=chain_matrix[i][h_img-1];

        if (elem<min_elem)
        {
            min_elem=elem;
            chain[h_img-1]=i;
        };
    };

    int center, left, ch;

    for(int j=1; j<h_img; ++j)
    {
        ch=chain[h_img-j];
        if (ch>0)  right=chain_matrix[ch-1][h_img-j-1]; else right=2000000000;
        center=chain_matrix[ch][h_img-j-1];
        if (ch<w_img-1) left=chain_matrix[ch+1][h_img-j-1]; else left=2000000000;

        chain[h_img-j-1]=ch;

        if ((right<center)and(right<left)) chain[h_img-j-1]=ch-1;
        if ((left<center)and(left<right)) chain[h_img-j-1]=ch+1;
    };

    for(int i=0; i<w_img; ++i)
    {
       delete [] chain_matrix[i];
       delete [] intensity_matrix[i];
    }

    delete [] chain_matrix;
    delete [] intensity_matrix;

    return chain;
};

void GrayDivision(QImage &img_to_proc, int intensity){
    QImage img_divisor=img_to_proc;
    GrayBlur(img_divisor);

    GrayDivision(img_to_proc,img_divisor,intensity);
};

int * Chain(QImage img){

    int w_img=img.width();
    int h_img=img.height();

    if (w_img<10) return NULL;
    if (h_img<10) return NULL;

    QImage img_copy=img;
    GrayDivision(img_copy, 5);

    int **chain_matrix = new int*[w_img];
    for(int i=0; i<w_img; ++i)
        chain_matrix[i]=new int[h_img];

    for(int i=0; i<w_img; ++i)
        chain_matrix[i][0]=Gray_from_RGB(img_copy.pixel(i,0));

    int min_sum;

    for(int j=1; j<h_img; ++j)
    for(int i=0; i<w_img; ++i)
        {
        if (i==0) min_sum=qMin(chain_matrix[i][j-1], chain_matrix[i+1][j-1]);
        if (i==(w_img-1)) min_sum=qMin(chain_matrix[i][j-1], chain_matrix[i-1][j-1]);

        if ((i>0)and(i<(w_img-1)))
        {
            min_sum=qMin(chain_matrix[i-1][j-1],chain_matrix[i][j-1]);
            min_sum=qMin(chain_matrix[i+1][j-1], min_sum);
        };

        chain_matrix[i][j]+=min_sum;
       };

    int * chain=new int[h_img];

    int min_elem=chain_matrix[0][h_img-1];
    int elem;
    chain[h_img-1]=0;

    for(int i=1; i<w_img; ++i)
    {
        elem=chain_matrix[i][h_img-1];

        if (elem<min_elem)
        {
            min_elem=elem;
            chain[h_img-1]=i;
        };
    };

    int right, center, left, ch;

    for(int j=1; j<h_img; ++j)
    {
        ch=chain[h_img-j];
        if (ch>0)  right=chain_matrix[ch-1][h_img-j-1]; else right=2000000000;
        center=chain_matrix[ch][h_img-j-1];
        if (ch<w_img-1) left=chain_matrix[ch+1][h_img-j-1]; else left=2000000000;

        chain[h_img-j-1]=ch;

        if ((right<center)and(right<left)) chain[h_img-j-1]=ch-1;
        if ((left<center)and(left<right)) chain[h_img-j-1]=ch+1;
    };

    for(int i=0; i<w_img; ++i)
       delete [] chain_matrix[i];

    delete [] chain_matrix;

    return chain;
};

void ClockwiseRotation(QImage &img_orig){
    int h_img=img_orig.height();
    int w_img=img_orig.width();
    QRgb point;
    QImage rotated_img=QImage(h_img, w_img, QImage::Format_RGB32);

    for(int i=0; i<w_img; ++i)
    for(int j=0; j<h_img; ++j)
    {
        point=img_orig.pixel(i,j);
        rotated_img.setPixel(h_img-j-1,i,point);
    };

    img_orig=rotated_img;
};


void CounterClockwiseRotation(QImage &img_orig){
    int h_img=img_orig.height();
    int w_img=img_orig.width();
    QRgb point;
    QImage rotated_img=QImage(h_img, w_img, QImage::Format_RGB32);

    for(int i=0; i<w_img; ++i)
    for(int j=0; j<h_img; ++j)
    {
        point=img_orig.pixel(i,j);
        rotated_img.setPixel(j,w_img-i-1,point);
    };

    img_orig=rotated_img;
};


int DeleteOneChain(QImage &img_orig){
    int w_img=img_orig.width();
    int h_img=img_orig.height();

    QImage new_img=QImage(w_img-1,h_img, QImage::Format_RGB32);

    int *chain=LessEnergyWay(img_orig);

    int ch;
    QRgb point;
    int position;

    for(int j=0; j<h_img; ++j)
    {
     ch=chain[j];
     for(int i=0; i<w_img-1; ++i)
        {
         position=i;
         if (i>ch) position+=1;

         point=img_orig.pixel(position,j);
         new_img.setPixel(i,j,point);

        };
    };

    delete []chain;
    img_orig=new_img;

   return 0;
};


int LiqudScale(QImage &img_orig, int new_width){
    int w_img=img_orig.width();

    if (new_width>=w_img) return 1;
    if (img_orig.height()<3) return 1;

    while(img_orig.width()>(new_width+1))
    DeleteTwoChains(img_orig);

    if (img_orig.width()>new_width) DeleteOneChain(img_orig);

    return 0;
};

void HorizontalMirror(QImage &img_orig){
    int w_img=img_orig.width();
    int h_img=img_orig.height();
    int w_half=w_img/2;
    QRgb point1, point2;

    for(int i=0; i<w_half; ++i)
    for(int j=0; j<h_img; ++j)
    {
        point1=img_orig.pixel(i,j);
        point2=img_orig.pixel(w_img-i-1,j);

        img_orig.setPixel(i,j,point2);
        img_orig.setPixel(w_img-i-1,j,point1);
    };

};

void VerticalMirror(QImage &img_orig){
    int w_img=img_orig.width();
    int h_img=img_orig.height();
    int h_half=h_img/2;
    QRgb point1, point2;

    for(int i=0; i<w_img; ++i)
    for(int j=0; j<h_half; ++j)
    {
        point1=img_orig.pixel(i,j);
        point2=img_orig.pixel(i,h_img-j-1);

        img_orig.setPixel(i,j,point2);
        img_orig.setPixel(i,h_img-j-1,point1);
    };

};

int DeleteTwoChains(QImage &img_orig){
    DeleteOneChain(img_orig);
 //   HorizontalMirror(img_orig);
    DeleteOneChain(img_orig);
 //   HorizontalMirror(img_orig);
    return 0;
};

int * LessEnergyWay(QImage img){
    return EnergyChain(img);
};

void LiqudScaleWH(QImage &img_orig, int width, int height){
    LiqudScale(img_orig, width);
    ClockwiseRotation(img_orig);
    LiqudScale(img_orig, height);
    CounterClockwiseRotation(img_orig);
};

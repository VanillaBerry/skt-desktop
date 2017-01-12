#include <QImage>

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
void GrayDivision(QImage &img_to_proc, int intensity){
    QImage img_divisor=img_to_proc;
    GrayBlur(img_divisor);

    GrayDivision(img_to_proc,img_divisor,intensity);
};

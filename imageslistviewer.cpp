#include "imageslistviewer.h"
#include "ui_imageslistviewer.h"

imageslistviewer::imageslistviewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::imageslistviewer)
{
    ui->setupUi(this);
    ui->scrollArea_image->setBackgroundRole(QPalette::Dark);
    ui->scrollArea_image->setWidget(imagelabel);
    ui->scrollArea_image->show();

    connect(ui->pushButton_NextImage, SIGNAL (pressed()), this, SLOT(handleButton_NEXT()));
    connect(ui->pushButton_PreviousImage, SIGNAL (pressed()), this, SLOT(handleButton_PREV()));
    connect(ui->toolButton_MagMinus, SIGNAL(pressed()), this, SLOT(handleButton_zoomOUT()));
    connect(ui->toolButton_MagPlus, SIGNAL(pressed()), this, SLOT(handleButton_zoomIN()));
}

imageslistviewer::~imageslistviewer()
{
    delete ui;
}


void imageslistviewer::handleButton_zoomIN(){
    scale*=1.25;
    if (scale>5) scale=5;
    refresh();
};

void imageslistviewer::handleButton_zoomOUT(){
    scale*=0.8;
    if (scale<0.2) scale=0.2;
    refresh();
};

void imageslistviewer::refresh(){
    img_viev=img_old;
    w_pixmap=scale*img_viev.width();
    h_pixmap=scale*img_viev.height();

    img_viev=img_viev.scaled(w_pixmap, h_pixmap);
    imagelabel->setPixmap(QPixmap::fromImage(img_viev, Qt::AutoColor));

};


void imageslistviewer::set_listofIMAGES(QList<QImage> *_list){
    _listofIMAGES = _list;
};


void imageslistviewer::handleButton_PREV(){
    QImage _img = _listofIMAGES->first();
    img_old=_img;
    scale=1.0;
    refresh();
};

void imageslistviewer::handleButton_NEXT(){
    QImage _img = _listofIMAGES->first();
    img_old=_img;
    scale=1.0;
    refresh();
};

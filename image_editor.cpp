#include "image_editor.h"
#include "ui_image_editor.h"
#include "img_edit/img_effects.h"
#include "QMessageBox"
#include "QInputDialog"
#include "QCheckBox"
#include "QFileDialog"

image_editor::image_editor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::image_editor)
{
    ui->setupUi(this);
    ui->scrollArea_image->hide();

    prev=true;
    ui->checkBox_prev->setChecked(prev);

    connect(ui->pushButton_gray, SIGNAL (released()), this, SLOT (handleButton_Gray()));
    connect(ui->pushButton_reset, SIGNAL (released()), this, SLOT (handleButton_Reset()));
    connect(ui->pushButton_edges, SIGNAL (released()), this, SLOT (handleButton_Edges()));
    connect(ui->toolButton_counter, SIGNAL (released()), this, SLOT (handleButton_Counter()));
    connect(ui->toolButton_clockwise, SIGNAL (released()), this, SLOT (handleButton_Clockwise()));
    connect(ui->pushButton_hmirror, SIGNAL (released()), this, SLOT (handleButton_Hmirror()));
    connect(ui->pushButton_vmirror, SIGNAL (released()), this, SLOT (handleButton_Vmirror()));
    connect(ui->pushButton_save, SIGNAL (released()), this, SLOT (handleButton_Save()));
    connect(ui->pushButton_resize, SIGNAL (released()), this, SLOT (handleButton_Resize()));
    connect(ui->pushButton_liquid, SIGNAL (released()), this, SLOT (handleButton_Liquid()));
    connect(ui->pushButton_autoliq, SIGNAL (released()), this, SLOT (handleButton_autoliq()));
    connect(ui->checkBox_prev, SIGNAL (clicked()), this, SLOT (handleCheck_Prev()));
    connect(ui->pushButton_zoomIN, SIGNAL (released()), this, SLOT (handleButton_zoomIN()));
    connect(ui->pushButton_zoomOUT, SIGNAL (released()), this, SLOT (handleButton_zoomOUT()));

    ui->label_size->hide();
    this->setWindowTitle("CRAB EDITOR");

}


image_editor::~image_editor()
{
    delete ui;
}

void image_editor::setImage(QImage img_orig){
    img_old=img_orig;
    img_new=img_orig;
    img_viev=img_orig;
    scale=1.0;
    w_pixmap=img_orig.height();
    h_pixmap=img_orig.width();

    imagelabel = new QLabel;
    imagelabel->setPixmap(QPixmap::fromImage(img_new, Qt::AutoColor));

    ui->scrollArea_image->setBackgroundRole(QPalette::Dark);
    ui->scrollArea_image->setWidget(imagelabel);
    ui->scrollArea_image->show();

};

void image_editor::handleButton_Gray(){
    toGray(img_new);
    refresh();
};

void image_editor::handleButton_Reset(){
    img_new=img_old;
    img_viev=img_old;

    w_pixmap=img_viev.width();
    h_pixmap=img_viev.height();

    scale=1.0;
    refresh();
};

void image_editor::handleButton_Edges(){
    GrayDivision(img_new, 3);
    refresh();
};

void image_editor::handleButton_Counter(){
    CounterClockwiseRotation(img_new);
    refresh();
};

void image_editor::handleButton_Clockwise(){
    ClockwiseRotation(image_editor::img_new);
    refresh();
};

void image_editor::handleButton_Hmirror(){
    HorizontalMirror(image_editor::img_new);
    refresh();
};

void image_editor::handleButton_Vmirror(){
    VerticalMirror(image_editor::img_new);
    refresh();
};

void image_editor::handleButton_Save(){
    int n = QMessageBox::warning(0,
                                 "SAVE",
                                 "Do you want to overwrite the image?",
                                 "Yes",
                                 "No",
                                 QString(),
                                 0,
                                 1
                                );
    if(!n) {
        img_old=img_new;
        img_new.save(str,0,100);
    }
    else
    {
        img_old=img_new;
        QString newstr = QFileDialog::getSaveFileName();
        img_old.save(newstr,0,100);

    };  /*!!!!!!*/

    refresh();
};

void image_editor::handleButton_Resize(){
    bool ok1;

        int width = QInputDialog::getInt(this, tr("QInputDialog::getInteger()"),
                                     tr("Width:"), 400, 100, 2000, 1, &ok1);
        if (ok1)
        {
            bool ok2;
            int height = QInputDialog::getInt(this, tr("QInputDialog::getInteger()"),
                                         tr("Height:"), 400, 100, 2000, 1, &ok2);
            if (ok2)
            {
                // Saving the changes!
                img_new=img_new.scaled(width, height, Qt::IgnoreAspectRatio, Qt::FastTransformation);
            };
        };

    refresh();
};

void image_editor::handleButton_Liquid(){

    int n = QMessageBox::warning(0,
                                 "WARNING",
                                 "This transformation can take up to few minutes."
                                 "\n Proceed?",
                                 "Yes",
                                 "No",
                                 QString(),
                                 0,
                                 1
                                );
    if(!n) { /*!!!!!!*/

    bool ok1;

        int width = QInputDialog::getInt(this, tr("QInputDialog::getInteger()"),
                                     tr("Width:"), 400, 100, 2000, 1, &ok1);
        if (ok1)
        {
            bool ok2;
            int height = QInputDialog::getInt(this, tr("QInputDialog::getInteger()"),
                                         tr("Height:"), 400, 100, 2000, 1, &ok2);
            if (ok2)
            {
                // Saving the changes!
                LiqudScaleWH(img_new, width, height);
            };
        };

    };   /*!!!!!!*/

    refresh();
};

void image_editor::refresh(){
    if (prev)
//    imagelabel->setPixmap(QPixmap::fromImage(img_new, Qt::AutoColor));
        img_viev=img_new;
    else
//    imagelabel->setPixmap(QPixmap::fromImage(img_old, Qt::AutoColor));


    img_viev=img_old;

    w_pixmap=scale*img_new.width();
    h_pixmap=scale*img_old.height();

    img_viev=img_viev.scaled(w_pixmap,h_pixmap);

    imagelabel->setPixmap(QPixmap::fromImage(img_viev, Qt::AutoColor));
    QString str = "Current size is " + QString::number(img_old.width());
    str+="x"+QString::number(img_old.height());
    ui->label_size->setText(str);
    ui->label_size->show();


};

void image_editor::handleCheck_Prev(){
    prev=(!prev);
    refresh();
};

void image_editor::handleButton_autoliq(){
    int n = QMessageBox::warning(0,
                                 "WARNING",
                                 "VZOOH can take up to few minutes."
                                 "\n Proceed?",
                                 "Yes",
                                 "No",
                                 QString(),
                                 0,
                                 1
                                );
    if(!n) { /*!!!!!!*/
    AutoDeleteEdges(img_new);
    }
    refresh();
};


void image_editor::setLocation(QString strng){
     str=strng;
};

void image_editor::handleButton_zoomIN(){
    scale*=1.25;
    if (scale>4) scale=4;
    refresh();
};

void image_editor::handleButton_zoomOUT(){
    scale*=0.8;
    if (scale<0.5) scale=0.5;
    refresh();
};

#include "small_dialogs.h"
#include "ui_add_subject.h"

/*
add_lecture::add_lecture(QWidget *parent) :
    QWidget(parent),
    add_lecture::ui(new Ui::add_lecture)
{};*/

add_subject::add_subject(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add_subject)
{


};

add_subject::~add_subject(){
    delete ui;
};

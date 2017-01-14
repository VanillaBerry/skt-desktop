#ifndef IMAGE_EDITOR_H
#define IMAGE_EDITOR_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class image_editor;
}

class image_editor : public QWidget
{
    Q_OBJECT

public:
    explicit image_editor(QWidget *parent = 0);
    ~image_editor();

void setImage(QImage img_orig);

private:
    QLabel *imagelabel;
    Ui::image_editor *ui;
    QImage img_new;
    QImage img_old;
    bool prev;

void refresh();

private slots:

void handleButton_Gray();
void handleButton_Reset();
void handleButton_Edges();
void handleButton_Counter();
void handleButton_Clockwise();
void handleButton_Hmirror();
void handleButton_Vmirror();
void handleButton_Save();
void handleButton_Resize();
void handleButton_Liquid();
void handleButton_Exit();
void handleCheck_Prev();

};

#endif // IMAGE_EDITOR_H

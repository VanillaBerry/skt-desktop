#ifndef IMAGESLISTVIEWER_H
#define IMAGESLISTVIEWER_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class imageslistviewer;
}

class imageslistviewer : public QWidget
{
    Q_OBJECT

public:
    explicit imageslistviewer(QWidget *parent = 0);
    ~imageslistviewer();
    void set_listofIMAGES(QList<QImage> *_list);

private:
    QImage img_old;
    QImage img_viev;
    QLabel *imagelabel;
    float scale;
    int w_pixmap;
    int h_pixmap;
    QList<QImage> *_listofIMAGES;
    void refresh();

    Ui::imageslistviewer *ui;

private slots:
    void handleButton_zoomIN();
    void handleButton_zoomOUT();
    void handleButton_PREV();
    void handleButton_NEXT();
};

#endif // IMAGESLISTVIEWER_H

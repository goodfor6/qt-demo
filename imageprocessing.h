#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H
#include <QtWidgets/QMainWindow>
#include "ui_imageprocessing.h"

class ImageProcessing:public QMainWindow
{
    Q_OBJECT

public:
    ImageProcessing(QWidget * parent = Q_NULLPTR);
    ~ImageProcessing();

    void helloWorld();

private:
    Ui::ImageProcessing ui;

private slots:
    void islot();

};
#endif // IMAGEPROCESSING_H


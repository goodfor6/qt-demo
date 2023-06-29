#include <QMainWindow>
#include <QtGui>
#include <QtWidgets>
#include "MainWindow.h"

ImageProcessing::ImageProcessing(QWidget * parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    this ->resize(400,400);

    helloWorld();

}

ImageProcessing::~ImageProcessing()
{

}

void Image

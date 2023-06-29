#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_imageprocessing.h"
#include <QtGui>
#include <QtWidgets>
#include <QMainWindow>


namespace Ui {
class ImageProcessing;
}

class ImageProcessing : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImageProcessing(QWidget *parent = nullptr);
    ~ImageProcessing();

    void helloWorld();
private:
    Ui::ImageProcessing *ui;

    // 头文件
    QDockWidget *dock_Image;    // 图像窗口
    QDockWidget* dock_Tool;// 工具箱窗口
    QDockWidget* dock_Geom;// 几何变换窗口
    QDockWidget* dock_Gray;// 灰度变换窗口
    QDockWidget* dock_Enhance;// 图像增强窗口
    QDockWidget* dock_Morp;// 形态学处理窗口
    QDockWidget* dock_Color;// 颜色模型窗口
    QDockWidget* dock_Prop;// 属性窗口
    QDockWidget* dock_Output;// 输出窗口
    QString currentPath;
    QLabel * imgLabel;
    void InitImage();
    void Menu_File();

private:
    int drawType;                               // 绘制类型
    QButtonGroup *toolButtonGroup;              // 按钮组
    void ToolWin();                             // 工具箱窗口

private:
//   QPushButton * colorBtn;//标准颜色对话框类
   QFrame *colorFram;

signals:
    void iSignal(int a);
    void mutiParamSignal(int a,float b);

private slots:
        void iSlot(int a);
        void alertSlot();
        void File_new();
        void File_open();
        void File_save();
        void File_saveas();
        void File_close();
        void toolButtonClicked(int id);
        void setColor();
};

#endif // MAINWINDOW_H

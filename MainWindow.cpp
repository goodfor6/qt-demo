#include "MainWindow.h"
#include "ui_imageprocessing.h"
#include <QtGui>
#include <QtWidgets>

#pragma execution_character_set("utf-8") //解决汉字乱码问题

ImageProcessing::ImageProcessing(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageProcessing)
{
    ui->setupUi(this);

    QWidget * p = takeCentralWidget();
   if(p)
       delete p;
   setDockNestingEnabled(true);


//   dock_Image->setFeatures(QDockWidget::DockWidgetMovable);
//   dock_Image->setFeatures(QDockWidget::DockWidgetFloatable);
//   dock_Image->setFeatures(QDockWidget::DockWidgetClosable);
//   dock_Image->setFeatures(QDockWidget::AllDockWidgetFeatures);



    connect(this,SIGNAL(mutiParamSignal(int,float)),this,SLOT(iSlot(int)));
    emit mutiParamSignal(115,0.3f);
    //icon,height,width
//    this ->resize(400,400);

    setWindowTitle("MyRobotAI图片处理软件");
    setWindowIcon(QIcon(":/Image/icon/advator.png"));

//    resize(QApplication::desktop()->width()*0.4,QApplication::desktop()->height()*0.9);
//    move(QApplication::desktop()->width()*0.05,QApplication::desktop()->height()*0.01);

    //menu,tools
    QMenu * file= menuBar()->addMenu(tr("文件"));

    QAction * act_file_new = new QAction(QIcon(":/Image/icon/tools.png"),tr("新建"),this);
    act_file_new->setShortcuts(QKeySequence::New);
    connect(act_file_new,SIGNAL(triggered()),this,SLOT(File_new));


    QAction * act_file_open = new QAction(QIcon(":/Image/icon/connect.png"),tr("打开"),this);
    act_file_open->setShortcuts(QKeySequence::Open);
    connect(act_file_open,SIGNAL(triggered()),this,SLOT(File_open()));


    QAction * act_file_save = new QAction(QIcon(":/Image/icon/device.png"),tr("保存"),this);
    act_file_save->setShortcuts(QKeySequence::Save);
    connect(act_file_save,SIGNAL(triggered()),this,SLOT(File_save()));


    QAction * act_file_saveas = new QAction(QIcon("/Image/icon/tools.png"),tr("另存为"),this);
    act_file_saveas->setShortcuts(QKeySequence::SaveAs);
    connect(act_file_saveas,SIGNAL(triggered()),this,SLOT(File_saveas()));


    QAction * act_file_close = new QAction(QIcon("/Image/icon/close.png"),tr("关闭"),this);
    act_file_close->setShortcuts(QKeySequence::Close);
    connect(act_file_close,SIGNAL(triggered()),this,SLOT(close()));


    file->addAction(act_file_new);
    file->addAction(act_file_open);
    file->addAction(act_file_save);
    file->addAction(act_file_saveas);
    file->addSeparator();
    file->addAction(act_file_close);




    //第二个菜单
//    QMenu *menu2 = menuBar()->addMenu(tr("菜单栏2"));
//    QAction *act2 = new QAction(QIcon("Image/icon/cam.png"),tr("一级菜单"),this);

//    QMenu *submenu = new QMenu();
//    QAction *subact = new QAction(QIcon("Image/icon/cam.png"),tr("二级菜单"),this);
//    submenu -> addAction(subact);
//    connect(subact,SIGNAL(triggered()),this,SLOT(subSlot()));

//    act2->setMenu(submenu);
//    menu2->addAction(act2);

    //tools
    ui->mainToolBar->addAction(act_file_new);
    ui->mainToolBar->addAction(act_file_open);
    ui->mainToolBar->addAction(act_file_save);

    QToolBar * toolBar = new QToolBar();
    toolBar -> setMovable(false);
    addToolBar(toolBar);

    QPushButton *button = new QPushButton();
    button -> setText(tr("控件"));

//    toolBar-> addAction(subact);
//    toolBar-> addWidget(button);

    //任务栏
    act_file_new ->setStatusTip(tr("新建"));
    act_file_open ->setStatusTip(tr("打开"));
    act_file_save ->setStatusTip(tr("保存"));
    act_file_saveas ->setStatusTip(tr("另存为"));
    act_file_close ->setStatusTip(tr("关闭"));

//    helloWorld();
    InitImage();
    ToolWin();      // 工具箱窗口
}


ImageProcessing::~ImageProcessing()
{
    delete ui;
}

//void ImageProcessing::helloWorld()
//{
//    QPushButton * button = new QPushButton(this);
//    button ->setText(tr("你好，QT！"));
//    button ->move(100,100);
//    connect(button,SIGNAL(clicked()),this,SLOT(alertSlot()));
//}
void ImageProcessing::File_new()
{
    QImage image = QImage(500,500,QImage::Format_RGB32);
    image.fill(qRgb(255,255,255));
    imgLabel->setPixmap(QPixmap::fromImage(image));
    imgLabel->resize(image.width(),image.height());
    currentPath="";
}
void ImageProcessing::File_open()
{
    QString path =QFileDialog::getOpenFileName(this,tr("选择图像"),".",tr("Images(*.jpg *.png *.bmp)"));
    if(!path.isEmpty())
    {
        QImage * img = new QImage();
        if(!img->load(path))
        {
            QMessageBox::information(this,tr("错误"),tr("打开图像失败！"));
            delete img;
            return;
        }
        imgLabel ->setPixmap(QPixmap::fromImage(*img));
        imgLabel->resize(img->width(),img->height());
        currentPath = path;
    }
}
void ImageProcessing::File_save()
{
    if(currentPath.isEmpty())
    {
        QString path = QFileDialog::getSaveFileName(this,tr("保存图像"),".",tr("Images(*.jpg *.png *.bmp)"));
        {
                if(!path.isEmpty())
                    currentPath = path;
        }
        QImage img = imgLabel->pixmap()->toImage();
        img.save(currentPath);

    }
}
void ImageProcessing::File_saveas()
{
    QString path = QFileDialog::getSaveFileName(this,tr("图像另存为"),".",tr("Images(*.jpg *.png *.bmp)"));
    if(!path.isEmpty())
    {
        QImage img = imgLabel->pixmap()->toImage();
        img.save(path);
        currentPath = path;
    }
}
void ImageProcessing::File_close()
{
     QMessageBox::information(this,tr("close"),tr("close!"));
}

//文件加载
void ImageProcessing::InitImage()
{
    // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //窗口布局
    // cpp
     QDockWidget* dock_Image = new QDockWidget(tr("图像"), this);               // 上节中已定义，如果只想做本节内容，可取消注释
    dock_Image->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);         // 设置为可移动可浮动，但不可关闭
    dock_Image->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);  // 可移动范围：左右
    dock_Image->setMinimumSize(600, 600);   // 设置最小宽高

    dock_Tool = new QDockWidget(tr("工具箱"), this);           // 工具箱窗口,若想设置特征或移动范围，方法同上。
    dock_Geom = new QDockWidget(tr("几何变换"), this);          // 几何变换窗口
    dock_Gray = new QDockWidget(tr("灰度变换"), this);          // 灰度变换窗口
    dock_Enhance = new QDockWidget(tr("图像增强"), this);       // 图像增强窗口
    dock_Morp = new QDockWidget(tr("形态学处理"), this);     // 形态学处理窗口
    dock_Color = new QDockWidget(tr("颜色模型"), this);         // 颜色模型窗口
    dock_Prop = new QDockWidget(tr("属性"), this);                // 属性窗口
    dock_Output = new QDockWidget(tr("输出"), this);          // 输出窗口

    // 进行布局
    setCentralWidget(dock_Image);       // 指定为中心窗口
    addDockWidget(Qt::LeftDockWidgetArea, dock_Tool);
    addDockWidget(Qt::BottomDockWidgetArea, dock_Output);
    addDockWidget(Qt::RightDockWidgetArea, dock_Geom);
    addDockWidget(Qt::RightDockWidgetArea, dock_Gray);
    addDockWidget(Qt::RightDockWidgetArea, dock_Enhance);
    addDockWidget(Qt::RightDockWidgetArea, dock_Morp);
    addDockWidget(Qt::RightDockWidgetArea, dock_Color);
    addDockWidget(Qt::RightDockWidgetArea, dock_Prop);

    // 分割窗口
    splitDockWidget(dock_Tool, dock_Image, Qt::Horizontal);     // 水平
    splitDockWidget(dock_Geom, dock_Output, Qt::Vertical);      // 垂直

    // 合并窗口
    tabifyDockWidget(dock_Geom, dock_Gray);
    tabifyDockWidget(dock_Gray, dock_Enhance);
    tabifyDockWidget(dock_Enhance, dock_Morp);
    tabifyDockWidget(dock_Morp, dock_Color);
    tabifyDockWidget(dock_Output, dock_Prop);

    dock_Geom->raise();             // raise()函数可使指定窗口置于最前

    // connect(dock_Tool, SIGNAL(visibilityChanged(bool)), this, SLOT(isDockTool()));
    // 当窗体隐藏或显示时，其信号为visibilityChanged(bool)函数，此处仅作简单演示，槽函数是自定义的，其他窗口同理。

    // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//    dock_Image = new QDockWidget(tr("图像"),this);
//    setCentralWidget(dock_Image);

    imgLabel = new QLabel(dock_Image);
    imgLabel->setScaledContents(true);

    QImage image = QImage(500,500,QImage::Format_RGB32);
    image.fill(qRgb(255,255,255));
    imgLabel->setPixmap(QPixmap::fromImage(image));
    imgLabel->resize(image.width(),image.height());

    QScrollArea * scrollArea = new QScrollArea(this);
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setAlignment(Qt::AlignCenter);
    scrollArea->setWidget(imgLabel);
    dock_Image->setWidget(scrollArea);

    //添加按钮功能
    QLabel * label = new QLabel(tr("label"),dock_Geom);
    QPushButton * button = new QPushButton(tr("按钮"),dock_Geom);
    connect(button,SIGNAL(clicked()),this,SLOT(slot_button));

    QLineEdit *lineEdit = new QLineEdit(tr("Line"),dock_Geom);
    lineEdit->setReadOnly(true);

    QTextEdit *textEdit = new QTextEdit(tr("Text"),dock_Geom);
    textEdit->textCursor().movePosition(QTextCursor::End);          // 垂直滚动条自动跟踪到最底部
    textEdit->setWordWrapMode(QTextOption::NoWrap);                 // 添加水平滚动条
    textEdit->setReadOnly(true);                                    // 设置只读
    textEdit->append("第1行");                                      // 换行显示
    textEdit->append("第2行");


    // 常用插件
    QSlider *slider = new QSlider(Qt::Horizontal,dock_Geom);  // 创建水平滑动条
    slider->setRange(0, 100);       // 设置范围
    slider->setValue(1);            // 设置初始值

    QSpinBox *spinbox = new QSpinBox(dock_Geom);             // 创建微调框
    spinbox->setRange(0, 100);      // 设置范围
    spinbox->setValue(1);           // 设置初始值

    connect(spinbox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));   // 两者的值同时更改
    connect(slider, SIGNAL(valueChanged(int)), spinbox, SLOT(setValue(int)));
    connect(spinbox, SIGNAL(valueChanged(int)), this, SLOT(slot_spinbox()));    // slot_spinbox()是自定义的槽函数，可根据需求自行修改

    //下拉框
    QComboBox *combo = new QComboBox(dock_Geom);     // 下拉选择框
    combo->addItem(tr("第一个选项"));    // 添加选项
    combo->addItem(tr("第二个选项"));
    connect(combo, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_combo())); // slot_combo()是自定义的槽函数，可根据需求自行修改
    // combo->currentIndex()可以查看当前索引值

    QRadioButton *radio1 = new QRadioButton(tr("选项1"),dock_Geom);// 单选按钮
    QRadioButton *radio2 = new QRadioButton(tr("选项2"),dock_Geom);// 单选按钮
    radio1->setChecked(true);       // 用于设定初始值
    //radio1->isChecked() == true   // 该语句用于判断单选按钮是否被选定
    connect(radio1, SIGNAL(clicked()), this, SLOT(slot_radio1()));// 自定义的槽函数，可根据需求自行修改
    connect(radio2, SIGNAL(clicked()), this, SLOT(slot_radio2()));

    QButtonGroup *radioGroup = new QButtonGroup(dock_Geom);  // 单选按钮组，不可视
    radioGroup->setExclusive(true);                 // 组内按钮互斥，即每次只能选定一个按钮
    radioGroup->addButton(radio1);
    radioGroup->addButton(radio2);

    // cpp

    // 按钮
    QPushButton * colorBtn= new QPushButton(tr("画笔颜色"),dock_Geom);
    connect(colorBtn, SIGNAL(clicked()), this, SLOT(setColor()));

    // QFrame控件
    colorFram= new QFrame(dock_Geom);
    colorFram->setFrameShape(QFrame::Box);              // 形状
    colorFram->setPalette(QPalette(Qt::black));         // 初始颜色
    colorFram->setAutoFillBackground(true);             // 填充
    colorFram->setFixedSize(25, 25);                    // 固定大小


//    void Image::setColor()     // 槽函数
//    {
//        QColor c = QColorDialog::getColor(Qt::blue);  // 颜色选择对话框
//        if (c.isValid())
//        {
//            frame_color->setPalette(QPalette(c));
//        }
//    }

    // 布局
    label->move(50, 50);        // 设定位置
    button->move(200, 50);
    lineEdit->move(50, 100);
    textEdit->move(50, 150);
    textEdit->resize(200, 100);
    slider->move(350,50);
    spinbox->move(500,50);
    combo->move(650,50);
    radio1->move(800, 50);
    radio2->move(800, 70);
    colorBtn->move(150,400);
    colorFram->move(300,400);

    // /////////////////////////////// 灰度布局////////////////////////////////////////////////////
    // 水平布局
    QPushButton *button_H1 = new QPushButton(tr("QHBoxLayout第一个按钮"));
    QPushButton *button_H2 = new QPushButton(tr("QHBoxLayout第二个按钮"));
    QPushButton *button_H3 = new QPushButton(tr("QHBoxLayout第三个按钮"));

    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->addWidget(button_H1);
    hlayout->addWidget(button_H2);
    hlayout->addWidget(button_H3);

    // 垂直布局
    QPushButton *button_V1 = new QPushButton(tr("QVBoxLayout第一个按钮"));
    QPushButton *button_V2 = new QPushButton(tr("QVBoxLayout第二个按钮"));
    QPushButton *button_V3 = new QPushButton(tr("QVBoxLayout第三个按钮"));

    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->addWidget(button_V1);
    vlayout->addWidget(button_V2);
    vlayout->addWidget(button_V3);

    // 格栅布局(控件大小随着窗口变化自动拉伸)
    QPushButton *button_G1 = new QPushButton(tr("QGridLayout第一个按钮"));
    QPushButton *button_G2 = new QPushButton(tr("QGridLayout第二个按钮"));
    QPushButton *button_G3 = new QPushButton(tr("QGridLayout第三个按钮"));
    QPushButton *button_G4 = new QPushButton(tr("QGridLayout第四个按钮"));

    QGridLayout *glayout = new QGridLayout();
    glayout->addWidget(button_G1, 0, 0);        // 第0行0列，第一个参数为控，第二个参数为第几行，第三个参数为第几列
    glayout->addWidget(button_G2, 1, 1);        // 第1行1列
    glayout->addWidget(button_G3, 2, 0);        // 第2行0列
    glayout->addWidget(button_G4, 2, 1);        // 第2行1列

    // 表格布局
    QLineEdit *line_F1 = new QLineEdit(tr("第一项"));
    QLineEdit *line_F2 = new QLineEdit(tr("第二项"));
    QLineEdit *line_F3 = new QLineEdit(tr("第三项"));
    QLineEdit *line_F4 = new QLineEdit(tr("第四项"));

    QFormLayout *flayout = new QFormLayout();
    flayout->addRow(tr("1"), line_F1);          // 添加行，第一列为标签，第二列为添加的控件QLineEdit
    flayout->addRow(tr("2"), line_F2);
    flayout->addRow(tr("3"), line_F3);
    flayout->addRow(tr("4"), line_F4);
    flayout->setSpacing(20);                    // 设置间距
    flayout->setMargin(20);                     // 设置外边距

    // 主布局采用垂直排列
    QVBoxLayout *pLayout = new QVBoxLayout();   // 使用垂直布局作为主布局
    pLayout->addLayout(hlayout);
    pLayout->addLayout(vlayout);
    pLayout->addStretch();                      // 增加弹簧
    pLayout->addLayout(glayout);
    pLayout->addLayout(flayout);

    QWidget *pWidget = new QWidget(dock_Gray);  // 这是QDockWidget布局的重点！！！
    pWidget->setLayout(pLayout);
    dock_Gray->setWidget(pWidget);


}


void ImageProcessing::ToolWin()                              // 工具箱窗口
{
    //dock_Tool = new QDockWidget(tr("工具箱"), this);             // 工具栏
    //dock_Tool->setFeatures(QDockWidget::DockWidgetClosable);

    QPushButton *button_pen = new QPushButton(QIcon(":/Image/icon/coors.png"), tr(""), this);
    button_pen->setFixedSize(35, 35);
    button_pen->setToolTip(tr("钢笔"));
    button_pen->setObjectName("customButton");
    QPushButton *button_line = new QPushButton(QIcon(":/Image/icon/device.png"), tr(""), this);
    button_line->setFixedSize(35, 35);
    button_line->setToolTip(tr("线条"));
    button_line->setObjectName("customButton");
    QPushButton *button_circle = new QPushButton(QIcon(":/Image/icon/Circle.png"), tr(""), this);
    button_circle->setFixedSize(35, 35);
    button_circle->setToolTip(tr("圆形"));
    button_circle->setObjectName("customButton");
    QPushButton *button_ellipse = new QPushButton(QIcon(":/Image/icon/Elipse.png"), tr(""), this);
    button_ellipse->setFixedSize(35, 35);
    button_ellipse->setToolTip(tr("椭圆"));
    button_ellipse->setObjectName("customButton");
    QPushButton *button_triangle = new QPushButton(QIcon(":/Image/icon/Triangle.png"), tr(""), this);
    button_triangle->setFixedSize(35, 35);
    button_triangle->setToolTip(tr("三角形"));
    button_triangle->setObjectName("customButton");
    QPushButton *button_rhombus = new QPushButton(QIcon(":/Image/icon/Rhombus.png"), tr(""), this);
    button_rhombus->setFixedSize(35, 35);
    button_rhombus->setToolTip(tr("菱形"));
    button_rhombus->setObjectName("customButton");
    QPushButton *button_rect = new QPushButton(QIcon(":/Image/icon/Rectangle.png"), tr(""), this);
    button_rect->setFixedSize(35, 35);
    button_rect->setToolTip(tr("长方形"));
    button_rect->setObjectName("customButton");
    QPushButton *button_square = new QPushButton(QIcon(":/Image/icon/Square.png"), tr(""), this);
    button_square->setFixedSize(35, 35);
    button_square->setToolTip(tr("正方形"));
    button_square->setObjectName("customButton");
    QPushButton *button_hexagon = new QPushButton(QIcon(":/Image/icon/Hexagon.png"), tr(""), this);
    button_hexagon->setFixedSize(35, 35);
    button_hexagon->setToolTip(tr("六边形"));
    button_hexagon->setObjectName("customButton");

    QGridLayout *toolLayout = new QGridLayout();
    toolLayout->setAlignment(Qt::AlignTop);
    toolLayout->addWidget(button_pen, 0, 0);
    toolLayout->addWidget(button_line, 0, 1);
    toolLayout->addWidget(button_ellipse, 1, 1);
    toolLayout->addWidget(button_circle, 1, 0);
    toolLayout->addWidget(button_triangle, 2, 0);
    toolLayout->addWidget(button_rhombus, 2, 1);
    toolLayout->addWidget(button_rect, 3, 0);
    toolLayout->addWidget(button_square, 3, 1);
    toolLayout->addWidget(button_hexagon, 4, 0);

    QWidget *toolWidget = new QWidget(dock_Tool);
    toolWidget->setLayout(toolLayout);
    dock_Tool->setWidget(toolWidget);


    // 按钮组 QButtonGroup
    toolButtonGroup = new QButtonGroup();
    toolButtonGroup->addButton(button_pen, 1);              // 自动分配的id为复数，从-2开始，
    toolButtonGroup->addButton(button_line, 2);             // 最好自己指定id，使用正数以避免冲突。
    toolButtonGroup->addButton(button_ellipse, 3);
    toolButtonGroup->addButton(button_circle, 4);
    toolButtonGroup->addButton(button_triangle, 5);
    toolButtonGroup->addButton(button_rhombus, 6);
    toolButtonGroup->addButton(button_rect, 7);
    toolButtonGroup->addButton(button_square, 8);
    toolButtonGroup->addButton(button_hexagon, 9);
    connect(toolButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(toolButtonClicked(int)));       // 按钮组的槽函数
}


// 绘图槽函数ButtonGroup
void ImageProcessing::toolButtonClicked(int id)
{
    QList<QAbstractButton *> buttons = toolButtonGroup->buttons();
    foreach(QAbstractButton *button, buttons)
    {
        if (toolButtonGroup->button(id) != button)  // 按钮组内其它按钮设置为不可用
            button->setChecked(false);
        else if (drawType == id)                    // 如果绘制类型与前次相同，则退出绘制模式
            drawType = 0;
        else
            drawType = id;
    }

    switch (drawType)
    {
    case 0:
        QMessageBox::information(this, tr("绘制"), tr("退出绘制模式！"));    // 后续将改为绘制功能函数
        break;
    case 1:
        QMessageBox::information(this, tr("绘制"), tr("钢笔！"));    break;
    case 2:
        QMessageBox::information(this, tr("绘制"), tr("线条！"));    break;
    case 3:
        QMessageBox::information(this, tr("绘制"), tr("椭圆形！"));   break;
    case 4:
        QMessageBox::information(this, tr("绘制"), tr("圆形！"));    break;
    case 5:
        QMessageBox::information(this, tr("绘制"), tr("三角形！"));   break;
    case 6:
        QMessageBox::information(this, tr("绘制"), tr("菱形！"));    break;
    case 7:
        QMessageBox::information(this, tr("绘制"), tr("长方形！"));   break;
    case 8:
        QMessageBox::information(this, tr("绘制"), tr("正方形！"));   break;
    case 9:
        QMessageBox::information(this, tr("绘制"), tr("六边形！"));   break;
    default:
        break;
    }
}
void ImageProcessing::setColor()     // 槽函数
{
    QColor c = QColorDialog::getColor(Qt::blue);  // 颜色选择对话框
    if (c.isValid())
    {
        colorFram->setPalette(QPalette(c));
    }
}

void ImageProcessing::iSlot(int b)
{
    QString qString;
    qDebug() << qString.number(b);
}
void ImageProcessing::alertSlot()
{
    QMessageBox::information(this,tr("hello"),tr("hello world !"));
}




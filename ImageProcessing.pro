#-------------------------------------------------
#
# Project created by QtCreator 2023-06-28T17:04:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageProcessing
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        MainWindow.cpp

HEADERS += \
        MainWindow.h

FORMS += \
        imageprocessing.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#DISTFILES += \
#    Image/icon/connect.png \
#    Image/icon/advator.png \
#    Image/icon/appIcon.png \
#    Image/icon/applogo.png \
#    Image/icon/Background.png \
#    Image/icon/BXML合并.png \
#    Image/icon/cam.png \
#    Image/icon/close.png \
#    Image/icon/connect.png \
#    Image/icon/CoordinateSystem32.png \
#    Image/icon/CoordinateSystemFolderOpenState32.png \
#    Image/icon/coors.png \
#    Image/icon/dataProcess.png \
#    Image/icon/device.png \
#    Image/icon/deviceInfo.png \
#    Image/icon/disconnect.png \
#    Image/icon/flightData.png \
#    Image/icon/flightData2.png \
#    Image/icon/FolderConnectionAdd32.png \
#    Image/icon/FolderConnectionDisconnectFrom32.png \
#    Image/icon/FolderWindowStyle32.png \
#    Image/icon/GenericBlueRightArrowLongTail32.png \
#    Image/icon/GenericCheckMarkBlueCircleOff32.png \
#    Image/icon/GenericCheckMarkGreen32.png \
#    Image/icon/GenericDeleteRed32.png \
#    Image/icon/GenericDocument32.png \
#    Image/icon/GenericSearch32.png \
#    Image/icon/GenericSearchClear32.png \
#    Image/icon/GPSIcon.png \
#    Image/icon/lg.png \
#    Image/icon/lidarData.png \
#    Image/icon/lidarData2.png \
#    Image/icon/logo.png \
#    Image/icon/logo2.png \
#    Image/icon/min.png \
#    Image/icon/more.png \
#    Image/icon/POS校正.png \
#    Image/icon/POS展点.png \
#    Image/icon/skin.png \
#    Image/icon/startPage.png \
#    Image/icon/support.png \
#    Image/icon/tab.png \
#    Image/icon/tools.png \
#    Image/icon/tools2.png \
#    Image/icon/unKnown.png \
#    Image/icon/update.png \
#    Image/icon/usbSize.png \
#    Image/icon/wlogo.png \
#    Image/icon/定拍工具.png \
#    Image/icon/改名工具.png \
#    Image/icon/航飞参数.png \
#    Image/icon/航飞数据处理.png \
#    Image/icon/激光数据处理.png \
#    Image/icon/扩展小工具.png \
#    Image/icon/设备详情.png \
#    Image/icon/数据导出.png \
#    Image/icon/数据质检.png \
#    Image/icon/数据转换.png \
#    Image/icon/作业申报.png \
#    Image/icon/坐标展示.png \
#    Image/icon/坐标转换.png \
#    Image/icon/cloud.ico

RESOURCES += \
    image.qrc

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEPENDPATH += \
    GUI/    \
    GUI/Sub_page/    \
    DATA/   \

INCLUDEPATH += \
    GUI/ \
    GUI/Sub_page/    \
    DATA/ \

SOURCES += \
    GUI/MyTreeWidget.cpp \
    GUI/Sub_page/Page_IMU_state.cpp \
    GUI/Sub_page/Page_IMU_param.cpp \
    main.cpp \
    GUI/MyMenu.cpp \
    GUI/MainWindow.cpp \
    GUI/UartComboBox.cpp \
    GUI/MyToolBar.cpp \
    DATA/Uart.cpp \

HEADERS += \
    GUI/MyMenu.h \
    GUI/MainWindow.h \
    GUI/MyTreeWidget.h \
    GUI/Sub_page/Page_IMU_state.h \
    GUI/Sub_page/Page_IMU_param.h \
    GUI/UartComboBox.h \
    GUI/MyToolBar.h \
    DATA/Uart.h \

TRANSLATIONS += \
    qt_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QT       += core gui opengl openglwidgets network serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    listwidgetitemscaner.cpp \
    main.cpp \
    mainwindow.cpp \
    scaner.cpp \
    scaneraddwindow.cpp \
    scanersetupwindow.cpp \
    scaneruartsetupwindow.cpp \
    scanvisualization.cpp \
    settingsForms/networkconfigwindow.cpp \
    settingsForms/roomparametersinputform.cpp

HEADERS += \
    listwidgetitemscaner.h \
    mainwindow.h \
    scaner.h \
    scaneraddwindow.h \
    scanersetupwindow.h \
    scaneruartsetupwindow.h \
    scanvisualization.h \
    settingsForms/networkconfigwindow.h \
    settingsForms/roomparametersinputform.h

FORMS += \
    mainwindow.ui \
    scaneraddwindow.ui \
    scanersetupwindow.ui \
    scaneruartsetupwindow.ui \
    settingsForms/networkconfigwindow.ui \
    settingsForms/roomparametersinputform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    FragmentShader.frag \
    VertexShader.vert

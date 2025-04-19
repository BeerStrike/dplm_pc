QT       += core gui opengl openglwidgets network serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    baseheightmap.cpp \
    combinatedheightmap.cpp \
    heightmap.cpp \
    main.cpp \
    mainwindow.cpp \
    room.cpp \
    scaner.cpp \
    scaneraddwindow.cpp \
    settingsForms/networkconfigwindow.cpp \
    settingsForms/roomparametersinputform.cpp \
    settingsForms/scanersetupwindow.cpp \
    settingsForms/scaneruartsetupwindow.cpp \
    udpserver.cpp \
    visualization/axisvisualizartor.cpp \
    visualization/basevisualizator.cpp \
    visualization/camera.cpp \
    visualization/heightmapvisualizator.cpp \
    visualization/roomvisualizator.cpp \
    visualization/scanervisualizator.cpp \
    visualization/scanvisualizationwidget.cpp

HEADERS += \
    baseheightmap.h \
    combinatedheightmap.h \
    heightmap.h \
    mainwindow.h \
    room.h \
    scaner.h \
    scaneraddwindow.h \
    settingsForms/networkconfigwindow.h \
    settingsForms/roomparametersinputform.h \
    settingsForms/scanersetupwindow.h \
    settingsForms/scaneruartsetupwindow.h \
    udpserver.h \
    visualization/axisvisualizartor.h \
    visualization/basevisualizator.h \
    visualization/camera.h \
    visualization/heightmapvisualizator.h \
    visualization/roomvisualizator.h \
    visualization/scanervisualizator.h \
    visualization/scanvisualizationwidget.h

FORMS += \
    mainwindow.ui \
    scaneraddwindow.ui \
    settingsForms/networkconfigwindow.ui \
    settingsForms/roomparametersinputform.ui \
    settingsForms/scanersetupwindow.ui \
    settingsForms/scaneruartsetupwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    FragmentShader.frag \
    VertexShader.vert

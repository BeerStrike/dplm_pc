QT       += core gui opengl openglwidgets network serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GUI/mainwindow.cpp \
    GUI/scanersmanadgerwidget.cpp \
    GUI/scanvisualizatorwidget.cpp \
    baseheightmap.cpp \
    combinatedheightmap.cpp \
    heightmap.cpp \
    main.cpp \
    room.cpp \
    scancontroller.cpp \
    scaner.cpp \
    udpserver.cpp \
    GUI/Forms/scaneraddwindow.cpp \
    GUI/Forms/networkconfigwindow.cpp \
    GUI/Forms/roomparametersinputform.cpp \
    GUI/Forms/scanersetupwindow.cpp \
    GUI/Forms/scaneruartsetupwindow.cpp \
    GUI/ScanVisualization/axisvisualizartor.cpp \
    GUI/ScanVisualization/basevisualizator.cpp \
    GUI/ScanVisualization/camera.cpp \
    GUI/ScanVisualization/heightmapvisualizator.cpp \
    GUI/ScanVisualization/roomvisualizator.cpp \
    GUI/ScanVisualization/scanervisualizator.cpp \
    GUI/ScanVisualization/scanvisualizationwidget.cpp

HEADERS += \
    GUI/mainwindow.h \
    GUI/scanersmanadgerwidget.h \
    GUI/scanvisualizatorwidget.h \
    baseheightmap.h \
    combinatedheightmap.h \
    heightmap.h \
    room.h \
    scancontroller.h \
    scaner.h \
    udpserver.h \
    GUI/Forms/scaneraddwindow.h \
    GUI/Forms/networkconfigwindow.h \
    GUI/Forms/roomparametersinputform.h \
    GUI/Forms/scanersetupwindow.h \
    GUI/Forms/scaneruartsetupwindow.h \
    GUI/ScanVisualization/axisvisualizartor.h \
    GUI/ScanVisualization/basevisualizator.h \
    GUI/ScanVisualization/camera.h \
    GUI/ScanVisualization/heightmapvisualizator.h \
    GUI/ScanVisualization/roomvisualizator.h \
    GUI/ScanVisualization/scanervisualizator.h \
    GUI/ScanVisualization/scanvisualizationwidget.h

FORMS += \
    GUI/Forms/scaneraddwindow.ui \
    GUI/Forms/networkconfigwindow.ui \
    GUI/Forms/roomparametersinputform.ui \
    GUI/Forms/scanersetupwindow.ui \
    GUI/Forms/scaneruartsetupwindow.ui \
    GUI/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    FragmentShader.frag \
    VertexShader.vert

QT       += core gui opengl openglwidgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    listwidgetitemscaner.cpp \
    main.cpp \
    mainwindow.cpp \
    networkconfigwindow.cpp \
    roomparametersinputform.cpp \
    scaner.cpp \
    scanersetupwindow.cpp \
    scanvisualization.cpp

HEADERS += \
    listwidgetitemscaner.h \
    mainwindow.h \
    networkconfigwindow.h \
    roomparametersinputform.h \
    scaner.h \
    scanersetupwindow.h \
    scanvisualization.h

FORMS += \
    mainwindow.ui \
    networkconfigwindow.ui \
    roomparametersinputform.ui \
    scanersetupwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    FragmentShader.frag \
    VertexShader.vert

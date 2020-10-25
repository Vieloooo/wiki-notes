QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    maininfo.cpp \
    mainwindow.cpp\
    choosemodal.cpp\
    deletewidget.cpp \
    widget.cpp \
    widgetbuildfile.cpp\
    mindmapdialog.cpp \
    node.cpp \
    link.cpp \
    inputtextdialog.cpp \
    nodeinfodialog.cpp \
    scene.cpp \
    aboutdialog.cpp \
    insertlinkdialog.cpp

HEADERS += \
    choosemodal.h \
    maininfo.h \
    deletewidget.h \
    widget.h \
    widgetbuildfile.h\
    mainwindow.h\
    mindmapdialog.h \
    node.h \
    link.h \
    inputtextdialog.h \
    nodeinfodialog.h \
    scene.h \
    aboutdialog.h \
    insertlinkdialog.h

FORMS += \
    choosemodal.ui \
    maininfo.ui \
    mainwindow.ui\
    deletewidget.ui \
    widget.ui \
    widgetbuildfile.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \

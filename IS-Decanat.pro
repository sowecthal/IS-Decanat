QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    authwindow.cpp \
    databases.cpp \
    dataclasses/discipline.cpp \
    dataclasses/group.cpp \
    dataclasses/user.cpp \
    editdisciplinedialog.cpp \
    editgroupdialog.cpp \
    editstudentdialog.cpp \
    edituserdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    #tables/userstable.cpp

HEADERS += \
    authwindow.h \
    config.h \
    databases.h \
    dataclasses/discipline.h \
    dataclasses/group.h \
    dataclasses/user.h \
    editdisciplinedialog.h \
    editgroupdialog.h \
    editstudentdialog.h \
    edituserdialog.h \
    mainwindow.h \
    #tables/userstable.h

FORMS += \
    authwindow.ui \
    editdisciplinedialog.ui \
    editgroupdialog.ui \
    editstudentdialog.ui \
    edituserdialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc


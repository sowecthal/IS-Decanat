QT      += testlib
QT      -= gui

CONFIG += c++11

HEADERS += \
    ../IS-Decanat/databases.h \
    ../IS-Decanat/dataclasses/user.h \
    ../IS-Decanat/dataclasses/group.h \
    ../IS-Decanat/dataclasses/discipline.h

SOURCES += \
    ../IS-Decanat/databases.cpp \
    ../IS-Decanat/dataclasses/user.cpp \
    ../IS-Decanat/dataclasses/group.cpp \
    ../IS-Decanat/dataclasses/discipline.cpp \
    tst_1.cpp

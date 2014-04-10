#-------------------------------------------------
#
# Project created by QtCreator 2014-03-28T10:33:55
#
#-------------------------------------------------

QT       += core gui
QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MEM
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    delegates.cpp \
    findtable.cpp \
    table.cpp \
    common.cpp \
    language.cpp \
    undocommands.cpp \
    about.cpp \
    configuration.cpp \
    customplot/qcustomplot.cpp \
    graphic.cpp \
    matrixc.cpp \
    mem.cpp

HEADERS  += mainwindow.h \
    delegates.h \
    findtable.h \
    table.h \
    common.h \
    language.h \
    undocommands.h \
    about.h \
    configuration.h \
    customplot/qcustomplot.h \
    graphic.h \
    matrixc.h \
    mem.h

FORMS    += mainwindow.ui \
    alternative.ui \
    criteria.ui \
    configurator.ui \
    build.ui \
    criteriaEdit.ui \
    criteriaRemove.ui \
    about.ui \
    alternativeEdit.ui \
    alternativeRemove.ui \
    graphic.ui \
    selectGraphic.ui \
    selectNForGraphic.ui \
    matrixc.ui

RESOURCES += \
    imagens.qrc

OTHER_FILES += \
    mem.rc

RC_FILE = mem.rc

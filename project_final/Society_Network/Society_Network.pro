TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    cmd_inter.cpp \
    cmd_type.cpp \
    db.cpp

HEADERS += \
    cmd_type.h \
    cmd_inter.h \
    db.h


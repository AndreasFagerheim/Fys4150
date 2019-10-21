TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG +=sdk_no_version_check

SOURCES += \
        libbok.cpp \
        main.cpp

HEADERS += \
    libbok.h

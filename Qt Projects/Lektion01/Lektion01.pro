TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Date.cpp \
        Person.cpp \
        main.cpp

DISTFILES += \
    .gitignore

HEADERS += \
    Date.h \
    Person.h

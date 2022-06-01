QT += testlib
QT -= gui

CONFIG += c++17 qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    ../src/sentencestorage.cpp \
    main.cpp \
    tst_sentencestorage.cpp

HEADERS += \
    ../src/sentencestorage.h \
    tst_sentencestorage.h

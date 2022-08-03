QT += testlib
QT -= gui

CONFIG += c++17 qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    ../src/languagestorage.cpp \
    ../src/sentencestorage.cpp \
    main.cpp \
    tst_languagestorage.cpp \
    tst_sentencestorage.cpp

HEADERS += \
    ../src/languagestorage.h \
    ../src/sentencestorage.h \
    tst_languagestorage.h \
    tst_sentencestorage.h

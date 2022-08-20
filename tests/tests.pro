QT += testlib sql
QT -= gui

CONFIG += c++17 qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    ../src/languagestorage.cpp \
    ../src/sentencestorage.cpp \
    ../src/user.cpp \
    ../src/usercache.cpp \
    ../src/userstorage.cpp \
    ../src/userstoragedb.cpp \
    main.cpp \
    tst_languagestorage.cpp \
    tst_sentencestorage.cpp \
    tst_usercache.cpp \
    tst_userstorage.cpp \
    tst_userstoragedb.cpp

HEADERS += \
    ../src/common.h \
    ../src/languagestorage.h \
    ../src/sentencestorage.h \
    ../src/user.h \
    ../src/usercache.h \
    ../src/userstorage.h \
    ../src/userstoragedb.h \
    tst_languagestorage.h \
    tst_sentencestorage.h \
    tst_usercache.h \
    tst_userstorage.h \
    tst_userstoragedb.h

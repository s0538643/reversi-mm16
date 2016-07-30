QT       += core testlib widgets
CONFIG   += testcase

TARGET = test
TEMPLATE = app


SOURCES +=\
    test.cpp\
    ../spielbrett.cpp \
    ../minimax.cpp\

HEADERS += ../spielbrett.h \
            ../minimax.h\

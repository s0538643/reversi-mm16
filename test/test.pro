QT       += core testlib widgets multimedia multimediawidgets
CONFIG   += testcase

TARGET = test
TEMPLATE = app


SOURCES +=\
    test.cpp\
    ../spielbrett.cpp \
    ../minimax.cpp \
    ../brettwidget.cpp \
    ../spielwindow.cpp \


HEADERS += ../spielbrett.h \
            ../minimax.h \
            ../brettwidget.h \
            ../spielwindow.h \


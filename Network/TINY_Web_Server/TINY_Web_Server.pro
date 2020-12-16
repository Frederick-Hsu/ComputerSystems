TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
LIBS = -ldl

SOURCES += \
    main.c \
    server_contents.c \
    tiny.c

HEADERS += \
    net.h \
    robust_io.h \
    server_contents.h \
    tiny.h

TEMPLATE = lib
DEFINES += robustio
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        with_buffer_robust_io.c \
        without_buffer_robust_io.c

HEADERS += \
    robust_io.h

DISTFILES += \
    Makefile

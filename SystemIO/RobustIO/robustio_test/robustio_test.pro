TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -rdynamic -ldl

SOURCES += \
    copy_file.c

HEADERS += \
    robust_io.h \
    with_buffer_robust_io.h \
    without_buffer_robust_io.h

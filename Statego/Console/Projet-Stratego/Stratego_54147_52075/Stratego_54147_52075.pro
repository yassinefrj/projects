TEMPLATE = app
CONFIG += console # c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++17 -pedantic-errors

SOURCES += \
    controller/controller.cpp \
    main.cpp \
    model/board.cpp \
    model/piece.cpp \
    model/player.cpp \
    model/position.cpp \
    model/square.cpp \
    model/stratego.cpp \
    utils/file_reader.cpp \
    utils/subject.cpp \
    view/view.cpp


HEADERS += \
    controller/controller.h \
    model/board.h \
    model/color.h \
    model/difficulty.h \
    model/piece.h \
    model/player.h \
    model/position.h \
    model/square.h \
    model/square_type.h \
    model/state.h \
    model/stratego.h \
    utils/file_reader.h \
    utils/keyboard.hpp \
    utils/observer.h \
    utils/string_convert.hpp \
    utils/subject.h \
    view/view.h


QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

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
    view/SquareBtn.cpp \
    view/menu.cpp \
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
    utils/observer.h \
    utils/subject.h \
    view/SquareBtn.h \
    view/Square_button.h \
    view/menu.h \
    view/view.h

FORMS += \
    view.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

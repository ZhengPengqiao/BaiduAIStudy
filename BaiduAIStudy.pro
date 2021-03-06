#-------------------------------------------------
#
# Project created by QtCreator 2020-03-27T21:58:15
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BaiduAIStudy
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS


INCLUDEPATH += $$PWD/Doc/aip-cpp-sdk /usr/include/jsoncpp/
LIBS += -lcurl -lcrypto -ljsoncpp


# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        customtabstyle.cpp \
        settingform.cpp \
    ocrform.cpp

HEADERS += \
        mainwindow.h \
        customtabstyle.h \
        settingform.h \
    ocrform.h

FORMS += \
        mainwindow.ui \
    settingform.ui \
    ocrform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore \
    assert/BaiduAi_Setting.xml

RESOURCES += \
    assert.qrc

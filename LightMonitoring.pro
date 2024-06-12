QT       += core gui
QT       += xml
QT       += serialport
QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    settings.cpp

HEADERS += \
    DefaultSettings.h \
    mainwindow.h \
    settings.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    translations/LightMonitoring_ru.ts \
    translations/LightMonitoring_en.ts \
    translations/LightMonitoring_de.ts

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    translations/LightMonitoring_de.qm \
    translations/LightMonitoring_en.qm \
    translations/LightMonitoring_ru.qm

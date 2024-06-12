#include "mainwindow.h"
#include "settings.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QScreen>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    auto settings = Settings::getInstance();

    if (settings->hasOldFile()) {
        //  set window geometry, coords and size of window
        w.setGeometry(
            settings->getPosX() / 2,
            settings->getPosY() / 2,
            settings->getWidth(),
            settings->getHeight()
        );
    }

    w.show();

    return a.exec();
}

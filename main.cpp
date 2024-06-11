#include "mainwindow.h"
#include "settings.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    auto settings = Settings::getInstance();
    w.resize(settings->getWidth(), settings->getHeight());
    w.show();

    return a.exec();
}

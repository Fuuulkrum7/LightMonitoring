#include "settings.h"

#include <QDir>
#include <QFile>
#include <QtXml>
#include <QXmlStreamWriter>

std::shared_ptr<Settings> Settings::singleton = nullptr;

std::shared_ptr<Settings> Settings::getInstance() {
    // if settings are not loaded yet
    if (singleton == nullptr) {
        singleton.reset(new Settings());
        singleton->loadSettings();
    }

    return singleton;
}

void Settings::writeSettings() {
    QFile fileXML(QDir::currentPath() + "/" + SETTINGS_FOLDER + "/" + SETTINGS_NAME);

    writeSettings(&fileXML);

    fileXML.close();
}

void Settings::writeSettings(QFile* fileXML) {
    fileXML->open(QFile::WriteOnly);

    QXmlStreamWriter stream(fileXML);
    stream.setAutoFormatting(true);
    stream.setAutoFormattingIndent(2);

    stream.writeStartDocument();

    stream.writeStartElement(START_ELEMENT);

    stream.writeTextElement(LOW_BORDER, QString::number(this->lowBorder));
    stream.writeTextElement(HIGH_BORDER, QString::number(this->highBorder));

    stream.writeEndElement();
    stream.writeEndDocument();
}

bool Settings::loadSettings() {
    auto path = QDir::currentPath() + "/" + SETTINGS_FOLDER;

    bool existed = QDir(path).exists();
    QFile fileXML(path + "/" + SETTINGS_NAME);

    // if there is not directory for settings file, create it
    if (!existed)  {
        QDir().mkdir(path);
    }

    // when file is not empty, read it
    if (fileXML.size() > 0)
    {
        QDomDocument domDoc;
        fileXML.open(QFile::ReadOnly);

        domDoc.setContent(&fileXML);
        // get one element from the whole file
        QDomElement domElement = domDoc.documentElement();

        // go into tag START_ELEMENT
        auto data = domElement.firstChildElement();

        // reading all values from xml
        while (!data.isNull()) {
            if (data.tagName() == LOW_BORDER) {
                lowBorder = data.firstChild().nodeValue().toFloat();
            }
            if (data.tagName() == HIGH_BORDER) {
                highBorder = data.firstChild().nodeValue().toFloat();
            }

            // got to next value
            data = data.nextSiblingElement();
        }
    }
    else
    {
        // make note, that we create file
        existed = false;
        // write it
        writeSettings(&fileXML);
        // set default values
        lowBorder = LOW_BORDER_VALUE;
        highBorder = HIGH_BORDER_VALUE;
    }
    // in any case close file
    fileXML.close();

    return existed;
}

float Settings::getHighBorder() const  {
    return highBorder;
}

float Settings::getLowBorder() const  {
    return lowBorder;
}

bool Settings::setHighBorder(float newBorder) {
    if (newBorder < lowBorder) {
        return false;
    }

    highBorder = newBorder;
    return true;
}

bool Settings::setLowBorder(float newBorder) {
    if (newBorder > highBorder) {
        return false;
    }

    lowBorder = newBorder;
    return true;
}

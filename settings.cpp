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

    fileXML.open(QFile::WriteOnly);

    QXmlStreamWriter stream(&fileXML);

    stream.setAutoFormatting(true);
    stream.setAutoFormattingIndent(2);

    stream.writeStartDocument();

    stream.writeStartElement(START_ELEMENT);

    stream.writeTextElement(LOW_BORDER, QString::number(lowBorder));
    stream.writeTextElement(HIGH_BORDER, QString::number(highBorder));

    stream.writeTextElement(WIDTH, QString::number(width));
    stream.writeTextElement(HEIGHT, QString::number(height));

    stream.writeTextElement(LANGUAGE, language);

    stream.writeTextElement(POS_X, QString::number(posX));
    stream.writeTextElement(POS_Y, QString::number(posY));

    stream.writeEndElement();
    stream.writeEndDocument();

    fileXML.close();
}

void Settings::loadSettings() {
    auto path = QDir::currentPath() + "/" + SETTINGS_FOLDER;

    oldFile = QDir(path).exists();
    QFile fileXML(path + "/" + SETTINGS_NAME);

    // if there is not directory for settings file, create it
    if (!oldFile)  {
        QDir().mkdir(path);
    }

    // set default values for borders
    lowBorder  = LOW_BORDER_VALUE;
    highBorder = HIGH_BORDER_VALUE;

    // window params by default
    width  = WIDTH_VALUE;
    height = HEIGHT_VALUE;

    // default lang
    language = LANGUAGE_VALUE;

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
            else if (data.tagName() == HIGH_BORDER) {
                highBorder = data.firstChild().nodeValue().toFloat();
            }
            else if (data.tagName() == WIDTH) {
                width = data.firstChild().nodeValue().toFloat();
            }
            else if (data.tagName() == HEIGHT) {
                height = data.firstChild().nodeValue().toFloat();
            }
            else if (data.tagName() == LANGUAGE) {
                language = data.firstChild().nodeValue();
            }
            else if (data.tagName() == POS_X) {
                posX = data.firstChild().nodeValue().toFloat();
            }
            else if (data.tagName() == POS_Y) {
                posY = data.firstChild().nodeValue().toFloat();
            }

            // got to next value
            data = data.nextSiblingElement();
        }
    }
    else
    {
        // make note, that we has no file
        oldFile = false;
    }

    // in any case close file
    fileXML.close();
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

bool Settings::hasOldFile() const {
    return oldFile;
}

uint16_t Settings::getWidth() const {
    return width;
}

uint16_t Settings::getHeight() const {
    return height;
}


void Settings::setWidth(uint16_t newValue) {
    width = newValue;
}

void Settings::setHeight(uint16_t newValue) {
    height = newValue;
}

uint16_t Settings::getPosX() const {
    return posX;
}

uint16_t Settings::getPosY() const {
    return posY;
}


void Settings::setPosX(uint16_t newValue) {
    posX = newValue;
}

void Settings::setPosY(uint16_t newValue) {
    posY = newValue;
}


QString Settings::getLanguage() const {
    return language;
}

void Settings::setLanguage(const QString &language) {
    this->language = language;
}

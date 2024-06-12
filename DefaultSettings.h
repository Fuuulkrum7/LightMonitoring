#ifndef DEFAULTSETTINGS_H
#define DEFAULTSETTINGS_H

#include <QString>
#include <cstdint>

static const QString SETTINGS_NAME = ".settings.xml";
static const QString SETTINGS_FOLDER = ".settings";

static const QString START_ELEMENT = "settings";

// names of elements
static const QString LOW_BORDER = "low_border";
static const QString HIGH_BORDER = "high_border";
static const QString WIDTH = "width";
static const QString HEIGHT = "height";
static const QString POS_X = "pos_x";
static const QString POS_Y = "pos_y";
static const QString LANGUAGE = "language";

static const float LOW_BORDER_VALUE = 0;
static const float HIGH_BORDER_VALUE = 100;

static const uint16_t WIDTH_VALUE = 720;
static const uint16_t HEIGHT_VALUE = 480;

static const QString LANGUAGE_VALUE = "ru";

#endif // DEFAULTSETTINGS_H

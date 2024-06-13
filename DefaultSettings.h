#ifndef DEFAULTSETTINGS_H
#define DEFAULTSETTINGS_H

#include <QString>
#include <cstdint>

inline const QString SETTINGS_NAME = ".settings.xml";
inline const QString SETTINGS_FOLDER = ".settings";

inline const QString START_ELEMENT = "settings";

// names of elements
inline const QString LOW_BORDER = "low_border";
inline const QString HIGH_BORDER = "high_border";
inline const QString WIDTH = "width";
inline const QString HEIGHT = "height";
inline const QString POS_X = "pos_x";
inline const QString POS_Y = "pos_y";
inline const QString LANGUAGE = "language";

inline const float LOW_BORDER_VALUE = 0;
inline const float HIGH_BORDER_VALUE = 100;

inline const uint16_t WIDTH_VALUE = 720;
inline const uint16_t HEIGHT_VALUE = 480;

inline const QString LANGUAGE_VALUE = "ru";

#endif // DEFAULTSETTINGS_H

#ifndef SETTINGS_H
#define SETTINGS_H

#include <cstdint>
#include <memory>
#include <QFile>

#include "DefaultSettings.h"

class Settings
{
public:
    Settings(Settings& other) = delete;
    void operator=(const Settings&) = delete;

    static std::shared_ptr<Settings> getInstance();

    void writeSettings();

    float getLowBorder() const;
    float getHighBorder() const;

    bool setLowBorder(float newBorder);
    bool setHighBorder(float newBorder);

    uint16_t getWidth() const;
    uint16_t getHeight() const;

    void setWidth(uint16_t newValue);
    void setHeight(uint16_t newValue);

    // is false, when file is created, and true,
    // when we already have settings file
    bool hasOldFile() const;

    uint16_t getPosX() const;
    uint16_t getPosY() const;

    void setPosX(uint16_t newValue);
    void setPosY(uint16_t newValue);

    QString getLanguage() const;
    void setLanguage(const QString &language);

    // this langs ar supported
    const QStringList languagesAllowed = {"ru", "en", "de"};
    const QStringList languagesAllowedNames = {"Русский", "English", "Deutsch"};

protected:
    Settings() = default;
    void loadSettings();
private:
    float lowBorder = 0;
    float highBorder = 0;
    uint16_t width = 0;
    uint16_t height = 0;

    uint16_t posX = 0;
    uint16_t posY = 0;

    bool oldFile = true;

    QString language;
    //  use singletone
    static std::shared_ptr<Settings> singleton;
};

#endif // SETTINGS_H

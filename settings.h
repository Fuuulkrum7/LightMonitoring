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
protected:
    Settings() = default;
    bool loadSettings();
private:
    float lowBorder = 0;
    float highBorder = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    //  use singletone
    static std::shared_ptr<Settings> singleton;
};

#endif // SETTINGS_H

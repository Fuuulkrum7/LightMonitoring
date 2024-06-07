#ifndef SETTINGS_H
#define SETTINGS_H

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
protected:
    Settings() = default;
    bool loadSettings();
private:
    float lowBorder = 0;
    float highBorder = 0;
    //  use singletone
    static std::shared_ptr<Settings> singleton;
};

#endif // SETTINGS_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLocale>
#include <QSerialPort>
#include <QTranslator>

#include "settings.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_comboBox_currentIndexChanged(int index);
    void on_lowBorderChanged();
    void on_highBorderChanged();
    void updateLuxValue(float lux);

private:
    void readData();
    void writeData(const QByteArray &data);

    Ui::MainWindow *ui;

    std::shared_ptr<Settings> settings;
    QSerialPort *port;
    QTranslator translator;
    QLocale currentLocale;
    void changeLanguage(const QString &languageCode);
    void updateLabelColor();
    void updateNumberFormats();
};
class ValueConverter {
private:
    std::vector<std::pair<int, int>> valuePairs;

public:
    ValueConverter() {
        valuePairs = {
            {81, 190},
            {100, 180},
            {120, 171},
            {140, 164},
            {160, 159},
            {180, 154},
            {200, 150},
            {250, 142},
            {300, 137},
            {400, 129}
        };
    }

    int convert(int inputValue) {
        // Если значение меньше минимального или больше максимального в таблице
        if (inputValue >= valuePairs.front().second) {
            return valuePairs.front().first;
        }
        if (inputValue <= valuePairs.back().second) {
            return valuePairs.back().first;
        }

        // Поиск ближайших значений
        for (size_t i = 0; i < valuePairs.size() - 1; ++i) {
            if (inputValue == valuePairs[i].second) {
                return valuePairs[i].first;
            }
            if (inputValue < valuePairs[i].second && inputValue > valuePairs[i + 1].second) {
                // Линейная интерполяция
                int x1 = valuePairs[i].second;
                int y1 = valuePairs[i].first;
                int x2 = valuePairs[i + 1].second;
                int y2 = valuePairs[i + 1].first;

                double slope = (double)(y2 - y1) / (x2 - x1);
                return y1 + slope * (inputValue - x1);
            }
        }

        return -1; // В случае ошибки
    }
};
#endif // MAINWINDOW_H

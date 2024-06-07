#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLocale>
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
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_comboBox_currentIndexChanged(int index);
    void on_lowBorderChanged();
    void on_highBorderChanged();
    void updateLuxValue(float lux);

private:
    Ui::MainWindow *ui;

    std::shared_ptr<Settings> settings;
    QTranslator translator;
    QLocale currentLocale;
    void changeLanguage(const QString &languageCode);
    void updateLabelColor();
    void updateNumberFormats();
};
#endif // MAINWINDOW_H

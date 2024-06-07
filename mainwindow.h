#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>

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

private:
    void readData();
    void writeData(const QByteArray &data);

    Ui::MainWindow *ui;

    std::shared_ptr<Settings> settings;
    QSerialPort *port;
};
#endif // MAINWINDOW_H

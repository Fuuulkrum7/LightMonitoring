#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QApplication>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    settings = Settings::getInstance();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeLanguage(const QString &languageCode) {
    QCoreApplication::removeTranslator(&translator);
    QString currentPath = QDir::currentPath();
    QString targetFolder = "LightMonitoring";
    QString resultPath;

    int targetIndex = currentPath.indexOf(targetFolder);
    if (targetIndex != -1)
        resultPath = currentPath.left(targetIndex + targetFolder.length());
    if (translator.load(resultPath + "/translations/LightMonitoring_" + languageCode + ".qm")) {
        qDebug() << "success";
        QCoreApplication::installTranslator(&translator);
        ui->retranslateUi(this);  // Обновить UI для перевода
    }
    else
        qDebug() << "not success";
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    QString languageCode;
    switch (index) {
    case 0:
        languageCode = "ru";
        break;
    case 1:
        languageCode = "en";
        break;
    case 2:
        languageCode = "de";
        break;
    default:
        languageCode = "ru";
        break;
    }
    changeLanguage(languageCode);
    qDebug() << languageCode;
}


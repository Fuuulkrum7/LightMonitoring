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

    // Установка начальных значений из настроек
    ui->lineEdit_2->setText(QString::number(settings->getLowBorder()));
    ui->lineEdit->setText(QString::number(settings->getHighBorder()));

    // Подключение сигналов
    connect(ui->lineEdit_2, &QLineEdit::editingFinished, this, &MainWindow::on_lowBorderChanged);
    connect(ui->lineEdit, &QLineEdit::editingFinished, this, &MainWindow::on_highBorderChanged);

    updateLabelColor();
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

void MainWindow::on_lowBorderChanged()
{
    bool ok;
    float lowBorder = ui->lineEdit_2->text().toFloat(&ok);
    if (ok && settings->setLowBorder(lowBorder)) {
        settings->writeSettings();
        qDebug() << "Low border set to" << lowBorder;
        updateLabelColor();
    } else {
        qDebug() << "Failed to set low border";
    }
}

void MainWindow::on_highBorderChanged()
{
    bool ok;
    float highBorder = ui->lineEdit->text().toFloat(&ok);
    if (ok && settings->setHighBorder(highBorder)) {
        settings->writeSettings();
        qDebug() << "High border set to" << highBorder;
        qDebug() << settings->getHighBorder();
        updateLabelColor();
    } else {
        qDebug() << "Failed to set high border";
    }
}

void MainWindow::updateLuxValue(float lux)
{
    QString luxText = QString::number(lux, 'f', 2);
    ui->label->setText(luxText);
    updateLabelColor();
}

void MainWindow::updateLabelColor()
{
    float lux = ui->label->text().toFloat();
    if (lux < settings->getLowBorder()) {
        ui->label->setStyleSheet("QLabel { color : blue; }");
    } else if (lux > settings->getHighBorder()) {
        ui->label->setStyleSheet("QLabel { color : red; }");
    } else {
        ui->label->setStyleSheet("QLabel { color : green; }");
    }
}


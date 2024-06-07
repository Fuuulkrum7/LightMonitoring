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
    ui->lineEdit_2->setText(currentLocale.toString(settings->getLowBorder(), 'f', 2));
    ui->lineEdit->setText(currentLocale.toString(settings->getHighBorder(), 'f', 2));

    // Подключение сигналов
    connect(ui->lineEdit_2, &QLineEdit::editingFinished, this, &MainWindow::on_lowBorderChanged);
    connect(ui->lineEdit, &QLineEdit::editingFinished, this, &MainWindow::on_highBorderChanged);

    // Установка начальной локали
    currentLocale = QLocale::system();

    updateLabelColor();
    updateNumberFormats();
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

    // Установка локали на основе языка
    if (languageCode == "ru") {
        currentLocale = QLocale(QLocale::Russian);
    } else if (languageCode == "en") {
        currentLocale = QLocale(QLocale::English);
    } else if (languageCode == "de") {
        currentLocale = QLocale(QLocale::German);
    }

    updateNumberFormats();
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
    QString text = ui->lineEdit_2->text();
    float lowBorder = currentLocale.toFloat(text, &ok);
    qDebug() << "Trying to set low border with text:" << text << ", converted to float:" << lowBorder;
    if (ok && settings->setLowBorder(lowBorder)) {
        settings->writeSettings();
        qDebug() << "Low border set to" << lowBorder;
    } else {
        qDebug() << "Failed to set low border with text:" << text;
    }
    updateLabelColor();
    //updateNumberFormats();
}

void MainWindow::on_highBorderChanged()
{
    bool ok;
    QString text = ui->lineEdit->text();
    float highBorder = currentLocale.toFloat(text, &ok);
    qDebug() << "Trying to set high border with text:" << text << ", converted to float:" << highBorder;
    if (ok && settings->setHighBorder(highBorder)) {
        settings->writeSettings();
        qDebug() << "High border set to" << highBorder;
    } else {
        qDebug() << "Failed to set high border with text:" << text;
    }
    updateLabelColor();
    //updateNumberFormats();
}

void MainWindow::updateLuxValue(float lux)
{
    // QString luxText = currentLocale.toString(lux, 'f', 2);
    // ui->label->setText(luxText);
    // updateLabelColor();
    0;
}

void MainWindow::updateLabelColor()
{
    qDebug() << ui->label->text();
    float lux = currentLocale.toFloat(ui->label->text());
    qDebug() << lux;
    if (lux < settings->getLowBorder()) {
        ui->label->setStyleSheet("QLabel { color : blue; }");
    } else if (lux > settings->getHighBorder()) {
        ui->label->setStyleSheet("QLabel { color : red; }");
    } else {
        ui->label->setStyleSheet("QLabel { color : green; }");
    }
    qDebug() << ui->label->text();
}

void MainWindow::updateNumberFormats()
{
    ui->lineEdit_2->setText(currentLocale.toString(settings->getLowBorder(), 'f', 2));
    ui->lineEdit->setText(currentLocale.toString(settings->getHighBorder(), 'f', 2));
    ui->label->setText(currentLocale.toString(ui->label->text().toFloat(), 'f', 2));
    qDebug() << ui->label->text();
}


#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QIODevice>
#include <QtEndian>
#include <QDebug>
#include <QApplication>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , port(new QSerialPort(this))
{
    ui->setupUi(this);
    settings = Settings::getInstance();
    port->setPortName("COM1");
    port->setBaudRate(9600);
    port->setDataBits(QSerialPort::Data8);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    port->setFlowControl(QSerialPort::NoFlowControl);

    port->open(QIODevice::ReadWrite);
    connect(port, &QSerialPort::readyRead, this, &MainWindow::readData);

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

MainWindow::~MainWindow() {
    settings->writeSettings();
    delete ui;
}

void MainWindow::readData() {
    QByteArray data = port->readAll();
    updateLuxValue(255u - qFromLittleEndian<qint16>(data.data()));
    //qDebug() << 255u - qFromLittleEndian<qint16>(data.data());
}

void MainWindow::writeData(const QByteArray &data) {
    port->write(data);
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
        QCoreApplication::installTranslator(&translator);
        ui->retranslateUi(this);  // Обновить UI для перевода
    }

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
    qDebug() << "Switched to " << languageCode;
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
        ui->lineEdit_2->setText(currentLocale.toString(settings->getLowBorder(), 'f', 2));
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
        ui->lineEdit->setText(currentLocale.toString(settings->getHighBorder(), 'f', 2));
    }
    updateLabelColor();
    //updateNumberFormats();
}

void MainWindow::updateLuxValue(float lux)
{
    QString luxText = currentLocale.toString(lux, 'f', 2);
    ui->label->setText(luxText);
    updateLabelColor();
}

void MainWindow::updateLabelColor()
{
    float lux = currentLocale.toFloat(ui->label->text());
    if (lux < settings->getLowBorder()) {
        ui->label->setStyleSheet("QLabel { color : blue; }");
    } else if (lux > settings->getHighBorder()) {
        ui->label->setStyleSheet("QLabel { color : red; }");
    } else {
        ui->label->setStyleSheet("QLabel { color : green; }");
    }
}

void MainWindow::updateNumberFormats()
{
    ui->lineEdit_2->setText(currentLocale.toString(settings->getLowBorder(), 'f', 2));
    ui->lineEdit->setText(currentLocale.toString(settings->getHighBorder(), 'f', 2));
    ui->label->setText(currentLocale.toString(ui->label->text().toFloat(), 'f', 2));
}


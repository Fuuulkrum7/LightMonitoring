#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIODevice>
#include <QtEndian>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    port(new QSerialPort(this))
{
    ui->setupUi(this);
    settings = Settings::getInstance();
    ui->setupUi(this);
    port->setPortName("COM3");
    port->setBaudRate(9600);
    port->setDataBits(QSerialPort::Data8);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    port->setFlowControl(QSerialPort::NoFlowControl);

    port->open(QIODevice::ReadWrite);
    connect(port, &QSerialPort::readyRead, this, &MainWindow::readData);
}

MainWindow::~MainWindow() {
    settings->writeSettings();
    delete ui;
}

void MainWindow::readData() {
    QByteArray data = port->readAll();
    // TODO here can be added read
    qDebug() << "here: " << 255u - qFromLittleEndian<qint16>(data.data());;
}

void MainWindow::writeData(const QByteArray &data) {
    port->write(data);
}

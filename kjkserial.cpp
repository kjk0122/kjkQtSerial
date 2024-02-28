// kjkserial.cpp

#include "kjkserial.h"
#include "ui_kjkserial.h"

Kjkserial::Kjkserial(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::Kjkserial),
    serial(new QSerialPort(this))
{
    ui->setupUi(this);

    connect(serial, &QSerialPort::readyRead, this, &Kjkserial::on_readyRead);
}

Kjkserial::~Kjkserial()
{
    delete ui;
}

void Kjkserial::on_connectButton_clicked()
{
    if (serial->isOpen()) {
        serial->close();
        ui->connectButton->setText("Connect");
    } else {
        serial->setPortName("COM8"); // Set your Arduino port here
        serial->setBaudRate(QSerialPort::Baud9600);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);

        if (serial->open(QIODevice::ReadWrite)) {
            ui->connectButton->setText("Disconnect");
        }
    }
}

void Kjkserial::on_sendButton_clicked()
{
    if (serial->isOpen()) {
        QString message = ui->messageEdit->text() + "\n";
        serial->write(message.toUtf8());
    }
}

void Kjkserial::on_readyRead()
{
    QByteArray data = serial->readAll();
    // Process received data as needed
}

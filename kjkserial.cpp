#include "kjkserial.h"
#include "ui_kjkserial.h"
#include "logger.h"
#include <QTextCursor>

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
    Logger logger("debug_log");

    if (serial->isOpen()) {
        serial->close();
        ui->connectButton->setText("Connect");
        logger.logMessage("Disconnected");
        qDebug() << "Disconnected";
    } else {
        serial->setPortName("COM8"); // Set your Arduino port here
        serial->setBaudRate(QSerialPort::Baud9600);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        logger.logMessage("Connected");
        qDebug() << "Connected";
        if (serial->open(QIODevice::ReadWrite)) {
            ui->connectButton->setText("Disconnect");
        }else{
            qDebug() << "Connection failed";
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
    QString receivedData = QString(data);

    // Log the entire received data
    Logger logger("value");
    logger.logMessage(receivedData);

    // Split the received data based on newline characters
    QStringList messages = receivedData.split("\n", Qt::SkipEmptyParts);

    // Display the last received message
    if (!messages.isEmpty()) {
        ui->numberGet->setText(messages.last());
    }
}



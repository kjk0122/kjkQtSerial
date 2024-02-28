#include "kjkserial.h"
#include "ui_kjkserial.h"
#include "logger.h"
#include <QTextCursor>
#include <QSerialPortInfo>

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

void Kjkserial::on_connectButton_clicked() {
    // 연결 관련 디버깅 파일 작성
    Logger logger("Connection_log");

    if (serial->isOpen()) {
        serial->close();
        ui->connectButton->setText("Connect");
        logger.logMessage("Disconnected");
        qDebug() << "Disconnected";
    } else {
        // 아두이노에 꽂은 시리얼 포트 목록 가져오기
        QString targetPortName = "Arduino";
        QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();
        QString portName;
        for (const auto& portInfo : availablePorts) {
            if (portInfo.description().contains(targetPortName, Qt::CaseInsensitive)) {
                portName = portInfo.portName();
                break;
            }
        }
        // 바우드레이트 등 설정해주기
        if (!portName.isEmpty()) {
            serial->setPortName(portName);
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);

            logger.logMessage("Connected to " + portName);
            qDebug() << "Connected to" << portName;

            if (serial->open(QIODevice::ReadWrite)) {
                ui->connectButton->setText("Disconnect");
            } else {
                qDebug() << "Connection failed";
            }
        } else {
            qDebug() << "Target port not found";
            logger.logMessage("Target port not found");
        }
    }
}

void Kjkserial::on_readyRead()
{
    QByteArray data = serial->readAll();
    QString receivedData = QString(data);

    // 값에 대한 로깅(조건문은 추후 추가)
    Logger logger("value");
    logger.logMessage(receivedData);

    // 제대로 받을때까지 필터링
    QStringList messages = receivedData.split("\n", Qt::SkipEmptyParts);
    // text에 보이는 방식은 갱신 형식으로
    if (!messages.isEmpty()) {
        ui->numberGet->setText(messages.last());
    }
}



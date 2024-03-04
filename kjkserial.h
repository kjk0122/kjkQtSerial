#ifndef KJKSERIAL_H
#define KJKSERIAL_H

#include <QMainWindow>
#include <QSerialPort>
#include "logger.h"
#include "sqlite.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Kjkserial; }
QT_END_NAMESPACE

class Kjkserial : public QMainWindow
{
    Q_OBJECT

public:
    Kjkserial(QWidget *parent = nullptr);
    ~Kjkserial();

private slots:
    void on_connectButton_clicked();
    void on_readyRead();

private:
    Ui::Kjkserial *ui;
    QSerialPort *serial;
    Logger logger;
    Sqlite *sqlite;  // Sqlite 멤버 변수를 추가

    // 나머지 멤버 변수 및 함수들은 그대로 유지
};

#endif // KJKSERIAL_H

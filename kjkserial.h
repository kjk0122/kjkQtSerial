#ifndef KJKSERIAL_H
#define KJKSERIAL_H

#include <QMainWindow>
#include <QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui {
class Kjkserial;
}
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
};

#endif

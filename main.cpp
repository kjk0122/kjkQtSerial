#include "kjkserial.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Kjkserial w;
    w.show();
    return a.exec();
}

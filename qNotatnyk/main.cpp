#include "widget.h"
#include "Note.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    qDebug() << __DATE__;
    qDebug() << __TIME__;
    return a.exec();
}

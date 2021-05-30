#include "IconNote.h"

#include <iostream>
#include <QWidget>
using namespace std;
IconNote::IconNote()
{

}

 QString IconNote::getDate()
{
    qDebug() << "INote has been created" << iN;
    QDateTime qdate = QDateTime::currentDateTime();
    QString date = qdate.toString();
    return date;
}

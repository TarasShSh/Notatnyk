#ifndef ICONNOTE_H
#define ICONNOTE_H
#include <string>
#include "QDebug"
#include <QTextBrowser>
#include <QDateTime>
#include "QLabel"       // текст
#include "QSortFilterProxyModel"

using namespace std;

class IconNote
{
private:


public:
    QTextBrowser *iN = new QTextBrowser(); // область прокрутки
    QLabel *dateL = new QLabel,            // текстова дата створення/редагування для іконки(редагування ще не реалізоване)
           *groupL = new QLabel;           // Назва групи нотатки
    IconNote();
    QString title, date, group;
    QString getDate();
    QString getTitle(){return title;}
    void setTitle(QString t){title = t;};

    QString getGroup(){return group;}
    void setGroup(QString g){group = g;}

};
#endif // ICONNOTE_H

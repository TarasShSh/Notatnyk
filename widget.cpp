#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QtCore>

Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("Нотатник");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::createShortcutNote(Note *n)
{
     ++i;
     n->date = n->getDate();
     n->setGroup("");
     ui->notesList->addItem(n->sc);

     ui->archiveButton->setEnabled(true);
     ui->archiveButton->setCursor(Qt::PointingHandCursor);
}

void Widget::on_createNoteButton_clicked()
{
    Note *n = new Note();
    qDebug() << "Note has been created" << n;
    n->show();
    qDebug()<< n->getDate();
    createShortcutNote(n); // функція створення ярлика нотатки
}

void Widget::on_aboutQTButton_clicked()
{
    QMessageBox::aboutQt(this,"About Qt");
}

void Widget::on_exitButton_clicked()
{
   close();
}

void Widget::on_toArchiveButton_clicked()
{

    qDebug() << "beep ArchiveLAY";
}

void Widget::on_oldestFirstButton_clicked()
{
     qDebug() << "beep OLDESTfirst";
}

void Widget::on_newestFirstButton_clicked()
{
    qDebug() << "beep newestFIRST";

}

void Widget::on_archiveButton_clicked()
{

    qDebug() << "beep Archive";
}

void Widget::openNote() // відкриття нотаток по ярликам
{

}

void Widget::on_notesList_itemClicked(QListWidgetItem *item) // перегляд тексту нотатки
{
    ui->preview->setText(item->whatsThis());
}

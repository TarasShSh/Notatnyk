#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QtCore>
#include <QAction>

Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("Нотатник");


    //QDir myPath();
    //myPath.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    //myList = myPath.entryList();

   Note* item;
    myList = getTitle(item);
    ui->notesList->addItems(myList);
    ui->lblt->setText(QString("%1").arg(ui->notesList->count()));




    //QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    //proxyModel->setSourceModel(new QStringListModel(list));

   // QStandardItemModel* mod = new QStandardItemModel(this);
    //ui->notesList->setModel(mod);
}

/*
void updateListFilter(const QString& filterString)
{
proxyModel->setFilterWildcard(QString("%1").arg(filterString);
}
*/

Widget::~Widget()
{
    delete ui;
}

void Widget::createShortcutNote(Note *n)
{
     ++i;
     n->date = n->getDate();
       n->group = n->getGroup();
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
  QApplication::quit();
}

void Widget::on_toArchiveButton_clicked()
{

    qDebug() << "beep ArchiveLAY";
}

void Widget::on_oldestFirstButton_clicked()
{
    if(ui->newestFirstButton->isChecked())
    {
     ui->notesList->model()->sort(0,Qt::AscendingOrder);
     qDebug() << "firstnewest";
    }
    if(ui->oldestFirstButton->isChecked())
    {
     ui->notesList->model()->sort(0,Qt::DescendingOrder);
     qDebug() << "firstoldest";
    }

}

void Widget::on_newestFirstButton_clicked()
{
   if(ui->newestFirstButton->isChecked())
   {
    ui->notesList->model()->sort(0,Qt::AscendingOrder);
    qDebug() << "firstnewest";
   }
   if(ui->oldestFirstButton->isChecked())
   {
    ui->notesList->model()->sort(0,Qt::DescendingOrder);
    qDebug() << "firstoldest";
   }

}

void Widget::openNote() // відкриття нотаток по ярликам
{

}

void Widget::on_notesList_itemClicked(QListWidgetItem *item) // перегляд тексту нотатки
{
    ui->preview->setText(item->whatsThis());
}



void Widget::on_pushButton_clicked(Note* item)
{
    if(!(ui->selfCheckBox->isChecked()))
    {
        item->group = item->getGroup();
        if(item->getGroup()=="self")
        {
            item->hide();
        }
    }
    else
    {
     item->show();
    }

}




void Widget::on_archiveButton_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this,"Архівування нотатки","Ви точно хочете архівувати цю нотатку?",
                          QMessageBox::Yes | QMessageBox::No);

    if(reply ==  QMessageBox::Yes)
    {
    QListWidgetItem* it = ui->notesList->takeItem(mySelected);
   ui->archiveList->addItem(it);
    }
    else
    {
    qDebug()<<"Wasn't archived ";
    }
}

void Widget::on_pushButton_2_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this,"Видалення нотатки","Ви точно хочете видалити цю нотатку назавжди?",
                          QMessageBox::Yes | QMessageBox::No);

    if(reply ==  QMessageBox::Yes)
    {
    QListWidgetItem* it = ui->notesList->takeItem(mySelected);
     delete it;
    }
    else
    {
    qDebug()<<"Wasn't deleted";
    }
}


void Widget::on_notesList_currentRowChanged(int currentRow)
{
    mySelected = currentRow;
}





void Widget::on_archiveList_itemClicked(QListWidgetItem *item)
{
    ui->preview->setText(item->whatsThis());
}


void Widget::on_archiveList_currentRowChanged(int currentRow)
{
     mySelected = currentRow;
}




void Widget::on_pushButton_3_clicked()
{    
    QListWidgetItem* it = ui->archiveList->takeItem(mySelected);
   ui->notesList->addItem(it);

    qDebug() << "beep Disarchive";
}


void Widget::on_pushButton_4_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this,"Видалення з архіву","Ви точно хочете видалити цю нотатку назавжди?",
                          QMessageBox::Yes | QMessageBox::No);

    if(reply ==  QMessageBox::Yes)
    {
        QListWidgetItem* it = ui->archiveList->takeItem(mySelected);
         delete it;
    }
    else
    {
        qDebug()<<"Wasn't deleted";
    }
}









void Widget::on_lineEdit_textChanged(const QString &arg1)
{
   QRegularExpression regExp(arg1, QRegularExpression::CaseInsensitiveOption);
   ui->notesList->clear();
   ui->notesList->addItems(myList.filter(regExp));
   ui->lblt->setText(QString("%1").arg(ui->notesList->count()));

}


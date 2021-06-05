#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QtCore>
#include <QAction>

Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("Нотатник");


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
    n->date = n->getDate();
    n->group = n->getGroup();
    n->setGroup(n->groupNames[0]);
    n->sc->setData(1, noteNumber);
    ui->notesList->addItem(n->sc);


    n->shcSetDate( n->getDate());
    n->shcSetTitle(n->getTitle());
    n->shcSetGroup(n->groupNames[0]);
    n->shc->setData(0, 1, noteNumber);
    ui->notesTree->addTopLevelItem(n->shc);

    ui->archiveButton->setEnabled(true);
    ui->archiveButton->setCursor(Qt::PointingHandCursor);
}
void Widget::on_createNoteButton_clicked()
{
    Note *n = new Note();
    ++noteNumber;
    notes[noteNumber] = n;
    qDebug() << "Note has been created" << n <<"Time:"<< n->getDate();
    n->show();
    createShortcutNote(n); // функція створення ярлика нотатки

    ui->actionsOnScLayer->setEnabled(true);
    ui->deleteButton->setEnabled(true);
    ui->createSubNote->setEnabled(true);
}
void Widget::on_createSubNote_clicked()
{
    Note *n = new Note();
    ++noteNumber;
    notes[noteNumber] = n;
    qDebug() << "Subnote has been created" << n <<"Time:"<< n->getDate();

    n->shcSetDate( n->getDate());
    n->shcSetTitle(n->getTitle());
    n->shcSetGroup(n->groupNames[0]);
    n->shc->setData(0, 1, noteNumber);
    n->show();
    ui->notesTree->currentItem()->addChild(n->shc);

}

void Widget::on_notesList_itemDoubleClicked(QListWidgetItem *item) // відкриття нотаток по ярликам
{
    notes[item->data(1).toInt()]->show();
}
void Widget::on_notesTree_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    notes[item->data(0,1).toInt()]->show();
}

void Widget::myListUpdate()
{
    myList.clear();
    for (int var = 0; var < ui->notesList->count(); ++var)
    {
    myList.append( ui->notesList->item(var)->text());
    }
}

void Widget::on_aboutQTButton_clicked()
{
    QMessageBox::aboutQt(this,"About Qt");
}

void Widget::on_exitButton_clicked()
{
  QApplication::quit();
}

void Widget::on_zaButton_clicked()
{
     ui->notesList->model()->sort(0,Qt::DescendingOrder);
     qDebug() << "z-a";
}
void Widget::on_azButton_clicked()
{
    ui->notesList->model()->sort(0,Qt::AscendingOrder);

    ui->notesList->sortItems(Qt::AscendingOrder);
    qDebug() << "a-z";
}

void Widget::on_notesList_itemClicked(QListWidgetItem *item) // перегляд тексту нотатки
{
    ui->preview->setText(item->whatsThis());

}
void Widget::on_notesTree_itemClicked(QTreeWidgetItem *item, int column)
{
    ui->preview->setText(item->whatsThis(0));
}

void Widget::on_filteredButton_clicked(Note* item)
{
    if(!(ui->selfCheckBox->isChecked()))
    {
        item->group = item->getGroup();
        if(item->getGroup()=="Персональна")
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
    QListWidgetItem* it = ui->notesList->takeItem(mySelected);
   ui->archiveList->addItem(it);

   ui->archiveNotesTree->addTopLevelItem( ui->notesTree->takeTopLevelItem(ui->notesTree->currentIndex().row()));
   myListUpdate();
    ui->unArchiveButton->setEnabled(true);
}

void Widget::on_deleteButton_clicked()
{
   QMessageBox::StandardButton reply = QMessageBox::question(this,"Видалення нотатки","Ви точно хочете видалити цю нотатку назавжди?",
                          QMessageBox::Yes | QMessageBox::No);

    if(reply ==  QMessageBox::Yes)
    {
        if(ui->tabWidget->currentWidget() == ui->notesTab)
        {
            delete ui->notesTree->currentItem();
        }
        else if(ui->tabWidget->currentWidget() == ui->archiveTab)
        {
            delete ui->archiveList->takeItem(mySelected);
            delete ui->archiveNotesTree->currentItem();
        }
    myListUpdate();
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




void Widget::on_unArchiveButton_clicked()
{    
    QListWidgetItem* it = ui->archiveList->takeItem(mySelected);
   ui->notesList->addItem(it);

   // Отримуємо номер виділеного рядка ui->notesTree->currentIndex().row()
   // Вирізаємо takeTopLevelItem() та додаємо addTopLevelItem виділений рядок до архіву

   // Отримуємо номер виділеного рядка ui->archiveNotesTree->currentIndex().row()
   // Вирізаємо takeTopLevelItem() та повертаємо addTopLevelItem виділений рядок нотаток
     ui->notesTree->addTopLevelItem( ui->archiveNotesTree->takeTopLevelItem( ui->archiveNotesTree->currentIndex().row() ) );


myListUpdate();
  // ui->notesTree->insertTopLevelItem(0,ui->archiveNotesTree->currentItem());
  // ui->notesTree->addTopLevelItem(ui->archiveNotesTree->currentItem());
    qDebug() << "beep Disarchive";
}

void Widget::on_searchLine_textChanged(const QString &arg1)
{
    QRegularExpression regExp(arg1, QRegularExpression::CaseInsensitiveOption);
    ui->notesList->clear();
    ui->notesList->addItems(myList.filter(regExp));
    myListFiltered = myList.filter(regExp);

    for (int i = 0; i < ui->notesList->count(); ++i)
    {
            for (int j= 0; j< myListFiltered.length(); ++j)
            {
                if(myList[i]!=myListFiltered[j])
                {
                    ui->notesList->item(i)->setHidden(true);
                }
                else
                {
                    ui->notesList->item(i)->setHidden(false);
                     j = myListFiltered.length();
                }
             }
    }
    //  TREE
    QList<QTreeWidgetItem*> filter = ui->notesTree->findItems(arg1,Qt::MatchExactly, 0);

    qDebug()<<ui->notesTree->topLevelItemCount();
    qDebug()<<ui->notesTree->topLevelItem(0)->childCount();
    int times = 0;
    for (int father = 0; father < (ui->notesTree->topLevelItemCount()); ++father)
    {
        qDebug() << "Father count = " << father;
    for (int child = 0; child < (ui->notesTree->topLevelItem(father)->childCount());)
        {
                qDebug() << "Child count = " << child;
                if(!ui->notesTree->topLevelItem(father)->child(child)->text(0).contains(regExp))
                {
                    qDebug() << "!contain " << true;
                    ui->notesTree->topLevelItem(father)->child(child)->setHidden(true);
                    ++child;
                }
                else
                {
                    qDebug() << "!contain " << false;
                     ui->notesTree->topLevelItem(father)->child(child)->setHidden(false);
                    ++child;
                     ++times;
                }
        }
    }
    ui->foundedNumber->setText(QString("%1").arg(times));
}

// При редагуванні будь-якого параметру об’єкта ->очищення й повторне додавання оновленого списку
void Widget::on_notesList_itemChanged(QListWidgetItem *item)
{
    myList.clear();
    for (int var = 0; var < ui->notesList->count(); ++var)
    {
        myList.append( ui->notesList->item(var)->text());
    }
}

void Widget::on_notesTree_clicked(const QModelIndex &index)
{

    qDebug()<<"notesTree_clicked index: "<<index;
}

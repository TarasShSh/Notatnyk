#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QtCore>
#include <QAction>

Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("Нотатник");
   ui->colors->hide();

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

    n->resize(470,630);
        n->setMinimumSize(470,630);
        n->setMaximumSize(880,630);
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

    n->resize(470,630);
        n->setMinimumSize(470,630);
        n->setMaximumSize(880,630);
        n->show();

    ui->notesTree->currentItem()->addChild(n->shc);

}


void Widget::on_notesTree_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    notes[item->data(0,1).toInt()]->show();
}

void Widget::on_aboutQTButton_clicked()
{
    QMessageBox::aboutQt(this,"About Qt");
}

void Widget::on_exitButton_clicked()
{
  QApplication::quit();
}

void Widget::on_notesTree_itemClicked(QTreeWidgetItem *item, int column)
{
    ui->preview->setText(item->whatsThis(0));
}

//--------------------------------------------------------
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
//--------------------------------------------------------


void Widget::on_archiveButton_clicked()
{
    // Отримуємо номер виділеного рядка ui->notesTree->currentIndex().row()
    // Вирізаємо takeTopLevelItem() та додаємо addTopLevelItem виділений рядок до архіву
   ui->archiveNotesTree->addTopLevelItem( ui->notesTree->takeTopLevelItem(ui->notesTree->currentIndex().row()));
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
            delete ui->archiveNotesTree->currentItem();
        }
    }
    else
    {
    qDebug()<<"Wasn't deleted";
    }
}

void Widget::on_unArchiveButton_clicked()
{
   // Отримуємо номер виділеного рядка ui->archiveNotesTree->currentIndex().row()
   // Вирізаємо takeTopLevelItem() та повертаємо addTopLevelItem виділений рядок нотаток
     ui->notesTree->addTopLevelItem( ui->archiveNotesTree->takeTopLevelItem( ui->archiveNotesTree->currentIndex().row() ) );

  // ui->notesTree->insertTopLevelItem(0,ui->archiveNotesTree->currentItem());
  // ui->notesTree->addTopLevelItem(ui->archiveNotesTree->currentItem());
    qDebug() << "beep Disarchive";
}

void Widget::on_searchLine_textChanged(const QString &arg1)
{
    QRegularExpression regExp(arg1, QRegularExpression::CaseInsensitiveOption);

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


void Widget::on_notesTree_clicked(const QModelIndex &index)
{

    qDebug()<<"notesTree_clicked index: "<<index;
}



void Widget::on_pushButton_clicked()
{

}


void Widget::on_pushButton_2_clicked()
{
    ui->colors->setEnabled(true);
    ui->colors->show();
}


void Widget::on_cViol_clicked()
{
    ui->notesTree->currentItem()->setBackgroundColor(0,Qt::magenta);
        ui->notesTree->currentItem()->setBackgroundColor(1,Qt::magenta);
            ui->notesTree->currentItem()->setBackgroundColor(2,Qt::magenta);
}


void Widget::on_cYellow_clicked()
{
    ui->notesTree->currentItem()->setBackgroundColor(0,Qt::yellow);
        ui->notesTree->currentItem()->setBackgroundColor(1,Qt::yellow);
            ui->notesTree->currentItem()->setBackgroundColor(2,Qt::yellow);
}


void Widget::on_cBrown_clicked()
{
    ui->notesTree->currentItem()->setBackgroundColor(0,Qt::darkRed);
        ui->notesTree->currentItem()->setBackgroundColor(1,Qt::darkRed);
            ui->notesTree->currentItem()->setBackgroundColor(2,Qt::darkRed);
}


void Widget::on_cBlue_clicked()
{
    ui->notesTree->currentItem()->setBackgroundColor(0,Qt::blue);
        ui->notesTree->currentItem()->setBackgroundColor(1,Qt::blue);
            ui->notesTree->currentItem()->setBackgroundColor(2,Qt::blue);
}


void Widget::on_cGreen_clicked()
{
    ui->notesTree->currentItem()->setBackgroundColor(0,Qt::green);
        ui->notesTree->currentItem()->setBackgroundColor(1,Qt::green);
            ui->notesTree->currentItem()->setBackgroundColor(2,Qt::green);
}


void Widget::on_cRed_clicked()
{
    ui->notesTree->currentItem()->setBackgroundColor(0,Qt::red);
        ui->notesTree->currentItem()->setBackgroundColor(1,Qt::red);
            ui->notesTree->currentItem()->setBackgroundColor(2,Qt::red);
}


void Widget::on_cGray_clicked()
{
    ui->notesTree->currentItem()->setBackgroundColor(0,Qt::gray);
        ui->notesTree->currentItem()->setBackgroundColor(1,Qt::gray);
            ui->notesTree->currentItem()->setBackgroundColor(2,Qt::gray);
}


void Widget::on_cWhite_clicked()
{
    ui->notesTree->currentItem()->setBackgroundColor(0,Qt::white);
        ui->notesTree->currentItem()->setBackgroundColor(1,Qt::white);
            ui->notesTree->currentItem()->setBackgroundColor(2,Qt::white);
}


void Widget::on_colors_tabCloseRequested(int index)
{
    ui->colors->setEnabled(false);
    ui->colors->hide();
}


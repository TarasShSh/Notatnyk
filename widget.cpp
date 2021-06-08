#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QtCore>
#include <QAction>
#include "QKeyEvent"
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
void Widget::keyPressEvent(QKeyEvent *event)
{
    if( event->key() ==Qt::Key_N )
    {
        on_createNoteButton_clicked();
    }
}
void Widget::createShortcutNote(Note *n)
{
    n->date = n->getDate();
    n->group = n->getGroup();
    n->setGroup(n->groupNames[0]);

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
    qDebug() << "Subnote has been created"<< noteNumber << n <<"Time:"<< n->getDate();

    n->shcSetDate( n->getDate());
    n->shcSetTitle(n->getTitle());
    n->shcSetGroup(n->groupNames[0]);
    n->shc->setData(0, 1, noteNumber);
      n->show();

    ui->notesTree->currentItem()->addChild(n->shc);
}

void Widget::on_notesTree_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    notes[item->data(0,1).toInt()]->show();
    item->setStatusTip(1, notes[0]->getDate());
    if(ui->recentNotes->topLevelItemCount() >= 3){
        delete ui->recentNotes->topLevelItem(3);
    }
    ui->recentNotes->topLevelItem(0)->setText(0,item->text(0)); // Встановлюємо заголовок,
    ui->recentNotes->topLevelItem(0)->setText(2,item->text(2)); // групу,
    ui->recentNotes->topLevelItem(0)->setText(1,notes[0]->getDate());// дату
    ui->recentNotes->topLevelItem(0)->setData(0,1,item->data(0,1).toInt()); // та номер нотатки
}

void Widget::on_recentNotes_itemPressed(QTreeWidgetItem *item, int column)
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

void Widget::on_notesTree_itemClicked(QTreeWidgetItem *item, int column) // нічого не залежить від колонки по якій натиснуто
{
    ui->preview->setText(item->whatsThis(0));
}
void Widget::on_archiveNotesTree_itemClicked(QTreeWidgetItem *item, int column)
{
    ui->preview->setText(item->whatsThis(0));
}


//--------------------------------------------------------
void Widget::on_filteredButton_clicked()
{
    if(       ui->noneCheckBox->isChecked()
            &&ui->selfCheckBox->isChecked()
            &&ui->workCheckBox->isChecked()
            &&ui->studyCheckBox->isChecked()
            &&ui->todoCheckBox->isChecked())
        for (int var = 0; var < ui->notesTree->topLevelItemCount(); ++var) {
        ui->notesTree->topLevelItem(var)->setHidden(false);
        for (int i = 0; i < ui->notesTree->topLevelItem(var)->childCount(); ++i) {
            ui->notesTree->topLevelItem(var)->child(i)->setHidden(false);
        }
        }
    else
    {
        for (int var = 0; var < ui->notesTree->topLevelItemCount(); ++var)
        {
        ui->notesTree->topLevelItem(var)->setHidden(true);
            for (int i = 0; i < ui->notesTree->topLevelItem(var)->childCount(); ++i)
            {
            ui->notesTree->topLevelItem(var)->child(i)->setHidden(true);
            }
        }
    QString groups[5] = {"Ніяка","Персональна","Робоча","Навчальна","ToDo"};

    if(ui->noneCheckBox->isChecked())
    {
        filterNShow(2, groups[0]);
    }
    if(ui->selfCheckBox->isChecked())
    {
        filterNShow(2, groups[1]);
    }

    if(ui->workCheckBox->isChecked())
    {
        filterNShow(2, groups[2]);
    }
    if(ui->studyCheckBox->isChecked())
    {
        filterNShow(2, groups[3]);
    }
    if(ui->todoCheckBox->isChecked())
    {
        filterNShow(2, groups[4]);
    }
   // ui->foundedNumber->setText(QString("%1").arg(count));
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
            // Видалення елементу зі списку

            delete ui->notesTree->currentItem();

        }
        else if(ui->tabWidget->currentWidget() == ui->archiveTab)
        {
            // Видалення елементу з архівного списку
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
    ui->foundedNumber->setText(QString("%1").arg(search(0, arg1)));
}

int Widget::search(int column, QString regExp)
{
    int times = 0;
    for (int father = 0; father < (ui->notesTree->topLevelItemCount()); ++father)
    {
        qDebug() << "Father count = " << father;
    for (int child = 0; child < (ui->notesTree->topLevelItem(father)->childCount());)
        {
                qDebug() << "Child count = " << child;
                        if(
                           ui->notesTree->topLevelItem(father)->child(child)->text(column).contains(regExp))
                {
                    qDebug() << "contain ";
                    ui->notesTree->topLevelItem(father)->child(child)->setHidden(false);
                    ++child;
                    ++times;
                }
                else
                {
                    qDebug() << "!contain ";
                    ui->notesTree->topLevelItem(father)->child(child)->setHidden(true);
                    ++child;
                }
        }
    }
    return times;
}
void Widget::filterNShow(int column, QString regExp)
{
    for (int father = 0; father < (ui->notesTree->topLevelItemCount()); ++father)
    {
        qDebug() << "Father count = " << father;
        if( ui->notesTree->topLevelItem(father)->text(column).contains(regExp))
        {
            ui->notesTree->topLevelItem(father)->setHidden(false);
        for (int child = 0; child < (ui->notesTree->topLevelItem(father)->childCount());++child)
        {
                qDebug() << "Child count = " << child;
                if( ui->notesTree->topLevelItem(father)->child(child)->text(column).contains(regExp))
                {
                    qDebug() << "contain ";
                    ui->notesTree->topLevelItem(father)->child(child)->setHidden(false);
                }
        }
    }
}
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

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("Нотатник");
    ui->scrollContents->setLayout(lay); // Додаємо все що діє у

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_createNoteButton_clicked()
{
    Note *n = new Note();
    qDebug() << "Note has been created" << n;
    n->show();
    createIconNote(n); // функція створення іконки нотатки
}
void Widget::createIconNote(IconNote *icon)
{

     /*3inARow =(
     if(pn_x == 280)
     {
         pn_x = 0;
         pn_y += 40;
     }
     else if(pn_x >= 0)
     {
         pn_x += 140;
     }
     p->setGeometry(pn_x, pn_y, 140, 40);
     */

     icon->dateL->setText(icon->getDate());
     icon->groupL->setText(icon->group);

     lay->addWidget(icon->dateL);         // Додаємо дату,
     lay->addWidget(icon->groupL);         // групу та
     lay->addWidget(icon->iN); // іконку до області прокручування
     ui->scrollArea->setWidgetResizable(true);
     icon->dateL->show();
     icon->groupL->show();
     icon->iN->show();
     /* Реалізація списком, якщо не вийде сортувати слої(спочатку створи QListWidget у widget.ui)
     QListWidgetItem *boob = new QListWidgetItem;
     boob->setText(icon->getTitle());
     ui->listWidget->addItem(boob);
     ui->listWidget->addItem(icon->getTitle());
     */
     // Варіанти отримання інформації
    // qDebug() << icon->getGroup(); // працює
    // qDebug()<<lay[1].property("group"); // крашить крашить крашить

}
void Widget::openNote()
{

}


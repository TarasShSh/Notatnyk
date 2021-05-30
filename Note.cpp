#include "Note.h"
#include "ui_Note.h"

Note::Note(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Note)
{
    ui->setupUi(this);
    ui->tabWidget->setEnabled(false);
    ui->tabWidget->hide();
}

Note::~Note()
{
    delete ui;
}

void Note::on_back_clicked()
{
    qDebug() << "back";
    groupL->setText(getGroup());
   this -> hide();

}


void Note::on_title_textChanged()
{
    iN->setText(ui->title->toPlainText());
}

void Note::on_toolButton_pressed()
{
    ui->tabWidget->setEnabled(true);
    ui->tabWidget->show();
}


void Note::on_tabWidget_tabCloseRequested(int index) // Не використовуватимемо більше однієї вкладки, тому index не використано
{
    ui->tabWidget->setEnabled(false);
    ui->tabWidget->hide();
}


void Note::on_todoButton_toggled(bool checked)
{
    if (checked) {
    setGroup("todo");

    qDebug() << getGroup();
    }
}
void Note::on_selfButton_toggled(bool checked)
{
    if (checked) {
    setGroup("self");
    }
}
void Note::on_studyButton_toggled(bool checked)
{
    if (checked) {
    setGroup("study");
    }
}
void Note::on_workButton_toggled(bool checked)
{
    if (checked) {
    setGroup("work");
    }
}


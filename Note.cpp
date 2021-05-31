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
QString Note::getDate()
{
    date = QDateTime::currentDateTime().toString();
    return date;
}

void Note::on_backButton_clicked()
{
    qDebug() << "back";

    if(getGroup()=="")
     {
        setGroup("Без групи");
     }
   close();
}

void Note::on_title_textChanged() // збереження заголовку
{
    setTitle(ui->title->toPlainText());
    sc->setText(getTitle());
}
void Note::on_NoteText_textChanged()// збереження тексту
{
   sc->setWhatsThis(ui->NoteText->toPlainText());
}

void Note::on_tabButton_clicked()
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
    if (checked)
    {
    setGroup("todo");

    // /img/todo.png
    iconGroupName.insert(5,getGroup());
    sc->setIcon(QIcon (iconGroupName));
    qDebug()<<iconGroupName;
    sc->setToolTip(getGroup());
    sc->toolTip();
    }
}

void Note::on_selfButton_toggled(bool checked)
{
    if (checked)
    {
    setGroup("self");
    sc->setStatusTip(getGroup());
    }
}

void Note::on_studyButton_toggled(bool checked)
{
    if (checked)
    {
    setGroup("study");
    sc->setStatusTip(getGroup());
    }
}

void Note::on_workButton_toggled(bool checked)
{
    if (checked)
    {
    setGroup("work");
    sc->setStatusTip(getGroup());
    qDebug()<<sc->statusTip();
    }
}

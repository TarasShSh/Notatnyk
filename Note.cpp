#include "Note.h"
#include "ui_Note.h"
#include <QFileDialog>
#include <QPixmap>

Note::Note(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Note)
{
    ui->setupUi(this);
    ui->tabWidget->setEnabled(false);
    ui->tabWidget->hide();
    /*
    ui->tabWidget_2->setEnabled(false);
    ui->tabWidget_2->hide();


    ui->tabWidget_3->hide();
   // ui->tab_4->hide();

    ui->toolButton->hide();
    ui->toolButton_2->hide();
    ui->toolButton_3->hide();
    ui->toolButton_4->hide();
    ui->toolButton_5->hide();
    ui->toolButton_6->hide();

    ui->tableView->hide();
    ui->label_2->hide();
    ui->line_2->hide();
    */
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
<<<<<<< HEAD

        sc->setToolTip(getGroup());
=======
    sc->setToolTip(getGroup());
    sc->toolTip();
>>>>>>> 8ba590de3f186b531df7cded81f25f33d15916ba
    }
}

void Note::on_selfButton_toggled(bool checked)
{
    if (checked)
    {
    setGroup("self");
    sc->setStatusTip(getGroup());

        sc->setToolTip(getGroup());
    }
}

void Note::on_studyButton_toggled(bool checked)
{
    if (checked)
    {
    setGroup("study");
    sc->setStatusTip(getGroup());

    //sc->setToolTip(getGroup());
    }
}

void Note::on_workButton_toggled(bool checked)
{
    if (checked)
    {
    setGroup("work");
    sc->setStatusTip(getGroup());
    qDebug()<<sc->statusTip();

        sc->setToolTip(getGroup());
    }
}


void Note::on_tabButton_2_clicked()
{
    //ui->tabWidget_2->setEnabled(true);
    //ui->tabWidget_2->show();
}


void Note::on_tabWidget_2_tabCloseRequested(int index)
{
   // ui->tabWidget_2->setEnabled(false);
   // ui->tabWidget_2->hide();
}


void Note::on_picture_toggled(bool checked)
{
    if (checked)
    {

    QString filename = QFileDialog::getOpenFileName(this, tr("Choose"),"",tr("Images(*.png *.jpg *.jpeg *.bmp *.gif)"));
   if(QString::compare(filename, QString())!=0)
   {
       QImage image;
       bool valid = image.load(filename);

       if(valid)
       {
           image = image.scaledToWidth(ui->lbl_image->width(), Qt::SmoothTransformation);
           ui->lbl_image->setPixmap(QPixmap::fromImage(image));
           // ui->tabWidget_3->show();
       }
       else
       {
           //Error
       }

   }
   //ui->picture->setEnabled(false);
    }
}


void Note::on_audio_toggled(bool checked)
{
    if (checked)
    {







/*
        ui->toolButton->show();
        ui->toolButton_2->show();
        ui->toolButton_3->show();
        ui->toolButton_4->show();
        ui->toolButton_5->show();
        ui->toolButton_6->show();

        ui->tableView->show();
        ui->label_2->show();
        ui->line_2->show();
        // ui->audio->setEnabled(false);
        */
    }
}


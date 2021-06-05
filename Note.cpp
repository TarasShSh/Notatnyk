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
     ui->fon_widget->setEnabled(false);

   /*
    ui->imgTabWidget->hide();
    ui->btn_stop->hide();
    ui->deleteMusicButton->hide();
    ui->btn_pause->hide();
    ui->btn_play->hide();
    ui->btn_next->hide();
    ui->btn_previous->hide();
    ui->vol->hide();
    ui->lon->hide();

    ui->playlistView->hide();
    ui->playingName->hide();
    ui->playingText->hide();
    ui->volumeText->hide();
    ui->line_2->hide();*/

      ui->fon1->hide();
       ui->fon2->hide();
        ui->fon3->hide();
         ui->fon4->hide();
          ui->fon5->hide();
           ui->fon6->hide();
            ui->fon7->hide();
            ui->fon_imp->hide();

      ui->imgImportTabWidget->hide();
      ui->fon_widget->hide();
       ui->tabWidget->hide();
       ui->sizeWidget->hide();



       m_playListModel = new QStandardItemModel(this);
       ui->playlistView->setModel(m_playListModel);
       m_playListModel->setHorizontalHeaderLabels(QStringList()  << tr("Audio Track") << tr("File Path"));
       ui->playlistView->hideColumn(1);
       ui->playlistView->verticalHeader()->setVisible(false);
       ui->playlistView->setSelectionBehavior(QAbstractItemView::SelectRows);
       ui->playlistView->setSelectionMode(QAbstractItemView::SingleSelection);
       ui->playlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);
       ui->playlistView->horizontalHeader()->setStretchLastSection(true);

       m_player = new QMediaPlayer(this);
       m_playlist = new QMediaPlaylist(m_player);
       m_player->setPlaylist(m_playlist);
       m_player->setVolume(70);
       m_playlist->setPlaybackMode(QMediaPlaylist::Loop);

       connect(ui->btn_previous, &QToolButton::clicked, m_playlist, &QMediaPlaylist::previous);
       connect(ui->btn_next, &QToolButton::clicked, m_playlist, &QMediaPlaylist::next);

       connect(ui->btn_play, &QToolButton::clicked, m_player, &QMediaPlayer::play);
       connect(ui->btn_pause, &QToolButton::clicked, m_player, &QMediaPlayer::pause);
       connect(ui->btn_stop, &QToolButton::clicked, m_player, &QMediaPlayer::stop);
       connect(ui->backButton, &QToolButton::clicked, m_player, &QMediaPlayer::stop);//щоб виключалась, коли ми закриваємо нотатку

       connect(ui->playlistView, &QTableView::doubleClicked, [this](const QModelIndex &index){m_playlist->setCurrentIndex(index.row());});
       connect(m_playlist, &QMediaPlaylist::currentIndexChanged, [this](int index){ ui->playingName->setText(m_playListModel->data(m_playListModel->index(index, 0)).toString());});

       connect(ui->lon, &QSlider::sliderMoved, m_player, &QMediaPlayer::setPosition);
       connect(m_player, &QMediaPlayer::durationChanged,ui->lon,&QSlider::setMaximum);
       connect(m_player, &QMediaPlayer::positionChanged,ui->lon,&QSlider::setValue);

}

Note::~Note()
{
    delete ui;
    delete m_playListModel;
        delete m_playlist;
        delete m_player;
}


QString Note::getDate()
{
    date = QDateTime::currentDateTime().toString();
    return date;
}

void Note::on_backButton_clicked()
{
    &QMediaPlayer::stop;
   close();
}

void Note::on_title_textChanged() // збереження заголовку
{
    setTitle(ui->title->toPlainText());
    sc->setText(getTitle());

    shc->setText(0, getTitle());
}
void Note::on_NoteText_textChanged()// збереження тексту
{
   sc->setWhatsThis(ui->NoteText->toPlainText());
   shc->setWhatsThis(0, ui->NoteText->toPlainText());
}

void Note::on_tabButton_clicked()
{
    ui->tabWidget->setEnabled(true);
    ui->tabWidget->show();
}

void Note::on_tabWidget_tabCloseRequested(int index) // Не використовуватимемо більше однієї вкладки, тому index не використано
{
   // ui->tabWidget->setEnabled(false);
    ui->tabWidget->hide();
}

void Note::on_noneButton_toggled(bool checked)
{
    if (checked)
    {
    setGroup(groupNames[0]);
    shc->setText(2, getGroup());

    ui->tabWidget->hide();
    ui->groupName->setText(getGroup());
    }
}
void Note::on_selfButton_toggled(bool checked)
{
    if (checked)
    {
    setGroup(groupNames[1]);
    sc->setStatusTip(getGroup());
    shc->setText(2, getGroup());

    ui->tabWidget->hide();
        ui->groupName->setText(getGroup());
    }
}
void Note::on_workButton_toggled(bool checked)
{
    if (checked)
    {
    setGroup(groupNames[2]);
    sc->setStatusTip(getGroup());
    shc->setText(2, getGroup());

    ui->tabWidget->hide();
        ui->groupName->setText(getGroup());
    }
}

void Note::on_studyButton_toggled(bool checked)
{
    if (checked)
    {
    setGroup(groupNames[3]);
    sc->setStatusTip(getGroup());
    shc->setText(2, getGroup());
    ui->tabWidget->hide();
        ui->groupName->setText(getGroup());
    }
}



void Note::on_todoButton_toggled(bool checked)
{
    if (checked)
    {
    setGroup(groupNames[4]);
    sc->setStatusTip(getGroup());
    shc->setText(2, getGroup());

    ui->tabWidget->hide();
        ui->groupName->setText(getGroup());
    }
}


/*
void Note::on_toolButton_2_clicked()
{
    QListWidgetItem* it = ui->playlistView->takeItem(currentRow());
     delete it;

    myListUpdate();
}

*/


void Note::on_pushButton_2_clicked()
{
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Open files"), QString(), tr("Audio Files (*.mp3)"));
       foreach (QString filePath, files)
       {
           QList<QStandardItem *> items;
           items.append(new QStandardItem(QDir(filePath).dirName()));
           items.append(new QStandardItem(filePath));
           m_playListModel->appendRow(items);
           m_playlist->addMedia(QUrl(filePath));
       }
    ui->btn_stop->show();
    ui->deleteMusicButton->show();
    ui->btn_pause->show();
    ui->btn_play->show();
    ui->btn_next->show();
    ui->btn_previous->show();

    ui->playlistView->show();
    ui->playingText->show();
    ui->playingName->show();
    ui->line_2->show();
    ui->vol->show();
    ui->lon->show();
}


void Note::on_vol_sliderMoved(int position)
{
    m_player->setVolume(position);
}

//----------------------------------------------ЗОБРАЖЕННЯ------------------------------------------------------------------------------------------
void Note::on_pushButton_clicked()
{
    ui->imgImportTabWidget->setEnabled(true);
    ui->imgImportTabWidget->show();
}

void Note::on_imgImport1_toggled(bool checked)
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
                image = image.scaledToWidth(ui->imgL1->width(), Qt::SmoothTransformation);
                ui->imgL1->setPixmap(QPixmap::fromImage(image));
                //ui->imgTabWidget->show();
               ui->imgImport1->setEnabled(false);
            }
            else
            {
                //Error
            }

        }
     }
}


void Note::on_imgImport2_toggled(bool checked)
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
               image = image.scaledToWidth(ui->imgL2->width(), Qt::SmoothTransformation);
               ui->imgL2->setPixmap(QPixmap::fromImage(image));
               //ui->imgTabWidget->show();
               ui->imgImport2->setEnabled(false);

           }
           else
           {
               //Error
           }

       }
    }
}





void Note::on_imgImport3_toggled(bool checked)
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
               image = image.scaledToWidth(ui->imgL3->width(), Qt::SmoothTransformation);
               ui->imgL3->setPixmap(QPixmap::fromImage(image));
               //ui->imgTabWidget->show();
               ui->imgImport3->setEnabled(false);

           }
           else
           {
               //Error
           }

       }
    }
}


void Note::on_imgImport4_toggled(bool checked)
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
               image = image.scaledToWidth(ui->imgL4->width(), Qt::SmoothTransformation);
               ui->imgL4->setPixmap(QPixmap::fromImage(image));
               //ui->imgTabWidget->show();
               ui->imgImport4->setEnabled(false);

           }
           else
           {
               //Error
           }

       }
    }
}


void Note::on_imgImport5_toggled(bool checked)
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
               image = image.scaledToWidth(ui->imgL5->width(), Qt::SmoothTransformation);
               ui->imgL5->setPixmap(QPixmap::fromImage(image));
               //ui->imgTabWidget->show();
               ui->imgImport5->setEnabled(false);

           }
           else
           {
               //Error
           }

       }
    }
}


void Note::on_imgImport6_toggled(bool checked)
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
               image = image.scaledToWidth(ui->imgL6->width(), Qt::SmoothTransformation);
               ui->imgL6->setPixmap(QPixmap::fromImage(image));
               //ui->imgTabWidget->show();
               ui->imgImport6->setEnabled(false);

           }
           else
           {
               //Error
           }

       }
    }
}


void Note::on_imgImport7_toggled(bool checked)
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
               image = image.scaledToWidth(ui->imgL7->width(), Qt::SmoothTransformation);
               ui->imgL7->setPixmap(QPixmap::fromImage(image));
               //ui->imgTabWidget->show();
               ui->imgImport7->setEnabled(false);

           }
           else
           {
               //Error
           }

       }
    }
}


void Note::on_imgImport8_toggled(bool checked)
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
               image = image.scaledToWidth(ui->imgL8->width(), Qt::SmoothTransformation);
               ui->imgL8->setPixmap(QPixmap::fromImage(image));
               //ui->imgTabWidget->show();
               ui->imgImport8->setEnabled(false);

           }
           else
           {
               //Error
           }

       }
    }
}


void Note::on_imgImportTabWidget_tabCloseRequested(int index)
{
    ui->imgImportTabWidget->setEnabled(false);
    ui->imgImportTabWidget->hide();
}

void Note::on_deleteImgButton_clicked()
{
    ui->imgL1->clear();
    ui->imgImport1->setEnabled(true);
}


void Note::on_deleteImgButton_2_clicked()
{
    ui->imgL2->clear();
    ui->imgImport2->setEnabled(true);
}


void Note::on_deleteImgButton_3_clicked()
{
    ui->imgL3->clear();
    ui->imgImport3->setEnabled(true);
}


void Note::on_deleteImgButton_4_clicked()
{
    ui->imgL4->clear();
    ui->imgImport4->setEnabled(true);
}


void Note::on_deleteImgButton_5_clicked()
{
    ui->imgL5->clear();
    ui->imgImport5->setEnabled(true);
}


void Note::on_deleteImgButton_6_clicked()
{
    ui->imgL6->clear();
    ui->imgImport6->setEnabled(true);
}


void Note::on_deleteImgButton_7_clicked()
{
    ui->imgL7->clear();
    ui->imgImport7->setEnabled(true);
}


void Note::on_deleteImgButton_8_clicked()
{
    ui->imgL8->clear();
    ui->imgImport8->setEnabled(true);
}


void Note::on_pushButton_3_clicked()
{
    ui->fon_widget->setEnabled(true);
    ui->fon_widget->show();
}


void Note::on_fon_widget_tabCloseRequested(int index)
{
    ui->fon_widget->hide();
}


void Note::on_f1_toggled(bool checked)
{
    if(checked)
    {
    ui->fon1->show();
     ui->fon2->hide();
      ui->fon3->hide();
       ui->fon4->hide();
        ui->fon5->hide();
         ui->fon6->hide();
          ui->fon7->hide();
          ui->fon_imp->hide();
    }
}


void Note::on_f2_toggled(bool checked)
{
     if(checked)
     {
    ui->fon1->hide();
     ui->fon2->show();
      ui->fon3->hide();
       ui->fon4->hide();
        ui->fon5->hide();
         ui->fon6->hide();
          ui->fon7->hide();
          ui->fon_imp->hide();
     }
}


void Note::on_f3_toggled(bool checked)
{
     if(checked)
     {
    ui->fon1->hide();
     ui->fon2->hide();
      ui->fon3->show();
       ui->fon4->hide();
        ui->fon5->hide();
         ui->fon6->hide();
          ui->fon7->hide();
          ui->fon_imp->hide();
     }
}


void Note::on_f4_toggled(bool checked)
{
     if(checked)
     {
    ui->fon1->hide();
     ui->fon2->hide();
      ui->fon3->hide();
       ui->fon4->show();
        ui->fon5->hide();
         ui->fon6->hide();
          ui->fon7->hide();
          ui->fon_imp->hide();
     }
}


void Note::on_f5_toggled(bool checked)
{
     if(checked)
     {
    ui->fon1->hide();
     ui->fon2->hide();
      ui->fon3->hide();
       ui->fon4->hide();
        ui->fon5->show();
         ui->fon6->hide();
          ui->fon7->hide();
          ui->fon_imp->hide();
     }
}


void Note::on_f6_toggled(bool checked)
{
     if(checked)
     {
    ui->fon1->hide();
     ui->fon2->hide();
      ui->fon3->hide();
       ui->fon4->hide();
        ui->fon5->hide();
         ui->fon6->show();
          ui->fon7->hide();
          ui->fon_imp->hide();
     }
}


void Note::on_fimport_toggled(bool checked)
{
     if(checked)
     {
         QString filename = QFileDialog::getOpenFileName(this, tr("Choose"),"",tr("Images(*.png *.jpg *.jpeg *.bmp *.gif)"));
        if(QString::compare(filename, QString())!=0)
        {
            QImage image;
            bool valid = image.load(filename);

            if(valid)
            {
                //image = image.scaledToWidth(ui->fon_import->width(), Qt::SmoothTransformation);
                ui->fon_imp->setPixmap(QPixmap::fromImage(image));

            }
            else
            {
                //Error
            }

        }
    ui->fon1->hide();
     ui->fon2->hide();
      ui->fon3->hide();
       ui->fon4->hide();
        ui->fon5->hide();
         ui->fon6->hide();
          ui->fon7->hide();
          ui->fon_imp->show();
     }
}


void Note::on_fbez_toggled(bool checked)
{
     if(checked)
     {
    ui->fon1->hide();
     ui->fon2->hide();
      ui->fon3->hide();
       ui->fon4->hide();
        ui->fon5->hide();
         ui->fon6->hide();
           ui->fon7->hide();
          ui->fon_imp->hide();
     }
}


void Note::on_f7_toggled(bool checked)
{
    if(checked)
    {
   ui->fon1->hide();
    ui->fon2->hide();
     ui->fon3->hide();
      ui->fon4->hide();
       ui->fon5->hide();
        ui->fon6->hide();
          ui->fon7->show();
         ui->fon_imp->hide();
    }
}


void Note::on_bRed_clicked()
{
    ui->NoteText->setTextColor(Qt::red);
     ui->title->setTextColor(Qt::red);
}


void Note::on_bBlack_clicked()
{
     ui->NoteText->setTextColor(Qt::black);
       ui->title->setTextColor(Qt::black);
}


void Note::on_bWhite_clicked()
{
     ui->NoteText->setTextColor(Qt::white);
        ui->title->setTextColor(Qt::white);
}


void Note::on_bGreen_clicked()
{
     ui->NoteText->setTextColor(Qt::green);
      ui->title->setTextColor(Qt::green);
}


void Note::on_bGray_clicked()
{
     ui->NoteText->setTextColor(Qt::gray);
      ui->title->setTextColor(Qt::gray);
}


void Note::on_bBlue_clicked()
{
     ui->NoteText->setTextColor(Qt::blue);
        ui->title->setTextColor(Qt::blue);
}


void Note::on_bYellow_clicked()
{
     ui->NoteText->setTextColor(Qt::yellow);
      ui->title->setTextColor(Qt::yellow);
}


void Note::on_bviol_clicked()
{
     ui->NoteText->setTextColor(Qt::darkMagenta);
      ui->title->setTextColor(Qt::darkMagenta);
}


void Note::on_bBrown_clicked()
{
     ui->NoteText->setTextColor(Qt::darkRed);
         ui->title->setTextColor(Qt::darkRed);
}


void Note::on_Kp_clicked()
{
    ui->NoteText->setFontItalic(true);
    ui->title->setFontItalic(true);
}


void Note::on_Kn_clicked()
{
    ui->NoteText->setFontItalic(false);
     ui->title->setFontItalic(false);
}


void Note::on_Bp_clicked()
{
  ui->NoteText->setFontWeight(200);
  ui->title->setFontWeight(200);
}


void Note::on_Bn_clicked()
{
    ui->NoteText->setFontWeight(0);
     ui->title->setFontWeight(0);
}


void Note::on_Cp_clicked()
{
     ui->NoteText->setFontUnderline(true);
     ui->title->setFontUnderline(true);
}


void Note::on_Cn_clicked()
{

     ui->NoteText->setFontUnderline(false);
       ui->title->setFontUnderline(false);
}


void Note::on_pushButton_4_clicked()
{
    ui->sizeWidget->setEnabled(true);
    ui->sizeWidget->show();
}


void Note::on_sizeWidget_tabCloseRequested(int index)
{
    ui->sizeWidget->hide();
}




void Note::on_s10_clicked()
{
    ui->NoteText->setFontPointSize(10);
}


void Note::on_s12_clicked()
{
       ui->NoteText->setFontPointSize(12);
}


void Note::on_s14_clicked()
{
       ui->NoteText->setFontPointSize(14);
}


void Note::on_s16_clicked()
{
       ui->NoteText->setFontPointSize(16);
}


void Note::on_s20_clicked()
{
       ui->NoteText->setFontPointSize(20);
}


void Note::on_s22_clicked()
{
       ui->NoteText->setFontPointSize(22);
}


void Note::on_s24_clicked()
{
       ui->NoteText->setFontPointSize(24);
}


void Note::on_s28_clicked()
{
       ui->NoteText->setFontPointSize(28);
}


void Note::on_s32_clicked()
{
       ui->NoteText->setFontPointSize(32);
}


void Note::on_s36_clicked()
{
       ui->NoteText->setFontPointSize(36);
}


void Note::on_s40_clicked()
{
       ui->NoteText->setFontPointSize(40);
}


void Note::on_s48_clicked()
{
       ui->NoteText->setFontPointSize(48);
}


void Note::on_bviol_2_clicked()
{
    ui->NoteText->setTextBackgroundColor(Qt::magenta);
        ui->title->setTextBackgroundColor(Qt::magenta);
}


void Note::on_bRed_2_clicked()
{
    ui->NoteText->setTextBackgroundColor(Qt::red);
        ui->title->setTextBackgroundColor(Qt::red);
}


void Note::on_bYellow_2_clicked()
{
    ui->NoteText->setTextBackgroundColor(Qt::yellow);
        ui->title->setTextBackgroundColor(Qt::yellow);
}


void Note::on_bBrown_2_clicked()
{
    ui->NoteText->setTextBackgroundColor(Qt::darkRed);
        ui->title->setTextBackgroundColor(Qt::darkRed);
}


void Note::on_bBlue_2_clicked()
{
    ui->NoteText->setTextBackgroundColor(Qt::blue);
        ui->title->setTextBackgroundColor(Qt::blue);
}


void Note::on_bBlack_2_clicked()
{
    ui->NoteText->setTextBackgroundColor(Qt::black);
        ui->title->setTextBackgroundColor(Qt::black);
}


void Note::on_bGreen_2_clicked()
{
    ui->NoteText->setTextBackgroundColor(Qt::green);
        ui->title->setTextBackgroundColor(Qt::green);
}


void Note::on_bGray_2_clicked()
{
    ui->NoteText->setTextBackgroundColor(Qt::gray);
        ui->title->setTextBackgroundColor(Qt::gray);
}


void Note::on_bWhite_2_clicked()
{
    ui->NoteText->setTextBackgroundColor(Qt::white);
        ui->title->setTextBackgroundColor(Qt::white);
}


void Note::on_pushButton_6_clicked()
{

}


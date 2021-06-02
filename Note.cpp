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
    ui->tabWidget_3->hide();

    ui->btn_stop->hide();
    ui->toolButton_2->hide();
    ui->btn_pause->hide();
    ui->btn_play->hide();
    ui->btn_next->hide();
    ui->btn_previous->hide();

    ui->playlistView->hide();
    ui->label_2->hide();
     ui->label_4->hide();
    ui->line_2->hide();





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
       connect(m_playlist, &QMediaPlaylist::currentIndexChanged, [this](int index){ ui->label_2->setText(m_playListModel->data(m_playListModel->index(index, 0)).toString());});
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
    //qDebug() << "back";

    if(getGroup()=="")
     {
        setGroup(groupNames[0]);
     }
    &QMediaPlayer::stop;
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

void Note::on_noneButton_toggled(bool checked)
{
    if (checked)
    {
    setGroup(groupNames[0]);
    sc->setStatusTip(getGroup());

        sc->setToolTip(getGroup());
    }
}
void Note::on_selfButton_toggled(bool checked)
{
    if (checked)
    {
    setGroup(groupNames[1]);
    sc->setStatusTip(getGroup());

        sc->setToolTip(getGroup());
    }
}
void Note::on_workButton_toggled(bool checked)
{
    if (checked)
    {
    setGroup(groupNames[2]);
    sc->setStatusTip(getGroup());
   // qDebug()<<sc->statusTip();

        sc->setToolTip(getGroup());
    }
}

void Note::on_studyButton_toggled(bool checked)
{
    if (checked)
    {
    setGroup(groupNames[3]);
    sc->setStatusTip(getGroup());

    //sc->setToolTip(getGroup());
    }
}



void Note::on_todoButton_toggled(bool checked)
{
    if (checked)
    {
    setGroup(groupNames[4]);

    // /img/todo.png
    iconGroupName.insert(5,getGroup());
    sc->setIcon(QIcon (iconGroupName));
    //qDebug()<<iconGroupName;

        sc->setToolTip(getGroup());
    sc->setToolTip(getGroup());
    sc->toolTip();
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
void Note::on_pushButton_clicked()
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
           ui->tabWidget_3->show();
       }
       else
       {
           //Error
       }

   }
}


void Note::on_pushButton_2_clicked()
{
    // С помощью диалога выбора файлов делаем множественный выбор mp3 файлов
       QStringList files = QFileDialog::getOpenFileNames(this, tr("Open files"), QString(), tr("Audio Files (*.mp3)"));

       // Далее устанавливаем данные по именам и пути к файлам
       // в плейлист и таблицу отображающую плейлист
       foreach (QString filePath, files)
       {
           QList<QStandardItem *> items;
           items.append(new QStandardItem(QDir(filePath).dirName()));
           items.append(new QStandardItem(filePath));
           m_playListModel->appendRow(items);
           m_playlist->addMedia(QUrl(filePath));
       }
     ui->label_4->show();
    ui->btn_stop->show();
    ui->toolButton_2->show();
    ui->btn_pause->show();
    ui->btn_play->show();
    ui->btn_next->show();
    ui->btn_previous->show();

    ui->playlistView->show();
    ui->label_2->show();
    ui->line_2->show();
}


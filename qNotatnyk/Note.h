#ifndef NOTE_H
#define NOTE_H
#pragma once
#include <iostream>
#include <QDateTime>
#include "QSortFilterProxyModel"
#include "QListWidget"
#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QSlider>
#include <QProgressBar>


using namespace std;

namespace Ui
{
class Note;
}

class Note :public QWidget
{
    Q_OBJECT

public:
    explicit Note(QWidget *parent = nullptr);
    ~Note();
    //QTextEdit title; //можливо створюватимемо дизайн із нуля
    QListWidgetItem *sc = new QListWidgetItem();
    int id;
    QString
            iconGroupName = "/img/.png",
            title ="1",
            text,
            date,
            group;
    QVector<QString> groupNames {"none", "self", "work", "study", "todo"};
    QString getDate();
    QString getTitle(){return title;}
    void setTitle(QString t){title=t;};

    QString getGroup(){return group;}
    void setGroup(QString g){group = g;}

    QString getText(){ return text;};
    void setText(QString txt){ text = txt;}

    void scSetDate(QString date){sc->setStatusTip(date);}
    void scSetTitle(QString t){sc->setText(t);}
private slots:
    void on_backButton_clicked(); // повернення до головного вікна
    void on_title_textChanged();
    void on_tabWidget_tabCloseRequested(int index);
    void on_tabButton_clicked();
    void on_noneButton_toggled(bool checked);
    void on_selfButton_toggled(bool checked);
    void on_workButton_toggled(bool checked);
    void on_studyButton_toggled(bool checked);
    void on_todoButton_toggled(bool checked);


    void on_NoteText_textChanged();

    //void on_toolButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_z1_toggled(bool checked);

    void on_z2_toggled(bool checked);



    void on_z3_toggled(bool checked);

    void on_z4_toggled(bool checked);

    void on_z5_toggled(bool checked);

    void on_z6_toggled(bool checked);

    void on_z7_toggled(bool checked);

    void on_z8_toggled(bool checked);

    void on_tabw_tabCloseRequested(int index);

    void on_vol_sliderMoved(int position);

private:
    Ui::Note *ui;
       QStandardItemModel  *m_playListModel;
       QMediaPlayer *m_player;
       QMediaPlaylist *m_playlist;
};

#endif // NOTE_H

#ifndef NOTE_H
#define NOTE_H
#pragma once
#include <iostream>
#include <QDateTime>
#include "QSortFilterProxyModel"
#include "QListWidget"
#include <QWidget>
/*
#include <QMediaPlayer>
#include <QMediaPlaylist>
*/

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
    QString
            iconGroupName = "/img/.png",
            title ="1",
            text,
            date,
            group;

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
    void on_backButton_clicked();
    void on_title_textChanged();
    void on_tabWidget_tabCloseRequested(int index);
    void on_tabButton_clicked();

    void on_todoButton_toggled(bool checked);
    void on_selfButton_toggled(bool checked);
    void on_studyButton_toggled(bool checked);
    void on_workButton_toggled(bool checked);


    void on_NoteText_textChanged();

    void on_tabButton_2_clicked();
    void on_tabWidget_2_tabCloseRequested(int index);
    void on_picture_toggled(bool checked);

    void on_audio_toggled(bool checked);

private:
    Ui::Note *ui;
};

#endif // NOTE_H

#ifndef NOTE_H
#define NOTE_H
#pragma once
#include <iostream>
#include <QDateTime>
#include "QSortFilterProxyModel"
#include "QListWidget" //del
#include "QTreeWidget"
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
    QTreeWidgetItem *shc = new QTreeWidgetItem();
    int id;
    QVector<QString> groupNames {"Ніяка", "Персональна", "Робоча", "Навчальна", "ToDo"};
    QString
            title = "Без назви",
            text,
            date,
            group =groupNames[0];
    QString getDate();
    QString getTitle(){return title;}
    void setTitle(QString t){title=t;};

    QString getGroup(){return group;}
    void setGroup(QString g){group = g;}

    QString getText(){ return text;};
    void setText(QString txt){ text = txt;}

    void scSetDate(QString date){sc->setStatusTip(date);}
    void scSetTitle(QString t){sc->setText(t);}


    void shcSetTitle(QString t){shc->setText(0, t);}
    void shcSetDate(QString date){shc->setText(1,date);}
    void shcSetGroup(QString g){shc->setText(2, g);}
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
// IMAGES IMPORT BUTTONS
    void on_imgImport1_toggled(bool checked);
    void on_imgImport2_toggled(bool checked);
    void on_imgImport3_toggled(bool checked);
    void on_imgImport4_toggled(bool checked);
    void on_imgImport5_toggled(bool checked);
    void on_imgImport6_toggled(bool checked);
    void on_imgImport7_toggled(bool checked);
    void on_imgImport8_toggled(bool checked);
    void on_imgImportTabWidget_tabCloseRequested(int index);

    void on_vol_sliderMoved(int position);

private:
    Ui::Note *ui;
       QStandardItemModel  *m_playListModel;
       QMediaPlayer *m_player;
       QMediaPlaylist *m_playlist;
};

#endif // NOTE_H

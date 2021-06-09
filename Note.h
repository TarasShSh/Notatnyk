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

    QTreeWidgetItem *shc = new QTreeWidgetItem();
    int id;

    QVector<QString> groupNames {"Ніяка", "Персональна", "Робоча", "Навчальна", "ToDo"};
    QString
            title = "Без назви",
            text,
            date,
            group =groupNames[0];

    QString getDate() {return QDateTime::currentDateTime().toString();};
    void setDate(QString d) {date = d;}

    QString getTitle(){return title;}
    void setTitle(QString t){title=t;}

    QString getGroup(){return group;}
    void setGroup(QString g){group = g;}

    QString getText(){ return text;};
    void setText(QString txt){ text = txt;}

    void shcSetTitle(QString t){shc->setText(0, t);}
    void shcSetDate(QString date){shc->setText(1,date);}
    void shcSetGroup(QString g){shc->setText(2, g);}


private slots:
    void on_backButton_clicked(); // повернення до головного вікна
    void on_title_textChanged();
    void on_NoteText_textChanged();

    // CHOOSE GROUP BUTTONS
    void on_tabWidget_tabCloseRequested(int index);
    void on_tabButton_clicked();
    void on_noneButton_toggled(bool checked);
    void on_selfButton_toggled(bool checked);
    void on_workButton_toggled(bool checked);
    void on_studyButton_toggled(bool checked);
    void on_todoButton_toggled(bool checked);

    // AUDIO IMPORT BUTTONS
    void on_pushButton_2_clicked();
    void on_vol_sliderMoved(int position);
    void on_deleteMusicButton_clicked();

    // IMAGES IMPORT BUTTONS
    void on_pushButton_clicked();
    void on_imgImport1_toggled(bool checked);
    void on_imgImport2_toggled(bool checked);
    void on_imgImport3_toggled(bool checked);
    void on_imgImport4_toggled(bool checked);
    void on_imgImport5_toggled(bool checked);
    void on_imgImport6_toggled(bool checked);
    void on_imgImport7_toggled(bool checked);
    void on_imgImport8_toggled(bool checked);
    void on_imgImportTabWidget_tabCloseRequested(int index);

    // IMAGES DELETE BUTTONS
    void on_deleteImgButton_clicked();
    void on_deleteImgButton_2_clicked();
    void on_deleteImgButton_3_clicked();
    void on_deleteImgButton_4_clicked();
    void on_deleteImgButton_5_clicked();
    void on_deleteImgButton_6_clicked();
    void on_deleteImgButton_7_clicked();
    void on_deleteImgButton_8_clicked();

    // BACKGROUND CHANGE BUTTONS
    void on_pushButton_3_clicked();
    void on_fon_widget_tabCloseRequested(int index);
    void on_f1_toggled(bool checked);
    void on_f2_toggled(bool checked);
    void on_f3_toggled(bool checked);
    void on_f4_toggled(bool checked);
    void on_f5_toggled(bool checked);
    void on_f6_toggled(bool checked);
    void on_fimport_toggled(bool checked);
    void on_fbez_toggled(bool checked);
    void on_f7_toggled(bool checked);

    // TEXT COLOR CHANGE BUTTONS
    void on_bRed_clicked();
    void on_bBlack_clicked();
    void on_bWhite_clicked();
    void on_bGreen_clicked();
    void on_bGray_clicked();
    void on_bBlue_clicked();
    void on_bYellow_clicked();
    void on_bviol_clicked();
    void on_bBrown_clicked();

    // TEXT STYLE CHANGE BUTTONS
    void on_Kp_clicked();
    void on_Kn_clicked();
    void on_Bp_clicked();
    void on_Bn_clicked();
    void on_Cp_clicked();
    void on_Cn_clicked();

    // TEXT SIZE CHANGE BUTTONS
    void on_pushButton_4_clicked();
    void on_sizeWidget_tabCloseRequested(int index);
    void on_s10_clicked();
    void on_s12_clicked();
    void on_s14_clicked();
    void on_s16_clicked();
    void on_s20_clicked();
    void on_s22_clicked();
    void on_s24_clicked();
    void on_s28_clicked();
    void on_s32_clicked();
    void on_s36_clicked();
    void on_s40_clicked();
    void on_s48_clicked();

    // TEXT BACKGROUND COLOR CHANGE BUTTONS
    void on_bviol_2_clicked();
    void on_bRed_2_clicked();
    void on_bYellow_2_clicked();
    void on_bBrown_2_clicked();
    void on_bBlue_2_clicked();
    void on_bBlack_2_clicked();
    void on_bGreen_2_clicked();
    void on_bGray_2_clicked();
    void on_bWhite_2_clicked();

    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();

private:
    Ui::Note *ui;

       QStandardItemModel  *m_playListModel;
       QMediaPlayer *m_player;
       QMediaPlaylist *m_playlist;
};

#endif // NOTE_H

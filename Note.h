#ifndef NOTE_H
#define NOTE_H
#pragma once
#include "IconNote.h"
#include <iostream>

#include <QWidget>
#include <QTextBrowser>

using namespace std;

namespace Ui
{
class Note;
}

class Note :public QWidget, public IconNote
{
    Q_OBJECT

public:
    explicit Note(QWidget *parent = nullptr);
    ~Note();
    //QTextEdit title; //можливо створюватимемо дизайн із нуля

    QString text;
    QString getText(){ return text;};
    void setText(QString txt){ text = txt;};

private slots:
    void on_back_clicked();
    void on_title_textChanged();

    void on_toolButton_pressed();

    void on_tabWidget_tabCloseRequested(int index);

    void on_todoButton_toggled(bool checked);
    void on_selfButton_toggled(bool checked);
    void on_studyButton_toggled(bool checked);
    void on_workButton_toggled(bool checked);

private:
    Ui::Note *ui;
};

#endif // NOTE_H

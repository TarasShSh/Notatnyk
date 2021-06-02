#ifndef WIDGET_H
#define WIDGET_H
#include <QStandardItemModel>
#include <QStandardItem>
#include "Note.h"
#include <QWidget>
#include "QDebug"
#include "QMessageBox"
#include "QTextEdit"
#include <QRegularExpression>
#include <QDir>
#include "QList"
QT_BEGIN_NAMESPACE
namespace Ui
{
    class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
private:
    Ui::Widget *ui;
    QStringList myList, myListFiltered;
    int mySelected = -1;
   // QList <>myList;
    bool hasElement(int value);
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    int i = -1;
    void createShortcutNote(Note *n);
    void myListUpdate();
private slots:

    void on_zaButton_clicked();
    void on_azButton_clicked();
    void on_notesList_itemClicked(QListWidgetItem *item);

    void on_createNoteButton_clicked();

    void on_archiveButton_clicked();

    void on_aboutQTButton_clicked();
    void on_exitButton_clicked();

    void on_pushButton_clicked(Note* item);

    void on_deleteButton_clicked();

    void on_notesList_currentRowChanged(int currentRow);



    void on_archiveList_itemClicked(QListWidgetItem *item);

    void on_archiveList_currentRowChanged(int currentRow);


    void on_unArchiveButton_clicked();

    void on_deleteArchiveButton_clicked();


    void on_lineEdit_textChanged(const QString &arg1);

    void on_notesList_itemChanged(QListWidgetItem *item);

public slots:
    void openNote();

};
#endif // WIDGET_H

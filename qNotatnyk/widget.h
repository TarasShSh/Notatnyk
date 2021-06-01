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
    QStringList myList;
    int mySelected = -1;

    bool hasElement(int value);
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    int i = -1;
    void createShortcutNote(Note *n);

private slots:

    void on_toArchiveButton_clicked();

    void on_oldestFirstButton_clicked();
    void on_newestFirstButton_clicked();
    void on_notesList_itemClicked(QListWidgetItem *item);

    void on_createNoteButton_clicked();

    void on_archiveButton_clicked();

    void on_aboutQTButton_clicked();
    void on_exitButton_clicked();

    void on_pushButton_clicked(Note* item);

    void on_pushButton_2_clicked();

    void on_notesList_currentRowChanged(int currentRow);



    void on_archiveList_itemClicked(QListWidgetItem *item);

    void on_archiveList_currentRowChanged(int currentRow);


    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    //void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_textChanged(const QString &arg1);

public slots:
    void openNote();

};
#endif // WIDGET_H

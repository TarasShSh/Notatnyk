#ifndef WIDGET_H
#define WIDGET_H
#include "Note.h"
#include <QWidget>
#include "QDebug"
#include "QMessageBox"
#include "QTextEdit"
#include "QListWidgetItem"
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

public slots:
    void openNote();

};
#endif // WIDGET_H

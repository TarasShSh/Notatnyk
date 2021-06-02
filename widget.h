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
    int noteNumber = -1;
    Note *notes[500];
   // QList <>myList;
    bool hasElement(int value);
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    int i = -1;
    void createShortcutNote(Note *n);
    void myListUpdate();
private slots:
// сортування та фільтри списку ярликів
    void on_azButton_clicked(); // від а-я
    void on_zaButton_clicked(); // від я-а
    void on_filteredButton_clicked(Note* item); // застосування фільтру за групами
    void on_lineEdit_textChanged(const QString &arg1); // пошукач
// Дії з нотатками
    void on_createNoteButton_clicked(); // створення нотатки її ярлика
    void on_archiveButton_clicked();    // архівування нотатки
    void on_deleteButton_clicked();     // видалення нотатки

    void on_unArchiveButton_clicked();  // повернення нотатки з архіву

    void on_notesList_itemDoubleClicked(QListWidgetItem *item); // відкриття нотатки для редагування
// Отримання ярлика зі звичайного та архівного списку для дій над ним
    void on_notesList_itemClicked(QListWidgetItem *item);
    void on_notesList_currentRowChanged(int currentRow);

    void on_archiveList_itemClicked(QListWidgetItem *item);
    void on_archiveList_currentRowChanged(int currentRow);

    void on_notesList_itemChanged(QListWidgetItem *item); // оновлення списку при додаванні нотатки
// Додаткові кнопки
    void on_aboutQTButton_clicked();
    void on_exitButton_clicked();
public slots:

};
#endif // WIDGET_H

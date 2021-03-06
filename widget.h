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

    QTreeWidget treeList, treeListFiltered;
    QList<QTreeWidgetItem*> notfilter;
    int noteNumber = -1;
    Note *notes[100]; // обмеження у 100 нотаток
    bool hasElement(int value);


public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void keyPressEvent(QKeyEvent *event);
    void createShortcutNote(Note *n);


private slots:
    // NOTES MANIPULATIONS
    void on_createNoteButton_clicked(); // створення нотатки її ярлика
    void on_archiveButton_clicked();    // архівування нотатки

    void on_deleteButton_clicked();     // видалення нотатки
    void on_unArchiveButton_clicked();  // повернення нотатки з архіву

    void on_notesTree_itemClicked(QTreeWidgetItem *item, int column);
    void on_notesTree_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_notesTree_clicked(const QModelIndex &index);
    void on_createSubNote_clicked();

    void on_archiveNotesTree_itemClicked(QTreeWidgetItem *item, int column);
    void on_recentNotes_itemPressed(QTreeWidgetItem *item, int column);

    // ADDITIONAL BUTTONS
    void on_aboutQTButton_clicked();
    void on_exitButton_clicked();
    void on_pushButton_clicked();

    // FILTER
    void on_filteredButton_clicked(); // застосування фільтру за групами

    // SEARCH BY CHILDS NAMES (AND RETURN AMOUNT OF FINDED ELEMENTS)
    void on_searchLine_textChanged(const QString &arg1); // пошукач
    int search(int column, QString regExp);
    void filterNShow(int column, QString regExp);

    // CURRENT ROW COLOR CHANGE BUTTONS
    void on_pushButton_2_clicked();
    void on_cViol_clicked();
    void on_cYellow_clicked();
    void on_cBrown_clicked();
    void on_cBlue_clicked();
    void on_cGreen_clicked();
    void on_cRed_clicked();
    void on_cGray_clicked();
    void on_cWhite_clicked();
    void on_colors_tabCloseRequested(int index);

};
#endif // WIDGET_H

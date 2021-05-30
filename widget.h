#ifndef WIDGET_H
#define WIDGET_H
#include "Note.h"

#include <QWidget>
#include <QScrollArea>
#include "QDebug"
#include "QMessageBox"
#include "QTextEdit"
#include "QPushButton"
#include "QVBoxLayout"  // прокручувач

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
    void createIconNote(IconNote *icon);
    int pn_x=0, pn_y=0;
    QVBoxLayout *lay = new QVBoxLayout; // Створюємо прокручувач при заповненні видимої області іконками нотаток

    /*ui->scrollContents->setLayout(lay);
    QScrollArea *scrollArea = new QScrollArea;
    QWidget *scrollContent = new QWidget;*/
private slots:
    void on_createNoteButton_clicked();
public slots:
    void openNote();

};
#endif // WIDGET_H

#ifndef IMPORTBOOKWINDOW_H
#define IMPORTBOOKWINDOW_H

#include <QDialog>

namespace Ui {
class importBookWindow;
}

class importBookWindow : public QDialog
{
    Q_OBJECT

public:
    explicit importBookWindow(QWidget *parent = nullptr);
    ~importBookWindow();
    void init();
    void bookListInit();
    QString bookIndex;
private:
    Ui::importBookWindow *ui;
private slots:
    void importBook();
    void setBookIndex(QModelIndex index);
};

#endif // IMPORTBOOKWINDOW_H

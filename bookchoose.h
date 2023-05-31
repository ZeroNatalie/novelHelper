#ifndef BOOKCHOOSE_H
#define BOOKCHOOSE_H

#include <QDialog>
#include <QStringListModel>
#include <QStandardItemModel>
#include "qdir.h"

namespace Ui {
class BookChoose;
}

class Book : public QDialog
{
    Q_OBJECT

public:
    explicit Book(QWidget *parent = nullptr);
    ~Book();
    void init();
    void bookListInit();
    QString bookIndex;
private:
    Ui::BookChoose *ui;
private slots:
    void ChooseBook();
    void setBtnAvailable();
    void backup();
    void setBookIndex(QModelIndex index);
    void on_btnAddBook_clicked();
    void on_btnDeleteBook_clicked();
    void importBook();
};

#endif // BOOKCHOOSE_H

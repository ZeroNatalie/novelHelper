#ifndef DELETEBOOK_H
#define DELETEBOOK_H

#include <QDialog>

namespace Ui {
class deleteBook;
}

class deleteBook : public QDialog
{
    Q_OBJECT

public:
    explicit deleteBook(QWidget *parent = nullptr);
    ~deleteBook();
    void setDeleteBookName(QString bn);
    QString getDeleteBookName();
private:
    Ui::deleteBook *ui;
    QString deleteName;
private slots:
    void deleteClick();
    void cancelClick();
};

#endif // DELETEBOOK_H

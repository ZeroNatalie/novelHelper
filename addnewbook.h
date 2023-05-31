#ifndef ADDNEWBOOK_H
#define ADDNEWBOOK_H

#include <QDialog>

namespace Ui {
class addNewBook;
}

class addNewBook : public QDialog
{
    Q_OBJECT

public:
    explicit addNewBook(QWidget *parent = nullptr);
    ~addNewBook();    
private:
    Ui::addNewBook *ui;
private slots:
    void addNewBookClick();
    void cancelClick();
};

#endif // ADDNEWBOOK_H

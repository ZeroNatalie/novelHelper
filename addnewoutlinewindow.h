#ifndef ADDNEWOUTLINEWINDOW_H
#define ADDNEWOUTLINEWINDOW_H

#include <QDialog>

namespace Ui {
class addNewOutlineWindow;
}

class addNewOutlineWindow : public QDialog
{
    Q_OBJECT

public:
    explicit addNewOutlineWindow(QWidget *parent = nullptr);
    ~addNewOutlineWindow();

private slots:
    void on_okBtn_clicked();

private:
    Ui::addNewOutlineWindow *ui;
};

#endif // ADDNEWOUTLINEWINDOW_H

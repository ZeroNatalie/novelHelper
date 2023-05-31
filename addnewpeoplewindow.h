#ifndef ADDNEWPEOPLEWINDOW_H
#define ADDNEWPEOPLEWINDOW_H

#include <QDialog>

namespace Ui {
class addNewPeopleWindow;
}

class addNewPeopleWindow : public QDialog
{
    Q_OBJECT

public:
    explicit addNewPeopleWindow(QString bookName,QWidget *parent = nullptr);
    ~addNewPeopleWindow();

private slots:
    void on_okBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::addNewPeopleWindow *ui;
    QString bookName;
};

#endif // ADDNEWPEOPLEWINDOW_H

#ifndef ADDNEWEVENTWINDOW_H
#define ADDNEWEVENTWINDOW_H

#include <QDialog>

namespace Ui {
class addNewEventWindow;
}

class addNewEventWindow : public QDialog
{
    Q_OBJECT

public:
    explicit addNewEventWindow(QString bookName,QWidget *parent = nullptr);
    ~addNewEventWindow();

private slots:
    void on_btnCancel_clicked();

    void on_btnOk_clicked();

private:
    Ui::addNewEventWindow *ui;
    QString bookName;
};

#endif // ADDNEWEVENTWINDOW_H

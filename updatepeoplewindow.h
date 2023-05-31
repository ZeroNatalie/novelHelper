#ifndef UPDATEPEOPLEWINDOW_H
#define UPDATEPEOPLEWINDOW_H

#include <QDialog>

namespace Ui {
class updatePeopleWindow;
}

class updatePeopleWindow : public QDialog
{
    Q_OBJECT

public:
    explicit updatePeopleWindow(QString bookName,QWidget *parent = nullptr);
    ~updatePeopleWindow();

private slots:
    void on_btnOK_clicked();

    void on_btnCancel_clicked();

private:
    Ui::updatePeopleWindow *ui;
    QString bookName;
};

#endif // UPDATEPEOPLEWINDOW_H

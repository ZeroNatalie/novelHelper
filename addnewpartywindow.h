#ifndef ADDNEWPARTYWINDOW_H
#define ADDNEWPARTYWINDOW_H

#include <QDialog>

namespace Ui {
class addnewpartywindow;
}

class addNewPartyWindow : public QDialog
{
    Q_OBJECT

public:
    explicit addNewPartyWindow(QString bookName,QWidget *parent = nullptr);
    ~addNewPartyWindow();

private slots:
    void on_btnOk_clicked();

private:
    Ui::addnewpartywindow *ui;
    QString bookName;
};

#endif // ADDNEWPARTYWINDOW_H

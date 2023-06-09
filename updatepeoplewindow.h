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
    explicit updatePeopleWindow(QString bookName,QString on,QString od,QString ono,QWidget *parent = nullptr);
    ~updatePeopleWindow();
    void setOldName(QString on);
    void setOldDescribe(QString od);
    void setOldNote(QString ono);
private slots:
    void on_btnOK_clicked();
    void on_btnCancel_clicked();

private:
    Ui::updatePeopleWindow *ui;
    QString bookName;
    QString oldName;
    QString oldDescribe;
    QString oldNote;
};

#endif // UPDATEPEOPLEWINDOW_H

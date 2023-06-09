#include "updatepeoplewindow.h"
#include "ui_updatepeoplewindow.h"
#include "database.h"

updatePeopleWindow::updatePeopleWindow(QString bn,QString on,QString od,QString ono,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::updatePeopleWindow),
    bookName(bn),
    oldName(on),
    oldDescribe(od),
    oldNote(ono)
{
    ui->setupUi(this);
    ui->updatePeoName->setText(oldName);
    ui->updatePeoDescribe->setText(oldDescribe);
    ui->updatePeoConnection->setText(oldNote);
}

updatePeopleWindow::~updatePeopleWindow()
{
    delete ui;
}

void updatePeopleWindow::on_btnOK_clicked()
{
    SqliteOperator sqls(bookName);
    QString newName = ui->updatePeoName->text();
    QString desc = ui->updatePeoDescribe->toPlainText();
    QString connec = ui->updatePeoConnection->toPlainText();
    sqls.modifyData("People",oldName,newName,desc,connec);
    this->close();
}
void updatePeopleWindow::on_btnCancel_clicked()
{
    this->close();
}
void updatePeopleWindow::setOldName(QString on){
    oldName = on;
}
void updatePeopleWindow::setOldDescribe(QString od){
    oldDescribe = od;
}
void updatePeopleWindow::setOldNote(QString ono){
    oldNote = ono;
}

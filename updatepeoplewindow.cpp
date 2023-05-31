#include "updatepeoplewindow.h"
#include "ui_updatepeoplewindow.h"
#include "database.h"

updatePeopleWindow::updatePeopleWindow(QString bn,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::updatePeopleWindow),
    bookName(bn)
{
    ui->setupUi(this);
}

updatePeopleWindow::~updatePeopleWindow()
{
    delete ui;
}

void updatePeopleWindow::on_btnOK_clicked()
{
    SqliteOperator sqls(bookName);
    QString name = ui->updatePeoName->text();
    QString desc = ui->updatePeoDescribe->toPlainText();
    QString connec = ui->updatePeoConnection->toPlainText();
    sqls.modifyData("People",name,desc,connec);
    this->close();
}


void updatePeopleWindow::on_btnCancel_clicked()
{
    this->close();
}


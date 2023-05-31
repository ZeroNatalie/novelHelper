#include "addnewpeoplewindow.h"
#include "ui_addnewpeoplewindow.h"
#include "database.h"

addNewPeopleWindow::addNewPeopleWindow(QString bn,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addNewPeopleWindow)
{
    ui->setupUi(this);
    bookName = bn;
}

addNewPeopleWindow::~addNewPeopleWindow()
{
    delete ui;
}

void addNewPeopleWindow::on_okBtn_clicked()
{
    SqliteOperator sqls(bookName);
    QString name = ui->addNewPeopleName->toPlainText();
    QString desc = ui->addNewPeopleDescribe->toPlainText();
    QString connec = ui->addNewPeopleConnection->toPlainText();
    w2dba data = {name,desc,connec};
    //w2dba w2dbaTest2 = {"name3", "text3","connection3"};
    sqls.singleInsertData("people",data);
    this->close();
}




void addNewPeopleWindow::on_cancelBtn_clicked()
{
    this->close();
}


#include "addnewpartywindow.h"
#include "ui_addnewpartywindow.h"
#include "database.h"

addNewPartyWindow::addNewPartyWindow(QString bn,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addnewpartywindow)
{
    ui->setupUi(this);
    bookName = bn;
}

addNewPartyWindow::~addNewPartyWindow()
{
    delete ui;
}


void addNewPartyWindow::on_btnOk_clicked()
{
    SqliteOperator sqls(bookName);
    QString name = ui->addNewPartyName->toPlainText();
    QString desc = ui->addNewPartyDescribe->toPlainText();
    QString connec = ui->addNewPartyConnection->toPlainText();
    w2dba data = {name,desc,connec};
    //w2dba w2dbaTest2 = {"name3", "text3","connection3"};
    sqls.singleInsertData("party",data);
    this->close();
}


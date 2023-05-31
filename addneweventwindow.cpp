#include "addneweventwindow.h"
#include "ui_addneweventwindow.h"
#include "database.h"

addNewEventWindow::addNewEventWindow(QString bn,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addNewEventWindow),
    bookName(bn)
{
    ui->setupUi(this);
}

addNewEventWindow::~addNewEventWindow()
{
    delete ui;
}

void addNewEventWindow::on_btnCancel_clicked()
{
    this->close();
}


void addNewEventWindow::on_btnOk_clicked()
{
    SqliteOperator sqls(bookName);
    QString name = ui->addNewEventName->text();
    QString desc = ui->addNewEventDescribe->toPlainText();
    QString connec = ui->addNewEventConnection->toPlainText();
    w2dba data = {name,desc,connec};
    sqls.singleInsertData("event",data);
    this->close();
}


#include "addnewoutlinewindow.h"
#include "ui_addnewoutlinewindow.h"

addNewOutlineWindow::addNewOutlineWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addNewOutlineWindow)
{
    ui->setupUi(this);
}

addNewOutlineWindow::~addNewOutlineWindow()
{
    delete ui;
}

void addNewOutlineWindow::on_okBtn_clicked()
{
    this->close();
}


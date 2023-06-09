#include "message.h"
#include "ui_message.h"

Message::Message(QString m,QWidget *parent) :
    QDialog(parent),
    message(m),
    ui(new Ui::Message)
{
    ui->setupUi(this);
    ui->text->setText(message);
    this->setWindowTitle("提示消息");
}

Message::~Message()
{
    delete ui;
}

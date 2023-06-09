#include "deletebook.h"
#include "ui_deletebook.h"
#include "QFile"

deleteBook::deleteBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deleteBook)
{
    ui->setupUi(this);
    this->setWindowTitle("确认删除");
    connect(ui->btnDelete,SIGNAL(clicked()),this,SLOT(deleteClick()));
    connect(ui->btnCancel,SIGNAL(clicked()),this,SLOT(cancelClick()));
}

deleteBook::~deleteBook()
{
    delete ui;
}

void deleteBook::setDeleteBookName(QString bn){
    deleteName = bn;
    QString text = "确定要删除作品："+bn+"吗？";
    ui->textDeleteBook->setText(text);
}

QString deleteBook::getDeleteBookName(){
    return deleteName;
}

void deleteBook::deleteClick(){
    QString path = QCoreApplication::applicationDirPath()+"/"+deleteName+".db";
    QFile file(path);
    QFile::setPermissions(path,QFile::ReadOther | QFile::WriteOther);
    if(file.exists()){
        file.remove();
        if(!file.exists()){
            qDebug() << "remove success!";
        }
        else{
            qDebug() << "remove failed!";
        }
    }
    else{
        qDebug() << "book don't exists!";
    }
    this->close();
}

void deleteBook::cancelClick(){
    this->close();
}

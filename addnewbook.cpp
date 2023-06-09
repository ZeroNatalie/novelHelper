#include "addnewbook.h"
#include "ui_addnewbook.h"
#include "QFile"
#include "database.h"

addNewBook::addNewBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addNewBook)
{
    ui->setupUi(this);
    this->setWindowTitle("新增作品");
    connect(ui->btnAddNewBook,SIGNAL(clicked()),this,SLOT(addNewBookClick()));
    connect(ui->btnCancel,SIGNAL(clicked()),this,SLOT(cancelClick()));
}

addNewBook::~addNewBook()
{
    delete ui;
}

void addNewBook::addNewBookClick(){

    QString newbookFileName = ui->newBookName->text()+".db";
    if(QFile::exists(newbookFileName)){
        qDebug() << "错误：作品重名";
    }
    else{
        SqliteOperator *sqls = new SqliteOperator(ui->newBookName->text());
        sqls->openDb();
        sqls->initDb();
        QString path = QCoreApplication::applicationDirPath()+"/"+newbookFileName;
//        qDebug() << path;
        QFile file(path);
        if(file.exists()){
            qDebug() << "add new book success!";
        }
    }
    this->close();
}
void addNewBook::cancelClick(){
    this->close();
}

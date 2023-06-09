#include "bookchoose.h"
#include "ui_bookchoose.h"
#include "qlistwidget.h"
#include "mainwindow.h"
#include "addnewbook.h"
#include "deletebook.h"
#include "importbookwindow.h"
#include "util.h"
#include "QKeyEvent"
#include "message.h"
Book::Book(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BookChoose)
{
    ui->setupUi(this);
    init();
}

Book::~Book()
{
    delete ui;
}
void Book::keyPressEvent(QKeyEvent *e){
    if(e->key()==Qt::Key_R){
        bookListInit();
    }
}
void Book::init(){   
    ui->btnChooseBook->setEnabled(false);
    ui->btnDeleteBook->setEnabled(false);
    connect(ui->btnChooseBook,SIGNAL(clicked()),this,SLOT(ChooseBook()));
    connect(ui->bookList,SIGNAL(clicked(QModelIndex)),this,SLOT(setBtnAvailable()));
    connect(ui->bookList,SIGNAL(clicked(QModelIndex)),this,SLOT(setBookIndex(QModelIndex)));
    connect(ui->btnBackup,SIGNAL(clicked()),this,SLOT(backup()));
    connect(ui->btnImport,SIGNAL(clicked()),this,SLOT(importBook()));
    bookListInit();
    this->setWindowTitle("作品选择");
}
void Book::bookListInit(){
    ui->bookList->clear();
    QStringList bookList = Util::getBookNameList(QCoreApplication::applicationDirPath());
    //QListWidget *bookList = new QListWidget;
    //ui->bookList->resize(365,400);
    //ui->bookList->setStyleSheet("QListWidget::item::selected{background:#edf2f3;}");
    ui->bookList->setViewMode(QListWidget::IconMode);
    ui->bookList->setIconSize(QSize(100,100));
    ui->bookList->setResizeMode(QListWidget::Adjust);
    ui->bookList->setMovement(QListWidget::Static);
    QString path = ":/img/ico/book.ico";
    //QFileInfoList filelist = new QFileInfoList;
    for(int i=0;i<bookList.size();i++){
        QListWidgetItem *ite = new QListWidgetItem;
        ite->setIcon(QIcon(path));
        ite->setText(bookList.at(i));
        ui->bookList->addItem(ite);
    }
}

void Book::ChooseBook(){
    MainWindow *w = new MainWindow(bookIndex);
    w->show();
}

//QStringList Book::getBookNameList(Qir dirPath){
//    QDir dir(dirPath);
//    QStringList bookName;
//    QStringList filter;
//    filter << "*.db";
//    dir.setNameFilters(filter);
//    QFileInfoList fileList = dir.entryInfoList(filter);
//    if(fileList.size()>0){
//        for(int i=0;i<fileList.size();i++){
//            bookName.append(fileList.at(i).baseName());
//        }
//    }
//    return bookName;
//}
void Book::setBtnAvailable(){
    ui->btnChooseBook->setEnabled(true);
    ui->btnDeleteBook->setEnabled(true);
}
void Book::setBookIndex(QModelIndex index){
    this->bookIndex = index.data().toString();
    qDebug() << bookIndex << "is choosed.";
}
void Book::backup(){
    QString currentPath = QCoreApplication::applicationDirPath();
    QString backupPath = QCoreApplication::applicationDirPath()+"/backup";
    QDir dir(backupPath);
    if(!dir.exists()){
        dir.mkdir(backupPath);
    }
    else{
        qDebug() << "back up dir exists!";
    }
    QString filename = this->bookIndex+".db";
    bool backupOk = QFile::copy(currentPath+"/"+filename,backupPath+"/"+filename);
    if(backupOk == 1){
        QString sum = "备份成功!";
        Message m(sum);
        m.exec();
    }
    else{
        QString fam = "备份失败!";
        Message m(fam);
        m.exec();
        //qDebug() << "backup error!";
    }
}

void Book::on_btnAddBook_clicked()
{
    addNewBook *n = new addNewBook;
    n->show();
}
void Book::on_btnDeleteBook_clicked()
{
    deleteBook *d = new deleteBook;
    d->setDeleteBookName(this->bookIndex);
    d->show();
}

void Book::importBook(){
    importBookWindow *i = new importBookWindow;
    i->show();
}

#include "importbookwindow.h"
#include "ui_importbookwindow.h"
#include  "message.h"
#include "util.h"
#include "qfile.h"
importBookWindow::importBookWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::importBookWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("导入作品");
    init();
}

importBookWindow::~importBookWindow()
{
    delete ui;
}
void importBookWindow::setBookIndex(QModelIndex index){
    this->bookIndex = index.data().toString();
}
void importBookWindow::init(){
    connect(ui->backupList,SIGNAL(clicked(QModelIndex)),this,SLOT(setBookIndex(QModelIndex)));
    connect(ui->btnChooseBook,SIGNAL(clicked()),this,SLOT(importBook()));
    bookListInit();
}
void importBookWindow::bookListInit(){
    ui->backupList->clear();
    QStringList bList = Util::getBookNameList(QCoreApplication::applicationDirPath()+"/backup");
    //QListWidget *bookList = new QListWidget;
    //ui->bookList->resize(365,400);
    //ui->bookList->setStyleSheet("QListWidget::item::selected{background:#edf2f3;}");
    ui->backupList->setViewMode(QListWidget::IconMode);
    ui->backupList->setIconSize(QSize(100,100));
    ui->backupList->setResizeMode(QListWidget::Adjust);
    ui->backupList->setMovement(QListWidget::Static);
    QString path = ":/img/ico/book.ico";
    //QFileInfoList filelist = new QFileInfoList;
    for(int i=0;i<bList.size();i++){
        QListWidgetItem *ite = new QListWidgetItem;
        ite->setIcon(QIcon(path));
        ite->setText(bList.at(i));
        ui->backupList->addItem(ite);
    }
}
void importBookWindow::importBook(){
    QString currentPath = QCoreApplication::applicationDirPath();
    QString backupPath = QCoreApplication::applicationDirPath()+"/backup";
    QString filename = this->bookIndex+".db";
    bool backupOk = QFile::copy(backupPath+"/"+filename,currentPath+"/"+filename);
    if(backupOk == 1){
        QString sum = "导入成功!";
        Message m(sum);
        m.exec();
    }
    else{
        QString fam = "导入失败!";
        Message m(fam);
        m.exec();
        //qDebug() << "backup error!";
    }
}

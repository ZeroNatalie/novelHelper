#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QLineEdit>
#include "addnewpeoplewindow.h"
#include "addnewpartywindow.h"
#include "addneweventwindow.h"
#include "updatepeoplewindow.h"
#include "addnewconnecion.h"


MainWindow::MainWindow(QString bookName,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setBookName(bookName);
    this->setWindowTitle(bookName);
    sqls = new SqliteOperator(bookName);
    init();
}
void MainWindow::setBookName(QString bn){
    bookName = bn;
}
void MainWindow::init()
{

    //创建并打开SQLite数据库
    //SqliteOperator sqls(bookName);
    sqls->openDb();
    QString peo = "people";
    QString par = "party";
    QString eve = "event";
//    QString con = "connection";
//    if(!sqls->isTableExist(peo)){
//        sqls->createTable(peo);
//    }
//    if(!sqls->isTableExist(par)){
//        sqls->createTable(par);
//    }
//    if(!sqls->isTableExist(eve)){
//        sqls->createTable(eve);
//    }
//    if(!sqls->isTableExist(con)){
//        sqls->createConnectionTable();
//    }
    //ui
    QStringList peopleList = sqls->queryName(peo);
    peopleModel  = new QStringListModel(peopleList);
    ui->listView_people->setModel(peopleModel);
    ui->peopleName->setAlignment(Qt::AlignHCenter);
    ui->peopleDescribe->setAlignment(Qt::AlignHCenter);

    QStringList partyList = sqls->queryName(par);
    partyModel  = new QStringListModel(partyList);
    ui->listView_party->setModel(partyModel);
    ui->partyName->setAlignment(Qt::AlignHCenter);

    QStringList eventList = sqls->queryName(eve);
    eventModel = new QStringListModel(eventList);
    ui->listView_event->setModel(eventModel);
    ui->eventName->setAlignment(Qt::AlignHCenter);

    QSqlTableModel *connectionModel = new QSqlTableModel(this);
    connectionModel->setTable("connection");
    QStringList headerList;
    headerList << "名称" <<"设定类型"<<"联系设定名称"<<"联系设定类型"<<"具体联系";
    for(int i = 0;i<headerList.size();i++){
        connectionModel->setHeaderData(i,Qt::Horizontal,headerList.at(i));
    }
    connectionModel->select();
    ui->peopleConnection->setModel(connectionModel);
    ui->peopleConnection->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->peopleConnection->setStyleSheet("QHeaderView::section{background-color:rgb(162,181,205)}\
                                        QTableView::item{color:white}\
                                        QTableView{border: 0px groove gary;border-radius:5px;}\
                                        QTableCornerButton::section{background-color:rgb(162,181,205)}");

    //connect
    connect(ui->listView_people,SIGNAL(clicked(QModelIndex)),this,SLOT(showPeopleClick(QModelIndex)));
    connect(ui->listView_people,SIGNAL(clicked(QModelIndex)),this,SLOT(showPeopleConnection(QModelIndex)));
    connect(ui->listView_party,SIGNAL(clicked(QModelIndex)),this,SLOT(showPartyClick(QModelIndex)));
    connect(ui->listView_event,SIGNAL(clicked(QModelIndex)),this,SLOT(showEventClick(QModelIndex)));
    connect(ui->btnAddNewPeople,SIGNAL(clicked()),this,SLOT(addNewPeopleClick()));
    connect(ui->btnDeletePeople,SIGNAL(clicked()),this,SLOT(deletePeopleClick()));
    connect(ui->btnExit,SIGNAL(clicked()),this,SLOT(exitClick()));
    connect(ui->btnAddPeopleConnection,SIGNAL(clicked()),this,SLOT(addNewConnection()));
    /*
    ItemModel = new QStandardItemModel(this);
    QStringList strList;
    strList.append("A");
    int nCount = strList.size();
    for(int i = 0; i < nCount; i++)
    {
        QString string = static_cast<QString>(strList.at(i));
        QStandardItem *item = new QStandardItem(string);
        ItemModel->appendRow(item);
    }
    ui->listView_people->setModel(ItemModel);
    ui->listView_people->setFixedSize(200,400);
    connect(ui->listView_people,SIGNAL(clicked(QModelIndex)),this,SLOT(showClick(QModelIndex)));
    */
 }

 void MainWindow::showPeopleClick(QModelIndex index)
 {
    this->ChoosenPeopleIndex = index.data().toString();
    w2dba ans = sqls->queryData("people",this->ChoosenPeopleIndex);
    ui->peopleName->setText(ans.name);
    ui->peopleDescribe->setText(ans.describe);
    ui->peopleNote->setText(ans.connection);

 }
 void MainWindow::showPeopleConnection(QModelIndex index){
    QSqlTableModel *connectionModel = new QSqlTableModel(this);
    connectionModel->setTable("connection");
    QStringList headerList;
    headerList << "名称" <<"设定类型"<<"联系设定名称"<<"联系设定类型"<<"具体联系";
    for(int i = 0;i<headerList.size();i++){
        connectionModel->setHeaderData(i,Qt::Horizontal,headerList.at(i));
    }
    this->ChoosenPeopleIndex = index.data().toString();
    QString str = QString("aname = '%1' OR bname = '%1'").arg(this->ChoosenPeopleIndex);
    connectionModel->setFilter(str);
    connectionModel->select();
    ui->peopleConnection->setModel(connectionModel);
 }
 void MainWindow::showPartyClick(QModelIndex index)
 {
    this->ChoosenPartyIndex = index.data().toString();
    //SqliteOperator s(bookName);
    w2dba ans = sqls->queryData("party",this->ChoosenPartyIndex);
    ui->partyName->setText(ans.name);
    ui->partyDescribe->setText(ans.describe);
    ui->partyNote->setText(ans.connection);
 }
 void MainWindow::showEventClick(QModelIndex index)
 {
    this->ChoosenEventIndex = index.data().toString();
    //SqliteOperator s(bookName);
    w2dba ans = sqls->queryData("event",this->ChoosenEventIndex);
    ui->eventName->setText(ans.name);
    ui->eventDescribe->setText(ans.describe);
    ui->eventNote->setText(ans.connection);
 }

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::exitClick(){
    //SqliteOperator sqlTest;
    QString name = "people";
    sqls->deleteTable(name);
    sqls->closeDb();
}
void MainWindow::addNewPeopleClick(){
    addNewPeopleWindow *npw = new addNewPeopleWindow(bookName);
    npw->show();
    //this->refreshList(); //应该是关闭那个窗口后才刷新
}
void MainWindow::deletePeopleClick(){
    //SqliteOperator sqlTest;
    sqls->deleteData("people",this->ChoosenPeopleIndex);
    this->refreshList();
}
void MainWindow::on_refreshBtn_clicked()
{
    this->refreshList();
}
void MainWindow::refreshList(){
    //SqliteOperator sqlTest;
    QStringList peopleList = sqls->queryName("people");
    peopleModel  = new QStringListModel(peopleList);
    ui->listView_people->setModel(peopleModel);
    ui->peopleDescribe->setAlignment(Qt::AlignHCenter);
    QStringList partyList = sqls->queryName("party");
    partyModel  = new QStringListModel(partyList);
    ui->listView_party->setModel(partyModel);
    QStringList eventList = sqls->queryName("event");
    eventModel  = new QStringListModel(eventList);
    ui->listView_event->setModel(eventModel);
}
void MainWindow::on_btnAddParty_clicked()
{
    addNewPartyWindow *nw = new addNewPartyWindow(bookName);
    nw->show();
}
void MainWindow::on_btnDeleteParty_clicked()
{
    //SqliteOperator sqlTest;
    sqls->deleteData("party",this->ChoosenPartyIndex);
    this->refreshList();
}
void MainWindow::on_btnAddEvent_clicked()
{
    addNewEventWindow *nw = new addNewEventWindow(bookName);
    nw->show();
}
void MainWindow::on_btnDeleteEvent_clicked()
{
    //SqliteOperator sqlTest;
    sqls->deleteData("event",this->ChoosenEventIndex);
    this->refreshList();
}
void MainWindow::on_btnUpdatePeople_clicked()
{
    updatePeopleWindow *nw = new updatePeopleWindow(bookName);
    nw->show();
}


void MainWindow::addNewConnection()
{
    QString selectedName,selectedType;
    switch(ui->tabWidget->currentIndex()){
        case 0:
            selectedType = "人物";
            selectedName = ui->peopleName->text();
            break;
        case 1:
            selectedType = "组织";
            selectedName = ui->partyName->text();
            break;
        case 2:
            selectedType = "事件";
            selectedName = ui->eventName->text();
        break;
        defualt:
        break;
    }
    addNewConnecion *c = new addNewConnecion(bookName);
    c->setSelectedName(selectedName);
    c->setSelectedType(selectedType);
    c->show();
}


#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QLineEdit>
#include "addnewpeoplewindow.h"
#include "addnewpartywindow.h"
#include "addneweventwindow.h"
#include "updatepeoplewindow.h"
#include "addnewconnecion.h"
#include "QKeyEvent"
#include "addnewoutlinewindow.h"

MainWindow::MainWindow(QString bookName,QWidget *parent)
    : QMainWindow(parent),
      bookName(bookName),
     ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //setBookName(bookName);
    this->setWindowTitle(bookName);
    sqls = new SqliteOperator(bookName);
    init();
}
void MainWindow::setBookName(QString bn){
    bookName = bn;
}
void MainWindow::keyPressEvent(QKeyEvent *e){
    if(e->key()==Qt::Key_R){
        refreshList();
    }
}
void MainWindow::init()
{

    //创建并打开SQLite数据库
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

//    QStringList hder;
//    hder << "章节" << "内容";
//    m_standardItemModel->setHorizontalHeaderLabels(hder);

//    // TreeView控件载入model
//    ui->treeView->setModel(m_standardItemModel);
//    ui->treeView->setStyleSheet("QHeaderView::section{background-color:rgb(162,181,205)}\
//                                QTreeView::item{color:white}");
//    // 展开数据
//    ui->treeView->expandAll();

    initTree();
    //connect
    connect(ui->listView_people,SIGNAL(clicked(QModelIndex)),this,SLOT(showPeopleClick(QModelIndex)));
    connect(ui->listView_people,SIGNAL(clicked(QModelIndex)),this,SLOT(showPeopleConnection(QModelIndex)));
    connect(ui->listView_party,SIGNAL(clicked(QModelIndex)),this,SLOT(showPartyClick(QModelIndex)));
    connect(ui->listView_event,SIGNAL(clicked(QModelIndex)),this,SLOT(showEventClick(QModelIndex)));
    connect(ui->btnAddNewPeople,SIGNAL(clicked()),this,SLOT(addNewPeopleClick()));
    connect(ui->btnDeletePeople,SIGNAL(clicked()),this,SLOT(deletePeopleClick()));
    connect(ui->btnExit,SIGNAL(clicked()),this,SLOT(exitClick()));
    connect(ui->btnAddPeopleConnection,SIGNAL(clicked()),this,SLOT(addNewConnection()));
    connect(ui->btnAddOutline,SIGNAL(clicked()),this,SLOT(addNewOutline()));
//    connect(ui->treeView,SIGNAL(clicked(QModelIndex)),this,SLOT(showOutlineClicked(QModelIndex)));

 }
void MainWindow::initTree(){
    // 初始化model
    QStandardItemModel* m_standardItemModel = new QStandardItemModel();
    m_standardItemModel->setColumnCount(2);
    // 使用model设置QTreeView表头
//    QStringList hder;
//    hder << "章节" << "内容";
//    m_standardItemModel->setHorizontalHeaderLabels(hder);
    m_standardItemModel->setHeaderData(0,Qt::Horizontal,"章节");
    m_standardItemModel->setHeaderData(1,Qt::Horizontal,"内容");

    // TreeView控件载入model
    ui->treeView->setModel(m_standardItemModel);
    ui->treeView->setStyleSheet("QHeaderView::section{background-color:rgb(162,181,205)}\
                                QTreeView::item{color:white}");
    // 展开数据
    ui->treeView->expandAll();

    // 创建根节点，抽象Item，并没有实际数据
    QStandardItem* itemRoot = m_standardItemModel->invisibleRootItem();

    // 创建并添加Item的第一个子节点
    //QStringList it1;
    //it1 << "第一卷" << "第一卷的内容";
    QStandardItem* itemCam = new QStandardItem(QStringLiteral("第一卷"));
    QStandardItem* item2 = new QStandardItem(QStringLiteral("第一卷的内容是故事的引子，讲述班级里出现了一起诡异的案件"));
    //itemRoot->appendRow(itemCam);
    m_standardItemModel->setItem(0,0,itemCam);
    m_standardItemModel->setItem(0,1,item2);

    // 向第一个子节点itemCam添加子节点数据
    QStandardItem* itemc1 = new QStandardItem("章节一");
    itemCam->appendRow(itemc1);
    QStandardItem* itemd1 = new QStandardItem("第一章的内容是：某一天下课后几人在班级里闲聊，讨论新转校生");
    itemCam->setChild(0,1,itemd1);
    QStandardItem* itemc2 = new QStandardItem("章节二");
    itemCam->appendRow(itemc2);
    QStandardItem* itemd2 = new QStandardItem("第二章的内容是：这天放学以后，班主任忽然让所有人留下接受调查……");
    itemCam->setChild(1,1,itemd2);
//    QList<QStandardItem*> camList;
//    camList.append(new QStandardItem("章节一"));
//    camList.append(new QStandardItem("章节二"));
//    camList.append(new QStandardItem("章节三"));
//    itemCam->appendRows(camList);
//    // 创建并添加Item的第二个子节点
//    QStandardItem* itemImg = new QStandardItem(QStringLiteral("第二卷"));
//    itemRoot->appendRow(itemImg);

//    // 向第二个子节点itemImg添加子节点数据
//    QList<QStandardItem*> imgList;
//    imgList.append(new QStandardItem("章节一"));
//    imgList.append(new QStandardItem("章节二"));
//    QStandardItem* ite = new QStandardItem(QStringLiteral("章节三"));
//    imgList.append(ite);
//    itemImg->appendRows(imgList);

    QList<QStandardItem*> iteList;
    iteList.append(new QStandardItem("小节一"));
    iteList.append(new QStandardItem("小节二"));
    itemc2->appendRows(iteList);
    QStandardItem* itemd3 = new QStandardItem("小节1的内容是：在几人的闲聊中引入几位班级名人：张明娜，胡军，江飞鸟和白桦……");
    itemc2->setChild(0,1,itemd3);
    QStandardItem* itemd4 = new QStandardItem("小节2的内容是：引入几人的性格特点和相互关系，隐晦地介绍班级里不同寻常的氛围……");
    itemc2->setChild(1,1,itemd4);
}
 void MainWindow::showPeopleClick(QModelIndex index)
 {
    this->ChoosenPeopleIndex = index.data().toString();
    w2dba ans = sqls->queryData("people",this->ChoosenPeopleIndex);
    ui->peopleName->setText(ans.name);
    ui->peopleDescribe->setText(ans.describe);
    ui->peopleNote->setText(ans.note);

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
    ui->partyNote->setText(ans.note);
 }
 void MainWindow::showEventClick(QModelIndex index)
 {
    this->ChoosenEventIndex = index.data().toString();
    //SqliteOperator s(bookName);
    w2dba ans = sqls->queryData("event",this->ChoosenEventIndex);
    ui->eventName->setText(ans.name);
    ui->eventDescribe->setText(ans.describe);
    ui->eventNote->setText(ans.note);
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
    QString od = ui->peopleDescribe->toPlainText();
    QString ono = ui->peopleNote->toPlainText();
    updatePeopleWindow *nw = new updatePeopleWindow(bookName,ChoosenPeopleIndex,od,ono);
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
    addNewConnectionWindow *c = new addNewConnectionWindow(bookName);
    c->setSelectedName(selectedName);
    c->setSelectedType(selectedType);
    c->show();
}
void MainWindow::addNewOutline(){
    addNewOutlineWindow *now = new addNewOutlineWindow;
    now->show();

    QStandardItemModel* m_standardItemModel = new QStandardItemModel();
    m_standardItemModel->setColumnCount(2);
    m_standardItemModel->setHeaderData(0,Qt::Horizontal,"章节");
    m_standardItemModel->setHeaderData(1,Qt::Horizontal,"内容");
    ui->treeView->setModel(m_standardItemModel);
    ui->treeView->setStyleSheet("QHeaderView::section{background-color:rgb(162,181,205)}\
                                QTreeView::item{color:white}");
    ui->treeView->expandAll();
    QStandardItem* itemRoot = m_standardItemModel->invisibleRootItem();
    QStandardItem* item1 = new QStandardItem(QStringLiteral("第一卷"));
    QStandardItem* item2 = new QStandardItem(QStringLiteral("第一卷的内容"));
    m_standardItemModel->setItem(0,0,item1);
    m_standardItemModel->setItem(0,1,item2);
    QStandardItem* itemc1 = new QStandardItem("章节一");
    item1->appendRow(itemc1);
    QStandardItem* itemd1 = new QStandardItem("第一章的内容");
    item1->setChild(0,1,itemd1);
    QStandardItem* itemc2 = new QStandardItem("章节二");
    item1->appendRow(itemc2);
    QStandardItem* itemd2 = new QStandardItem("第2章的内容");
    item1->setChild(1,1,itemd2);

    QList<QStandardItem*> iteList;
    iteList.append(new QStandardItem("小节一"));
    iteList.append(new QStandardItem("小节二"));
    itemc2->appendRows(iteList);
    QStandardItem* itemd3 = new QStandardItem("小节1的内容");
    itemc2->setChild(0,1,itemd3);
    QStandardItem* itemd4 = new QStandardItem("小节2的内容");
    itemc2->setChild(1,1,itemd4);

    QStandardItem* item3 = new QStandardItem(QStringLiteral("章节三"));
    QStandardItem* item4 = new QStandardItem(QStringLiteral("章节三的内容"));
    item1->appendRow(item3);
    item1->setChild(2,1,item4);
}
//void MainWindow::showOutlineClicked(QModelIndex index){
//    qDebug() << index.data();
//}

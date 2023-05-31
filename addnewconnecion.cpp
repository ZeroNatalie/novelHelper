#include "addnewconnecion.h"
#include "ui_addnewconnecion.h"
#include "database.h"

addNewConnecion::addNewConnecion(QString bn,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addNewConnecion),
    bookName(bn)
{
    ui->setupUi(this);
    init();
    this->setWindowTitle("增加关系");
}
void addNewConnecion::init(){
    ui->connectTypeBox->clear();
    ui->connectTypeBox->addItem("人物");
    ui->connectTypeBox->addItem("组织");
    ui->connectTypeBox->addItem("事件");
    ui->connectTypeBox->addItem("设定");
    connect(ui->connectTypeBox,SIGNAL(currentIndexChanged(int)),this,SLOT(on_connectTypeBox_currentIndexChanged(int)));
    connect(ui->connectNameBox,SIGNAL(currentIndexChanged(int)),this,SLOT(connectNameChoose()));
    connect(ui->btnAddConnection,SIGNAL(clicked()),this,SLOT(newConnectionClicked()));
}

addNewConnecion::~addNewConnecion()
{
    delete ui;
}
void addNewConnecion::setSelectedType(QString t){
    this->selectedType=t;
}
void addNewConnecion::setSelectedName(QString n){
    this->selectedName=n;
    ui->selectedName->setText(n);
}

void addNewConnecion::connectNameChoose()
{
    connectName = ui->connectNameBox->currentText();
}


void addNewConnecion::on_connectTypeBox_currentIndexChanged(int index)
{
    ui->connectNameBox->clear();
    QString tableName;
    switch(index){
    case 0:
        tableName = "people";
        break;
    case 1:
        tableName = "party";
        break;
    case 2:
        tableName = "event";
        break;
    default:
        tableName = "other";
    }
    SqliteOperator sql(bookName);
    QStringList list = sql.queryName(tableName);
    for(int i = 0;i<list.size();i++){
        ui->connectNameBox->addItem(list.at(i));
    }
    connectType = ui->connectTypeBox->currentText();
    connectName = ui->connectNameBox->currentText();
}
QString addNewConnecion::getConnectionNote(){
    return ui->connectionNote->text();
}

void addNewConnecion::newConnectionClicked(){
    SqliteOperator sql(bookName);
    sql.InsertConnection(selectedName,selectedType,connectName,connectType,getConnectionNote());
    this->close();
}


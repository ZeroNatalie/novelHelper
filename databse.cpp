#include "database.h"
#include <QCoreApplication>

// 构造函数中初始化数据库对象，并建立数据库
SqliteOperator::SqliteOperator(QString dbName)
{
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        // 建立和SQlite数据库的连接
        database = QSqlDatabase::addDatabase("QSQLITE");
        //QString dbPath = QCoreApplication::applicationDirPath()+"//"+name+".db";
        QString dbPath = QCoreApplication::applicationDirPath()+"//"+dbName+".db";
        // 设置数据库文件的名字
        database.setDatabaseName(dbPath);
    }
}

// 打开数据库
bool SqliteOperator::openDb()
{
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        qDebug() << "database opened.";
    }

    return true;
}
void SqliteOperator::initDb(){
    QString peo = "people";
    QString par = "party";
    QString eve = "event";
    QString oth = "other";
    createTable(peo);
    createTable(par);
    createTable(eve);
    createTable(oth);
    createConnectionTable();
}
void SqliteOperator::createTest(){
    QSqlQuery sqlQuery(database);
    QString s = QString("create table test(id int primary key);");
    sqlQuery.prepare(s);
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to create table. " << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "Table created!";
    }
    //sqlQuery.exec("create table test(id int primary key);");
}
// 创建数据表
void SqliteOperator::createTable(QString tableName)
{
    // 用于执行sql语句的对象
    QSqlQuery sqlQuery(database);
    //sqlQuery.exec("create table Addres(id int primary key, name varchar);");
    // 构建创建数据库的sql语句字符串
    QString createSql = QString("CREATE TABLE %1 (\
                          name TEXT PRIMARY KEY NOT NULL,\
                          describe TEXT NOT NULL,\
                          connection TEXT,\
                          istop INTEGER NOT NULL)").arg(tableName);

    sqlQuery.prepare(createSql);
    // 执行sql语句
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to create table. " << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "Table created!";
    }
}
void SqliteOperator::createConnectionTable(){
    QSqlQuery sqlQuery(database);
    QString createSql = QString("CREATE TABLE connection(\
                                aname TEXT NOT NULL,\
                                atype TEXT NOT NULL,\
                                bname TEXT NOT NULL,\
                                btype TEXT NOT NULL,\
                                desribe TEXT)");
    sqlQuery.prepare(createSql);
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to create connection table. " << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "connection table created!";
    }
}

// 判断数据库中某个数据表是否存在
bool SqliteOperator::isTableExist(QString& tableName)
{
    QSqlDatabase database = QSqlDatabase::database();
    if(database.tables().contains(tableName))
    {
        return true;
    }

    return false;
}

// 查询全部数据
void SqliteOperator::queryTable(QString tableName)
{
    QSqlQuery sqlQuery;
    QString qtb = "SELECT * FROM "+tableName;
    sqlQuery.prepare(qtb);
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next())
        {
            QString name = sqlQuery.value(0).toString();
            QString describe = sqlQuery.value(1).toString();
            QString connection = sqlQuery.value(2).toString();
            qDebug()<<QString("query table  name:%1    describe:%2    connection:%3").arg(name).arg(describe).arg(connection);
        }
    }
}
//查询名字返回list
QStringList SqliteOperator::queryName(QString tableName){
    QSqlQuery sqlQuery;
    QStringList ans;
    QString select = "select name from " + tableName + " order by istop";
    sqlQuery.prepare(select);
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query nameList. " << sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next())
        {
            ans.append(sqlQuery.value(0).toString());
        }
    }
    return ans;
}
//查询某个数据显示
w2dba SqliteOperator::queryData(QString tableName,QString n){
    QSqlQuery sqlQuery;
    w2dba ans;
    QString select = "select * from "+tableName+" where name='"+n+"'";
    sqlQuery.prepare(select);
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query this data. " << sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next()){
            ans.name = n;
            ans.describe = sqlQuery.value(1).toString();
            ans.connection = sqlQuery.value(2).toString();
//            qDebug() << "query data successs!" << QString("name:%1    describe:%2    connection:%3").arg(ans.name).arg(ans.describe).arg(ans.connection);
        }
    }
    return ans;
}
//test query.unfinished.
//QStringList SqliteOperator::queryList(){
//    QSqlQuery sqlQuery;
//    QStringList ans;
//    sqlQuery.exec("select * from learn");
//    if(!sqlQuery.exec())
//    {
//        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
//    }
//    else
//    {
//        while(sqlQuery.next())
//        {
//            ans.append(sqlQuery.value(0).toString());
//        }
//    }
//    return ans;
//}
// 插入单条数据
void SqliteOperator::singleInsertData(QString tableName,w2dba &singledb)
{
    QSqlQuery sqlQuery;
    QString insert = "INSERT INTO "+tableName+" VALUES (:name,:describe,:connection,0)";
    sqlQuery.prepare(insert);
    sqlQuery.bindValue(":name", singledb.name);
    sqlQuery.bindValue(":describe", singledb.describe);
    sqlQuery.bindValue(":connection", singledb.connection);
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to insert data. " << sqlQuery.lastError();
    }
    else
    {
        // do something
    }
}
void SqliteOperator::InsertConnection(QString aName, QString aType,QString bName, QString bType,QString describe){
    QSqlQuery sqlQuery;
    QString insert ="INSERT INTO connection VALUES (:aname,:atype,:bname,:btype,:describe)";
    sqlQuery.prepare(insert);
    sqlQuery.bindValue(":aname",aName);
    sqlQuery.bindValue(":atype",aType);
    sqlQuery.bindValue(":bname",bName);
    sqlQuery.bindValue(":btype",bType);
    sqlQuery.bindValue(":describe",describe);
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to insert data. " << sqlQuery.lastError();
    }
    else
    {
        // do something
    }
}
// 插入多条数据
void SqliteOperator::moreInsertData(QString tableName,QList<w2dba>& moredb)
{
    // 进行多个数据的插入时，可以利用绑定进行批处理
    QSqlQuery sqlQuery;
    QString insert = "INSERT INTO "+tableName+" VALUES(?,?,?,0)";
    sqlQuery.prepare(insert);
    QVariantList nameList,describeList,connectionList;
    for(int i=0; i< moredb.size(); i++)
    {
        nameList << moredb.at(i).name;
        describeList << moredb.at(i).describe;
        connectionList << moredb.at(i).connection;
    }
    sqlQuery.addBindValue(nameList);
    sqlQuery.addBindValue(describeList);
    sqlQuery.addBindValue(connectionList);

    if (!sqlQuery.execBatch()) // 进行批处理，如果出错就输出错误
    {
        qDebug() << sqlQuery.lastError();
    }
}

// 修改数据
void SqliteOperator::modifyData(QString tableName,QString name, QString describe,QString connection)
{
    QSqlQuery sqlQuery;
    QString up = "update "+tableName+" set describe=?,connection=? where name='"+name+"'";
    sqlQuery.prepare(up);
    sqlQuery.addBindValue(describe);
    sqlQuery.addBindValue(connection);
    if(!sqlQuery.exec())
    {
        qDebug() <<"update failed:"<< sqlQuery.lastError();
    }
    else
    {
        qDebug() << "updated data success!";
    }
}

// 删除数据
void SqliteOperator::deleteData(QString tableName,QString name)
{
    QSqlQuery sqlQuery;
    QString del = "DELETE FROM "+tableName+" WHERE name = ?";
    sqlQuery.prepare(del);
    sqlQuery.addBindValue(name);
    if(!sqlQuery.exec())
    {
        qDebug()<<"delete error:"<<sqlQuery.lastError();
    }
    else
    {
        qDebug()<<"deleted data success!";
    }
}

//删除数据表
void SqliteOperator::deleteTable(QString& tableName)
{
    QSqlQuery sqlQuery;

    sqlQuery.exec(QString("DROP TABLE %1").arg(tableName));
    if(sqlQuery.exec())
    {
        qDebug() << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "deleted table success";
    }
}

void SqliteOperator::closeDb(void)
{
    database.close();
}

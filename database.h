#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
typedef struct
{
    QString name;
    QString describe;
    QString connection;
}w2dba;

class SqliteOperator
{
public:
    SqliteOperator(QString dbName);
    // 打开数据库
    bool openDb(void);
    void initDb();
    // 创建数据表
    void createTable(QString tableName);
    void createConnectionTable();
    // 判断数据表是否存在
    bool isTableExist(QString& tableName);
    // 查询全部数据
    void queryTable(QString tableName);
    //add new func:return all name
    QStringList queryName(QString tableName);
    w2dba queryData(QString tableName,QString name);
    // 插入数据
    void singleInsertData(QString tableName,w2dba &singleData); // 插入单条数据
    void moreInsertData(QString tableName,QList<w2dba> &moreData); // 插入多条数据
    // 修改数据
    void modifyData(QString tableName,QString name, QString describe,QString connection);
    // 删除数据
    void deleteData(QString tableName,QString name);
    //删除数据表
    void deleteTable(QString& tableName);
    // 关闭数据库
    void closeDb();
    void createTest();
    void InsertConnection(QString aName,QString aType,QString bName,QString bType,QString describe);
private:
    QSqlDatabase database;// 用于建立和数据库的连接
};

#endif // DATABASE_H




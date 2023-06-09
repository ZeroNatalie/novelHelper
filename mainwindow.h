#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QSqlTableModel>
#include <QModelIndex>
#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString bookName,QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QString bookName;
    //QSqlQueryModel *connetionModel = nullptr;
public:
    void setBookName(QString bn);
     QString ChoosenPeopleIndex;
     QString ChoosenPartyIndex;
     QString ChoosenEventIndex;
     //QStandardItemModel* m_standardItemModel;
     QStringListModel *peopleModel;
     QStringListModel *partyModel;
     QStringListModel *eventModel;
     //QSqlTableModel *connectionModel;
     void init();
    SqliteOperator *sqls;
    void initTree();
    void keyPressEvent(QKeyEvent *e);
 private slots:
     void showPeopleClick(QModelIndex index);
     void showPeopleConnection(QModelIndex index);
     void showPartyClick(QModelIndex index);
     void showEventClick(QModelIndex index);
     void exitClick();
     void addNewPeopleClick();
     void deletePeopleClick();
     void on_refreshBtn_clicked();
     void refreshList();
     void on_btnAddParty_clicked();
     void on_btnDeleteParty_clicked();
     void on_btnAddEvent_clicked();
     void on_btnDeleteEvent_clicked();
     void on_btnUpdatePeople_clicked();
     void addNewConnection();
     void addNewOutline();
//     void showOutlineClicked(QModelIndex index);
//     void on_btnAddPeopleConnection_2_clicked();
};
#endif // MAINWINDOW_H

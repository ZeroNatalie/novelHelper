#ifndef ADDNEWCONNECION_H
#define ADDNEWCONNECION_H

#include <QDialog>

namespace Ui {
class addNewConnecion;
}

class addNewConnectionWindow : public QDialog
{
    Q_OBJECT

public:
    explicit addNewConnectionWindow(QString bookName,QWidget *parent = nullptr);
    ~addNewConnectionWindow();
    void setSelectedName(QString);
    void setSelectedType(QString);
    void init();
    QString selectedName;
    QString selectedType;
    QString connectName;
    QString connectType;
private slots:
//    void connectTypeChoose(int index);
    void connectNameChoose();
    void newConnectionClicked();
    void on_connectTypeBox_currentIndexChanged(int index);
    QString getConnectionNote();
private:
    Ui::addNewConnecion *ui;
    QString bookName;
    QString aName;
    QString aType;
    QString bName;
    QString bType;
};

#endif // ADDNEWCONNECION_H

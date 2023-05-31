#ifndef ADDNEWCONNECION_H
#define ADDNEWCONNECION_H

#include <QDialog>

namespace Ui {
class addNewConnecion;
}

class addNewConnecion : public QDialog
{
    Q_OBJECT

public:
    explicit addNewConnecion(QString bookName,QWidget *parent = nullptr);
    ~addNewConnecion();
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

#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
//include for database
#include <QtSql/QSqlDatabase>
#include <QCoreApplication>
#include <QDebug>
#include <QStringList>
#include "database.h"
#include "bookchoose.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    //qDebug() << "drivers:";
    //qDebug() << QSqlDatabase::drivers();
    //drivers:QList("QSQLITE", "QODBC", "QPSQL"),qsqlite=sqlitev3
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "learn_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
//    MainWindow w;
//    w.show();
    Book b;
    b.show();
    return a.exec();
}

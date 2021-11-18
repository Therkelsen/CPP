#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include <string>
#include <QtSql>
#include <QSqlDatabase>
#include <QCoreApplication>
#include <QSqlDriver>
#include <QString>

class Database
{
public:
    Database();
    void insertData(QString regnr, QString model, int aar);
    void extractData();
    unsigned int countEntries();
    void clearDatabase();
    void disconnect();

private:
    QSqlDatabase db;
    unsigned int entries = 0;
};

#endif // DATABASE_H

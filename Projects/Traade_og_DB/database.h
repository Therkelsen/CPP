#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include <iomanip>
#include <string>

#include <QtSql>
#include <QString>
#include <QSqlDriver>
#include <QSqlDatabase>
#include <QCoreApplication>

class Database
{
public:
    Database();
    void openDatabase();
    void createTable();
    void insertData(QString regnr, QString model, int aar);
    void extractData();
    std::string extractHighestRegNr();
    unsigned int countRows();
    void clearTable();
    void clearDatabase();
    void disconnect();

private:
    QSqlDatabase db;
    unsigned int rows = 0;
};

#endif // DATABASE_H

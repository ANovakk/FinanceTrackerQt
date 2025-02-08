#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QString>
#include <QDebug>
#include <QList>
#include "transaction.h"

class Database {
public:
    Database();
    ~Database();

    bool open();
    void createTable();
    void insertTransaction(const Transaction &transaction);
    QList<Transaction> getAllTransactions();
    QList<Transaction> getTransactionsByDate(const QString &date);
    QList<Transaction> getTransactionsByCategory(const QString &category);
    QList<Transaction> getFilteredTransactions(
        const QString &type,
        const QString &category,
        const QString &date,
        const QString &month,
        const QString &year);

private:
    QSqlDatabase db;
};

#endif // DATABASE_H

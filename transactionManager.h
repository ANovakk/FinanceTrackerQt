#ifndef TRANSACTIONMANAGER_H
#define TRANSACTIONMANAGER_H

#include "database.h"
#include "transaction.h"
#include <QList>

class TransactionManager {
public:
    TransactionManager(Database &db);

    void addTransaction(const Transaction &transaction);
    QList<Transaction> getAllTransactions();
    QList<Transaction> getTransactionsByCategory(const QString &category);
    QList<Transaction> getTransactionsByDate(const QString &date);
    QList<Transaction> getFilteredTransactions(
        const QString &type,
        const QString &category,
        const QString &date,
        const QString &month,
        const QString &year);

private:
    Database &db;
};

#endif // TRANSACTIONMANAGER_H

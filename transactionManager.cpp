#include "transactionManager.h"

TransactionManager::TransactionManager(Database &db) : db(db) {}

void TransactionManager::addTransaction(const Transaction &transaction) {
    db.insertTransaction(transaction);
}

QList<Transaction> TransactionManager::getAllTransactions() {
    return db.getAllTransactions();
}

QList<Transaction> TransactionManager::getTransactionsByCategory(const QString &category) {
    return db.getTransactionsByCategory(category);
}

QList<Transaction> TransactionManager::getTransactionsByDate(const QString &date) {
    return db.getTransactionsByDate(date);
}

QList<Transaction> TransactionManager::getFilteredTransactions(
    const QString &type,
    const QString &category,
    const QString &date,
    const QString &month,
    const QString &year) {
    return db.getFilteredTransactions(type, category, date, month, year);
}

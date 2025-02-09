#include <QDate>
#include <QApplication>
#include "database.h"
#include "transaction.h"
#include "transactionManager.h"
#include "mainwindow.h"

void print_transactions(QList<Transaction> transactions) {
    for (const Transaction &t : transactions) {
        qDebug() << "ID:" << t.getId()
        << "Type:" << t.getType()
        << "Amount:" << t.getAmount()
        << "Category:" << t.getCategory()
        << "Date:" << t.getDate()
        << "Note:" << t.getNote()
        << "Currency:" << t.getCurrency();
    }
    qDebug() << "";
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Database db;
    db.open();
    db.createTable();

    TransactionManager transactionManager(db);

    MainWindow w(transactionManager);
    w.show();

    // QList<Transaction> transactions_add = {
    //     Transaction("Income", 120, "Games", "2022-12-12", "Minecraft", "USD")};
    //
    // for (Transaction& transaction : transactions_add) {
    //     transactionManager.addTransaction(transaction);
    // }

    QList<Transaction> transactions;
    transactions = transactionManager.getAllTransactions();
    print_transactions(transactions);

    qDebug() << "Transactions by date";
    QString currentDate = "2021-02-06";
    transactions = transactionManager.getTransactionsByDate(currentDate);
    print_transactions(transactions);

    qDebug() << "Transactions by category";
    QString currentCategory = "Car";
    transactions = transactionManager.getTransactionsByCategory(currentCategory);
    print_transactions(transactions);


    transactions = transactionManager.getFilteredTransactions("", "", "", "04", "2025");
    qDebug() << "Transactions: 2025";
    print_transactions(transactions);

    transactions = transactionManager.getFilteredTransactions("Income", "", "", "", "2024");
    qDebug() << "Transactions: Income 2025";
    print_transactions(transactions);

    transactions = transactionManager.getFilteredTransactions("", "Freelance", "", "", "");
    qDebug() << "Transactions: Games";
    print_transactions(transactions);

    return app.exec();
}

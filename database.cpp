#include "database.h"
#include <QCoreApplication>
#include <QDebug>

Database::Database() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString path = "/Users/andreynovak/CLionProjects/FinanceTrackerQt/database.db";
    qDebug() << path;
    db.setDatabaseName(path);
}

Database::~Database() {
    if (db.isOpen()) {
        db.close();
    }
}

bool Database::open() {
    if (!db.open()) {
        qDebug() << "Error: Unable to open database!" << db.lastError().text();
        return false;
    }
    return true;
}

void Database::createTable() {
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS transactions ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "type TEXT, "
               "amount REAL, "
               "category TEXT,"
               "date TEXT,"
               "note TEXT,"
               "currency TEXT)");
}

void Database::insertTransaction(const Transaction &transaction) {
    QSqlQuery query;
    query.prepare("INSERT INTO transactions (type, amount, category, date, note, currency) "
                  "VALUES (:type, :amount, :category, :date, :note, :currency)");
    query.bindValue(":type", transaction.getType());
    query.bindValue(":amount", transaction.getAmount());
    query.bindValue(":category", transaction.getCategory());
    query.bindValue(":date", transaction.getDate());
    query.bindValue(":note", transaction.getNote());
    query.bindValue(":currency", transaction.getCurrency());

    if (!query.exec()) {
        qDebug() << "Error: Unable to insert transaction!" << query.lastError().text();
    }
}

QList<Transaction> Database::getAllTransactions() {
    QList<Transaction> transactions;
    QSqlQuery query("SELECT * FROM transactions");
    while (query.next()) {
        int id = query.value(0).toInt();
        QString type = query.value(1).toString();
        double amount = query.value(2).toDouble();
        QString category = query.value(3).toString();
        QString date = query.value(4).toString();
        QString note = query.value(5).toString();
        QString currency = query.value(6).toString();

        Transaction transaction(type, amount, category, date, note, currency);
        transaction.setId(id);

        transactions.append(transaction);
    }
    return transactions;
}

QList<Transaction> Database::getTransactionsByCategory(const QString &category) {
    QList<Transaction> transactions;

    QString queryStr = "SELECT * FROM transactions WHERE category = :category";
    QSqlQuery query;
    query.prepare(queryStr);
    query.bindValue(":category", category);

    if (query.exec()) {
        while (query.next()) {
            int id = query.value(0).toInt();
            QString type = query.value(1).toString();
            double amount = query.value(2).toDouble();
            QString category = query.value(3).toString();
            QString date = query.value(4).toString();
            QString note = query.value(5).toString();
            QString currency = query.value(6).toString();

            Transaction transaction(type, amount, category, date, note, currency);
            transaction.setId(id);

            transactions.append(transaction);
        }
    } else {
        qDebug() << "Error: Unable to execute query!" << query.lastError().text();
    }

    return transactions;
}

QList<Transaction> Database::getTransactionsByDate(const QString &date) {
    QList<Transaction> transactions;

    QString queryStr = "SELECT * FROM transactions WHERE date = :date";
    QSqlQuery query;
    query.prepare(queryStr);
    query.bindValue(":date", date);

    if (query.exec()) {
        while (query.next()) {
            int id = query.value(0).toInt();
            QString type = query.value(1).toString();
            double amount = query.value(2).toDouble();
            QString category = query.value(3).toString();
            QString date = query.value(4).toString();
            QString note = query.value(5).toString();
            QString currency = query.value(6).toString();

            Transaction transaction(type, amount, category, date, note, currency);
            transaction.setId(id);

            transactions.append(transaction);
        }
    } else {
        qDebug() << "Error: Unable to execute query!" << query.lastError().text();
    }

    return transactions;
}

QList<Transaction> Database::getFilteredTransactions(
    const QString &type,
    const QString &category,
    const QString &date,
    const QString &month,
    const QString &year)
{
    QList<Transaction> transactions;
    QSqlQuery query;
    QString queryStr = "SELECT * FROM transactions WHERE 1=1";

    if (!type.isEmpty()) {
        queryStr += " AND type = :type";
    }
    if (!category.isEmpty()) {
        queryStr += " AND category = :category";
    }
    if (!date.isEmpty()) {
        queryStr += " AND date LIKE :date";
    }
    if (!month.isEmpty()) {
        queryStr += " AND strftime('%m', date) = :month";
    }
    if (!year.isEmpty()) {
        queryStr += " AND strftime('%Y', date) = :year";
    }

    query.prepare(queryStr);

    if (!type.isEmpty()) {
        query.bindValue(":type", type);
    }
    if (!category.isEmpty()) {
        query.bindValue(":category", category);
    }
    if (!date.isEmpty()) {
        query.bindValue(":date", date);
    }
    if (!month.isEmpty()) {
        query.bindValue(":month", month);
    }
    if (!year.isEmpty()) {
        query.bindValue(":year", year);
    }

    if (query.exec()) {
        while (query.next()) {
            int id = query.value(0).toInt();
            QString type = query.value(1).toString();
            double amount = query.value(2).toDouble();
            QString category = query.value(3).toString();
            QString date = query.value(4).toString();
            QString note = query.value(5).toString();
            QString currency = query.value(6).toString();
            Transaction transaction(type, amount, category, date, note, currency);
            transaction.setId(id);

            transactions.append(transaction);
        }
    } else {
        qDebug() << "Error: Unable to execute query!" << query.lastError().text();
    }

    return transactions;
}

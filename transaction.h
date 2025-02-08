#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>

class Transaction {
public:
    Transaction();
    Transaction(const QString &type, double amount, const QString &category,
                const QString &date, const QString &note, const QString &currency);

    int getId() const;
    void setId(int id);

    QString getType() const;
    void setType(const QString &type);

    double getAmount() const;
    void setAmount(double amount);

    QString getCategory() const;
    void setCategory(const QString &category);

    QString getDate() const;
    void setDate(const QString &date);

    QString getNote() const;
    void setNote(const QString &note);

    QString getCurrency() const;
    void setCurrency(const QString &currency);


private:
    int id;
    QString type;
    double amount;
    QString category;
    QString date;
    QString note;
    QString currency;
};

#endif // TRANSACTION_H

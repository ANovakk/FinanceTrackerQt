#include "transaction.h"

Transaction::Transaction() : id(0), amount(0.0) {}

Transaction::Transaction(const QString &type, double amount, const QString &category,
                         const QString &date, const QString &note, const QString &currency)
    : id(-1), type(type), amount(amount), category(category),
    date(date), note(note), currency(currency){}

int Transaction::getId() const {
    return id;
}

void Transaction::setId(int id) {
    this->id = id;
}

QString Transaction::getType() const {
    return type;
}

void Transaction::setType(const QString &type) {
    this->type = type;
}

double Transaction::getAmount() const {
    return amount;
}

void Transaction::setAmount(double amount) {
    this->amount = amount;
}

QString Transaction::getCategory() const {
    return category;
}

void Transaction::setCategory(const QString &category) {
    this->category = category;
}

QString Transaction::getDate() const {
    return date;
}

void Transaction::setDate(const QString &date) {
    this->date = date;
}

QString Transaction::getNote() const {
    return note;
}

void Transaction::setNote(const QString &note) {
    this->note = note;
}

QString Transaction::getCurrency()const {
    return currency;
}

void Transaction::setCurrency(const QString &currency) {
    this->currency = currency;
}

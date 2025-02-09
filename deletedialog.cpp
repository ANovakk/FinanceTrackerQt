#include "deletedialog.h"
#include <QVBoxLayout>
#include <QDebug>

DeleteDialog::DeleteDialog(QWidget *parent)
    : QDialog(parent) {
    setWindowTitle("Transaction");
    setFixedSize(200, 100);

    deleteButton = new QPushButton("Delete", this);
    connect(deleteButton, &QPushButton::clicked, this, &DeleteDialog::onDeleteClicked);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(deleteButton);
    setLayout(layout);
}

void DeleteDialog::onDeleteClicked() {
    qDebug() << "Delete clicked!";
    this->close();
}

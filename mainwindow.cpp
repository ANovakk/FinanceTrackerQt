#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->buttonOverviewPage, &QPushButton::clicked, this, &MainWindow::showPageOverview);
    connect(ui->buttonTransactionsPage, &QPushButton::clicked, this, &MainWindow::showPageTransactions);
    connect(ui->buttonAddTransaction, &QPushButton::clicked, this, &MainWindow::addTransaction);
    this->setFocus();

    setupModel();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setupModel() {
    model = new QSqlTableModel(this);
    model->setTable("transactions");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
}

void MainWindow::showPageOverview() {
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::showPageTransactions() {
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::addTransaction() {
    QString type = ui->TransactionType->currentText();
    QString amount = ui->TransactionAmount->toPlainText();
    QString category = ui->TransactionCategory->currentText();
    QDate date = ui->TransactionDate->date();
    QString note = ui->TransactionNote->toPlainText();
    QString currency = ui->TransactionCurrency->currentText();

    if (amount.isEmpty() || category.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all the fields.");
        return;
    }

    ui->TransactionAmount->clear();
    ui->TransactionCategory->setCurrentIndex(0);
    ui->TransactionNote->clear();

    qDebug() << type;
    qDebug() << amount;
    qDebug() << category;
    qDebug() << date;
    qDebug() << note;
    qDebug() << currency;
}

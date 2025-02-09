#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "customdelegate.h"
#include <QMessageBox>
#include <QStringListModel>

MainWindow::MainWindow(TransactionManager &transactionManager, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), transactionManager(transactionManager) {
    ui->setupUi(this);

    connect(ui->buttonOverviewPage, &QPushButton::clicked, this, &MainWindow::showPageOverview);
    connect(ui->buttonTransactionsPage, &QPushButton::clicked, this, &MainWindow::showPageTransactions);
    connect(ui->buttonAddTransaction, &QPushButton::clicked, this, &MainWindow::addTransaction);

    // Delete focus from any field
    this->setFocus();

    // Set current date
    ui->TransactionDate->setDate(QDate::currentDate());

    setupModel();
    setupListViewModel();
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

void MainWindow::setupListViewModel() {
    listViewModel = new QStringListModel(this);

    QStringList transactionList;

    for (const Transaction &transaction : transactionManager.getAllTransactions()) {
        QString transactionInfo = QString("Type: %1 | Amount: %2 | Date: %3")
                                      .arg(transaction.getType())
                                      .arg(transaction.getAmount())
                                      .arg(transaction.getDate());
        transactionList.append(transactionInfo);
    }

    listViewModel->setStringList(transactionList);
    ui->listView->setModel(listViewModel);

    // Disable editing for QListView
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    CustomDelegate *delegate = new CustomDelegate(this);
    ui->listView->setItemDelegate(delegate);

    connect(delegate, &CustomDelegate::deleteButtonClicked, this, &MainWindow::onDeleteButtonClicked);

    ui->listView->setStyleSheet(
        "QListView::item {"
        "    height: 60px;"
        "}"
    );
}

void MainWindow::onDeleteButtonClicked(int row) {
    qDebug() << "Delete requested for row:" << row;
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

    Transaction transaction = Transaction(type, amount.toDouble(), category, date.toString("yyyy-MM-dd"), note, currency);

    transactionManager.addTransaction(transaction);
    model->select();
    ui->tableView->resizeColumnsToContents();
}

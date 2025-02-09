#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->buttonOverviewPage, &QPushButton::clicked, this, &MainWindow::showPageOverview);
    connect(ui->buttonTransactionsPage, &QPushButton::clicked, this, &MainWindow::showPageTransactions);

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

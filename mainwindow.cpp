#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

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

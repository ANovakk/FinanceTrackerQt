#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QStringListModel>
#include "database.h"
#include "transactionManager.h"
#include "customdelegate.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(TransactionManager &transactionManager, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSqlTableModel *model;
    QStringListModel *listViewModel;
    TransactionManager &transactionManager;

    void setupModel();
    void setupListViewModel();
    void showPageOverview();
    void showPageTransactions();
    void addTransaction();
};
#endif // MAINWINDOW_H

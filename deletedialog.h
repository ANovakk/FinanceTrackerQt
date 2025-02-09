#ifndef DELETEDIALOG_H
#define DELETEDIALOG_H

#include <QDialog>
#include <QPushButton>

class DeleteDialog : public QDialog {
    Q_OBJECT

public:
    explicit DeleteDialog(QWidget *parent = nullptr);

private slots:
    void onDeleteClicked();

private:
    QPushButton *deleteButton;
};

#endif // DELETEDIALOG_H

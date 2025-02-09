#ifndef CUSTOMDELEGATE_H
#define CUSTOMDELEGATE_H

#include <QStyledItemDelegate>
#include <QPushButton>
#include <QPainter>
#include <QApplication>
#include <QMouseEvent>
#include <QDebug>

class CustomDelegate : public QStyledItemDelegate {
    Q_OBJECT

public:
    explicit CustomDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;
};

#endif // CUSTOMDELEGATE_H
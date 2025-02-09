#include "customdelegate.h"

CustomDelegate::CustomDelegate(QObject *parent)
    : QStyledItemDelegate(parent) {}

void CustomDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QStyledItemDelegate::paint(painter, option, index);

    QStyleOptionButton button;
    button.rect = QRect(option.rect.right() - 50, option.rect.top(), 40, option.rect.height());
    button.text = "Click";
    button.state = QStyle::State_Enabled;

    QApplication::style()->drawControl(QStyle::CE_PushButton, &button, painter);
}

bool CustomDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) {
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            QRect buttonRect(option.rect.right() - 50, option.rect.top(), 40, option.rect.height());
            if (buttonRect.contains(mouseEvent->pos())) {
                qDebug() << "Button clicked for row:" << index.row();
                return true;
            }
        }
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}
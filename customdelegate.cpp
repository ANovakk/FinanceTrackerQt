#include "customdelegate.h"
#include "deletedialog.h"

CustomDelegate::CustomDelegate(QObject *parent)
    : QStyledItemDelegate(parent), lastClickedRow(-1) {}

void CustomDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QStyledItemDelegate::paint(painter, option, index);

    QRect buttonRect(option.rect.right() - 50, option.rect.top(), 40, option.rect.height());

    painter->save();
    painter->setPen(Qt::black);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(buttonRect);
    painter->restore();

    QStyleOptionButton button;
    button.rect = buttonRect;
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
                lastClickedRow = index.row();

                DeleteDialog *dialog = new DeleteDialog();
                connect(dialog, &DeleteDialog::accepted, this, [this]() {
                    emit deleteButtonClicked(lastClickedRow);
                });
                dialog->exec();

                return true;
            }
        }
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

QSize CustomDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QSize size = QStyledItemDelegate::sizeHint(option, index);
    size.setHeight(60);
    return size;
}
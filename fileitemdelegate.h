#ifndef FILEITEMDELEGATE_H
#define FILEITEMDELEGATE_H
#include <QStyledItemDelegate>
#include <QPushButton>
class FileItemDelegate : public QStyledItemDelegate
{
public:
    FileItemDelegate(QObject * parent = 0);

    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // FILEITEMDELEGATE_H

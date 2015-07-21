#ifndef FILEITEMDELEGATE_H
#define FILEITEMDELEGATE_H
#include <QItemDelegate>
#include <QStyledItemDelegate>
#include <QPushButton>
#include "filemodel.h"
class FileItemDelegate : public QStyledItemDelegate
{
public:
    FileItemDelegate(QObject * parent = 0);


virtual void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;

};

#endif // FILEITEMDELEGATE_H

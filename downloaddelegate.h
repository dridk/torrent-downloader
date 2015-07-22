#ifndef FILEITEMDELEGATE_H
#define FILEITEMDELEGATE_H
#include <QItemDelegate>
#include <QStyledItemDelegate>
#include <QPushButton>
#include "downloadmodel.h"
class DownloadDelegate : public QStyledItemDelegate
{
public:
    DownloadDelegate(QObject * parent = 0);


virtual void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;

    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

};

#endif // FILEITEMDELEGATE_H

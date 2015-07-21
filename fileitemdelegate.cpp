#include "fileitemdelegate.h"

FileItemDelegate::FileItemDelegate(QObject * parent)
    :QStyledItemDelegate(parent)
{

}

QWidget *FileItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    if ( index.column() == 3 )
        return new QPushButton("test", parent);



    return QStyledItemDelegate::createEditor(parent, option,index);
}


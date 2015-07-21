#include "fileitemdelegate.h"
#include <QStyleOptionProgressBar>
#include <QApplication>
#include <QDebug>
#include <QPainter>
FileItemDelegate::FileItemDelegate(QObject * parent)
    :QStyledItemDelegate(parent)
{

}

void FileItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{


    if (index.column() == FileModel::PROGRESS_COL)
    {
        int progress = index.data().toInt();


        if (progress > 0 && progress < 100 ) {
            QStyleOptionProgressBar barOption;

            barOption.minimum = 0;
            barOption.maximum = 100;
            barOption.textAlignment = Qt::AlignCenter;
            barOption.textVisible = true;
            barOption.text = QString("Downloading %1").arg(progress);
            barOption.rect = option.rect.adjusted(5,5,-5,-5);
            barOption.progress =  progress;
            QApplication::style()->drawControl(QStyle::CE_ProgressBar, &barOption,painter);
        }

        else {

//            painter->drawText(option.rect, Qt::AlignHCenter, QString("click to download"));
            QStyledItemDelegate::paint(painter, option, index);


        }





    }

    else
        QStyledItemDelegate::paint(painter, option, index);
}

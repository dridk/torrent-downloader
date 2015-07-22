#include "downloaddelegate.h"
#include <QStyleOptionProgressBar>
#include <QApplication>
#include <QDebug>
#include <QIcon>
#include <QPainter>
DownloadDelegate::DownloadDelegate(QObject * parent)
    :QStyledItemDelegate(parent)
{

}

void DownloadDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    QString name   =  index.data(Qt::DisplayRole).toString();
    float progress =  index.data(DownloadModel::ProgressRole).toFloat();
    int bytes      =  index.data(DownloadModel::ByteRole).toInt();
    int total      =  index.data(DownloadModel::TotalRole).toInt();
    float speed    =  index.data(DownloadModel::SpeedRole).toFloat();
    QString status =  index.data(DownloadModel::StatusRole).toString();
    QString remains=  index.data(DownloadModel::RemainingRole).toString();


    if (option.state & QStyle::State_Selected)
        painter->fillRect(option.rect, option.palette.highlight());

    else
        painter->fillRect(option.rect, option.palette.light());


    QPen pen ;
    pen.setColor(Qt::lightGray);
    pen.setStyle(Qt::DotLine);
    painter->setPen(pen);

    painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());


    painter->setPen(QPen(Qt::black));

    QStyleOptionProgressBar barOption;


    int height = 20;
    int marge  = 60;
    barOption.minimum = 0;
    barOption.maximum = 100;
    barOption.textAlignment = Qt::AlignCenter;
    barOption.textVisible = true;
    barOption.text = QString("Downloading %1").arg(progress);
    barOption.rect.setLeft(option.rect.left() + marge);
    barOption.rect.setRight(option.rect.right() - marge);
    barOption.rect.setTop(option.rect.top() + height +5);
    barOption.rect.setHeight(height);
    barOption.progress =  progress;

    QIcon icon = index.data(Qt::DecorationRole).value<QIcon>();

    if (!icon.isNull())
        painter->drawPixmap(option.rect.x()+10,option.rect.y()+20,icon.pixmap(32,32));

    painter->drawText(barOption.rect.x(),barOption.rect.top()-5,QString(name));
    painter->drawText(barOption.rect.x(),barOption.rect.bottom()+15,QString("%1 %2 of %3 at %4 KB/sec; %5 remain")
                                                                            .arg(status).arg(bytes).arg(total).arg(speed).arg(remains)  );


    QApplication::style()->drawControl(QStyle::CE_ProgressBar, &barOption,painter);

    QApplication::style()->drawPrimitive(QStyle::PE_PanelItemViewRow, &option, painter);



}

QSize DownloadDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    return QSize(option.rect.width(), 75);


}

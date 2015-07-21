#include "runmodel.h"
#include <QDebug>
RunModel::RunModel(QObject * parent)
    :QAbstractTableModel(parent)
{

    mOffset = 0;

}

int RunModel::rowCount(const QModelIndex &parent) const
{


    return mDatas.size();

}

int RunModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant RunModel::data(const QModelIndex &index, int role) const
{

    if (!index.isValid())
        return QVariant();

    if ( role == Qt::DisplayRole)
    {

        if(index.column() == NAME_COL)
            return mDatas.at(index.row()).name;

        if(index.column() == DATE_COL)
            return mDatas.at(index.row()).date.toString("dd MMM yyyy hh:mm");

    }


    return QVariant();

}

void RunModel::load()
{

    mDatas.clear();


    QNetworkReply * reply =  TorrentServerManager::i()->getRunList(mOffset);

    connect(reply,SIGNAL(finished()),this,SLOT(loadded()));



}

void RunModel::nextPage()
{
    if (mOffset * mLimit < mTotalCount)
    {
        mOffset++;
        load();
    }


}

void RunModel::prevPage()
{
    if ( mOffset > 0)
    {
        mOffset--;
        load();
    }
}

void RunModel::loadded()
{
    mDatas.clear();
    beginResetModel();

    qDebug()<<"received";
    QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());


    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());


    mTotalCount = document.object().value("meta").toObject().value("total_count").toInt();
    mLimit      = document.object().value("meta").toObject().value("limit").toInt();
    mOffset     = document.object().value("meta").toObject().value("offset").toInt();

    qDebug()<<Q_FUNC_INFO<<"total "<<mTotalCount;

    QJsonArray array = document.object().value("objects").toArray();

    foreach (QJsonValue value, array)
    {

        RunItem item;
        item.name         = value.toObject().value("resultsName").toString();
        item.date         = QDateTime::fromString(value.toObject().value("timeStamp").toString(),Qt::ISODate);
        item.id           = value.toObject().value("id").toInt();
        item.reportLink   = QUrl(value.toObject().value("reportLink").toString());

        mDatas.append(item);

    }


    endResetModel();



}


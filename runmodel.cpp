#include "runmodel.h"
#include <QDebug>
#include <QIcon>
RunModel::RunModel(QObject * parent)
    :QAbstractTableModel(parent)
{

    mOffset = 0;
    QStringList statusList;
    statusList<<"Calibration"<<"Signal Processing"<<"Complete";
}

int RunModel::rowCount(const QModelIndex &parent) const
{


    return mDatas.size();

}

int RunModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant RunModel::data(const QModelIndex &index, int role) const
{

    if (!index.isValid())
        return QVariant();

    if ( role == Qt::DisplayRole)
    {

        if(index.column() == NAME_COL)
            return mDatas.at(index.row()).name;

        if(index.column() == STATUS_COL){
            return mDatas.at(index.row()).status;
}

        if(index.column() == DATE_COL)
            return mDatas.at(index.row()).date.toString("dd MMM yyyy hh:mm");

    }

    if ( role == Qt::DecorationRole)
    {
        if ( index.column() == 0)
            return QIcon(":/icons/folder.png");

        if (index.column() == STATUS_COL)
        {
            if (mDatas.at(index.row()).status == "Completed")
                return QIcon(":/icons/bullet_valid.png");

            if (mDatas.at(index.row()).status == "Signal Processing")
                return QIcon(":/icons/progressbar.png");

        }
    }

    return QVariant();

}

QVariant RunModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if( role == Qt::DisplayRole)
 {
     if (section == NAME_COL)
         return "Name";
     if ( section == DATE_COL)
         return "Date";
    if (section == STATUS_COL)
        return "Status";

 }

 return QVariant();
}

const RunItem &RunModel::item(const QModelIndex &index)
{
    if (!index.isValid())
        return RunItem();

    else
        return mDatas.at(index.row());


}

void RunModel::load()
{

    mDatas.clear();


    QNetworkReply * reply =  TorrentServerManager::i()->getResultList(mOffset);

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
        item.status       = value.toObject().value("status").toString();
        mDatas.append(item);

    }


    endResetModel();

    emit finished();


}


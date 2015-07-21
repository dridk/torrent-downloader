#include "filemodel.h"

FileModel::FileModel(QObject *parent)
    :QAbstractTableModel(parent)
{
    mPending = false;
}

int FileModel::rowCount(const QModelIndex &parent) const
{
    return mDatas.count();
}

int FileModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant FileModel::data(const QModelIndex &index, int role) const
{

    if (!index.isValid())
        return QVariant();


    if (role == Qt::DisplayRole)
    {

        if (index.column() == EXT_COL)
        return mDatas.at(index.row()).ext;

        if (index.column() == BARCODE_COL)
            return mDatas.at(index.row()).barcode;

        if (index.column() == SAMPLE_COL)
            return mDatas.at(index.row()).sample;

        if (index.column() == PROGRESS_COL)
            return mDatas.at(index.row()).progress;
    }

    if ( role == Qt::CheckStateRole)
    {
        if (index.column() == 0)
            return mDatas.at(index.row()).checked;
    }


    return QVariant();

}

bool FileModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;
    if (role == Qt::CheckStateRole)
    {
        qDebug()<<value;
            mDatas[index.row()].checked = !mDatas[index.row()].checked;



    }
return true;
}

Qt::ItemFlags FileModel::flags(const QModelIndex &index) const
{

    if (index.column() == 0)
        return Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable;

        return Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsUserCheckable;

}

void FileModel::load(int resultId)
{
    if (!mPending) {
        QNetworkReply * reply =  TorrentServerManager::i()->getResult(resultId);
        connect(reply,SIGNAL(finished()),this,SLOT(loadded()));
        mDatas.clear();
        mPending = true;
    }

}

void FileModel::loadded()
{
    qDebug()<<"file received";
    mDatas.clear();
    beginResetModel();


    QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());

    QString data = QString::fromUtf8(reply->readAll());

    // Load BAM / BAI File
    QRegularExpression expression("var barcodes_json.+]");
    QRegularExpressionMatch match = expression.match(data);

    if ( match.hasMatch())
    {
        QString json = match.captured();
        json = json.remove(QRegularExpression("var barcodes_json.="));

        QJsonParseError error;

        QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8(), &error);
     qDebug()<<Q_FUNC_INFO<<"bam list size "<<doc.array().size();
        foreach (QJsonValue value, doc.array())
        {
            FileItem item;
            item.barcode = value.toObject().value("barcode_name").toString();
            item.sample  = value.toObject().value("sample").toString();
            item.checked = false;
            item.link    = QUrl(value.toObject().value("bam_link").toString());
            item.ext     = "bam";



            if (!item.link.isEmpty())
                mDatas.append(item);

        }



    }



    endResetModel();
    mPending = false;
    emit finished();

}


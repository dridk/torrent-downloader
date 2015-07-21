#include "filemodel.h"
#include <QIcon>
#include <QFont>
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

    if (role == Qt::DecorationRole)
    {
        if ( index.column() == BARCODE_COL)
            return QIcon(":/icons/barcode_2d.png");

        if (index.column() == SAMPLE_COL)
            return QIcon(":/icons/user_nude.png");
    }

    if ( role == Qt::CheckStateRole)
    {
        if (index.column() == 0)
            return mDatas.at(index.row()).checked;
    }


    if ( role == Qt::FontRole)
    {
        QFont font;
        if ( mDatas.at(index.row()).checked)
            font.setBold(true);
        return font;
    }

    return QVariant();

}

bool FileModel::setData(const QModelIndex &idx, const QVariant &value, int role)
{
    if (!idx.isValid())
        return false;
    if (role == Qt::CheckStateRole)
    {
        if ( idx.column() == 0){
            mDatas[idx.row()].checked = !mDatas[idx.row()].checked;
            emit dataChanged(index(idx.row(),0), index(idx.row(), columnCount()));
            emit checkedCountChanged(checkedCount());
        }

    }


    if (role == Qt::EditRole)
    {
        if (idx.column() == PROGRESS_COL)
        {

            mDatas[idx.row()].progress = value.toFloat();
            emit dataChanged(index(idx.row(),0), index(idx.row(), columnCount()));



        }

    }

    return true;
}

QVariant FileModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if ( orientation == Qt::Horizontal)
    {
        if ( role == Qt::DisplayRole)
        {
            if (section == EXT_COL)
                return QString(tr("Type"));
            if (section == BARCODE_COL)
                return QString(tr("Barcode"));
            if (section == SAMPLE_COL)
                return QString(tr("Sample"));
            if (section == PROGRESS_COL)
                return QString(tr("Download"));


        }



    }
    return QVariant();
}

Qt::ItemFlags FileModel::flags(const QModelIndex &index) const
{

    if (index.column() == 0)
        return Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable;

    return Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsUserCheckable;

}

void FileModel::clearProgress()
{
    beginResetModel();

    for (int i=0; i<count(); ++i){
        mDatas[i].progress = 0;
        mDatas[i].checked = false;

    }

    endResetModel();

}

int FileModel::count() const
{
    return mDatas.size();
}

int FileModel::checkedCount() const
{
    int total = 0;
    foreach (FileItem item, mDatas)
    {
        if (item.checked)
            total++;
    }

    return total;
}

FileItem &FileModel::item(int row)
{
    return mDatas[row];
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


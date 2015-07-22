#include "downloadmodel.h"
#include <QFileInfo>
#include <QDebug>
#include <QIcon>
#include <QMutableListIterator>
DownloadModel::DownloadModel()
{

    mDest = QDir("C:/tmp/torrentdownloader");
    mDest.mkdir(mDest.path());
}

int DownloadModel::rowCount(const QModelIndex &parent) const
{
    return mItems.count();
}

QVariant DownloadModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();


    if ( role == Qt::DisplayRole)
        return  mItems.value(index.row())->basename;



    if ( role == Qt::DecorationRole)
        return  QIcon(":/icons/folder.png");


    if ( role == ProgressRole)
        return mItems.value(index.row())->progress;

    if ( role == ByteRole)
        return mItems.value(index.row())->bytes;

    if ( role == TotalRole)
        return mItems.value(index.row())->totalBytes;

    if ( role == SpeedRole)
        return mItems.value(index.row())->speed;

    if ( role == StatusRole)
        return mItems.value(index.row())->status;

    if ( role == RemainingRole)
        return mItems.value(index.row())->remaining;



    return QVariant();
}

QNetworkReply *DownloadModel::add(const QUrl &url)
{

    QNetworkReply * reply  = NULL;
    QFileInfo info(url.path());

    QFile * file = new QFile(mDest.absoluteFilePath(info.baseName()));

    if ( file->open(QIODevice::WriteOnly|QIODevice::Append)) {

        qDebug()<<"salut";

        reply = TorrentServerManager::i()->getFile(url);
        qDebug()<<reply;

        DownloadItem * item = new DownloadItem;
        item->reply = reply;
        item->basename = info.baseName();
        item->url = url;
        item->file = file;
        item->progress = 0;
        item->status = "Downloading";

        beginResetModel();
        mItems.append(item);
        mHashs.insert(reply, item);
        endResetModel();

        connect(reply,SIGNAL(readyRead()),this,SLOT(write()));
        connect(reply,SIGNAL(finished()),this,SLOT(finished()));
        connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(downloadProgress(qint64,qint64)));

    }

    else
        qDebug()<<Q_FUNC_INFO<<"cannot open file";


    return reply;
}

void DownloadModel::clear()
{
    beginResetModel();

    QMutableListIterator<DownloadItem *> i(mItems);
    while (i.hasNext()) {
        DownloadItem * val = i.next();
        if (!val->file->isOpen())
            i.remove();
    }


    endResetModel();
}

void DownloadModel::cancel(const QModelIndex &index)
{
    if (!index.isValid())
        return;

    QNetworkReply * reply = mItems.value(index.row())->reply;

    if (reply->isRunning())
        reply->abort();


}

void DownloadModel::write()
{
    qDebug()<<"write";
    QNetworkReply * reply = qobject_cast<QNetworkReply*> (sender());

    if (mHashs.contains(reply))
    {
        mHashs[reply]->file->write(reply->readAll());
    }
}

void DownloadModel::finished()
{
    QNetworkReply * reply = qobject_cast<QNetworkReply*> (sender());

    qDebug()<<Q_FUNC_INFO<<" finished" <<reply->errorString();

    if (mHashs.contains(reply))
    {
        if (reply->error()== QNetworkReply::OperationCanceledError){
            mHashs[reply]->file->remove();
            mHashs[reply]->file->close();
            mHashs[reply]->progress = 100;
            mHashs[reply]->status = "Canceled";

        }
        else {
            mHashs[reply]->file->close();
            mHashs[reply]->status = "Finished";
        }

        reply->deleteLater();
        mHashs.remove(reply);

    }
}

void DownloadModel::downloadProgress(qint64 bytes, qint64 total)
{

    float progress = float(bytes) / float(total) * 100.0f;
    QNetworkReply * reply = qobject_cast<QNetworkReply*> (sender());
    if (mHashs.contains(reply))
    {

        DownloadItem * item = mHashs.value(reply);
        int row = mItems.indexOf(item);

        mHashs[reply]->progress = progress;
        mHashs[reply]->bytes = bytes;
        mHashs[reply]->totalBytes = total;
        mHashs[reply]->speed = -1;


        emit dataChanged(index(row), index(row));



    }

}




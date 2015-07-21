#include "downloader.h"
#include <QDebug>
Downloader::Downloader(QObject *parent) : QObject(parent)
{

    mDest = QDir("C:/tmp/torrentdownloader");
    mDest.mkdir(mDest.path());


}

Downloader::~Downloader()
{

}

QNetworkReply* Downloader::add(const QUrl &url)
{
    QNetworkReply * reply  = NULL;
    QFileInfo info(url.path());

    QFile * file = new QFile(mDest.absoluteFilePath(info.baseName()));

    if ( file->open(QIODevice::WriteOnly|QIODevice::Append)) {

        reply = TorrentServerManager::i()->getFile(url.path());

        mHashs.insert(reply,file);

        connect(reply,SIGNAL(readyRead()),this,SLOT(write()));
        connect(reply,SIGNAL(finished()),this,SLOT(finished()));

    }

    else
        qDebug()<<Q_FUNC_INFO<<"cannot open file";


    return reply;
}

void Downloader::abort()
{
    foreach ( QNetworkReply * reply, mHashs.keys())
        reply->abort();
}

void Downloader::clear()
{
    mHashs.clear();
}

void Downloader::write()
{
    //qDebug()<<"write";
    QNetworkReply * reply = qobject_cast<QNetworkReply*> (sender());

    if (mHashs.contains(reply))
    {
        mHashs[reply]->write(reply->readAll());
    }
}

void Downloader::finished()
{
    //qDebug()<<"finished";
    QNetworkReply * reply = qobject_cast<QNetworkReply*> (sender());
    if (mHashs.contains(reply))
    {
        if (reply->error()== QNetworkReply::OperationCanceledError)
            mHashs[reply]->remove();

        mHashs[reply]->close();
        reply->deleteLater();
        mHashs.remove(reply);

    }

}


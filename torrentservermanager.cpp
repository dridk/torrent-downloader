#include "torrentservermanager.h"

TorrentServerManager * TorrentServerManager::mInstance = NULL;


TorrentServerManager *TorrentServerManager::i()
{
    if (NULL == mInstance )
        mInstance = new TorrentServerManager();

    return mInstance;
}

void TorrentServerManager::setServer(const QString &ip, int port)
{

    mUrl.setHost(ip);
    mUrl.setPort(port);

}

void TorrentServerManager::setUser(const QString &username, const QString &password)
{

    mUrl.setUserName(username);
    mUrl.setPassword(password);
}

QNetworkReply *TorrentServerManager::getRunList(int page)
{

    QUrlQuery query;
    query.addQueryItem("format","json");
    query.addQueryItem("offset",QString::number(page));

    mUrl.setPath("/rundb/api/v1/results/");
    mUrl.setScheme("http");
    mUrl.setQuery(query);

    QNetworkRequest request(mUrl);

    qDebug()<<mUrl;

    return get(request);


}

TorrentServerManager::TorrentServerManager(QObject *parent)
    :QNetworkAccessManager(parent)

{





}


#include "torrentservermanager.h"
#include <QWebView>
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

QNetworkReply *TorrentServerManager::getResultList(int page)
{

    QUrlQuery query;
    query.addQueryItem("format","json");
    query.addQueryItem("offset",QString::number(page));
    query.addQueryItem("order_by","-timeStamp");

    mUrl.setPath("/rundb/api/v1/results/");
    mUrl.setScheme("http");
    mUrl.setQuery(query);

    QNetworkRequest request(mUrl);

    qDebug()<<mUrl;

    return get(request);


}

QNetworkReply *TorrentServerManager::getResult(int resultId)
{
    mUrl.setQuery(QUrlQuery());
    mUrl.setPath(QString("/report/%1/").arg(resultId));
    mUrl.setScheme("http");

    QNetworkRequest request(mUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"text/html");

    qDebug()<<mUrl;

    return get(request);
}

QNetworkReply *TorrentServerManager::getFile(const QUrl& url)
{
//    mUrl.setQuery(QUrlQuery());
//    mUrl.setPath(path);

    qDebug()<<Q_FUNC_INFO<< url;


    return get(QNetworkRequest(url));


}

QUrl TorrentServerManager::fromPath(const QString &path)
{
    mUrl.setQuery(QUrlQuery());
    mUrl.setPath(path);
    return mUrl;
}

QUrl TorrentServerManager::resultUrl(int resultId) const
{
    QUrl url = mUrl;
    url.setQuery(QUrlQuery());
    url.setPath(QString("/report/%1/").arg(resultId));
    url.setScheme("http");

    return url;

}



TorrentServerManager::TorrentServerManager(QObject *parent)
    :QNetworkAccessManager(parent)
{





}


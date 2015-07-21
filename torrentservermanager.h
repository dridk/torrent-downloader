#ifndef TORRENTSERVERMANAGER_H
#define TORRENTSERVERMANAGER_H
#include <QtNetwork>
#include <QUrl>
class TorrentServerManager;

class TorrentServerManager : public QNetworkAccessManager
{
public :
    static TorrentServerManager * i();


     void setServer(const QString& ip, int port = 80);
     void setUser(const QString& username, const QString& password);


     QNetworkReply * getRunList(int page=0);




private:
    TorrentServerManager(QObject * parent = 0);
    static TorrentServerManager * mInstance;

    QUrl mUrl;


};

#endif // TORRENTSERVERMANAGER_H

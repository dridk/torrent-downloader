#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QUrl>
#include <QtCore>
#include <QtNetwork>
#include <QSignalMapper>
#include "torrentservermanager.h"

class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QObject *parent = 0);
    ~Downloader();

public slots:
    QNetworkReply * add(const QUrl& url);
    void abort();
    void clear();

protected slots:
    void write();
    void finished();

private:
    QHash<QNetworkReply*, QFile *> mHashs;
    QDir mDest;

};

#endif // DOWNLOADER_H

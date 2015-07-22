#ifndef DOWNLOADMODEL_H
#define DOWNLOADMODEL_H
#include <QAbstractListModel>
#include "torrentservermanager.h"
#include <QFile>
#include <QDir>
struct DownloadItem {
    QUrl url ;
    QString basename;
    float progress;
    int bytes;
    int totalBytes;
    float speed;
    QString remaining;
    QString status;
    QFile * file;
    QNetworkReply* reply;

};



class DownloadModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum {
        ProgressRole = Qt::UserRole,
        ByteRole,
        TotalRole,
        SpeedRole,
        StatusRole,
        RemainingRole
    };
    DownloadModel();
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    QNetworkReply * add(const QUrl& path);
public slots:
    void clear();
    void cancel(const QModelIndex& index);


protected slots:
    void write();
    void finished();
    void downloadProgress(qint64,qint64);


private:
    QList<DownloadItem*> mItems;
    QHash<QNetworkReply*, DownloadItem*> mHashs;
    QDir mDest;

};

#endif // DOWNLOADMODEL_H

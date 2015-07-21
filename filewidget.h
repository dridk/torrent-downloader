#ifndef FILEWIDGET_H
#define FILEWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <QSignalMapper>
#include "filemodel.h"
#include "fileitemdelegate.h"
#include "downloader.h"
class FileWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FileWidget(QWidget *parent = 0);

public slots:
    void load(int runId);
    void download();
    void downloadAll();
    void cancelDownload();

protected slots:
    void viewClicked(const QModelIndex& index);
    void mapReplyToItem(QNetworkReply * reply, const QModelIndex& index);

    void downloadProgress(qint64 bytes,qint64 total);

signals:
    void checkedCountChanged(int count);



private:

    QTableView * mView;
    FileModel * mModel;
    FileItemDelegate * mDelegate;
    Downloader * mDownloader;

    QMap<QNetworkReply*, QModelIndex > mProgressMap;



};

#endif // FILEWIDGET_H

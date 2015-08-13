#ifndef FILEWIDGET_H
#define FILEWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <QSignalMapper>
#include <QSortFilterProxyModel>
#include <QMenu>
#include "filemodel.h"
#include "downloaddelegate.h"
#include "downloader.h"
class FileWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FileWidget(QWidget *parent = 0);

    FileModel * model();
    QTableView * view();


    QList<FileItem> selectedItems();

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


protected:
    void setupFilterMenu();

private:

    QTableView * mView;
    FileModel * mModel;
    DownloadDelegate * mDelegate;
    QSortFilterProxyModel * mProxyModel;
    Downloader * mDownloader;
    QLineEdit * mFilterEdit;
    QMap<QNetworkReply*, QModelIndex > mProgressMap;



};

#endif // FILEWIDGET_H

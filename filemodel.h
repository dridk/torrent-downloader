#ifndef FILEMODEL_H
#define FILEMODEL_H

#include <QAbstractTableModel>
#include <QJsonDocument>
#include "torrentservermanager.h"
#include "fileitem.h"
class FileModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum {
        EXT_COL = 2,
        BARCODE_COL = 0,
        SAMPLE_COL = 1,
        PROGRESS_COL = 3
    };
    FileModel(QObject * parent =0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    Qt::ItemFlags flags(const QModelIndex &index) const;

public slots:
    void load(int resultId);


protected slots:
    void loadded();

signals:
    void finished();

private:
    QList<FileItem> mDatas;
    bool mPending;

};

#endif // FILEMODEL_H

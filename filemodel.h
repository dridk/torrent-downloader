#ifndef FILEMODEL_H
#define FILEMODEL_H

#include <QAbstractTableModel>
#include <QJsonDocument>
#include <QSignalMapper>
#include <QWebPage>
#include <QWebFrame>
#include <QWebElementCollection>
#include <QFileInfo>
#include "torrentservermanager.h"
#include "fileitem.h"
class FileModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum {
        EXT_COL = 0,
        BARCODE_COL = 1,
        SAMPLE_COL = 2,
    };
    FileModel(QObject * parent =0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent= QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &idx, const QVariant &value, int role = Qt::EditRole);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;
    void clearProgress();

    int count() const;
    int checkedCount() const;
    FileItem& item(int row) ;
    bool isLoading();
    QList<FileItem> checkedItems() const;

    static QIcon extIcon(const QString& ext);

public slots:
    void load(int resultId);
     void loadded();

protected:
    void parseBamTable();
    void parseVcfTable();
    void setLoading(bool active);

signals:
    void finished();
    void checkedCountChanged(int count);
    void loadingChanged(bool active);
private:
    QList<FileItem> mDatas;
    QList<QString> mExtensions;
    bool mLoading;
    QWebPage * mWebPage;



};

#endif // FILEMODEL_H

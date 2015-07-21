#ifndef RUNMODEL_H
#define RUNMODEL_H
#include <QList>
#include <QtNetwork>
#include <QJsonDocument>
#include "QAbstractTableModel"
#include "torrentservermanager.h"
#include "runitem.h"

class RunModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum {
        NAME_COL = 0,
        STATUS_COL = 1,
        DATE_COL = 2

    };
    RunModel(QObject * parent = 0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    const RunItem& item(const QModelIndex& index);



public slots:
    void load();
    void nextPage();
    void prevPage();

protected slots:
    void loadded();

signals:
    void finished();

private:
   QList<RunItem> mDatas;
   int mOffset;
   int mTotalCount;
   int mLimit;

};

#endif // RUNMODEL_H

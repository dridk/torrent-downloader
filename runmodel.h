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
        DATE_COL = 1

    };
    RunModel(QObject * parent = 0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

public slots:
    void load();
    void nextPage();
    void prevPage();

protected slots:
    void loadded();



private:
   QList<RunItem> mDatas;
   int mOffset;
   int mTotalCount;
   int mLimit;

};

#endif // RUNMODEL_H

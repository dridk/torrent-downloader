#ifndef FILEMODEL_H
#define FILEMODEL_H

#include <QAbstractTableModel>

class FileModel : public QAbstractTableModel
{
public:
    FileModel(QObject * parent =0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
};

#endif // FILEMODEL_H

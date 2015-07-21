#ifndef FILEWIDGET_H
#define FILEWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include "filemodel.h"
#include "fileitemdelegate.h"
class FileWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FileWidget(QWidget *parent = 0);

public slots:
    void load(int runId);


protected slots:
    void viewClicked(const QModelIndex& index);


private:

    QTableView * mView;
    FileModel * mModel;
    FileItemDelegate * mDelegate;


};

#endif // FILEWIDGET_H

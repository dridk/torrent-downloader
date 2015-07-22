#ifndef DOWNLOADWIDGET_H
#define DOWNLOADWIDGET_H

#include <QtWidgets>
#include <QListView>
#include "downloadmodel.h"
#include "downloaddelegate.h"
#include "torrentservermanager.h"

class DownloadWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DownloadWidget(QWidget *parent = 0);

    DownloadModel * model();
protected slots:
    void clear();
    void cancel();
    void open();
private:
    QListView * mView;
    DownloadModel * mModel;
    DownloadDelegate * mDelegate;

    QPushButton * mCancelButton;
    QPushButton * mClearButton;

    QPushButton * mOpenButton;
};

#endif // DOWNLOADWIDGET_H

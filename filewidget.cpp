#include "filewidget.h"

FileWidget::FileWidget(QWidget *parent) : QWidget(parent)
{

    mModel = new FileModel;
    mView  = new QTableView;
    mDownloader = new Downloader;
    mProxyModel = new QSortFilterProxyModel;
    mFilterEdit = new QLineEdit;

    mProxyModel->setSourceModel(mModel);
    mView->setModel(mProxyModel);

    mView->verticalHeader()->hide();
    mView->setEditTriggers(QAbstractItemView::CurrentChanged);
    mView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    mView->horizontalHeader()->setStretchLastSection(true);
    mView->setAlternatingRowColors(true);
    mView->setSelectionBehavior(QAbstractItemView::SelectRows);
    mView->setSelectionMode(QAbstractItemView::MultiSelection);

    mProxyModel->setFilterKeyColumn(0);



    QVBoxLayout * vLayout = new QVBoxLayout;
    vLayout->setContentsMargins(0,0,0,0);

    vLayout->addWidget(mFilterEdit);
    vLayout->addWidget(mView);

    setLayout(vLayout);
    setupFilterMenu();


    connect(mView,SIGNAL(clicked(QModelIndex)),this,SLOT(viewClicked(QModelIndex)));
    connect(mModel,SIGNAL(checkedCountChanged(int)),this,SIGNAL(checkedCountChanged(int)));

    connect(mFilterEdit,SIGNAL(textChanged(QString)),mProxyModel, SLOT(setFilterRegExp(QString)));

}

FileModel *FileWidget::model()
{
    return mModel;
}

QTableView *FileWidget::view()
{
    return mView;
}

QList<FileItem> FileWidget::selectedItems()
{
    QList<FileItem> items;

    foreach ( QModelIndex index, mView->selectionModel()->selectedRows()) {

        items.append(mModel->item(mProxyModel->mapToSource(index).row()));

    }

    return items;



}

void FileWidget::load(int runId)
{
    mModel->load(runId);


}

void FileWidget::download()
{


}

void FileWidget::downloadAll()
{

    //    for (int row = 0; row < mModel->count(); ++row)
    //    {
    //        if ( mModel->item(row).checked) {
    //            QNetworkReply * reply = mDownloader->add(mModel->item(row).link);

    //            QModelIndex progressIndex = mModel->index(row, FileModel::PROGRESS_COL);
    //            mapReplyToItem(reply, progressIndex);


    //        }


    //    }



}

void FileWidget::cancelDownload()
{

    //    mDownloader->abort();
    //    mProgressMap.clear();
    //    mModel->clearProgress();


}


void FileWidget::viewClicked(const QModelIndex &index)
{

}

void FileWidget::mapReplyToItem(QNetworkReply *reply, const QModelIndex &index)
{
    //    mProgressMap.insert(reply,index);
    //    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(downloadProgress(qint64,qint64)));
}

void FileWidget::downloadProgress(qint64 bytes, qint64 total)
{
    //    QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());

    //    if (mProgressMap.contains(reply))
    //    {
    //        QModelIndex pIndex = mProgressMap.value(reply);
    //        float percent = float(bytes) / float(total) * 100.0;
    //        mModel->setData(pIndex, percent);

    //        if ( percent == 100)
    //            mModel->setData(mModel->index(pIndex.row(),0), false, Qt::CheckStateRole);



    //    }


}

void FileWidget::setupFilterMenu()
{

    mFilterEdit->setPlaceholderText("Filter ...");
    QAction * filterAction = mFilterEdit->addAction(QIcon(":/icons/filter.png"),QLineEdit::TrailingPosition);


    QMenu * filterMenu = new QMenu(this);

    QActionGroup * actionGroup = new QActionGroup(this);
    actionGroup->addAction("By type")->setCheckable(true);
    actionGroup->addAction("By barcode")->setCheckable(true);
    actionGroup->addAction("By name")->setCheckable(true);

    actionGroup->setExclusive(true);

    actionGroup->actions().first()->setChecked(true);

    filterMenu->addActions(actionGroup->actions());

    filterAction->setCheckable(true);

    filterAction->setMenu(filterMenu);



}



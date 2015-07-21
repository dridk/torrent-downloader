#include "filewidget.h"

FileWidget::FileWidget(QWidget *parent) : QWidget(parent)
{

    mModel = new FileModel;
    mView  = new QTableView;
    mDelegate = new FileItemDelegate;
    mDownloader = new Downloader;

    mView->setModel(mModel);
    mView->setItemDelegate(mDelegate);
    mView->verticalHeader()->hide();
    mView->setEditTriggers(QAbstractItemView::CurrentChanged);
    mView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    mView->horizontalHeader()->setStretchLastSection(true);
    mView->setAlternatingRowColors(true);
    mView->setSelectionBehavior(QAbstractItemView::SelectRows);
    mView->setSelectionMode(QAbstractItemView::SingleSelection);



    QVBoxLayout * vLayout = new QVBoxLayout;
    vLayout->setContentsMargins(0,0,0,0);

    vLayout->addWidget(mView);

    setLayout(vLayout);


    connect(mView,SIGNAL(clicked(QModelIndex)),this,SLOT(viewClicked(QModelIndex)));


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

    for (int row = 0; row < mModel->count(); ++row)
    {
        if ( mModel->item(row).checked) {
            QNetworkReply * reply = mDownloader->add(mModel->item(row).link);

            QModelIndex progressIndex = mModel->index(row, FileModel::PROGRESS_COL);
            mapReplyToItem(reply, progressIndex);


        }


    }



}

void FileWidget::cancelDownload()
{

    mDownloader->abort();
    mProgressMap.clear();
    mModel->clearProgress();


}

void FileWidget::viewClicked(const QModelIndex &index)
{

}

void FileWidget::mapReplyToItem(QNetworkReply *reply, const QModelIndex &index)
{
    mProgressMap.insert(reply,index);
    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(downloadProgress(qint64,qint64)));
}

void FileWidget::downloadProgress(qint64 bytes, qint64 total)
{
    QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());

    if (mProgressMap.contains(reply))
    {
        QModelIndex pIndex = mProgressMap.value(reply);
        float percent = float(bytes) / float(total) * 100.0;
        mModel->setData(pIndex, percent);




    }


}



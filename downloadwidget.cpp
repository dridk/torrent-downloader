#include "downloadwidget.h"

DownloadWidget::DownloadWidget(QWidget *parent) : QWidget(parent)
{

    mView = new QListView;
    mModel = new DownloadModel;
    mDelegate = new DownloadDelegate;
    mCancelButton= new QPushButton(tr("Stop selection"));
    mOpenButton = new QPushButton(tr("Open Destination"));
    mClearButton = new QPushButton(tr("Clear finished"));
    mView->setModel(mModel);
    mView->setItemDelegate(mDelegate);

    QVBoxLayout * vLayout = new QVBoxLayout;
    QHBoxLayout * hLayout = new QHBoxLayout;

    hLayout->addWidget(mCancelButton);
    hLayout->addWidget(mClearButton);

    hLayout->addStretch();
    hLayout->addWidget(mOpenButton);


    vLayout->addWidget(mView);
    vLayout->addLayout(hLayout);

    setLayout(vLayout);


    resize(500,400);

    connect(mCancelButton,SIGNAL(clicked(bool)),this,SLOT(cancel()));
    connect(mClearButton,SIGNAL(clicked(bool)),this,SLOT(clear()));
    connect(mOpenButton,SIGNAL(clicked(bool)),this,SLOT(open()));

    setWindowTitle("Download list");
}

DownloadModel *DownloadWidget::model()
{
    return mModel;
}

void DownloadWidget::clear()
{
    mModel->clear();

}

void DownloadWidget::cancel()
{

    mModel->cancel(mView->currentIndex());

}

void DownloadWidget::open()
{

}


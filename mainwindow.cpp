#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QHBoxLayout>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mCancelButton = new QPushButton(tr("Cancel"));
    mDLButton = new QPushButton(tr("Download"));

    QHBoxLayout * hLayout = new QHBoxLayout;
    hLayout->addWidget(mCancelButton);
    hLayout->addStretch();
    hLayout->addWidget(mDLButton);

    mMainToolBar  = new QToolBar(this);
    mConnectBar   = new ConnectBar(this);

    QAction * ac = mMainToolBar->addAction("Download");

    connect(ac,SIGNAL(triggered(bool)),this,SLOT(showDownloadDialog()));

    addToolBar(mMainToolBar);
    addToolBar(mConnectBar);


    mRunWidget      = new RunWidget();
    mFileWidget     = new FileWidget();
    mDownloadWidget = new DownloadWidget();

    QVBoxLayout * vLayout = new QVBoxLayout;

    QSplitter * splitter = new QSplitter(Qt::Vertical);
    splitter->addWidget(mRunWidget);
    splitter->addWidget(mFileWidget);

    vLayout->addWidget(splitter);
    vLayout->addLayout(hLayout);

    QWidget * mainWidget = new QWidget();
    mainWidget->setLayout(vLayout);

    setCentralWidget(mainWidget);

    connect(mRunWidget,SIGNAL(clicked(int)),mFileWidget,SLOT(load(int)));
    connect(mDLButton, SIGNAL(clicked()),this, SLOT(startDownload()));
//    connect(mCancelButton,SIGNAL(clicked()),this,SLOT(cancelDownload()));
    connect(mConnectBar,SIGNAL(connectClicked()),this,SLOT(connectToServer()));
    connect(mFileWidget,SIGNAL(checkedCountChanged(int)),this,SLOT(setCheckedCount(int)));

    connectToServer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectToServer()
{
    TorrentServerManager::i()->setServer(mConnectBar->host());
    TorrentServerManager::i()->setUser(mConnectBar->user(),mConnectBar->pass());

    qDebug()<<"connect";

    mRunWidget->load();

}

void MainWindow::setCheckedCount(int count)
{

//    mDLAllButton->setText(QString("Download %1").arg(count));

}

void MainWindow::showDownloadDialog()
{

    mDownloadWidget->show();

//    mDownloadWidget->model()->add(QUrl("http://10.67.70.16/output/Home/Auto_user_OUE-96-20131128_ACTN1_AmpliSeq_122_134/download_links/IonXpress_020_R_2013_06_07_10_45_38_user_OUE-96-20131128_ACTN1_AmpliSeq_Auto_user_OUE-96-20131128_ACTN1_AmpliSeq_122.bam"));
//    mDownloadWidget->model()->add(QUrl("http://10.67.70.16/output/Home/Auto_user_OUE-96-20131128_ACTN1_AmpliSeq_122_134/download_links/IonXpress_020_R_2013_06_07_10_45_38_user_OUE-96-20131128_ACTN1_AmpliSeq_Auto_user_OUE-96-20131128_ACTN1_AmpliSeq_122.bam"));
//    mDownloadWidget->model()->add(QUrl("http://10.67.70.16/output/Home/Auto_user_OUE-96-20131128_ACTN1_AmpliSeq_122_134/download_links/IonXpress_020_R_2013_06_07_10_45_38_user_OUE-96-20131128_ACTN1_AmpliSeq_Auto_user_OUE-96-20131128_ACTN1_AmpliSeq_122.bam"));


}

void MainWindow::startDownload()
{


    foreach (FileItem item, mFileWidget->model()->checkedItems())
    {

            mDownloadWidget->model()->add(item.url);
    }




}



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
    mDLAllButton = new QPushButton(tr("Download All"));

    QHBoxLayout * hLayout = new QHBoxLayout;
    hLayout->addWidget(mCancelButton);
    hLayout->addStretch();
    hLayout->addWidget(mDLButton);
    hLayout->addWidget(mDLAllButton);



    mConnectBar = new ConnectBar(this);



    addToolBar(mConnectBar);


    mRunWidget = new RunWidget();
    mFileWidget = new FileWidget();


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
connect(mDLAllButton, SIGNAL(clicked()),mFileWidget, SLOT(downloadAll()));
connect(mDLButton, SIGNAL(clicked()),mFileWidget, SLOT(download()));
connect(mCancelButton,SIGNAL(clicked()),mFileWidget,SLOT(cancelDownload()));
connect(mConnectBar,SIGNAL(connectClicked()),this,SLOT(connectToServer()));
connect(mFileWidget,SIGNAL(checkedCountChanged(int)),this,SLOT(setCheckedCount(int)));
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

    mDLAllButton->setText(QString("Download %1").arg(count));

}


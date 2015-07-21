#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QHBoxLayout>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    TorrentServerManager::i()->setServer("10.67.70.16");
    TorrentServerManager::i()->setUser("ionadmin","ionadmin");



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

}

MainWindow::~MainWindow()
{
    delete ui;
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QHBoxLayout>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mRunWidget      = new RunWidget();
    mFileWidget     = new FileWidget();
    mDownloadWidget = new DownloadWidget();
    mClearButton    = new QPushButton(tr("Clear selection"));
    mDLButton       = new QPushButton(tr("Download"));
    mShowListButton = new QPushButton(tr("Show downloads"));
    mConnectBar     = new ConnectBar(this);


    QHBoxLayout * hLayout = new QHBoxLayout;
    hLayout->addWidget(mClearButton);
    hLayout->addStretch();
    hLayout->addWidget(mShowListButton);
    hLayout->addWidget(mDLButton);


    addToolBar(mConnectBar);




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
    connect(mClearButton,SIGNAL(clicked(bool)), mFileWidget->view(),SLOT(clearSelection()));
    connect(mShowListButton,SIGNAL(clicked(bool)),mDownloadWidget,SLOT(show()));
    connect(mConnectBar,SIGNAL(connectClicked()),this,SLOT(connectToServer()));
    connect(ui->actionAbout_Qt,SIGNAL(triggered(bool)),qApp,SLOT(aboutQt()));
    connect(ui->actionAbout,SIGNAL(triggered(bool)),this,SLOT(showAbout()));
    connect(mFileWidget->view()->selectionModel(),SIGNAL(selectionChanged(QItemSelection,QItemSelection)),this,SLOT(updateFileCount()));
    connect(mRunWidget->model(),SIGNAL(error(QString)),this,SLOT(showError(QString)));


    // connectToServer();
    updateFileCount();

    setWindowTitle(qAppName());

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
void MainWindow::startDownload()
{

    QList<FileItem> items = mFileWidget->selectedItems();

    if (items.isEmpty())
        return;

    DownloadDialog dialog(this);
    dialog.setPreview(items.first());

    if (dialog.exec() == QDialog::Accepted)
    {

        foreach (FileItem item, items)
        {

            mDownloadWidget->model()->setDestination(dialog.destination());
            mDownloadWidget->model()->add(item.url, dialog.fromSchema(item));

        }

    }

    mFileWidget->view()->clearSelection();

}

void MainWindow::showAbout()
{

    QMessageBox dialog(this);
    dialog.setText(qAppName() +" "+ qApp->applicationVersion()+"\nLabsquare 2015 - Sacha Schutz\nhttps://github.com/dridk/torrent-downloader");
    dialog.setWindowTitle("About");
    dialog.exec();


}

void MainWindow::showError(const QString &message)
{

    QMessageBox::warning(this,"error", message);

}

void MainWindow::updateFileCount()
{

    int count = mFileWidget->view()->selectionModel()->selectedRows().count();

    mDLButton->setEnabled(count > 0);

    mDLButton->setText(QString("Download (%1)").arg(count));

}




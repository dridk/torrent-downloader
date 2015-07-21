#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    TorrentServerManager::i()->setServer("10.67.70.16");
    TorrentServerManager::i()->setUser("ionadmin","ionadmin");



    mConnectBar = new ConnectBar(this);



    addToolBar(mConnectBar);


    mRunWidget = new RunWidget();

    setCentralWidget(mRunWidget);

}

MainWindow::~MainWindow()
{
    delete ui;
}

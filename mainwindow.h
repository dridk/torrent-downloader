#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QToolBar>
#include "torrentservermanager.h"
#include "connectbar.h"
#include "runwidget.h"
#include "filewidget.h"
#include "downloadwidget.h"
#include "downloaddialog.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void connectToServer();
    void setCheckedCount(int count);

    void showDownloadDialog();

    void startDownload();

private:
    Ui::MainWindow *ui;
    ConnectBar * mConnectBar;
    RunWidget * mRunWidget;
    FileWidget * mFileWidget;
    DownloadWidget * mDownloadWidget;

    QPushButton * mCancelButton;
    QPushButton * mDLButton;

    QToolBar * mMainToolBar;



};

#endif // MAINWINDOW_H

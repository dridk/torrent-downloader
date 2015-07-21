#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "torrentservermanager.h"
#include "connectbar.h"
#include "runwidget.h"
#include "filewidget.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ConnectBar * mConnectBar;
    RunWidget * mRunWidget;
    FileWidget * mFileWidget;

    QPushButton * mCancelButton;
    QPushButton * mDLButton;
    QPushButton * mDLAllButton;



};

#endif // MAINWINDOW_H

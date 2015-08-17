#include "mainwindow.h"
#include <QApplication>
#include "downloadwidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("TorrentDownloader");
    a.setApplicationVersion("alpha 0.2");
    a.setOrganizationDomain("labsquare.org");
    a.setOrganizationName("labsquare");

    MainWindow w;
    w.show();



    return a.exec();
}

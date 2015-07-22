#ifndef FILEITEM_H
#define FILEITEM_H
#include <QtCore>

class FileItem
{
public:
    FileItem();


    QString ext;
    QString barcode;
    QString sample;
    QUrl url;
    bool checked;
    float progress;

};

#endif // FILEITEM_H

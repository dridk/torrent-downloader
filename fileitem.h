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
    QUrl link;
    bool checked;
    float progress;

};

#endif // FILEITEM_H

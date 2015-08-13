#ifndef DOWNLOADDIALOG_H
#define DOWNLOADDIALOG_H

#include <QtWidgets>
#include <QFileSystemModel>
#include <QTreeView>
#include <QDialog>
#include "fileitem.h"

class DownloadDialog : public QDialog
{
    Q_OBJECT
public:
    DownloadDialog(QWidget * parent = 0);

    void setPreview(const FileItem& item);
     QString fromSchema( const FileItem& fileItem);
    QString schema();
    QString destination();

protected slots:
    void updatePreview();
private:

    QTreeView * mView;
    QFileSystemModel * mModel;
    QLineEdit * mShemaEdit;
    QLabel * mPreviewLabel;
    QDialogButtonBox * mBox;

    FileItem mPreviewItem;

};

#endif // DOWNLOADDIALOG_H

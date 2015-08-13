#include "downloaddialog.h"
#include <QFileInfo>
DownloadDialog::DownloadDialog(QWidget *parent)
    :QDialog(parent)
{
    mView  = new QTreeView;
    mModel = new QFileSystemModel;
    mShemaEdit = new QLineEdit;
    mPreviewLabel = new QLabel;
    mBox = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);

    mView->setModel(mModel);
    QVBoxLayout * vLayout = new QVBoxLayout;

    mShemaEdit->setText("{BARCODE}_{SAMPLE}.{EXT}");
    mShemaEdit->setPlaceholderText("type your template name ...");



    vLayout->addWidget(mView);
    vLayout->addWidget(mShemaEdit);
    vLayout->addWidget(mPreviewLabel);
    vLayout->addWidget(mBox);

    setLayout(vLayout);

    resize(400,600);

    mModel->setRootPath(QDir::currentPath());

    mView->hideColumn(1);
    mView->hideColumn(2);
    mView->hideColumn(3);
    mView->hideColumn(4);

    mModel->setFilter(QDir::AllDirs|QDir::NoDotAndDotDot);

//    connect(mView,SIGNAL(doubleClicked(QModelIndex)),mView,SLOT(setRootIndex(QModelIndex)));

    connect(mShemaEdit,SIGNAL(textChanged(QString)),this,SLOT(updatePreview()));

    connect(mBox,SIGNAL(accepted()),this,SLOT(accept()));
    connect(mBox,SIGNAL(rejected()),this,SLOT(reject()));

}

void DownloadDialog::setPreview(const FileItem &item)
{
    mPreviewItem = item;

    updatePreview();

}

QString DownloadDialog::fromSchema(const FileItem &fileItem)
{
    QString result = mShemaEdit->text();

    result.replace("{SAMPLE}", fileItem.sample);
    result.replace("{BARCODE}", fileItem.barcode);
    result.replace("{EXT}", fileItem.ext);

    QFileInfo info(fileItem.url.toString());
    result.replace("{BASENAME}", info.baseName());

    return result;
}



QString DownloadDialog::schema()
{
    return mShemaEdit->text();
}

QString DownloadDialog::destination()
{
   return mModel->filePath(mView->currentIndex());
}



void DownloadDialog::updatePreview()
{
    mPreviewLabel->setText(fromSchema(mPreviewItem));
}




#include "filemodel.h"
#include <QIcon>
#include <QFont>
#include <QWebView>
#include <QFontMetrics>
FileModel::FileModel(QObject *parent)
    :QAbstractTableModel(parent)
{
    mLoading=false;
    mWebPage = new QWebPage(this);

    mExtensions.append("bam");


    //    qDebug()<<extractUrl("<a class=\"btn\" href=\"/output/Home/Auto_user_GRO-66-2015-07-20-Ampliseq_exome_IC-Caro_133_216/download_links/IonXpress_024_R_2015_07_21_12_52_15_user_GRO-66-2015-07-20-Ampliseq_exome_IC-Caro_Auto_user_GRO-66-2015-07-20-Ampliseq_exome_IC-Caro_133.bam\">BAM</a>");

}

int FileModel::rowCount(const QModelIndex &parent) const
{
    return mDatas.count();
}

int FileModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant FileModel::data(const QModelIndex &index, int role) const
{

    if (!index.isValid())
        return QVariant();


    if (role == Qt::DisplayRole)
    {

        if (index.column() == EXT_COL)
            return mDatas.at(index.row()).ext;

        if (index.column() == BARCODE_COL)
            return mDatas.at(index.row()).barcode;

        if (index.column() == SAMPLE_COL)
            return mDatas.at(index.row()).sample;


    }

    if (role == Qt::DecorationRole)
    {
        if ( index.column() == BARCODE_COL)
            return QIcon(":/icons/barcode_2d.png");

        if (index.column() == SAMPLE_COL)
            return QIcon(":/icons/user_nude.png");

        if ( index.column() == EXT_COL)
            return QIcon(":/icons/mark_to_download.png");
    }


    if ( role == Qt::FontRole)
    {
        QFont font;
        if ( mDatas.at(index.row()).checked)
            font.setBold(true);
        return font;
    }

    return QVariant();

}

bool FileModel::setData(const QModelIndex &idx, const QVariant &value, int role)
{
    //    if (!idx.isValid())
    //        return false;
    //    if (role == Qt::CheckStateRole)
    //    {
    //        if ( idx.column() == 0){
    //            mDatas[idx.row()].checked = !mDatas[idx.row()].checked;
    //            emit dataChanged(index(idx.row(),0), index(idx.row(), columnCount()));
    //            emit checkedCountChanged(checkedCount());
    //        }

    //    }

    return true;
}

QVariant FileModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if ( orientation == Qt::Horizontal)
    {
        if ( role == Qt::DisplayRole)
        {
            if (section == EXT_COL)
                return QString(tr("Type"));
            if (section == BARCODE_COL)
                return QString(tr("Barcode"));
            if (section == SAMPLE_COL)
                return QString(tr("Sample"));
        }
    }
    return QVariant();
}

Qt::ItemFlags FileModel::flags(const QModelIndex &index) const
{

    return Qt::ItemIsSelectable|Qt::ItemIsEnabled;

}

void FileModel::clearProgress()
{
    beginResetModel();

    for (int i=0; i<count(); ++i){
        mDatas[i].progress = 0;
        mDatas[i].checked = false;
    }

    endResetModel();

}

int FileModel::count() const
{
    return mDatas.size();
}

int FileModel::checkedCount() const
{
    return checkedItems().count();

}

FileItem &FileModel::item(int row)
{
    return mDatas[row];
}

bool FileModel::isLoading()
{
    return mLoading;
}

QList<FileItem> FileModel::checkedItems() const
{
    QList<FileItem> list;

    foreach (FileItem item, mDatas)
    {
        if (item.checked)
            list.append(item);
    }

    return list;
}

QIcon FileModel::extIcon(const QString &ext)
{
    QPainter painter;
    QFontMetrics metrics(painter.font());

    int w = metrics.width(ext);
    int h = metrics.height();

    QPixmap pix(w+10, h+10);
    pix.fill(Qt::blue);
    painter.begin(&pix);
    painter.drawRect(0,0,w,h);

    painter.end();

    return QIcon(pix);


}

void FileModel::load(int resultId)
{
    if (isLoading())
        return;

    setLoading(true);
    mWebPage->mainFrame()->setUrl(TorrentServerManager::i()->resultUrl(resultId));
    mWebPage->networkAccessManager()->setCookieJar(TorrentServerManager::i()->cookieJar());


    connect(mWebPage,SIGNAL(loadFinished(bool)),this,SLOT(loadded()));

}

void FileModel::loadded()
{

    beginResetModel();
    mDatas.clear();

    parseBamTable();
    parseVcfTable();

    endResetModel();

    setLoading(false);


}

void FileModel::parseBamTable()
{
    //Get barcode table html
    QWebElement bamTable = mWebPage->mainFrame()->findFirstElement("table#barcodes tbody");

    foreach ( QWebElement tr, bamTable.findAll("tr"))
    {
        FileItem item;

        QWebElementCollection tdCol =  tr.findAll("td");

        item.barcode = tdCol.at(0).toPlainText();
        item.sample  = tdCol.at(1).toPlainText();
        item.checked = false;

        foreach (QWebElement href, tr.findAll("td span a.btn"))
        {
            QString path = href.attribute("href");
            item.url     = TorrentServerManager::i()->fromPath(path);
            item.ext     = href.toPlainText();
            mDatas.append(item);
        }
    }
}

void FileModel::parseVcfTable()
{
    //Find first which frame is the vcf one
    QWebFrame * vcfFrame = NULL;
    foreach (QWebFrame * subFrame, mWebPage->mainFrame()->childFrames())
    {

        if (subFrame->baseUrl().toString().contains("variantCaller_block.html"))
            vcfFrame = subFrame;
    }

    //If frame exist, start parsing
    if (vcfFrame)
    {
        foreach ( QWebElement tr, vcfFrame->findAllElements("table tr"))
        {
            FileItem item;
            QWebElementCollection td = tr.findAll("td");

            item.barcode = td.at(0).toPlainText();
            item.sample  = td.at(1).toPlainText();
            item.checked = false;

            QUrl linkUrl =  vcfFrame->baseUrl().adjusted(QUrl::RemoveFilename);


            foreach (QWebElement href, tr.findAll("td a.btn"))
            {

                item.url     = QUrl(linkUrl.toString() + href.attribute("href"));
                item.ext     = href.toPlainText();

                mDatas.append(item);
            }
        }
    }
}

void FileModel::setLoading(bool active)
{
    mLoading = active;
    emit loadingChanged(active);
}





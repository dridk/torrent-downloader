#include "filewidget.h"

FileWidget::FileWidget(QWidget *parent) : QWidget(parent)
{

    mModel = new FileModel;
    mView  = new QTableView;
    mDownloader = new Downloader;
    mProxyModel = new QSortFilterProxyModel;
    mFilterEdit = new QLineEdit;

    mProxyModel->setSourceModel(mModel);
    mView->setModel(mProxyModel);

    mView->verticalHeader()->hide();
    mView->setEditTriggers(QAbstractItemView::CurrentChanged);
    mView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    mView->horizontalHeader()->setStretchLastSection(true);
    mView->setAlternatingRowColors(true);
    mView->setSelectionBehavior(QAbstractItemView::SelectRows);
    mView->setSelectionMode(QAbstractItemView::MultiSelection);

    mProxyModel->setFilterKeyColumn(0);



    QVBoxLayout * vLayout = new QVBoxLayout;
    vLayout->setContentsMargins(0,0,0,0);

    vLayout->addWidget(mFilterEdit);
    vLayout->addWidget(mView);

    setLayout(vLayout);
    setupFilterMenu();


    connect(mModel,SIGNAL(checkedCountChanged(int)),this,SIGNAL(checkedCountChanged(int)));
    connect(mModel,SIGNAL(loadingChanged(bool)),this,SLOT(setDisabled(bool)));
    connect(mFilterEdit,SIGNAL(textChanged(QString)),mProxyModel, SLOT(setFilterRegExp(QString)));

}

FileModel *FileWidget::model()
{
    return mModel;
}

QTableView *FileWidget::view()
{
    return mView;
}

QList<FileItem> FileWidget::selectedItems()
{
    QList<FileItem> items;

    foreach ( QModelIndex index, mView->selectionModel()->selectedRows()) {

        items.append(mModel->item(mProxyModel->mapToSource(index).row()));

    }

    return items;



}

void FileWidget::load(int runId)
{
    mModel->load(runId);


}

void FileWidget::filterChanged(QAction *action)
{

    mProxyModel->setFilterKeyColumn(action->data().toInt());



}


void FileWidget::setupFilterMenu()
{

    mFilterEdit->setPlaceholderText("Filter ...");
    QAction * filterAction = mFilterEdit->addAction(QIcon(":/icons/filter.png"),QLineEdit::TrailingPosition);


    QMenu * filterMenu = new QMenu(this);

    QActionGroup * actionGroup = new QActionGroup(this);
    QAction *typeAction    = actionGroup->addAction("By type");
    QAction *barcodeAction = actionGroup->addAction("By barcode");
    QAction *nameAction    = actionGroup->addAction("By name");

    typeAction->setCheckable(true);
    barcodeAction->setCheckable(true);
    nameAction->setCheckable(true);

    typeAction->setData(0);
    barcodeAction->setData(1);
    nameAction->setData(2);

    actionGroup->setExclusive(true);
    actionGroup->actions().first()->setChecked(true);

    filterMenu->addActions(actionGroup->actions());
    filterAction->setCheckable(true);
    filterAction->setMenu(filterMenu);



    connect(actionGroup,SIGNAL(triggered(QAction*)),this,SLOT(filterChanged(QAction*)));

}



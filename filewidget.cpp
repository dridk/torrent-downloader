#include "filewidget.h"

FileWidget::FileWidget(QWidget *parent) : QWidget(parent)
{

    mModel = new FileModel;
    mView  = new QTableView;
    mDelegate = new FileItemDelegate;

    mView->setModel(mModel);
//    mView->setItemDelegate(mDelegate);
    mView->verticalHeader()->hide();
    mView->setEditTriggers(QAbstractItemView::CurrentChanged);
    //mView->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
   // mView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    mView->setAlternatingRowColors(true);
    mView->setSelectionBehavior(QAbstractItemView::SelectRows);
    mView->setSelectionMode(QAbstractItemView::SingleSelection);

    QVBoxLayout * vLayout = new QVBoxLayout;
    vLayout->setContentsMargins(0,0,0,0);

    vLayout->addWidget(mView);

    setLayout(vLayout);


    connect(mView,SIGNAL(clicked(QModelIndex)),this,SLOT(viewClicked(QModelIndex)));

}

void FileWidget::load(int runId)
{
    mModel->load(runId);


}

void FileWidget::viewClicked(const QModelIndex &index)
{

}



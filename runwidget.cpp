#include "runwidget.h"

RunWidget::RunWidget(QWidget *parent) : QWidget(parent)
{

    mFilter = new QLineEdit();
    mPrevButton = new QToolButton();
    mNextButton = new QToolButton();
    mView =new QTableView();
    mModel = new RunModel();

    mView->setModel(mModel);

    mView->verticalHeader()->hide();
    mView->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    mView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    mView->setAlternatingRowColors(true);
    mView->setSelectionBehavior(QAbstractItemView::SelectRows);
    mView->setSelectionMode(QAbstractItemView::SingleSelection);

    mPrevButton->setIcon(QIcon(":/icons/resultset_previous.png"));
    mNextButton->setIcon(QIcon(":/icons/resultset_next.png"));


    mFilter->setPlaceholderText("Filter...");
    QHBoxLayout * hLayout = new QHBoxLayout;
    hLayout->addWidget(mPrevButton);
    hLayout->addWidget(mNextButton);
    hLayout->addWidget(mFilter);
    // hLayout->addStretch();

    hLayout->setContentsMargins(0,0,0,0);

    QVBoxLayout * vLayout = new QVBoxLayout;
    vLayout->addLayout(hLayout);
    vLayout->addWidget(mView);
    vLayout->setContentsMargins(0,0,0,0);
    vLayout->setSpacing(0);

    setLayout(vLayout);


    connect(mPrevButton,SIGNAL(clicked(bool)),mModel,SLOT(prevPage()));
    connect(mNextButton,SIGNAL(clicked(bool)),mModel,SLOT(nextPage()));
    connect(mModel,SIGNAL(loadingChanged(bool)),this,SLOT(setDisabled(bool)));
    connect(mView,SIGNAL(clicked(QModelIndex)),this,SLOT(viewClicked(QModelIndex)));
    connect(mFilter,SIGNAL(returnPressed()),this,SLOT(load()));


}

RunModel *RunWidget::model()
{
 return mModel;
}

void RunWidget::load()
{

    mModel->load(mFilter->text());
}



void RunWidget::viewClicked(const QModelIndex &index)
{

    int runId = mModel->item(index).id;
    emit clicked(runId);

}


